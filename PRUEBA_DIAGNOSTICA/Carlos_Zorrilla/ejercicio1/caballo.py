"""
UNIVERSIDAD NACIONAL EXPERIMENTAL DE GUAYANA (UNEG)
CARRERA: INGENIERÍA EN INFORMÁTICA
ASIGNATURA: LENGUAJES Y COMPILADORES
PROFESOR: MSc. Félix Márquez
PERIODO: 2026-II

EJERCICIO 1: Validador de Movimientos de Caballo en Tablero de Ajedrez
Implementación en Python con análisis léxico y verificación geométrica.
"""

import time
import os

def es_movimiento_caballo(c1, r1, c2, r2):
    """
    Verifica si el desplazamiento entre (c1, r1) y (c2, r2)
    corresponde a un movimiento en 'L' válido para un caballo.
    """
    dc = abs(ord(c2) - ord(c1))
    dr = abs(int(r2) - int(r1))
    return (dc == 1 and dr == 2) or (dc == 2 and dr == 1)

def verificar_movimientos(ak, c_cadena, n=None):
    """
    Valida una secuencia de movimientos de caballo a partir de la posición inicial Ak.
    Detiene la verificación al primer error encontrado.
    
    Retorna:
        (es_correcto: bool, mensaje: str)
    """
    # Posición inicial
    if len(ak) < 2 or ak[0] < 'a' or ak[0] > 'h' or ak[1] < '1' or ak[1] > '8':
        return False, f"Posición inicial inválida: {ak}"
    
    curr_c = ak[0]
    curr_r = ak[1]
    
    tokens = c_cadena.strip().split()
    total_a_verificar = n if n is not None else len(tokens)
    
    for i in range(total_a_verificar):
        if i >= len(tokens):
            return False, f"movimiento INCORRECTO: faltan movimientos (se esperaban {total_a_verificar}, se recibieron {len(tokens)})."
        
        token = tokens[i]
        num_mov = i + 1
        
        # Validar longitud mínima de notación (Ej: Kc2)
        if len(token) < 3:
            return False, f"movimiento INCORRECTO: formato inválido en movimiento {num_mov} ('{token}')."
            
        pieza = token[0]
        col = token[1]
        fila = token[2]
        
        # 1. Validar identificador de pieza (debe ser 'K')
        if pieza != 'K':
            return False, f"movimiento INCORRECTO falla letra {pieza} no pertenece a un caballo."
        
        # 2. Validar límites del tablero
        if col < 'a' or col > 'h' or fila < '1' or fila > '8':
            return False, f"movimiento INCORRECTO falla en el movimiento {num_mov}: casilla fuera del tablero ({col}{fila})."
        
        # 3. Validar geometría de movimiento en 'L'
        if not es_movimiento_caballo(curr_c, curr_r, col, fila):
            return False, f"movimiento INCORRECTO falla en el movimiento {num_mov}."
        
        # Actualizar posición actual del caballo
        curr_c = col
        curr_r = fila
        
    return True, "movimiento CORRECTO."

def ejecutar_pruebas_enunciado():
    print("=" * 70)
    print("EJERCICIO 1: PRUEBAS DE EJEMPLOS DEL ENUNCIADO")
    print("=" * 70)
    
    casos = [
        ("a1", 4, "Kc2 Kd4 Kb3 Kc5", "movimiento CORRECTO."),
        ("a1", 4, "Kc2 Kd4 Kb4 Kc5", "INCORRECTO falla en el movimiento 3."),
        ("a2", 5, "Kc3 Ke4 Kf6 Ke8 Kg7", "movimiento CORRECTO."),
        ("a2", 5, "Kc8 Ke4 Kf6 Ke8 Kg7", "INCORRECTO falla en el movimiento 1."),
        ("a8", 2, "Kb6 Kd7", "movimiento CORRECTO."),
        ("a8", 2, "Kb6 Kb7", "INCORRECTO falla en el movimiento 2."),
        ("a1", 10, "Kc2 Kd4 Kf3 Ke5 Kg6 Kh8 Kf7 Kd8 Kc6 Kb4", "movimiento CORRECTO."),
        ("a1", 10, "Kc2 Kd4 Kf3 Ke5 Kg6 Kh8 Kf7 Kd8 Kc6 Qb4", "movimiento INCORRECTO falla letra Q no pertenece a un caballo."),
        ("a1", 10, "Kc2 Kd4 Kf3 Ke5 Kg6 Kh8 Kf7 Kd8 Kh6 Kb4", "movimiento INCORRECTO falla en el movimiento 9"),
    ]
    
    for idx, (ak, n, c_str, esperada) in enumerate(casos, 1):
        _, salida = verificar_movimientos(ak, c_str, n)
        # Normalización para verificar equivalencia semántica exacta
        norm_salida = salida.lower().replace("movimiento ", "").strip().rstrip('.')
        norm_esperada = esperada.lower().replace("movimiento ", "").strip().rstrip('.')
        coincide = (norm_salida == norm_esperada)
        estado = "[OK]" if coincide else "[FALLO]"
        print(f"Caso {idx:02d}: Ak={ak}, n={n}")
        print(f"  Cadena : {c_str}")
        print(f"  Salida : {salida}")
        print(f"  Esperad: {esperada} {estado}")
        print("-" * 70)

