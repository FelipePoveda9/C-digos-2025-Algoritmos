#include <iostream>
#include <ctime>  
#include <string>

using namespace std;

// Clase Prestamo
class Prestamo {
private:
    int usuario;
    int libro;
    int genero;
public:
    Prestamo() : usuario(-1), libro(-1), genero(-1) {}
    Prestamo(int u, int l, int g) : usuario(u), libro(l), genero(g) {}

    // Getters
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

// Clase nodo con plantilla
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

// Clase Biblioteca
class Biblioteca {
private:
    ListaEnlazada<Prestamo> prestamos;
    int nu; // Número de usuarios
    int nl; // Número de libros
    int ng; // Número de géneros
    int np; // Número de préstamos
    int* librosPrestados;

public:
    Biblioteca(int u = 100, int l = 100, int g = 100, int p = 1000) : nu(u), nl(l), ng(g), np(p) {
        librosPrestados = new int[nl](); // Crear vector dinámico de libros prestados e inicializar en 0
    }

    ~Biblioteca() {
        delete[] librosPrestados; // Liberar memoria del vector dinámico
    }

    void init_lista() {
        for (int i = 0; i < np; i++) {
            int u = rand() % nu;
            int l = rand() % nl;
            int g = rand() % ng;
            Prestamo t(u, l, g);
            prestamos.insertar(t);
        }
        cout << "Se han generado " << prestamos.get_size() << " préstamos." << endl;
        prestamos.mostrar();
        llenar_arreglo();  // Llenar el vector después de generar los préstamos
    }

    void llenar_arreglo() {
        Nodo<Prestamo>* ptr = prestamos.get(0);
        while (ptr != nullptr) {
            int libroIndex = ptr->getValor().getLibro();  // Obtiene el índice del libro
            if (libroIndex >= 0 && libroIndex < nl) {     // Verifica que el índice esté en el rango correcto
                librosPrestados[libroIndex]++;            // Incrementa el contador de préstamos por libro
            }
            ptr = ptr->getSiguiente();
        }

        cout << "\nArreglo de libros prestados: " << endl;
        for (int i = 0; i < nl; i++) {
            cout << "{"<< librosPrestados[i] << "},";
        }
        cout << endl;
    }
};

// Función principal
int main() {
    srand(time(0));  // Inicialización del generador de números aleatorios con el tiempo actual

    int u = 10;  // Número de usuarios
    int l = 10;  // Número de libros
    int g = 10;  // Número de géneros
    int p = 100; // Número de préstamos

    Biblioteca bib = Biblioteca(u, l, g, p);
    bib.init_lista();

    return 0;
}
