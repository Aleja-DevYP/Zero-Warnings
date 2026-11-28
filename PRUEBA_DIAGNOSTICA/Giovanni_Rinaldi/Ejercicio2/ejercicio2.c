#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generar_coeficientes_pascal(int n) {
    double **pascal = (double **)malloc((n + 1) * sizeof(double *));
    for (int i = 0; i <= n; i++) {
        pascal[i] = (double *)malloc((i + 1) * sizeof(double));
        pascal[i][0] = 1.0;
        pascal[i][i] = 1.0;
        for (int j = 1; j < i; j++) {
            pascal[i][j] = pascal[i - 1][j - 1] + pascal[i - 1][j];
        }
    }

    for (int i = 0; i <= n; i++) {
        free(pascal[i]);
    }
    free(pascal);
}

int main() {
    clock_t start = clock();
    generar_coeficientes_pascal(100);
    clock_t end = clock();

    double tiempo_ms = ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;
    printf("Tiempo en C para n=100: %.6f ms\n", tiempo_ms);
    return 0;
}
