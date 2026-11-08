/*
 * UNIVERSIDAD NACIONAL EXPERIMENTAL DE GUAYANA (UNEG)
 * VICERRECTORADO ACADÉMICO - COORDINACIÓN DE INGENIERÍA EN INFORMÁTICA
 * ASIGNATURA: LENGUAJES Y COMPILADORES
 * DOCENTE: Msc. Félix Márquez
 * PERIODO LECTIVO: 2026-II
 * 
 * EJERCICIO 2: Generación de Polinomio (x+1)^n con Triángulo de Pascal
 * y Evaluación Paso a Paso f(x) = (x+1)^n.
 * Implementado en C con memoria dinámica (malloc/free) y soporte de 128-bits.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

typedef unsigned __int128 uint128_t;

/* Convierte un entero de 128 bits sin signo a cadena decimal */
void u128_to_str(uint128_t n, char* buffer, size_t buf_size) {
    if (n == 0) {
        snprintf(buffer, buf_size, "0");
        return;
    }
    char temp[64];
    int idx = 0;
    while (n > 0 && idx < 63) {
        temp[idx++] = '0' + (int)(n % 10);
        n /= 10;
    }
    int out_idx = 0;
    for (int i = idx - 1; i >= 0 && out_idx < (int)buf_size - 1; i--) {
        buffer[out_idx++] = temp[i];
    }
    buffer[out_idx] = '\0';
}

/*
 * Genera la fila n del Triángulo de Pascal utilizando memoria dinámica.
 * Retorna un puntero al arreglo de coeficientes de tamaño (n + 1).
 */
uint128_t* generar_fila_pascal_dinamica(int n) {
    if (n < 0) return NULL;

    /* Asignación dinámica de memoria */
    uint128_t* fila = (uint128_t*)malloc((n + 1) * sizeof(uint128_t));
    if (!fila) return NULL;

    fila[0] = 1;
    for (int i = 1; i <= n; i++) {
        fila[i] = 1;
        for (int j = i - 1; j > 0; j--) {
            fila[j] = fila[j] + fila[j - 1];
        }
    }
    return fila;
}

/*
 * Formatea los coeficientes del polinomio (x+1)^n en una cadena en memoria dinámica.
 */
char* formatear_polinomio_dinamico(int n, const uint128_t* coefs) {
    size_t cap = 2048 + n * 64;
    char* resultado = (char*)malloc(cap);
    if (!resultado) return NULL;

    snprintf(resultado, cap, "(x+1)^%d = ", n);

    if (n == 0) {
        strcat(resultado, "1");
        return resultado;
    }

    char num_buf[64];
    for (int k = 0; k <= n; k++) {
        int grado = n - k;
        uint128_t c = coefs[k];

        if (k > 0) {
            strcat(resultado, "+");
        }

        if (grado == 0) {
            u128_to_str(c, num_buf, sizeof(num_buf));
            strcat(resultado, num_buf);
        } else if (grado == 1) {
            if (c == 1) {
                strcat(resultado, "x");
            } else {
                u128_to_str(c, num_buf, sizeof(num_buf));
                strcat(resultado, num_buf);
                strcat(resultado, "x");
            }
        } else {
            if (c == 1) {
                char term[32];
                snprintf(term, sizeof(term), "x^%d", grado);
                strcat(resultado, term);
            } else {
                u128_to_str(c, num_buf, sizeof(num_buf));
                strcat(resultado, num_buf);
                char term[32];
                snprintf(term, sizeof(term), "x^%d", grado);
                strcat(resultado, term);
            }
        }
    }
    return resultado;
}

/* Función auxiliar para calcular potencias enteras con 128-bits */
uint128_t potencia_u128(uint128_t base, int exp) {
    uint128_t res = 1;
    while (exp > 0) {
        if (exp % 2 == 1) res *= base;
        base *= base;
        exp /= 2;
    }
    return res;
}

/*
 * Muestra el cálculo paso a paso para un x dado evaluado en el polinomio generado.
 */
void calcular_paso_a_paso_c(int n, const uint128_t* coefs, unsigned long long x) {
    char s_x[64], s_c[64], s_pot[64], s_val[64], s_sum[64], s_dir[64];
    u128_to_str(x, s_x, sizeof(s_x));

    printf("\n----------------------------------------------------------------------\n");
    printf("CALCULO PASO A PASO PARA x = %s, n = %d: f(%s) = (%s + 1)^%d\n", s_x, n, s_x, s_x, n);
    printf("----------------------------------------------------------------------\n");

    char* pol_str = formatear_polinomio_dinamico(n, coefs);
    printf("Polinomio expandido: %s\n\n", pol_str);
    free(pol_str);

    printf("Sustituyendo x = %s en cada termino del polinomio:\n", s_x);

    uint128_t suma_acumulada = 0;
    for (int k = 0; k <= n; k++) {
        int grado = n - k;
        uint128_t c = coefs[k];
        uint128_t pot = potencia_u128(x, grado);
        uint128_t val = c * pot;
        suma_acumulada += val;

        u128_to_str(c, s_c, sizeof(s_c));
        u128_to_str(pot, s_pot, sizeof(s_pot));
        u128_to_str(val, s_val, sizeof(s_val));

        if (grado == 0) {
            printf("  Paso %02d: Termino independiente (grado 0): C(%d,%d) = %s\n", k + 1, n, k, s_c);
        } else if (grado == 1) {
            printf("  Paso %02d: Termino grado 1: C(%d,%d) * (%s)^1 = %s * %s = %s\n", k + 1, n, k, s_x, s_c, s_x, s_val);
        } else {
            printf("  Paso %02d: Termino grado %d: C(%d,%d) * (%s)^%d = %s * %s = %s\n", k + 1, grado, n, k, s_x, grado, s_c, s_pot, s_val);
        }
    }

    u128_to_str(suma_acumulada, s_sum, sizeof(s_sum));
    printf("\nSumatoria de los terminos evaluados:\n  f(%s) = %s\n", s_x, s_sum);

    /* Verificación binomial directa: (x + 1)^n */
    uint128_t directo = potencia_u128(x + 1, n);
    u128_to_str(directo, s_dir, sizeof(s_dir));
    printf("\nVerificacion directa con formula binomial (x + 1)^n:\n");
    printf("  (%s + 1)^%d = (%llu)^%d = %s\n", s_x, n, x + 1, n, s_dir);
    printf("  Resultado: %s\n", (suma_acumulada == directo) ? "SISTEMA COINCIDE [VERIFICADO CORRECTO]" : "DISCREPANCIA [ERROR]");
}

