# PRUEBA DIAGNÓSTICA — LENGUAJES Y COMPILADORES (2026-II)
## Estudiante: Carlos Alejandro Zorrilla Figuera (C.I. V-28.783.889)
### Grupo: Zero Warnings

---

## 📁 Estructura de la Entrega Individual

```text
Carlos_Zorrilla/
├── enlace_video_drive.txt              <-- Enlace de Google Drive al video de defensa (5%)
├── README.md                          <-- Documentación técnica de los ejercicios
│
├── ejercicio1/                        <-- Ejercicio 1: Validador de Movimientos de Caballo
│   ├── caballo.c                      (Código en C con temporizadores de alta resolución)
│   ├── caballo.exe                    (Ejecutable compilado con GCC -O2)
│   ├── movimientos_500.txt            (Secuencia completa de 500 movimientos válidos desde a2)
│   ├── tiempos_ejercicio1_c.txt       (Mediciones de tiempos en C para n=100 y 10x 500)
│   └── compilar_y_ejecutar.bat        (Script de compilación y ejecución individual)
│
├── ejercicio2/                        <-- Ejercicio 2: Polinomio (x+1)^n y Triángulo de Pascal
│   ├── pascal_polinomio.c             (Código en C con memoria dinámica malloc/free y enteros de 128 bits)
│   ├── pascal_polinomio.exe           (Ejecutable C)
│   ├── pascal_polinomio.py            (Código en Python con paso a paso y benchmark)
│   ├── tiempos_n100_c.txt             (Tiempos para n=100 en C)
│   ├── tiempos_n100_python.txt        (Tiempos para n=100 en Python)
│   ├── tiempos_n100_comparacion.txt   (Análisis comparativo de rendimiento C vs Python)
│   └── compilar_y_ejecutar.bat        (Script de compilación y ejecución individual)
│
└── ejercicio3/                        <-- Ejercicio 3: Detección y Traducción de Palabras Reservadas
    ├── traductor_c.c                  (Analizador léxico en C con memoria dinámica en Heap)
    ├── traductor_c.exe                (Ejecutable C)
    ├── traductor_c.py                 (Analizador léxico en Python)
    ├── ejemplo_entrada.c              (Código fuente C de prueba)
    ├── ejemplo_traducido.c            (Código resultante traducido al español por C)
    ├── ejemplo_traducido_python.c     (Código resultante traducido por Python)
    └── compilar_y_ejecutar.bat        (Script de compilación y ejecución individual)
```

---

## 🚀 Instrucciones de Ejecución Individual

### Ejercicio 1: Validador de Caballo
Desde la carpeta `ejercicio1/`:
```cmd
compilar_y_ejecutar.bat
```
O directamente:
```cmd
gcc -O2 caballo.c -o caballo.exe
caballo.exe
```

### Ejercicio 2: Polinomio y Triángulo de Pascal
Desde la carpeta `ejercicio2/`:
```cmd
compilar_y_ejecutar.bat
```
O de forma manual:
```cmd
python pascal_polinomio.py
gcc -O2 pascal_polinomio.c -o pascal_polinomio.exe
pascal_polinomio.exe
```

### Ejercicio 3: Analizador Léxico y Traductor
Desde la carpeta `ejercicio3/`:
```cmd
compilar_y_ejecutar.bat
```
O de forma manual:
```cmd
python traductor_c.py
gcc -O2 traductor_c.c -o traductor_c.exe
traductor_c.exe ejemplo_entrada.c ejemplo_traducido.c
```

---

## 📊 Resumen Técnico de Resultados

* **Ejercicio 1:** Validación al 100% de los 9 casos del enunciado y de los 500 movimientos válidos desde `a2`. Tiempo para 10 repeticiones de los 500 movimientos: **0.27 ms**. Tiempo para $n=100$: **7.7 µs**.
* **Ejercicio 2:** Generación con memoria dinámica contigua en el Heap (`malloc`/`free`) y tipo nativo `unsigned __int128` de GCC para soportar $\binom{100}{50} \approx 10^{29}$ sin desbordamiento. Para $n=100$: **5.07 µs en C** vs **538.87 µs en Python** (Speedup de **106x**).
* **Ejercicio 3:** Analizador léxico formal que discrimina cadenas (`"..."`), caracteres (`'...'`) y comentarios (`//`, `/* */`). Detectó 32 palabras reservadas de 18 tipos distintos traduciéndolas a español con liberación estricta de memoria.
