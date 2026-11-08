#include <stdio.h>
#include <stdlib.h>

/* Programa de prueba en C para analisis lexico y traduccion */
// Funcion que calcula el factorial
entero calcular_factorial(entero n) {
    si (n <= 1) {
        retornar 1;
    } sino {
        retornar n * calcular_factorial(n - 1);
    }
}

// Estructura de prueba
estructura Persona {
    caracter nombre[50];
    entero edad;
    flotante salario;
};

entero main() {
    entero contador = 0;
    constante entero limite = 5;
    doble suma = 0.0;
    
    printf("Iniciando bucle de prueba...\n");
    
    para (entero i = 0; i < limite; i++) {
        si (i % 2 == 0) {
            contador++;
        } sino {
            continuar;
        }
    }
    
    mientras (contador > 0) {
        suma += contador;
        contador--;
        si (suma > 10.0) {
            romper;
        }
    }
    
    segun (limite) {
        caso 5:
            printf("Limite es 5\n");
            romper;
        defecto:
            printf("Otro valor\n");
            romper;
    }
    
    vacio* puntero = NULL;
    sin_signo entero positivo = 42;
    
    retornar 0;
}
