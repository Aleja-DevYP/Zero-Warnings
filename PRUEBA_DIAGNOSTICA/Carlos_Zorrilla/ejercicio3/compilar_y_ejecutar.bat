@echo off
echo ========================================================
echo EJERCICIO 3: TRADUCTOR DE PALABRAS RESERVADAS (C y Python)
echo ========================================================

echo.
echo [1/3] Ejecutando solucion en Python...
python traductor_c.py

echo.
echo [2/3] Compilando solucion en C con GCC...
gcc -O2 traductor_c.c -o traductor_c.exe
if %ERRORLEVEL% NEQ 0 (
    echo Error al compilar traductor_c.c
    pause
    exit /b %ERRORLEVEL%
)

echo.
echo [3/3] Ejecutando solucion en C...
traductor_c.exe ejemplo_entrada.c ejemplo_traducido.c

echo.
echo ========================================================
echo Proceso finalizado. Archivo traducido generado con exito.
echo ========================================================
pause
