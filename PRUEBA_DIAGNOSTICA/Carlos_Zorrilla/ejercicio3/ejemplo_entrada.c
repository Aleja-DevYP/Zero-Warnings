#include <stdio.h>
#include <stdlib.h>

/* Programa de prueba en C para analisis lexico y traduccion */
// Funcion que calcula el factorial
int calcular_factorial(int n) {
    if (n <= 1) {
        return 1;
    } else {
        return n * calcular_factorial(n - 1);
    }
}

// Estructura de prueba
struct Persona {
    char nombre[50];
    int edad;
    float salario;
};

int main() {
    int contador = 0;
    const int limite = 5;
    double suma = 0.0;
    
    printf("Iniciando bucle de prueba...\n");
    
    for (int i = 0; i < limite; i++) {
        if (i % 2 == 0) {
            contador++;
        } else {
            continue;
        }
    }
    
    while (contador > 0) {
        suma += contador;
        contador--;
        if (suma > 10.0) {
            break;
        }
    }
    
    switch (limite) {
        case 5:
            printf("Limite es 5\n");
            break;
        default:
            printf("Otro valor\n");
            break;
    }
    
    void* puntero = NULL;
    unsigned int positivo = 42;
    
    return 0;
}
