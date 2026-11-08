@echo off
echo ========================================================
echo EJERCICIO 2: POLINOMIO Y TRIANGULO DE PASCAL (C y Python)
echo ========================================================

echo.
echo [1/3] Ejecutando solucion en Python...
python pascal_polinomio.py

echo.
echo [2/3] Compilando solucion en C con GCC...
gcc -O2 pascal_polinomio.c -o pascal_polinomio.exe
if %ERRORLEVEL% NEQ 0 (
    echo Error al compilar pascal_polinomio.c
    pause
    exit /b %ERRORLEVEL%
)

echo.
echo [3/3] Ejecutando solucion en C...
pascal_polinomio.exe

echo.
echo ========================================================
echo Mediciones completadas. Archivos txt generados con exito.
echo ========================================================
pause
