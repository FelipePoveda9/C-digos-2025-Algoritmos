#include <iostream>
#include <string>
using namespace std;

class ClaseBorrador {
private:
    int atributoEntero; // Almacena un número entero
    string atributoCadena; // Almacena una cadena de texto

public:
    // ===================== CONSTRUCTORES =====================
    
    // Constructor por defecto: inicializa los atributos con valores predeterminados
    ClaseBorrador();
    
    // Constructor con parámetros: permite inicializar la clase con valores específicos
    ClaseBorrador(int entero, string cadena);

    // Destructor: libera recursos si es necesario cuando el objeto se destruye
    ~ClaseBorrador();

    // ===================== MÉTODOS GETTERS =====================
    
    // Devuelve el valor del atributo entero
    int getAtributoEntero() const;
    
    // Devuelve el valor del atributo cadena
    string getAtributoCadena() const;

    // ===================== MÉTODOS SETTERS =====================
    
    // Establece un nuevo valor para el atributo entero
    void setAtributoEntero(int valor);
    
    // Establece un nuevo valor para el atributo cadena
    void setAtributoCadena(string valor);

    // ===================== MÉTODOS ADICIONALES =====================
    
    // Muestra la información actual de los atributos en la consola
    void mostrarInformacion() const;
    
    // Retorna una representación en cadena de los atributos del objeto
    string toString() const;
};