int main() {
    printf("======================================================================\n");
    printf("UNIVERSIDAD NACIONAL EXPERIMENTAL DE GUAYANA (UNEG)\n");
    printf("LENGUAJES Y COMPILADORES - PRUEBA DIAGNOSTICA 2026-II\n");
    printf("EJERCICIO 2 (C): POLINOMIO (x+1)^n Y TRIANGULO DE PASCAL\n");
    printf("======================================================================\n\n");

    /* a) Generar y mostrar para n=0 a 7 usando memoria dinámica */
    printf("a) Coeficientes del triangulo de Pascal y polinomios generados (n=0 a 7):\n");
    for (int n = 0; n <= 7; n++) {
        uint128_t* fila = generar_fila_pascal_dinamica(n);
        char* pol = formatear_polinomio_dinamico(n, fila);

        printf("  (n =%d): ", n);
        char buf[64];
        for (int k = 0; k <= n; k++) {
            u128_to_str(fila[k], buf, sizeof(buf));
            printf("%s ", buf);
        }
        printf(" => %s\n", pol);

        /* Liberar memoria dinámica */
        free(pol);
        free(fila);
    }

    /* b) Demostración del cálculo paso a paso */
    uint128_t* fila_3 = generar_fila_pascal_dinamica(3);
    calcular_paso_a_paso_c(3, fila_3, 2);
    free(fila_3);

    uint128_t* fila_4 = generar_fila_pascal_dinamica(4);
    calcular_paso_a_paso_c(4, fila_4, 3);
    free(fila_4);

    /* Medición de tiempo de ejecución para n=100 */
    printf("\n======================================================================\n");
    printf("MEDICION DE TIEMPOS DE GENERACION EN C PARA n=100\n");
    printf("======================================================================\n");

    LARGE_INTEGER freq, start, end;
    QueryPerformanceFrequency(&freq);

    int repeticiones = 50000; /* 50,000 iteraciones para máxima precisión */
    uint128_t* fila_100 = NULL;

    QueryPerformanceCounter(&start);
    for (int r = 0; r < repeticiones; r++) {
        if (fila_100) free(fila_100);
        fila_100 = generar_fila_pascal_dinamica(100);
    }
    QueryPerformanceCounter(&end);

    double total_ms = (double)(end.QuadPart - start.QuadPart) * 1000.0 / freq.QuadPart;
    double prom_ms = total_ms / repeticiones;
    double prom_us = prom_ms * 1000.0;

    char central_str[64];
    u128_to_str(fila_100[50], central_str, sizeof(central_str));

    printf("Fila n=100 generada dinamicamente: 101 coeficientes\n");
    printf("Coeficiente central C(100, 50): %s\n", central_str);
    printf("Tiempo total (%d iteraciones): %.4f ms\n", repeticiones, total_ms);
    printf("Tiempo promedio por generacion: %.6f ms (%.3f us)\n", prom_ms, prom_us);

    /* Guardar archivo txt */
    FILE* out_txt = fopen("tiempos_n100_c.txt", "w");
    if (!out_txt) {
        out_txt = fopen("ejercicio2/tiempos_n100_c.txt", "w");
    }
    if (out_txt) {
        fprintf(out_txt, "UNIVERSIDAD NACIONAL EXPERIMENTAL DE GUAYANA (UNEG)\n");
        fprintf(out_txt, "LENGUAJES Y COMPILADORES - PRUEBA DIAGNOSTICA 2026-II\n");
        fprintf(out_txt, "EJERCICIO 2: TIEMPO DE GENERACION (x+1)^100 EN C\n");
        fprintf(out_txt, "============================================================\n\n");
        fprintf(out_txt, "Parametro n: 100\n");
        fprintf(out_txt, "Total de coeficientes: 101\n");
        fprintf(out_txt, "Coeficiente C(100, 50): %s\n", central_str);
        fprintf(out_txt, "Iteraciones evaluadas: %d\n", repeticiones);
        fprintf(out_txt, "Tiempo total: %.4f ms\n", total_ms);
        fprintf(out_txt, "Tiempo promedio por generacion: %.6f ms (%.3f us)\n", prom_ms, prom_us);
        fclose(out_txt);
        printf("\nResultados exportados con exito a: tiempos_n100_c.txt\n");
    }

    free(fila_100);
    return 0;
}
