#include <iostream>
#include <ctime>  
#include <string>

using namespace std;

// Función para crear una matriz dinámica
int** crear_mat(int f, int c) {
    int** m = new int*[f];
    for (int i = 0; i < f; i++) {
        m[i] = new int[c];
        for (int j = 0; j < c; j++) {
            m[i][j] = 0;
        }
    }
    return m;
}

// Función para destruir la matriz
void destruir_mat(int** m, int f) {
    for (int i = 0; i < f; i++) {
        delete[] m[i];
    }
    delete[] m;
}

// Función para imprimir la matriz
void print_mat(int** m, int f, int c) {
    for (int i = 0; i < f; i++) {
        for (int j = 0; j < c; j++) {
            cout << m[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

// Clase NumRutas
class NumRutas {
private:
    int codigo_Pasajero;
    int codigo_Vehiculo;
    int codigo_Ruta;
public:
    NumRutas() {
        codigo_Pasajero=-1; 
        codigo_Vehiculo=-1;
        codigo_Ruta=-1;
    }
    NumRutas(int pa, int v, int h){
        codigo_Pasajero=pa;
        codigo_Vehiculo=v;
        codigo_Ruta=h;
    }
    
    //Setters y Getters
    int getUsuario() const { 
        return codigo_Pasajero; 
    }
    void setUsuario(int pa) { 
        codigo_Pasajero = pa; 
    }
    int getLibro() const { 
        return codigo_Vehiculo; 
    }
    void setLibro(int v) { 
        codigo_Vehiculo = v; 
    }

    int getGenero() const { 
        return codigo_Ruta; 
    }
    void setGenero(int h) { 
        codigo_Ruta = h; 
    }

    NumRutas& operator=(const NumRutas& f) {
        codigo_Pasajero = f.codigo_Pasajero;
        codigo_Vehiculo = f.codigo_Vehiculo;
        codigo_Ruta = f.codigo_Ruta;
        return *this;
    }

    string to_string() const {
        return std::to_string(codigo_Pasajero) + ", " + std::to_string(codigo_Vehiculo) + ", " + std::to_string(codigo_Ruta);
    }
    
    friend std::ostream& operator<<(std::ostream& os, const NumRutas& p) {
        return os << p.to_string();
    }
};
// Clase nodo con plantilla
template <typename T>
class Nodo {
private:
    T valor;
    Nodo<T>* siguiente;
public:
    Nodo(T _valor) : valor(_valor), siguiente(nullptr) {}

    void setSiguiente(Nodo<T>* _siguiente) { this->siguiente = _siguiente; }
    void setValor(T _valor) { this->valor = _valor; }
    T getValor() const { return valor; }
    Nodo<T>* getSiguiente() const { return siguiente; }
};

// Clase lista enlazada con plantilla
template <typename T>
class ListaEnlazada {
private:
    Nodo<T>* cabeza;
    int size;
public:
    ListaEnlazada() : cabeza(nullptr), size(0) {}

    ~ListaEnlazada() {
        Nodo<T>* actual = cabeza;
        Nodo<T>* siguiente = nullptr;
        while(actual != nullptr) {
            siguiente = actual->getSiguiente();
            delete actual;
            actual = siguiente;
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

    void insertarEnPosicion(int posicion, const T& _valor) {
        Nodo<T>* nuevoNodo = new Nodo<T>(_valor);

        if (posicion == 0) {
            nuevoNodo->setSiguiente(cabeza);
            cabeza = nuevoNodo;
            return;
        }

        Nodo<T>* actual = cabeza;
        int contador = 0;
        while (actual != nullptr && contador < (posicion - 1)) {
            actual = actual->getSiguiente();
            contador++;
        }

        if (actual == nullptr) {
            std::cout << "Posición inválida" << std::endl;
            delete nuevoNodo;
            return;
        }

        nuevoNodo->setSiguiente(actual->getSiguiente());
        actual->setSiguiente(nuevoNodo);
    }

    bool eliminar(const T& _valor) {
        Nodo<T>* actual = cabeza;
        Nodo<T>* anterior = nullptr;
        while (actual) {
            if (actual->getValor() == _valor) {
                if (anterior) {
                    anterior->setSiguiente(actual->getSiguiente());
                } else {
                    cabeza = actual->getSiguiente();
                }
                delete actual;
                return true;
            }
            anterior = actual;
            actual = actual->getSiguiente();
        }
        return false;
    }

    Nodo<T>* buscarPorValor(const T& _valor) const {
        Nodo<T>* actual = cabeza;
        while (actual != nullptr) {
            if (actual->getValor() == _valor) {
                return actual;
            }
            actual = actual->getSiguiente();
        }
        return nullptr;
    }

    int get_size() const { return size; }

    void mostrar() const {
        Nodo<T>* actual = cabeza;
        cout << "Lista de valores: " << endl;
        while (actual != nullptr) {
            cout << actual->getValor() << endl;
            actual = actual->getSiguiente();
        }
        cout << "nullptr" << endl;
    }

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

// Clase Transcol
class Transcol {
private:
    ListaEnlazada<NumRutas> NumRutas_;
    int** matriz;
    int cp; // Codigo pasajeros
    int cv; // Codigo vehiculos
    int cr; // Codigo ruta
    int nr; // Número de rutas
    //pas = Total de numrutas
public:
    Transcol(int pa = 100, int v = 100, int h = 100, int pas = 1000) : cp(pa), cv(v), cr(h), nr(pas) {
        matriz = crear_mat(cv, cr);
    }

    ~Transcol() { destruir_mat(matriz, cv); }

    void init_lista() {
        NumRutas* t;
        int pa, v, h;
        for (int i = 0; i < nr; i++) {
            pa = rand() % cp;
            v = rand() % cv;
            h = rand() % cr;
            t = new NumRutas(pa, v, h);
            NumRutas_.insertar(*t);
        }
        cout << "Se han generado " << NumRutas_.get_size() << " rutas." << endl;
    }

    void calcular_matriz() {
        Nodo<NumRutas>* ptr = NumRutas_.get(0);
        for (int i = 0; i < nr; i++) {
            matriz[ptr->getValor().getLibro()][ptr->getValor().getGenero()]++;
            ptr = ptr->getSiguiente();
        }
        cout << "Matriz de vehículos por ruta: " << endl;
        print_mat(matriz, cv, cr);
    }

    void ruta_mas_popular() {
        int max_ruta = 0;
        int codigo_Ruta = -1;
        for (int i = 0; i < cr; i++) {
            int total = 0;
            for (int j = 0; j < cv; j++) {
                total += matriz[j][i];
            }
            if (total > max_ruta) {
                max_ruta = total;
                codigo_Ruta = i;
            }
        }
        cout << "Ruta más popular: " << codigo_Ruta << " con " << max_ruta << " rutas." << endl;
    }

    void ruta_menos_popular() {
        int min_ruta = 1000;
        int codigo_Ruta = -1;
        for (int i = 0; i < cr; i++) {
            int total = 0;
            for (int j = 0; j < cv; j++) {
                total += matriz[j][i];
            }
            if (total < min_ruta) {
                min_ruta = total;
                codigo_Ruta = i;
            }
        }
        cout << "Ruta menos popular: " << codigo_Ruta << " con " << min_ruta << " rutas." << endl;
    }

    void vehiculo_mas_viajes() {
        int max_viajes = 0;
        int codigo_Vehiculo = -1;
        for (int i = 0; i < cv; i++) {
            int total = 0;
            for (int j = 0; j < cr; j++) {
                total += matriz[i][j];
            }
            if (total > max_viajes) {
                max_viajes = total;
                codigo_Vehiculo = i;
            }
        }
        cout << "Vehículo con más viajes: " << codigo_Vehiculo << " con " << max_viajes << " viajes." << endl;
    }

    void vehiculo_menos_viajes() {
        int min_viajes = 1000;
        int codigo_Vehiculo = -1;
        for (int i = 0; i < cv; i++) {
            int total = 0;
            for (int j = 0; j < cr; j++) {
                total += matriz[i][j];
            }
            if (total < min_viajes) {
                min_viajes = total;
                codigo_Vehiculo = i;
            }
        }
        cout << "Vehículo con menos viajes: " << codigo_Vehiculo << " con " << min_viajes << " viajes." << endl;
    }

    void promedio_viajes_vehiculo() {
        for (int i = 0; i < cr; i++) {
            int total = 0;
            for (int j = 0; j < cv; j++) {
                total += matriz[j][i];
            }
            double promedio = total / (double)cv;
            cout << "Promedio de viajes por vehículo " << i << ": " << promedio << endl;
        }
    }
};

int main() {
    srand(time(0));  // Inicialización del generador de números aleatorios con el tiempo actual
    int pa = 10;
    int v = 10;
    int h = 10;
    int pas = 100;
    Transcol bib = Transcol(pa, v, h, pas);
    bib.init_lista();
    bib.calcular_matriz();

    bib.ruta_mas_popular();
    bib.ruta_menos_popular();
    bib.vehiculo_mas_viajes();
    bib.vehiculo_menos_viajes();
    bib.promedio_viajes_vehiculo();
    
    return 0;
}
