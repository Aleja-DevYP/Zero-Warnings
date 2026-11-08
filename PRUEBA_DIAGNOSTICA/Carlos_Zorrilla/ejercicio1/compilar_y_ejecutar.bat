@echo off
echo ========================================================
echo EJERCICIO 1: VALIDADOR DE CABALLO (C y Python)
echo ========================================================

echo.
echo [1/3] Ejecutando solucion en Python...
python caballo.py

echo.
echo [2/3] Compilando solucion en C con GCC...
gcc -O2 caballo.c -o caballo.exe
if %ERRORLEVEL% NEQ 0 (
    echo Error al compilar caballo.c
    pause
    exit /b %ERRORLEVEL%
)

echo.
echo [3/3] Ejecutando solucion en C...
caballo.exe

echo.
echo ========================================================
echo Proceso finalizado con exito. Tiempos guardados en .txt
echo ========================================================
pause
