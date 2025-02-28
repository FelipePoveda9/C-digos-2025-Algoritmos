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

// ===================== CLASE Prestamo =====================
class Prestamo {
private:
    int usuario;
    int libro;
    int genero;
public:
    Prestamo() : usuario(-1), libro(-1), genero(-1) {}
    Prestamo(int u, int l, int g) : usuario(u), libro(l), genero(g) {}
    
    int getUsuario() const { return usuario; }
    int getLibro() const { return libro; }
    int getGenero() const { return genero; }
    
    string to_string() const {
        return std::to_string(usuario) + ", " + std::to_string(libro) + ", " + std::to_string(genero);
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Prestamo& p) {
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

// ===================== CLASE Biblioteca =====================
class Biblioteca {
private:
    ListaEnlazada<Prestamo> prestamos;
    int* prestamosPorLibro;
    int* prestamosPorGenero;
    int nu, nl, ng, np;

public:
    Biblioteca(int u = 100, int l = 100, int g = 100, int p = 1000) : nu(u), nl(l), ng(g), np(p) {
        prestamosPorLibro = crear_array(nl);
        prestamosPorGenero = crear_array(ng);
    }

    ~Biblioteca() {
        destruir_array(prestamosPorLibro);
        destruir_array(prestamosPorGenero);
    }

    void init_lista() {
        for (int i = 0; i < np; i++) {
            int u = rand() % nu;
            int l = rand() % nl;
            int g = rand() % ng;
            prestamos.insertar(Prestamo(u, l, g));
        }
        cout << "Se han generado " << prestamos.get_size() << " préstamos." << endl;
    }

    void calcular_array() {
        Nodo<Prestamo>* ptr = prestamos.get(0);
        while (ptr != nullptr) {
            int libroIndex = ptr->getValor().getLibro();
            int generoIndex = ptr->getValor().getGenero();
            if (libroIndex < nl && generoIndex < ng) {
                prestamosPorLibro[libroIndex]++;
                prestamosPorGenero[generoIndex]++;
            }
            ptr = ptr->getSiguiente();
        }
        cout << "Préstamos por libro: " << endl;
        print_array(prestamosPorLibro, nl);
        cout << "Préstamos por género: " << endl;
        print_array(prestamosPorGenero, ng);
    }
};

// ===================== FUNCIÓN PRINCIPAL =====================
int main() {
    srand(time(0));  
    int u = 10, l = 10, g = 10, p = 100;
    Biblioteca bib(u, l, g, p);
    bib.init_lista();
    bib.calcular_array();
    return 0;
}
