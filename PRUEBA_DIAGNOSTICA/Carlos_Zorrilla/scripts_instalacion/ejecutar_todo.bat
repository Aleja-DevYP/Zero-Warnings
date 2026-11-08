@echo off
setlocal enabledelayedexpansion

echo ======================================================================
echo UNIVERSIDAD NACIONAL EXPERIMENTAL DE GUAYANA (UNEG)
echo LENGUAJES Y COMPILADORES - PRUEBA DIAGNOSTICA 2026-II
echo SCRIPT GENERAL DE COMPILACION Y EJECUCION DE LOS TRES EJERCICIOS
echo ======================================================================

set "ROOT=%~dp0.."

echo.
echo ======================================================================
echo === [PASO 1/3] EJECUTANDO EJERCICIO 1 (VALIDADOR DE CABALLO)
echo ======================================================================
cd "%ROOT%\ejercicio1"
echo 1.1 Ejecutando en Python...
python caballo.py
echo 1.2 Compilando en C con GCC...
gcc -O2 caballo.c -o caballo.exe
if %ERRORLEVEL% NEQ 0 (
    echo Error al compilar caballo.c
    exit /b %ERRORLEVEL%
)
echo 1.3 Ejecutando en C...
caballo.exe

echo.
echo ======================================================================
echo === [PASO 2/3] EJECUTANDO EJERCICIO 2 (POLINOMIO Y TRIANGULO DE PASCAL)
echo ======================================================================
cd "%ROOT%\ejercicio2"
echo 2.1 Ejecutando en Python...
python pascal_polinomio.py
echo 2.2 Compilando en C con GCC...
gcc -O2 pascal_polinomio.c -o pascal_polinomio.exe
if %ERRORLEVEL% NEQ 0 (
    echo Error al compilar pascal_polinomio.c
    exit /b %ERRORLEVEL%
)
echo 2.3 Ejecutando en C...
pascal_polinomio.exe

echo.
echo ======================================================================
echo === [PASO 3/3] EJECUTANDO EJERCICIO 3 (ANALIZADOR LEXICO Y TRADUCTOR)
echo ======================================================================
cd "%ROOT%\ejercicio3"
echo 3.1 Ejecutando en Python...
python traductor_c.py
echo 3.2 Compilando en C con GCC...
gcc -O2 traductor_c.c -o traductor_c.exe
if %ERRORLEVEL% NEQ 0 (
    echo Error al compilar traductor_c.c
    exit /b %ERRORLEVEL%
)
echo 3.3 Ejecutando en C...
traductor_c.exe ejemplo_entrada.c ejemplo_traducido.c

echo.
echo ======================================================================
echo === TODOS LOS EJERCICIOS HAN SIDO COMPILADOS Y EJECUTADOS CON EXITO.
echo ======================================================================
cd "%ROOT%"
