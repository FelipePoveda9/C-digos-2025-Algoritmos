#include <iostream>
#include <cstdlib> // Para rand()
#include <ctime>   // Para time()

using namespace std;

// ===================== FUNCIÓN PARA CREAR UNA MATRIZ DINÁMICA =====================
int** crear_matriz(int filas, int columnas) {
    int** matriz = new int*[filas]; // Crea un arreglo de punteros
    for (int i = 0; i < filas; i++) {
        matriz[i] = new int[columnas]; // Crea cada fila como un arreglo de enteros
    }
    return matriz;
}

// ===================== FUNCIÓN PARA LLENAR UNA MATRIZ CON VALORES ALEATORIOS =====================
void llenar_matriz(int** matriz, int filas, int columnas) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            matriz[i][j] = rand() % 10; // Genera números aleatorios entre 0 y 9
        }
    }
}

// ===================== FUNCIÓN PARA IMPRIMIR UNA MATRIZ =====================
void imprimir_matriz(int** matriz, int filas, int columnas) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            cout << matriz[i][j] << "\t"; // Imprime cada número con tabulación
        }
        cout << endl;
    }
}

// ===================== FUNCIÓN PARA SUMAR DOS MATRICES =====================
int** sumar_matrices(int** A, int** B, int filas, int columnas) {
    int** resultado = crear_matriz(filas, columnas);
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            resultado[i][j] = A[i][j] + B[i][j]; // Suma elemento por elemento
        }
    }
    return resultado;
}

// ===================== FUNCIÓN PARA RESTAR DOS MATRICES =====================
int** restar_matrices(int** A, int** B, int filas, int columnas) {
    int** resultado = crear_matriz(filas, columnas);
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            resultado[i][j] = A[i][j] - B[i][j]; // Resta elemento por elemento
        }
    }
    return resultado;
}

// ===================== FUNCIÓN PARA MULTIPLICAR DOS MATRICES =====================
int** multiplicar_matrices(int** A, int** B, int filasA, int columnasA, int columnasB) {
    int** resultado = crear_matriz(filasA, columnasB);
    
    // Inicializar matriz resultado en 0
    for (int i = 0; i < filasA; i++) {
        for (int j = 0; j < columnasB; j++) {
            resultado[i][j] = 0;
            for (int k = 0; k < columnasA; k++) {
                resultado[i][j] += A[i][k] * B[k][j]; // Producto escalar de la fila de A con la columna de B
            }
        }
    }
    return resultado;
}

// ===================== FUNCIÓN PARA LIBERAR MEMORIA DE UNA MATRIZ =====================
void destruir_matriz(int** matriz, int filas) {
    for (int i = 0; i < filas; i++) {
        delete[] matriz[i]; // Elimina cada fila
    }
    delete[] matriz; // Elimina el array de punteros
}

// ===================== FUNCIÓN PRINCIPAL =====================
int main() {
    srand(time(0)); // Inicializar generador de números aleatorios

    int filas = 3, columnas = 3; // Definir tamaño de las matrices

    // Crear y llenar matrices A y B
    int** A = crear_matriz(filas, columnas);
    int** B = crear_matriz(filas, columnas);
    llenar_matriz(A, filas, columnas);
    llenar_matriz(B, filas, columnas);

    // Imprimir matrices originales
    cout << "Matriz A:" << endl;
    imprimir_matriz(A, filas, columnas);
    
    cout << "\nMatriz B:" << endl;
    imprimir_matriz(B, filas, columnas);

    // Suma de matrices
    int** suma = sumar_matrices(A, B, filas, columnas);
    cout << "\nSuma de A + B:" << endl;
    imprimir_matriz(suma, filas, columnas);

    // Resta de matrices
    int** resta = restar_matrices(A, B, filas, columnas);
    cout << "\nResta de A - B:" << endl;
    imprimir_matriz(resta, filas, columnas);

    // Multiplicación de matrices (solo si tienen dimensiones compatibles)
    int** multiplicacion = multiplicar_matrices(A, B, filas, columnas, columnas);
    cout << "\nMultiplicación de A * B:" << endl;
    imprimir_matriz(multiplicacion, filas, columnas);

    // Liberar memoria de todas las matrices creadas
    destruir_matriz(A, filas);
    destruir_matriz(B, filas);
    destruir_matriz(suma, filas);
    destruir_matriz(resta, filas);
    destruir_matriz(multiplicacion, filas);

    return 0;
}
