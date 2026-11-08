"""
UNIVERSIDAD NACIONAL EXPERIMENTAL DE GUAYANA (UNEG)
CARRERA: INGENIERÍA EN INFORMÁTICA
ASIGNATURA: LENGUAJES Y COMPILADORES
PROFESOR: MSc. Félix Márquez
PERIODO: 2026-II

EJERCICIO 2: Generación de Polinomio (x+1)^n mediante Triángulo de Pascal,
Evaluación Paso a Paso con x dado y Medición de Tiempos para n=100.
Implementación en Python.
"""

import time
import os

def generar_triangulo_pascal(n):
    """
    Genera el triángulo de Pascal hasta la fila n usando listas dinámicas.
    Retorna la lista completa del triángulo [fila_0, fila_1, ..., fila_n]
    donde cada fila contiene los coeficientes binomiales C(n, k).
    """
    if n < 0:
        raise ValueError("El exponente n debe ser un entero no negativo.")
        
    triangulo = [[1]]
    for i in range(1, n + 1):
        fila_anterior = triangulo[i - 1]
        nueva_fila = [1]
        for j in range(1, i):
            nueva_fila.append(fila_anterior[j - 1] + fila_anterior[j])
        nueva_fila.append(1)
        triangulo.append(nueva_fila)
        
    return triangulo

def generar_fila_pascal(n):
    """
    Genera únicamente la fila n del triángulo de Pascal con memoria O(n).
    """
    if n < 0:
        raise ValueError("El exponente n debe ser un entero no negativo.")
    fila = [1]
    for i in range(1, n + 1):
        fila = [1] + [fila[j - 1] + fila[j] for j in range(1, i)] + [1]
    return fila

def formatear_polinomio(n, coeficientes):
    """
    Formatea los coeficientes del polinomio (x+1)^n en notación algebraica estándar.
    Ejemplo para n=3: x^3+3x^2+3x+1
    """
    if n == 0:
        return "(x+1)^0 = 1"
        
    terminos = []
    for k in range(n + 1):
        coef = coeficientes[k]
        grado = n - k
        
        if grado == 0:
            terminos.append(str(coef))
        elif grado == 1:
            if coef == 1:
                terminos.append("x")
            else:
                terminos.append(f"{coef}x")
        else: # grado > 1
            if coef == 1:
                terminos.append(f"x^{grado}")
            else:
                terminos.append(f"{coef}x^{grado}")
                
    polinomio_str = "+".join(terminos)
    return f"(x+1)^{n} = {polinomio_str}"

def calcular_paso_a_paso(n, coeficientes, x):
    """
    Muestra de forma detallada y pedagógica el cálculo paso a paso
    de f(x) = (x+1)^n según el polinomio generado.
    """
    print("\n" + "-" * 70)
    print(f"CÁLCULO PASO A PASO PARA x = {x}, n = {n}: f({x}) = ({x} + 1)^{n}")
    print("-" * 70)
    print(f"Polinomio expandido: {formatear_polinomio(n, coeficientes)}")
    print(f"\nSustituyendo x = {x} en cada término del polinomio:")
    
    suma_acumulada = 0
    pasos_terminos = []
    
    for k in range(n + 1):
        coef = coeficientes[k]
        grado = n - k
        potencia_x = x ** grado
        valor_termino = coef * potencia_x
        suma_acumulada += valor_termino
        
        if grado == 0:
            desc = f"Término independiente (grado 0): C({n},{k}) = {coef}"
            expr = f"{coef}"
        elif grado == 1:
            desc = f"Término grado 1: C({n},{k}) * ({x})^1 = {coef} * {x} = {valor_termino}"
            expr = f"{coef}*({x})"
        else:
            desc = f"Término grado {grado}: C({n},{k}) * ({x})^{grado} = {coef} * {potencia_x} = {valor_termino}"
            expr = f"{coef}*({x}^{grado})"
            
        pasos_terminos.append((expr, valor_termino))
        print(f"  Paso {k + 1:02d}: {desc}")
        
    print("\nSumatoria de los términos:")
    suma_str = " + ".join([str(val) for _, val in pasos_terminos])
    print(f"  f({x}) = {suma_str} = {suma_acumulada}")
    
    # Comprobación directa
    resultado_directo = (x + 1) ** n
    print(f"\nVerificación directa con la fórmula base (x + 1)^n:")
    print(f"  ({x} + 1)^{n} = {x + 1}^{n} = {resultado_directo}")
    
    coinciden = (suma_acumulada == resultado_directo)
    print(f"  ¿El cálculo coincide? {'SÍ [VERIFICADO CORRECTO]' if coinciden else 'NO [ERROR]'}")
    return suma_acumulada

def benchmark_n100(repeticiones=5000):
    print("\n" + "=" * 70)
    print(f"BENCHMARK PYTHON: GENERACIÓN DE (x+1)^100 ({repeticiones} ITERACIONES)")
    print("=" * 70)
    
    # Calentamiento
    for _ in range(100):
        _ = generar_fila_pascal(100)
        
    tiempos = []
    t0_global = time.perf_counter()
    for _ in range(repeticiones):
        t0 = time.perf_counter()
        fila = generar_fila_pascal(100)
        t1 = time.perf_counter()
        tiempos.append((t1 - t0) * 1000)
    t1_global = time.perf_counter()
    
    tiempo_total_ms = (t1_global - t0_global) * 1000
    tiempo_prom_ms = tiempo_total_ms / repeticiones
    tiempo_prom_us = tiempo_prom_ms * 1000
    
    print(f"Coeficientes generados para n=100: {len(fila)} términos")
    print(f"Coeficiente central C(100, 50): {fila[50]}")
    print(f"Tiempo total ({repeticiones} iteraciones): {tiempo_total_ms:.4f} ms")
    print(f"Tiempo promedio por generación: {tiempo_prom_ms:.6f} ms ({tiempo_prom_us:.3f} µs)")
    
    return tiempo_prom_ms, tiempo_prom_us, fila

def main():
    print("======================================================================")
    print("UNIVERSIDAD NACIONAL EXPERIMENTAL DE GUAYANA (UNEG)")
    print("LENGUAJES Y COMPILADORES - PRUEBA DIAGNÓSTICA 2026-II")
    print("EJERCICIO 2: POLINOMIO (x+1)^n Y TRIÁNGULO DE PASCAL (PYTHON)")
    print("======================================================================\n")
    
    # Demostración de las filas 0 a 7 (como en la figura del examen)
    print("a) Coeficientes del triángulo de Pascal y polinomios generados (n=0 a 7):")
    triangulo = generar_triangulo_pascal(7)
    for n_idx, fila in enumerate(triangulo):
        coef_str = " ".join([str(c) for c in fila])
        pol_str = formatear_polinomio(n_idx, fila)
        print(f"  (n ={n_idx}): {coef_str:<25} => {pol_str}")
        
    # Demostración con paso a paso para n=3 y x=2, y luego n=4 y x=3
    fila_3 = triangulo[3]
    calcular_paso_a_paso(3, fila_3, 2)
    
    fila_4 = triangulo[4]
    calcular_paso_a_paso(4, fila_4, 3)
    
    # Medición de tiempo para n=100
    t_prom_ms, t_prom_us, fila_100 = benchmark_n100(repeticiones=5000)

if __name__ == "__main__":
    main()
