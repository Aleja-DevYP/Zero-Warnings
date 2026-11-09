/*
 * EJERCICIO 1: Validador de Movimientos de Caballo en Tablero de Ajedrez
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

/* Función para calcular valor absoluto de enteros */
static int mi_abs(int val) {
    return (val < 0) ? -val : val;
}

/* Verifica si el movimiento entre (c1, r1) y (c2, r2) es un salto en 'L' de caballo */
int es_movimiento_caballo(char c1, char r1, char c2, char r2) {
    int dc = mi_abs((int)c2 - (int)c1);
    int dr = mi_abs((int)r2 - (int)r1);
    return ((dc == 1 && dr == 2) || (dc == 2 && dr == 1));
}

/*
 * Valida la secuencia de movimientos dados en 'cadena' partiendo de la posición inicial 'ak'.
 * Retorna: 1 si es correcto, 0 si es incorrecto.
 * Llena 'msg_salida' con el mensaje correspondiente al resultado.
 */
int verificar_movimientos(const char* ak, const char* cadena, int n, char* msg_salida, size_t msg_size) {
    if (!ak || strlen(ak) < 2) {
        snprintf(msg_salida, msg_size, "Posicion inicial invalida.");
        return 0;
    }

    char curr_col = ak[0];
    char curr_row = ak[1];

    if (curr_col < 'a' || curr_col > 'h' || curr_row < '1' || curr_row > '8') {
        snprintf(msg_salida, msg_size, "Posicion inicial fuera de rango: %s", ak);
        return 0;
    }

    /* Clonar la cadena en memoria dinámica para tokenizar con strtok */
    size_t len = strlen(cadena);
    char* copia = (char*)malloc(len + 1);
    if (!copia) {
        snprintf(msg_salida, msg_size, "Error: Memoria insuficiente.");
        return 0;
    }
    memcpy(copia, cadena, len + 1);

    char* token = strtok(copia, " \t\r\n");
    int mov_idx = 0;
    int correcto = 1;

    while (token != NULL && mov_idx < n) {
        mov_idx++;
        size_t tok_len = strlen(token);

        if (tok_len < 3) {
            snprintf(msg_salida, msg_size, "movimiento INCORRECTO: formato invalido en movimiento %d.", mov_idx);
            correcto = 0;
            break;
        }

        char pieza = token[0];
        char dest_col = token[1];
        char dest_row = token[2];

        /* 1. Validar que la pieza sea caballo ('K') */
        if (pieza != 'K') {
            snprintf(msg_salida, msg_size, "movimiento INCORRECTO falla letra %c no pertenece a un caballo.", pieza);
            correcto = 0;
            break;
        }

        /* 2. Validar límites de la casilla de destino */
        if (dest_col < 'a' || dest_col > 'h' || dest_row < '1' || dest_row > '8') {
            snprintf(msg_salida, msg_size, "movimiento INCORRECTO falla en el movimiento %d: casilla fuera de tablero.", mov_idx);
            correcto = 0;
            break;
        }

        /* 3. Validar movimiento en 'L' */
        if (!es_movimiento_caballo(curr_col, curr_row, dest_col, dest_row)) {
            snprintf(msg_salida, msg_size, "movimiento INCORRECTO falla en el movimiento %d", mov_idx);
            correcto = 0;
            break;
        }

        /* Actualizar casilla actual */
        curr_col = dest_col;
        curr_row = dest_row;

        token = strtok(NULL, " \t\r\n");
    }

    if (correcto) {
        if (mov_idx < n) {
            snprintf(msg_salida, msg_size, "movimiento INCORRECTO: se esperaban %d movimientos pero solo habia %d.", n, mov_idx);
            correcto = 0;
        } else {
            snprintf(msg_salida, msg_size, "movimiento CORRECTO.");
        }
    }

    free(copia);
    return correcto;
}

/* Lee el contenido completo de un archivo en memoria dinámica */
char* leer_archivo_dinamico(const char* ruta) {
    FILE* f = fopen(ruta, "rb");
    if (!f) return NULL;

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);

    char* buffer = (char*)malloc(size + 1);
    if (!buffer) {
        fclose(f);
        return NULL;
    }

    fread(buffer, 1, size, f);
    buffer[size] = '\0';
    fclose(f);
    return buffer;
}

