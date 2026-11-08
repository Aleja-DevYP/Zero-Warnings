@echo off
echo ======================================================================
echo UNEG - LENGUAJES Y COMPILADORES - PRUEBA DIAGNOSTICA 2026-II
echo SCRIPT DE VERIFICACION DE COMPONENTES Y DEPENDENCIAS
echo ======================================================================

echo.
echo [1/3] Verificando compilador de C (GCC / MinGW)...
gcc --version >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo [ADVERTENCIA] GCC no esta en el PATH del sistema.
    echo Por favor asegurese de tener instalado MinGW-W64 o GCC para compilar los codigos en C.
) else (
    echo [OK] Compilador GCC detectado correctamente:
    gcc --version | findstr /C:"gcc" /C:"Copyright"
)

echo.
echo [2/3] Verificando interprete de Python...
python --version >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo [ADVERTENCIA] Python no esta en el PATH del sistema.
    echo Por favor instale Python 3.8 o superior para ejecutar los scripts .py.
) else (
    echo [OK] Interprete Python detectado correctamente:
    python --version
)

echo.
echo [3/3] Verificando librerias estandar...
echo Nota: Ambos proyectos utilizan exclusivamente librerias estandar:
echo   - En C: stdio.h, stdlib.h, string.h, ctype.h, windows.h
echo   - En Python: time, os, sys (no requieren paquetes externos con pip)

echo.
echo ======================================================================
echo Entorno verificado con exito. Puede ejecutar 'ejecutar_todo.bat'.
echo ======================================================================
