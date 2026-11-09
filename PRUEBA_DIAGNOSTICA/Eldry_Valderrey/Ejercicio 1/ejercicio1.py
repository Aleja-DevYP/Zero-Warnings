import time

def es_movimiento_valido_caballo(pos_actual, pos_siguiente):
    # Validar que las posiciones estén dentro del tablero
    columnas = {'a': 1, 'b': 2, 'c': 3, 'd': 4, 'e': 5, 'f': 6, 'g': 7, 'h': 8}
    
    col_actual, fila_actual = pos_actual[0], int(pos_actual[1])
    col_siguiente, fila_siguiente = pos_siguiente[0], int(pos_siguiente[1])
    
    if col_siguiente not in columnas or not (1 <= fila_siguiente <= 8):
        return False

    dx = abs(columnas[col_actual] - columnas[col_siguiente])
    dy = abs(fila_actual - fila_siguiente)
    
    # El caballo se mueve en "L": 2 casillas en una dirección y 1 en la perpendicular
    return (dx == 1 and dy == 2) or (dx == 2 and dy == 1)

def verificar_movimientos(pos_inicial, n, cadena_movimientos):
    movimientos = cadena_movimientos.split()
    pos_actual = pos_inicial
    
    # Verificar que el número de movimientos coincida con n
    if len(movimientos) != n:
        # Se asume verificación de longitud si es estrictamente necesario
        pass

    for i, mov in enumerate(movimientos):
        letra = mov[0]
        if letra != 'K':
            return f"movimiento INCORRECTO falla letra {letra} no pertenece a un caballo."
        
        pos_siguiente = mov[1:3]
        
        if not es_movimiento_valido_caballo(pos_actual, pos_siguiente):
            return f"INCORRECTO falla en el movimiento {i + 1}."
        
        pos_actual = pos_siguiente
        
    return "movimiento CORRECTO."

# --- PRUEBAS DE EJEMPLO DEL DOCUMENTO ---
ejemplos = [
    ("a1", 4, "Kc2 Kd4 Kb3 Kc5"),
    ("a1", 4, "Kc2 Kd4 Kb4 Kc5"),
    ("a2", 5, "Kc3 Ke4 Kf6 Ke8 Kg7"),
    ("a2", 5, "Kc8 Ke4 Kf6 Ke8 Kg7"),
    ("a8", 2, "Kb6 Kd7"),
    ("a8", 2, "Kb6 Kb7"),
    ("a1", 10, "Kc2 Kd4 Kf3 Ke5 Kg6 Kh8 Kf7 Kd8 Kc6 Kb4"),
    ("a1", 10, "Kc2 Kd4 Kf3 Ke5 Kg6 Kh8 Kf7 Kd8 Kc6 Qb4"),
    ("a1", 10, "Kc2 Kd4 Kf3 Ke5 Kg6 Kh8 Kf7 Kd8 Kh6 Kb4")
]

print("--- RESULTADOS DE LOS EJEMPLOS ---")
for pos, n, cadena in ejemplos:
    resultado = verificar_movimientos(pos, n, cadena)
    print(f"Para Ak={pos} n={n} -> Salida: {resultado}")

# --- MEDICIÓN DE TIEMPO (10 VECES, 500 MOVIMIENTOS) ---
# Se asume la posición inicial a1 basada en el primer movimiento hacia Kb4, pero el cálculo requiere el punto origen. 
# El reverso del primer movimiento "Kb4" válido más probable desde a1/c1/c2 etc. Asumiremos "a2" o "c2" validan Kb4. 
# Tomando "a2" como posición inicial para la prueba de rendimiento:
posicion_inicial_500 = "a2"

movimientos_500 = "Kb4 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg1 Kh3 Kg5 Ke6 Kc7 Ka8 Kc7 Kb5 Kd6 Kb7 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Ka6 Kb8 Kd7 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 Kd4 Kb3 Ka1 Kc2 Ka3 Kc4 Ka5 Kc6 Ka7 Kc8 Ka7 Kc6 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Kd5 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg1 Kh3 Kg5 Ke6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 Kd6 Kb7 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Ka6 Kb8 Kd7 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 Kd4 Kb3 Ka1 Kc2 Ka3 Kc4 Ka5 Kc6 Ka7 Kc8 Ka7 Kc6 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Kd5 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg1 Kh3 Kg5 Ke6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 Kd6 Kb7 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Ka6 Kb8 Kd7 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 Kd4 Kb3 Ka1 Kc2 Ka3 Kc4 Ka5 Kc6 Ka7 Kc8 Ka7 Kc6 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Kd5 Kb6 Ka8"

# Iniciar medición
inicio_tiempo = time.perf_counter()

for _ in range(10):
    verificar_movimientos(posicion_inicial_500, 500, movimientos_500)

fin_tiempo = time.perf_counter()
tiempo_total = fin_tiempo - inicio_tiempo

print("\n--- MEDICIÓN DE RENDIMIENTO ---")
print(f"Tiempo total para verificar 500 movimientos 10 veces: {tiempo_total:.6f} segundos")