int main() {
    char msg[256];

    printf("=== EJERCICIO 1: VALIDADOR DE MOVIMIENTOS DE CABALLO ===\n\n");

    /* Pruebas del enunciado */
    struct {
        const char* ak;
        int n;
        const char* c;
        const char* esperado;
    } pruebas[] = {
        {"a1", 4, "Kc2 Kd4 Kb3 Kc5", "movimiento CORRECTO."},
        {"a1", 4, "Kc2 Kd4 Kb4 Kc5", "movimiento INCORRECTO falla en el movimiento 3"},
        {"a2", 5, "Kc3 Ke4 Kf6 Ke8 Kg7", "movimiento CORRECTO."},
        {"a2", 5, "Kc8 Ke4 Kf6 Ke8 Kg7", "movimiento INCORRECTO falla en el movimiento 1"},
        {"a8", 2, "Kb6 Kd7", "movimiento CORRECTO."},
        {"a8", 2, "Kb6 Kb7", "movimiento INCORRECTO falla en el movimiento 2"},
        {"a1", 10, "Kc2 Kd4 Kf3 Ke5 Kg6 Kh8 Kf7 Kd8 Kc6 Kb4", "movimiento CORRECTO."},
        {"a1", 10, "Kc2 Kd4 Kf3 Ke5 Kg6 Kh8 Kf7 Kd8 Kc6 Qb4", "movimiento INCORRECTO falla letra Q no pertenece a un caballo."},
        {"a1", 10, "Kc2 Kd4 Kf3 Ke5 Kg6 Kh8 Kf7 Kd8 Kh6 Kb4", "movimiento INCORRECTO falla en el movimiento 9"}
    };

    int num_pruebas = sizeof(pruebas) / sizeof(pruebas[0]);
    for (int i = 0; i < num_pruebas; i++) {
        verificar_movimientos(pruebas[i].ak, pruebas[i].c, pruebas[i].n, msg, sizeof(msg));
        printf("Prueba %02d [Ak=%s, n=%d]:\n  Cadena : %s\n  Salida : %s\n", 
               i + 1, pruebas[i].ak, pruebas[i].n, pruebas[i].c, msg);
    }

    /* Benchmark de rendimiento */
    printf("\n======================================================================\n");
    printf("MEDICION DE TIEMPOS DE EJECUCION EN C (BENCHMARK)\n");
    printf("======================================================================\n");

    char* datos_500 = leer_archivo_dinamico("movimientos_500.txt");
    if (!datos_500) {
        datos_500 = leer_archivo_dinamico("ejercicio1/movimientos_500.txt");
    }
    if (!datos_500) {
        printf("Error: no se pudo encontrar 'movimientos_500.txt'.\n");
        return 1;
    }

    /* Contar tokens */
    int total_movs = 0;
    {
        char* temp = strdup(datos_500);
        char* t = strtok(temp, " \t\r\n");
        while (t) {
            total_movs++;
            t = strtok(NULL, " \t\r\n");
        }
        free(temp);
    }
    printf("Total de movimientos cargados en la secuencia: %d\n", total_movs);

    /* Medición con QueryPerformanceCounter */
    LARGE_INTEGER freq, start, end;
    QueryPerformanceFrequency(&freq);

    /* 1. Medir 10 repeticiones de la secuencia completa */
    double tiempos_10[10];
    double suma_10 = 0.0;

    for (int rep = 0; rep < 10; rep++) {
        QueryPerformanceCounter(&start);
        verificar_movimientos("a2", datos_500, total_movs, msg, sizeof(msg));
        QueryPerformanceCounter(&end);

        double elapsed_ms = (double)(end.QuadPart - start.QuadPart) * 1000.0 / freq.QuadPart;
        tiempos_10[rep] = elapsed_ms;
        suma_10 += elapsed_ms;
    }

    printf("Resultado verificacion: %s\n", msg);
    printf("Tiempo total 10 repeticiones (secuencia completa): %.4f ms\n", suma_10);
    printf("Tiempo promedio por verificacion: %.4f ms\n\n", suma_10 / 10.0);

    /* 2. Medir para n=100 movimientos promediado en 1000 corridas */
    int rep_100 = 1000;
    QueryPerformanceCounter(&start);
    for (int i = 0; i < rep_100; i++) {
        verificar_movimientos("a2", datos_500, 100, msg, sizeof(msg));
    }
    QueryPerformanceCounter(&end);

    double total_100_ms = (double)(end.QuadPart - start.QuadPart) * 1000.0 / freq.QuadPart;
    double prom_100_ms = total_100_ms / rep_100;
    double prom_100_us = prom_100_ms * 1000.0;

    printf("Medicion para n=100 movimientos (1000 iteraciones):\n");
    printf("Tiempo total: %.4f ms\n", total_100_ms);
    printf("Tiempo promedio por verificacion (n=100): %.6f ms (%.3f us)\n", prom_100_ms, prom_100_us);

    free(datos_500);
    return 0;
}
