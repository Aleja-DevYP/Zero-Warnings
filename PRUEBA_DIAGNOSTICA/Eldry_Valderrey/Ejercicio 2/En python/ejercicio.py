import time

def generar_coeficientes(n):
    # Memoria dinámica: la lista crece dinámicamente según n
    coeficientes = [1]
    for i in range(1, n + 1):
        siguiente = [1] * (i + 1)
        for j in range(1, i):
            siguiente[j] = coeficientes[j - 1] + coeficientes[j]
        coeficientes = siguiente
    return coeficientes

def mostrar_polinomio(n, coeficientes):
    terminos = []
    for i, coef in enumerate(coeficientes):
        potencia = n - i
        if coef == 0: continue
        
        if potencia == 0:
            terminos.append(str(coef))
        elif potencia == 1:
            terminos.append(f"{coef if coef != 1 else ''}x")
        else:
            terminos.append(f"{coef if coef != 1 else ''}x^{potencia}")
            
    print(f"(x+1)^{n} = " + " + ".join(terminos))

def evaluar_paso_a_paso(n, coeficientes, x):
    print(f"\nEvaluando para x = {x}:")
    
    # Paso 1: Sustitución
    sustitucion = [f"{coef}({x})^{n-i}" for i, coef in enumerate(coeficientes)]
    print("f(x) = " + " + ".join(sustitucion))
    
    # Paso 2: Resolviendo potencias
    potencias = [f"{coef}({x**(n-i)})" for i, coef in enumerate(coeficientes)]
    print("f(x) = " + " + ".join(potencias))
    
    # Paso 3: Multiplicación
    multiplicaciones = [str(coef * (x**(n-i))) for i, coef in enumerate(coeficientes)]
    print("f(x) = " + " + ".join(multiplicaciones))
    
    # Paso 4: Suma final
    total = sum(coef * (x**(n-i)) for i, coef in enumerate(coeficientes))
    print(f"f(x) = {total}\n")

# --- PRUEBAS DEL DOCUMENTO ---
n_ejemplo = 4
x_ejemplo = 2

print("--- DEMOSTRACIÓN ---")
coefs = generar_coeficientes(n_ejemplo)
mostrar_polinomio(n_ejemplo, coefs)
evaluar_paso_a_paso(n_ejemplo, coefs, x_ejemplo)

# --- MEDICIÓN DE TIEMPO n=100 ---
inicio = time.perf_counter()
coefs_100 = generar_coeficientes(100)
fin = time.perf_counter()
tiempo_py = fin - inicio

# Guardar en archivo .txt
with open("resultados_tiempo.txt", "a") as archivo:
    archivo.write(f"Tiempo de ejecucion Python (n=100): {tiempo_py:.6f} segundos\n")

print(f"--- RENDIMIENTO ---")
print(f"Tiempo para n=100 calculado y guardado en 'resultados_tiempo.txt': {tiempo_py:.6f} segundos")