#include <iostream>
#include <ctime>  
#include <string>

using namespace std;

// ===================== FUNCIÓN PARA CREAR UN ARRAY DINÁMICO =====================
int* crear_array(int size) {
    int* arr = new int[size](); // Se inicializa en 0
    return arr;
}

// ===================== FUNCIÓN PARA DESTRUIR UN ARRAY =====================
void destruir_array(int* arr) {
    delete[] arr;
}

// ===================== FUNCIÓN PARA IMPRIMIR UN ARRAY =====================
void print_array(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// ===================== CLASE NumRutas =====================
class NumRutas {
private:
    int codigo_Pasajero;
    int codigo_Vehiculo;
    int codigo_Ruta;
public:
    NumRutas() : codigo_Pasajero(-1), codigo_Vehiculo(-1), codigo_Ruta(-1) {}
    NumRutas(int pa, int v, int h) : codigo_Pasajero(pa), codigo_Vehiculo(v), codigo_Ruta(h) {}
    
    int getUsuario() const { return codigo_Pasajero; }
    int getVehiculo() const { return codigo_Vehiculo; }
    int getRuta() const { return codigo_Ruta; }
    
    string to_string() const {
        return std::to_string(codigo_Pasajero) + ", " + std::to_string(codigo_Vehiculo) + ", " + std::to_string(codigo_Ruta);
    }
    
    friend std::ostream& operator<<(std::ostream& os, const NumRutas& p) {
        return os << p.to_string();
    }
};

// ===================== CLASE Nodo =====================
template <typename T>
class Nodo {
private:
    T valor;
    Nodo<T>* siguiente;
public:
    Nodo(T _valor) : valor(_valor), siguiente(nullptr) {}
    void setSiguiente(Nodo<T>* _siguiente) { this->siguiente = _siguiente; }
    T getValor() const { return valor; }
    Nodo<T>* getSiguiente() const { return siguiente; }
};

// ===================== CLASE ListaEnlazada =====================
template <typename T>
class ListaEnlazada {
private:
    Nodo<T>* cabeza;
    int size;
public:
    ListaEnlazada() : cabeza(nullptr), size(0) {}
    ~ListaEnlazada() {
        Nodo<T>* actual = cabeza;
        while(actual != nullptr) {
            Nodo<T>* temp = actual->getSiguiente();
            delete actual;
            actual = temp;
        }
    }
    void insertar(const T& _valor) {
        Nodo<T>* nuevoNodo = new Nodo<T>(_valor);
        if(cabeza == nullptr) {
            cabeza = nuevoNodo;
        } else {
            Nodo<T>* actual = cabeza;
            while (actual->getSiguiente()) {
                actual = actual->getSiguiente();
            }
            actual->setSiguiente(nuevoNodo);
        }
        size++;
    }
    int get_size() const { return size; }
    Nodo<T>* get(int i) const {
        if (i >= 0 && i < size) {
            int j = 0;
            Nodo<T>* actual = cabeza;
            while (j < i) {
                actual = actual->getSiguiente();
                j++;
            }
            return actual;
        }
        return nullptr;
    }
};

// ===================== CLASE Transcol =====================
class Transcol {
private:
    ListaEnlazada<NumRutas> NumRutas_;
    int* viajesPorVehiculo;
    int* viajesPorRuta;
    int cp, cv, cr, nr;

public:
    Transcol(int pa = 100, int v = 100, int h = 100, int pas = 1000) : cp(pa), cv(v), cr(h), nr(pas) {
        viajesPorVehiculo = crear_array(cv);
        viajesPorRuta = crear_array(cr);
    }

    ~Transcol() {
        destruir_array(viajesPorVehiculo);
        destruir_array(viajesPorRuta);
    }

    void init_lista() {
        for (int i = 0; i < nr; i++) {
            int pa = rand() % cp;
            int v = rand() % cv;
            int h = rand() % cr;
            NumRutas_.insertar(NumRutas(pa, v, h));
        }
        cout << "Se han generado " << NumRutas_.get_size() << " rutas." << endl;
    }

    void calcular_array() {
        Nodo<NumRutas>* ptr = NumRutas_.get(0);
        for (int i = 0; i < nr; i++) {
            int vehiculoIndex = ptr->getValor().getVehiculo();
            int rutaIndex = ptr->getValor().getRuta();
            if (vehiculoIndex < cv && rutaIndex < cr) {
                viajesPorVehiculo[vehiculoIndex]++;
                viajesPorRuta[rutaIndex]++;
            }
            ptr = ptr->getSiguiente();
        }
        cout << "Viajes por vehículo: " << endl;
        print_array(viajesPorVehiculo, cv);
        cout << "Viajes por ruta: " << endl;
        print_array(viajesPorRuta, cr);
    }
};

// ===================== FUNCIÓN PRINCIPAL =====================
int main() {
    srand(time(0));  
    int pa = 10, v = 10, h = 10, pas = 100;
    Transcol sistema(pa, v, h, pas);
    sistema.init_lista();
    sistema.calcular_array();
    return 0;
}
