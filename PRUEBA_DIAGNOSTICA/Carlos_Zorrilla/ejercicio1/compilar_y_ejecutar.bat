@echo off
echo ========================================================
echo EJERCICIO 1: VALIDADOR DE CABALLO (LENGUAJE C)
echo ========================================================

echo.
echo [1/2] Compilando solucion en C con GCC...
gcc -O2 caballo.c -o caballo.exe
if %ERRORLEVEL% NEQ 0 (
    echo Error al compilar caballo.c
    pause
    exit /b %ERRORLEVEL%
)

echo.
echo [2/2] Ejecutando solucion en C...
caballo.exe

echo.
echo ========================================================
echo Verificacion completada con exito. Tiempos guardados.
echo ========================================================
pause
