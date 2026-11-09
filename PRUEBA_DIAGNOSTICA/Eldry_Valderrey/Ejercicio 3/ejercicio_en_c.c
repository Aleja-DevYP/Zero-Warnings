#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Generador de triángulo de Pascal con memoria dinámica
unsigned long long *generar_coeficientes(int n) {
  // Asignación de memoria dinámica
  unsigned long long *coeficientes =
      (unsigned long long *)malloc((n + 1) * sizeof(unsigned long long));
  unsigned long long *temp =
      (unsigned long long *)malloc((n + 1) * sizeof(unsigned long long));

  coeficientes[0] = 1;

  for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= i; j++) {
      temp[j] = coeficientes[j];
    }

    coeficientes[0] = 1;
    for (int j = 1; j < i; j++) {
      coeficientes[j] = temp[j - 1] + temp[j];
    }
    coeficientes[i] = 1;
  }

  // Liberar memoria temporal
  free(temp);
  return coeficientes;
}

void mostrar_polinomio(int n, unsigned long long *coefs) {
  printf("(x+1)^%d = ", n);
  for (int i = 0; i <= n; i++) {
    int potencia = n - i;
    if (i > 0)
      printf(" + ");

    if (potencia == 0) {
      printf("%llu", coefs[i]);
    } else if (potencia == 1) {
      if (coefs[i] == 1)
        printf("x");
      else
        printf("%llux", coefs[i]);
    } else {
      if (coefs[i] == 1)
        printf("x^%d", potencia);
      else
        printf("%llux^%d", coefs[i], potencia);
    }
  }
  printf("\n");
}

void evaluar_paso_a_paso(int n, unsigned long long *coefs, int x) {
  printf("\nEvaluando para x = %d:\n", x);

  // Paso 1: Sustitución
  printf("f(x) = ");
  for (int i = 0; i <= n; i++) {
    if (i > 0)
      printf(" + ");
    printf("%llu(%d)^%d", coefs[i], x, n - i);
  }
  printf("\n");

  // Paso 2: Resolviendo potencias
  printf("f(x) = ");
  for (int i = 0; i <= n; i++) {
    if (i > 0)
      printf(" + ");
    printf("%llu(%.0f)", coefs[i], pow(x, n - i));
  }
  printf("\n");

  // Paso 3 y Resultado final
  unsigned long long total = 0;
  printf("f(x) = ");
  for (int i = 0; i <= n; i++) {
    if (i > 0)
      printf(" + ");
    unsigned long long valor = coefs[i] * (unsigned long long)pow(x, n - i);
    printf("%llu", valor);
    total += valor;
  }
  printf("\nf(x) = %llu\n\n", total);
}

int main() {
  int n_ejemplo = 4;
  int x_ejemplo = 2;

  printf("--- DEMOSTRACION ---\n");
  unsigned long long *coefs = generar_coeficientes(n_ejemplo);
  mostrar_polinomio(n_ejemplo, coefs);
  evaluar_paso_a_paso(n_ejemplo, coefs, x_ejemplo);

  // Liberar memoria principal tras uso
  free(coefs);

  // --- MEDICION DE TIEMPO n=100 ---
  clock_t inicio = clock();
  unsigned long long *coefs_100 = generar_coeficientes(100);
  clock_t fin = clock();

  double tiempo_c = (double)(fin - inicio) / CLOCKS_PER_SEC;
  free(coefs_100); // Evitar fugas de memoria

  printf("--- RENDIMIENTO ---\n");
  printf("Tiempo en C (n=100): %f segundos\n", tiempo_c);

  // Guardar en archivo .txt (Modo Append)
  FILE *archivo = fopen("resultados_tiempo.txt", "a");
  if (archivo != NULL) {
    fprintf(archivo, "Tiempo de ejecucion C (n=100): %f segundos\n", tiempo_c);
    fclose(archivo);
  } else {
    printf("Error al abrir el archivo txt.\n");
  }

  return 0;
}