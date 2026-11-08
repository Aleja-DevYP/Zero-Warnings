# UNIVERSIDAD NACIONAL EXPERIMENTAL DE GUAYANA (UNEG)
## VICERRECTORADO ACADÉMICO - COORDINACIÓN DE INGENIERÍA EN INFORMÁTICA
### ASIGNATURA: LENGUAJES Y COMPILADORES
**Docente:** Msc. Félix Márquez  
**Periodo Lectivo:** 2026-II  
**Actividad:** Prueba Diagnóstica (Ponderación: 10%)

---

## 📁 ESTRUCTURA DEL REPOSITORIO

De acuerdo con las instrucciones de la prueba diagnóstica, la entrega está organizada de la siguiente manera:

```text
PRUEBA_DIAGNOSTICA/
└── [Nombre_Apellido_Seccion]/
    ├── enlace_video_drive.txt              <-- Enlace de Google Drive al video de defensa (5%)
    ├── DEFENSA_VIDEO_GUION.md             <-- Guion cronometrado para la defensa audiovisual (<= 5 min)
    ├── README.md                          <-- Documentación técnica completa de la solución
    │
    ├── ejercicio1/                        <-- Ejercicio 1: Validador de Movimientos de Caballo
    │   ├── caballo.c                      (Código en C con alta precisión temporal)
    │   ├── caballo.exe                    (Ejecutable compilado con GCC -O2)
    │   ├── movimientos_500.txt            (Secuencia completa de 500 movimientos válidos desde a2)
    │   ├── tiempos_ejercicio1_c.txt       (Mediciones de tiempos en C para n=100 y 10x 500)
    │   └── compilar_y_ejecutar.bat        (Script de compilación y ejecución automática)
    │
    ├── ejercicio2/                        <-- Ejercicio 2: Polinomio (x+1)^n y Triángulo de Pascal
    │   ├── pascal_polinomio.c             (Código en C con memoria dinámica malloc/free y enteros de 128 bits)
    │   ├── pascal_polinomio.py            (Código en Python con paso a paso y benchmark)
    │   ├── tiempos_n100_c.txt             (Tiempos para n=100 en C)
    │   ├── tiempos_n100_python.txt        (Tiempos para n=100 en Python)
    │   ├── tiempos_n100_comparacion.txt   (Análisis comparativo de rendimiento C vs Python)
    │   └── compilar_y_ejecutar.bat        (Script de compilación y ejecución automática)
    │
    ├── ejercicio3/                        <-- Ejercicio 3: Detección y Traducción de Palabras Reservadas
    │   ├── traductor_c.c                  (Analizador léxico en C con memoria dinámica en Heap)
    │   ├── traductor_c.py                 (Analizador léxico en Python)
    │   ├── ejemplo_entrada.c              (Código fuente C de prueba para traducir)
    │   ├── ejemplo_traducido.c            (Código resultante traducido al español por C)
    │   ├── ejemplo_traducido_python.c     (Código resultante traducido por Python)
    │   └── compilar_y_ejecutar.bat        (Script de compilación y ejecución automática)
    │
    └── scripts_instalacion/               <-- Scripts de entorno e instalación
        ├── instalar_dependencias.bat      (Verifica GCC, Python y entorno del sistema)
        └── ejecutar_todo.bat              (Compila y ejecuta los 3 ejercicios secuencialmente)
```

---

## 🚀 INSTRUCCIONES DE COMPILACIÓN Y EJECUCIÓN

### Requisitos previos:
- **Compilador C:** MinGW-W64 GCC o equivalente compatible con C99/C11 (incluye soporte para `unsigned __int128`).
- **Python:** Python 3.8 o superior (se utilizó Python 3.12).
- Ambos lenguajes utilizan únicamente librerías estándar del sistema operativo.

### Ejecución Rápida de Todo el Proyecto:
Hacer doble clic en:
```cmd
scripts_instalacion\ejecutar_todo.bat
```
O desde la consola PowerShell / CMD:
```powershell
.\scripts_instalacion\ejecutar_todo.bat
```

---

## 📊 RESUMEN TÉCNICO DE CADA EJERCICIO

### 1. Ejercicio 1: Validador de Movimientos de Caballo
- **Planteamiento:** Verificar si una secuencia de $n$ movimientos es válida a partir de una casilla $A_k$. Notación: `K` seguido de columna (`a`-`h`) y fila (`1`-`8`). El programa se detiene al encontrar el primer movimiento incorrecto.
- **Validaciones implementadas:**
  1. Identificador de pieza: Detecta si la letra es distinta de `'K'` (Ej: `Qb4` -> `movimiento INCORRECTO falla letra Q no pertenece a un caballo.`).
  2. Rango del tablero: Casilla dentro de `[a-h]` y `[1-8]`.
  3. Movimiento geométrico en "L": $|\Delta c| = 1 \land |\Delta r| = 2$ ó $|\Delta c| = 2 \land |\Delta r| = 1$.
- **Resultados de Rendimiento:**
  - Secuencia completa (500 movimientos desde posición inicial a2 verificados 10 veces): **0.32 ms en C** vs **5.67 ms en Python** (~17.3x más rápido).
  - Verificación para $n=100$: **6.16 µs en C** vs **108.31 µs en Python** (~17.5x más rápido).

### 2. Ejercicio 2: Polinomio $(x+1)^n$ y Triángulo de Pascal
- **Planteamiento:** Generar los coeficientes de $(x+1)^n$ usando el Triángulo de Pascal con **memoria dinámica**, mostrar el polinomio resultante, y calcular paso a paso para un valor dado de $x$ según el polinomio. Medir el tiempo para $n=100$ en Python vs C.
- **Aspecto Clave:** Para $n=100$, el coeficiente central $\binom{100}{50} = 100891344545564193334812497256$ tiene 29 dígitos decimales y 97 bits. Se implementó en C utilizando `unsigned __int128` sobre arreglos asignados dinámicamente con `malloc()`.
- **Resultados de Rendimiento (n = 100):**
  - **C:** **5.07 µs** por generación (evaluado en 50,000 iteraciones).
  - **Python:** **538.87 µs** por generación (evaluado en 5,000 iteraciones).
  - **Speedup:** El código en C es **106 veces más rápido** que Python debido al modelo de ejecución compilado y memoria contigua en el Heap.

### 3. Ejercicio 3: Detección y Traducción de Palabras Reservadas en C
- **Planteamiento:** Cargar un programa escrito en C en memoria de forma dinámica (`malloc`), verificar si existen palabras reservadas de C y traducirlas a su equivalente en español.
- **Rigor de Compiladores:** Implementación de un analizador léxico que evita colisiones en:
  1. Cadenas de texto literales (`"..."`).
  2. Comentarios de línea (`//`) y de bloque (`/* ... */`).
  3. Subcadenas de identificadores (ejemplo: `printf` no se traduce, `point` no altera `int`).
- **Resultados:** Detectó 32 ocurrencias de 18 tipos de palabras reservadas en el archivo de prueba, generando `ejemplo_traducido.c` con tipos y estructuras en español (`entero`, `si`, `sino`, `para`, `mientras`, `retornar`, `estructura`, `segun`, etc.) y liberando toda la memoria dinámica.