def benchmark():
    print("\n" + "=" * 70)
    print("MEDICIÓN DE TIEMPOS DE EJECUCIÓN (BENCHMARK)")
    print("=" * 70)
    
    # 1. Medir 10 veces los 500 movimientos (224 en el bloque de texto del examen)
    directorio_actual = os.path.dirname(os.path.abspath(__file__))
    archivo_500 = os.path.join(directorio_actual, "movimientos_500.txt")
    
    with open(archivo_500, "r", encoding="utf-8") as f:
        cadena_500 = f.read().strip()
    
    total_tokens = len(cadena_500.split())
    print(f"Cargada cadena de prueba con {total_tokens} movimientos.")
    
    # Repetir 10 veces la verificación
    repeticiones = 10
    tiempos_500 = []
    
    t0_global = time.perf_counter()
    for rep in range(repeticiones):
        t0 = time.perf_counter()
        valido, msg = verificar_movimientos("a2", cadena_500, total_tokens)
        t1 = time.perf_counter()
        tiempos_500.append((t1 - t0) * 1000) # en milisegundos
    t1_global = time.perf_counter()
    
    tiempo_total_500_ms = (t1_global - t0_global) * 1000
    tiempo_promedio_500_ms = sum(tiempos_500) / repeticiones
    
    print(f"Resultado verificación 500 movimientos: {msg}")
    print(f"Tiempo total (10 repeticiones): {tiempo_total_500_ms:.4f} ms")
    print(f"Tiempo promedio por ejecución: {tiempo_promedio_500_ms:.4f} ms")
    
    # 2. Medir para n=100 movimientos
    subcadena_100 = " ".join(cadena_500.split()[:100])
    tiempos_100 = []
    repeticiones_100 = 1000
    
    t0_100_glob = time.perf_counter()
    for _ in range(repeticiones_100):
        t0 = time.perf_counter()
        verificar_movimientos("a2", subcadena_100, 100)
        t1 = time.perf_counter()
        tiempos_100.append((t1 - t0) * 1000)
    t1_100_glob = time.perf_counter()
    
    tiempo_promedio_100_ms = sum(tiempos_100) / repeticiones_100
    tiempo_promedio_100_us = tiempo_promedio_100_ms * 1000
    
    print(f"\nMedición para n=100 movimientos:")
    print(f"Tiempo promedio por verificación (n=100): {tiempo_promedio_100_ms:.6f} ms ({tiempo_promedio_100_us:.3f} µs)")
    
    # Guardar resultados en txt
    archivo_tiempos = os.path.join(directorio_actual, "tiempos_ejercicio1_python.txt")
    with open(archivo_tiempos, "w", encoding="utf-8") as f:
        f.write("UNIVERSIDAD NACIONAL EXPERIMENTAL DE GUAYANA (UNEG)\n")
        f.write("LENGUAJES Y COMPILADORES - PRUEBA DIAGNÓSTICA 2026-II\n")
        f.write("EJERCICIO 1: TIEMPOS DE EJECUCIÓN (PYTHON)\n")
        f.write("=" * 60 + "\n\n")
        f.write(f"1. Verificación 10 veces de la secuencia completa ({total_tokens} movimientos):\n")
        for i, t in enumerate(tiempos_500, 1):
            f.write(f"   Iteración {i:02d}: {t:.5f} ms\n")
        f.write(f"   Tiempo total 10 iteraciones: {tiempo_total_500_ms:.5f} ms\n")
        f.write(f"   Tiempo promedio: {tiempo_promedio_500_ms:.5f} ms\n\n")
        f.write(f"2. Verificación de n=100 movimientos (Promediado en {repeticiones_100} iteraciones):\n")
        f.write(f"   Tiempo promedio por corrida (n=100): {tiempo_promedio_100_ms:.6f} ms ({tiempo_promedio_100_us:.3f} µs)\n")
        f.write(f"   Tiempo acumulado: {(t1_100_glob - t0_100_glob) * 1000:.4f} ms\n")
    
    print(f"\nResultados exportados con éxito a: {archivo_tiempos}")

if __name__ == "__main__":
    ejecutar_pruebas_enunciado()
    benchmark()
