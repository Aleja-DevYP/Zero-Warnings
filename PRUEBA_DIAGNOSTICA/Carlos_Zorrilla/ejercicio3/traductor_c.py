"""
UNIVERSIDAD NACIONAL EXPERIMENTAL DE GUAYANA (UNEG)
CARRERA: INGENIERÍA EN INFORMÁTICA
ASIGNATURA: LENGUAJES Y COMPILADORES
PROFESOR: MSc. Félix Márquez
PERIODO: 2026-II

EJERCICIO 3: Analizador Léxico para Detección y Traducción de Palabras Reservadas en C
Implementación en Python.
"""

import os
import re

# Diccionario de palabras reservadas estándar en C (ANSI / C99 / C11) y traducción al español
DICCIONARIO_C_A_ES = {
    "auto": "automatico",
    "break": "romper",
    "case": "caso",
    "char": "caracter",
    "const": "constante",
    "continue": "continuar",
    "default": "defecto",
    "do": "hacer",
    "double": "doble",
    "else": "sino",
    "enum": "enumeracion",
    "extern": "externo",
    "float": "flotante",
    "for": "para",
    "goto": "ir_a",
    "if": "si",
    "inline": "en_linea",
    "int": "entero",
    "long": "largo",
    "register": "registro",
    "restrict": "restringido",
    "return": "retornar",
    "short": "corto",
    "signed": "con_signo",
    "sizeof": "tamano_de",
    "static": "estatico",
    "struct": "estructura",
    "switch": "segun",
    "typedef": "definir_tipo",
    "union": "union",
    "unsigned": "sin_signo",
    "void": "vacio",
    "volatile": "volatil",
    "while": "mientras",
    "_Bool": "_Booleano",
    "_Complex": "_Complejo",
}

def analizar_y_traducir_codigo_c(codigo_fuente):
    """
    Analizador léxico que recorre el código carácter por carácter,
    ignora strings y comentarios, detecta palabras reservadas y genera el código traducido.
    """
    tamano = len(codigo_fuente)
    i = 0
    linea_actual = 1
    
    conteo_keywords = {k: 0 for k in DICCIONARIO_C_A_ES}
    lineas_keywords = {k: [] for k in DICCIONARIO_C_A_ES}
    resultado = []
    
    while i < tamano:
        c = codigo_fuente[i]
        
        if c == '\n':
            linea_actual += 1
            resultado.append(c)
            i += 1
            continue
            
        # 1. Comentarios de una sola línea //
        if c == '/' and i + 1 < tamano and codigo_fuente[i + 1] == '/':
            inicio = i
            while i < tamano and codigo_fuente[i] != '\n':
                i += 1
            resultado.append(codigo_fuente[inicio:i])
            continue
            
        # 2. Comentarios multilínea /* ... */
        if c == '/' and i + 1 < tamano and codigo_fuente[i + 1] == '*':
            inicio = i
            i += 2
            while i < tamano:
                if codigo_fuente[i] == '\n':
                    linea_actual += 1
                if codigo_fuente[i] == '*' and i + 1 < tamano and codigo_fuente[i + 1] == '/':
                    i += 2
                    break
                i += 1
            resultado.append(codigo_fuente[inicio:i])
            continue
            
        # 3. Literales de cadena "..."
        if c == '"':
            inicio = i
            i += 1
            while i < tamano:
                if codigo_fuente[i] == '\\' and i + 1 < tamano:
                    i += 2
                    continue
                sc = codigo_fuente[i]
                i += 1
                if sc == '"':
                    break
            resultado.append(codigo_fuente[inicio:i])
            continue
            
        # 4. Literales de caracter '...'
        if c == '\'':
            inicio = i
            i += 1
            while i < tamano:
                if codigo_fuente[i] == '\\' and i + 1 < tamano:
                    i += 2
                    continue
                sc = codigo_fuente[i]
                i += 1
                if sc == '\'':
                    break
            resultado.append(codigo_fuente[inicio:i])
            continue
            
        # 5. Identificadores y Palabras Reservadas [a-zA-Z_][a-zA-Z0-9_]*
        if c.isalpha() or c == '_':
            inicio = i
            while i < tamano and (codigo_fuente[i].isalnum() or codigo_fuente[i] == '_'):
                i += 1
            lexema = codigo_fuente[inicio:i]
            
            if lexema in DICCIONARIO_C_A_ES:
                conteo_keywords[lexema] += 1
                lineas_keywords[lexema].append(linea_actual)
                resultado.append(DICCIONARIO_C_A_ES[lexema])
            else:
                resultado.append(lexema)
            continue
            
        # Cualquier otro caracter
        resultado.append(c)
        i += 1
        
    codigo_traducido = "".join(resultado)
    return codigo_traducido, conteo_keywords, lineas_keywords

def main():
    dir_actual = os.path.dirname(os.path.abspath(__file__))
    ruta_entrada = os.path.join(dir_actual, "ejemplo_entrada.c")
    ruta_salida = os.path.join(dir_actual, "ejemplo_traducido_python.c")
    
    print("======================================================================")
    print("UNIVERSIDAD NACIONAL EXPERIMENTAL DE GUAYANA (UNEG)")
    print("LENGUAJES Y COMPILADORES - PRUEBA DIAGNÓSTICA 2026-II")
    print("EJERCICIO 3: DETECCIÓN Y TRADUCCIÓN DE PALABRAS RESERVADAS (PYTHON)")
    print("======================================================================\n")
    
    if not os.path.exists(ruta_entrada):
        print(f"Error: no se encuentra el archivo de entrada '{ruta_entrada}'")
        return
        
    with open(ruta_entrada, "r", encoding="utf-8") as f:
        codigo = f.read()
        
    print(f"[1] Código fuente cargado dinámicamente ({len(codigo)} caracteres).")
    
    print("[2] Ejecutando análisis léxico...")
    traducido, conteos, lineas = analizar_y_traducir_codigo_c(codigo)
    
    print("\n======================================================================")
    print("REPORTE DE PALABRAS RESERVADAS ENCONTRADAS")
    print("======================================================================")
    print(f"{'PALABRA (C)':<15} | {'TRADUCCIÓN (ES)':<15} | {'CANTIDAD':<8} | LINEAS DONDE APARECE")
    print("-" * 70)
    
    total_encontradas = 0
    tipos_distintos = 0
    for kw, cnt in conteos.items():
        if cnt > 0:
            total_encontradas += cnt
            tipos_distintos += 1
            lineas_str = ", ".join(map(str, lineas[kw][:10]))
            if cnt > 10:
                lineas_str += "..."
            print(f"{kw:<15} | {DICCIONARIO_C_A_ES[kw]:<15} | {cnt:<8} | {lineas_str}")
            
    print("-" * 70)
    print(f"Resumen: {total_encontradas} apariciones de palabras reservadas detectadas ({tipos_distintos} tipos distintos).\n")
    
    with open(ruta_salida, "w", encoding="utf-8") as f:
        f.write(traducido)
    print(f"[3] Código traducido guardado en: {ruta_salida}")

if __name__ == "__main__":
    main()
