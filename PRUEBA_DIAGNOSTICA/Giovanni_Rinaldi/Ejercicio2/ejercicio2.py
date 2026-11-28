import time

def generar_pascal(n):
    triangulo = [[1]]
    for i in range(1, n + 1):
        fila = [1]
        for j in range(1, i):
            fila.append(triangulo[i-1][j-1] + triangulo[i-1][j])
        fila.append(1)
        triangulo.append(fila)
    return triangulo

t0 = time.perf_counter()
pascal_100 = generar_pascal(100)
t1 = time.perf_counter()

print(f"Coeficientes n=100 generados. (Muestra primeros 5): {pascal_100[100][:5]}...")
print(f"Tiempo en Python para n=100: {(t1 - t0) * 1000:.6f} ms")