#include <iostream>
#include <string>
using namespace std;

class ClaseBorrador {
private:
    int atributoEntero;
    string atributoCadena;

public:
    // Constructor por defecto
    ClaseBorrador();
    
    // Constructor con parámetros
    ClaseBorrador(int entero, string cadena);

    // Destructor
    ~ClaseBorrador();

    // Getters
    int getAtributoEntero() const;
    string getAtributoCadena() const;

    // Setters
    void setAtributoEntero(int valor);
    void setAtributoCadena(string valor);

    // Métodos adicionales
    void mostrarInformacion() const;
    string toString() const;
};
