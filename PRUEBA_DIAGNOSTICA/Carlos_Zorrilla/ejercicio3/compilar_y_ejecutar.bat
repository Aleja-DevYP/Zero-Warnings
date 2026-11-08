@echo off
echo ========================================================
echo EJERCICIO 3: TRADUCTOR DE PALABRAS RESERVADAS (LENGUAJE C)
echo ========================================================

echo.
echo [1/2] Compilando solucion en C con GCC...
gcc -O2 traductor_c.c -o traductor_c.exe
if %ERRORLEVEL% NEQ 0 (
    echo Error al compilar traductor_c.c
    pause
    exit /b %ERRORLEVEL%
)

echo.
echo [2/2] Ejecutando solucion en C...
traductor_c.exe ejemplo_entrada.c ejemplo_traducido.c

echo.
echo ========================================================
echo Proceso finalizado. Archivo traducido generado con exito.
echo ========================================================
pause
