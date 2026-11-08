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
* **Carlos Alejandro Zorrilla Figuera** — C.I. V-28.783.889 *(Líder / Integrante)*
* *(Espacio para los demás integrantes del grupo asignados por la cátedra)*

---

## 📁 Estructura del Repositorio

Cumpliendo con la directiva del profesor:
> *"En el repositorio de su grupo ubicado en carpeta PRUEBA DIAGNOSTICA, colocar una carpeta con su nombre y colocar allí tres carpetas una para cada ejercicio, y en la raíz de su carpeta indicar el enlace al drive donde estará el video con su defensa (5%)."*

```text
Zero_Warnings/
├── README.md                               <-- Portada oficial del grupo
└── PRUEBA_DIAGNOSTICA/
    └── Carlos_Zorrilla/                     <-- Carpeta del estudiante
        ├── enlace_video_drive.txt           <-- Enlace de Google Drive al video de defensa
        ├── DEFENSA_VIDEO_GUION.md          <-- Guion cronometrado para la defensa audiovisual (<= 5 min)
        ├── README.md                       <-- Documentación técnica completa
        ├── ejercicio1/                     <-- Ejercicio 1: Validador de Caballo (C y Python)
        │   ├── caballo.c
        │   ├── caballo.py
        │   ├── movimientos_500.txt         (500 movimientos válidos desde a2)
        │   ├── tiempos_ejercicio1_c.txt
        │   ├── tiempos_ejercicio1_python.txt
        │   └── compilar_y_ejecutar.bat
        ├── ejercicio2/                     <-- Ejercicio 2: Polinomio (x+1)^n (C y Python)
        │   ├── pascal_polinomio.c          (Memoria dinámica malloc/free y 128-bits)
        │   ├── pascal_polinomio.py
        │   ├── tiempos_n100_c.txt
        │   ├── tiempos_n100_python.txt
        │   ├── tiempos_n100_comparacion.txt
        │   └── compilar_y_ejecutar.bat
        ├── ejercicio3/                     <-- Ejercicio 3: Analizador Léxico y Traductor en C
        │   ├── traductor_c.c               (Carga en Heap y traducción sin alterar strings/comentarios)
        │   ├── traductor_c.py
        │   ├── ejemplo_entrada.c
        │   ├── ejemplo_traducido.c
        │   └── compilar_y_ejecutar.bat
        └── scripts_instalacion/            <-- Scripts de ejecución por lotes
            ├── instalar_dependencias.bat
            └── ejecutar_todo.bat
```

---

## ⚡ Ejecución Rápida
Para compilar y ejecutar automáticamente todos los ejercicios en secuencia:
```cmd
cd PRUEBA_DIAGNOSTICA\Carlos_Zorrilla\scripts_instalacion
ejecutar_todo.bat
```
