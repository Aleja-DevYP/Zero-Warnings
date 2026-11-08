# 🚀 Repositorio: Zero Warnings
## UNIVERSIDAD NACIONAL EXPERIMENTAL DE GUAYANA (UNEG)
### VICERRECTORADO ACADÉMICO - COORDINACIÓN DE INGENIERÍA EN INFORMÁTICA
**Asignatura:** Lenguajes y Compiladores  
**Docente:** Msc. Félix Márquez (`lyc.fmarquez@e.uneg.edu.ve`)  
**Periodo Lectivo:** 2026-II  

> **Nombre del Grupo:** Zero Warnings  
> **Eslogan:** *"0 errores, 0 advertencias, 100% de fe."*  

---

## 👥 Integrantes del Equipo
* **Carlos Alejandro Zorrilla Figuera** — C.I. V-28.783.889
* *(Espacio para los demás integrantes del grupo asignados por la cátedra)*

---

## 📁 Estructura del Repositorio

Cumpliendo con la directiva del profesor:
> *"En el repositorio de su grupo ubicado en carpeta PRUEBA DIAGNOSTICA, colocar una carpeta con su nombre y colocar allí tres carpetas una para cada ejercicio, y en la raíz de su carpeta indicar el enlace al drive donde estará el video con su defensa (5%)."*

```text
Zero_Warnings/
├── README.md                               <-- Portada oficial del grupo Zero Warnings
└── PRUEBA_DIAGNOSTICA/                     <-- Carpeta grupal de la evaluación
    ├── README.md                           (Índice de integrantes del grupo)
    │
    ├── Carlos_Zorrilla/                     <-- Entrega individual de Carlos Zorrilla
    │   ├── enlace_video_drive.txt           <-- Enlace de Google Drive al video de defensa
    │   ├── README.md                       <-- Documentación técnica de sus ejercicios
    │   │
    │   ├── ejercicio1/                     <-- Ejercicio 1: Validador de Caballo (Lenguaje C)
    │   │   ├── caballo.c
    │   │   ├── caballo.exe
    │   │   ├── movimientos_500.txt         (500 movimientos válidos desde a2)
    │   │   ├── tiempos_ejercicio1_c.txt    (Tiempos 10x 500 movs y n=100)
    │   │   └── compilar_y_ejecutar.bat     (Ejecución individual)
    │   │
    │   ├── ejercicio2/                     <-- Ejercicio 2: Polinomio (x+1)^n (C y Python)
    │   │   ├── pascal_polinomio.c          (Memoria dinámica malloc/free y 128-bits)
    │   │   ├── pascal_polinomio.exe
    │   │   ├── pascal_polinomio.py
    │   │   ├── tiempos_n100_c.txt
    │   │   ├── tiempos_n100_python.txt
    │   │   ├── tiempos_n100_comparacion.txt
    │   │   └── compilar_y_ejecutar.bat     (Ejecución individual)
    │   │
    │   └── ejercicio3/                     <-- Ejercicio 3: Analizador Léxico y Traductor en C
    │       ├── traductor_c.c               (Carga en Heap dinámico y traducción sin alterar strings/comentarios)
    │       ├── traductor_c.exe
    │       ├── traductor_c.py
    │       ├── ejemplo_entrada.c
    │       ├── ejemplo_traducido.c
    │       └── compilar_y_ejecutar.bat     (Ejecución individual)
    │
    └── [Carpeta_Otro_Integrante]/          <-- Espacio para cada compañero del grupo
```

---

## ⚡ Ejecución Individual de los Ejercicios
Cada ejercicio cuenta con su propio script y comandos para ser ejecutado de forma independiente dentro de su respectivo directorio:

* **Ejercicio 1:** Entrar a `ejercicio1/` y ejecutar `compilar_y_ejecutar.bat` o `caballo.exe`.
* **Ejercicio 2:** Entrar a `ejercicio2/` y ejecutar `compilar_y_ejecutar.bat` o `python pascal_polinomio.py`.
* **Ejercicio 3:** Entrar a `ejercicio3/` y ejecutar `compilar_y_ejecutar.bat` o `traductor_c.exe ejemplo_entrada.c ejemplo_traducido.c`.
