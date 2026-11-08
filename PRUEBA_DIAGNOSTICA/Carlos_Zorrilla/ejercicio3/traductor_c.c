/*
 * UNIVERSIDAD NACIONAL EXPERIMENTAL DE GUAYANA (UNEG)
 * VICERRECTORADO ACADÉMICO - COORDINACIÓN DE INGENIERÍA EN INFORMÁTICA
 * ASIGNATURA: LENGUAJES Y COMPILADORES
 * DOCENTE: Msc. Félix Márquez
 * PERIODO LECTIVO: 2026-II
 * 
 * EJERCICIO 3: Analizador Léxico para Detección y Traducción de Palabras Reservadas en C
 * Implementación en C con carga en memoria dinámica (malloc/free) y análisis léxico formal.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINEAS_OCURRENCIA 100

/* Estructura para registrar palabras reservadas del lenguaje C */
typedef struct {
    const char* palabra_c;
    const char* traduccion_es;
    int conteo;
    int lineas[MAX_LINEAS_OCURRENCIA];
} PalabraReservada;

/* Tabla completa de palabras reservadas en estándar C (ANSI / C99 / C11) */
static PalabraReservada TABLA_KEYWORDS[] = {
    {"auto",     "automatico",   0, {0}},
    {"break",    "romper",       0, {0}},
    {"case",     "caso",         0, {0}},
    {"char",     "caracter",     0, {0}},
    {"const",    "constante",    0, {0}},
    {"continue", "continuar",    0, {0}},
    {"default",  "defecto",      0, {0}},
    {"do",       "hacer",        0, {0}},
    {"double",   "doble",        0, {0}},
    {"else",     "sino",         0, {0}},
    {"enum",     "enumeracion",  0, {0}},
    {"extern",   "externo",      0, {0}},
    {"float",    "flotante",     0, {0}},
    {"for",      "para",         0, {0}},
    {"goto",     "ir_a",         0, {0}},
    {"if",       "si",           0, {0}},
    {"inline",   "en_linea",     0, {0}},
    {"int",      "entero",       0, {0}},
    {"long",     "largo",        0, {0}},
    {"register", "registro",     0, {0}},
    {"restrict", "restringido",  0, {0}},
    {"return",   "retornar",     0, {0}},
    {"short",    "corto",        0, {0}},
    {"signed",   "con_signo",    0, {0}},
    {"sizeof",   "tamano_de",    0, {0}},
    {"static",   "estatico",     0, {0}},
    {"struct",   "estructura",   0, {0}},
    {"switch",   "segun",        0, {0}},
    {"typedef",  "definir_tipo", 0, {0}},
    {"union",    "union",        0, {0}},
    {"unsigned", "sin_signo",    0, {0}},
    {"void",     "vacio",        0, {0}},
    {"volatile", "volatil",      0, {0}},
    {"while",    "mientras",     0, {0}},
    {"_Bool",    "_Booleano",    0, {0}}
};

static const int NUM_KEYWORDS = sizeof(TABLA_KEYWORDS) / sizeof(TABLA_KEYWORDS[0]);

/* Busca si un identificador corresponde a una palabra reservada en C */
int buscar_palabra_reservada(const char* ident) {
    for (int i = 0; i < NUM_KEYWORDS; i++) {
        if (strcmp(TABLA_KEYWORDS[i].palabra_c, ident) == 0) {
            return i;
        }
    }
    return -1;
}

/* Lee el archivo fuente completo cargándolo en memoria dinámica */
char* cargar_archivo_en_memoria_dinamica(const char* ruta, long* tamano_salida) {
    FILE* f = fopen(ruta, "rb");
    if (!f) return NULL;

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);

    /* Asignación dinámica en Heap */
    char* buffer = (char*)malloc(size + 1);
    if (!buffer) {
        fclose(f);
        return NULL;
    }

    size_t leidos = fread(buffer, 1, size, f);
    buffer[leidos] = '\0';
    fclose(f);

    if (tamano_salida) *tamano_salida = leidos;
    return buffer;
}

/*
 * Analizador léxico que recorre el código en memoria dinámica,
 * discrimina literales de cadena, comentarios y operadores,
 * detecta palabras reservadas y genera el código traducido al español.
 */
char* procesar_y_traducir_c(const char* codigo_fuente, long tamano_fuente, int* total_reservadas_encontradas) {
    /* Asignamos un buffer dinámico para el código traducido con margen de crecimiento */
    size_t capacidad_salida = (size_t)tamano_fuente * 2 + 1024;
    char* salida = (char*)malloc(capacidad_salida);
    if (!salida) return NULL;

    size_t idx_out = 0;
    long i = 0;
    int linea_actual = 1;
    *total_reservadas_encontradas = 0;

    #define APPEND_CHAR(c) do { \
        if (idx_out + 2 >= capacidad_salida) { \
            capacidad_salida *= 2; \
            salida = (char*)realloc(salida, capacidad_salida); \
        } \
        salida[idx_out++] = (c); \
    } while(0)

    #define APPEND_STR(s) do { \
        size_t slen = strlen(s); \
        while (idx_out + slen + 2 >= capacidad_salida) { \
            capacidad_salida *= 2; \
            salida = (char*)realloc(salida, capacidad_salida); \
        } \
        memcpy(salida + idx_out, (s), slen); \
        idx_out += slen; \
    } while(0)

    while (i < tamano_fuente) {
        char c = codigo_fuente[i];

        if (c == '\n') {
            linea_actual++;
            APPEND_CHAR(c);
            i++;
            continue;
        }

        /* 1. Omitir comentarios de una línea (// ...) */
        if (c == '/' && i + 1 < tamano_fuente && codigo_fuente[i + 1] == '/') {
            while (i < tamano_fuente && codigo_fuente[i] != '\n') {
                APPEND_CHAR(codigo_fuente[i]);
                i++;
            }
            continue;
        }

        /* 2. Omitir comentarios multilínea (/* ... * /) */
        if (c == '/' && i + 1 < tamano_fuente && codigo_fuente[i + 1] == '*') {
            APPEND_CHAR(codigo_fuente[i++]);
            APPEND_CHAR(codigo_fuente[i++]);
            while (i < tamano_fuente) {
                if (codigo_fuente[i] == '\n') linea_actual++;
                if (codigo_fuente[i] == '*' && i + 1 < tamano_fuente && codigo_fuente[i + 1] == '/') {
                    APPEND_CHAR(codigo_fuente[i++]);
                    APPEND_CHAR(codigo_fuente[i++]);
                    break;
                }
                APPEND_CHAR(codigo_fuente[i++]);
            }
            continue;
        }

        /* 3. Omitir literales de cadena de texto ("...") */
        if (c == '"') {
            APPEND_CHAR(codigo_fuente[i++]);
            while (i < tamano_fuente) {
                char sc = codigo_fuente[i];
                if (sc == '\\' && i + 1 < tamano_fuente) {
                    APPEND_CHAR(codigo_fuente[i++]);
                    APPEND_CHAR(codigo_fuente[i++]);
                    continue;
                }
                APPEND_CHAR(sc);
                i++;
                if (sc == '"') break;
            }
            continue;
        }

        /* 4. Omitir literales de carácter ('...') */
        if (c == '\'') {
            APPEND_CHAR(codigo_fuente[i++]);
            while (i < tamano_fuente) {
                char sc = codigo_fuente[i];
                if (sc == '\\' && i + 1 < tamano_fuente) {
                    APPEND_CHAR(codigo_fuente[i++]);
                    APPEND_CHAR(codigo_fuente[i++]);
                    continue;
                }
                APPEND_CHAR(sc);
                i++;
                if (sc == '\'') break;
            }
            continue;
        }

        /* 5. Reconocer Identificadores y Palabras Reservadas ([a-zA-Z_][a-zA-Z0-9_]*) */
        if (isalpha(c) || c == '_') {
            char lexema[128];
            int lex_idx = 0;
            while (i < tamano_fuente && (isalnum(codigo_fuente[i]) || codigo_fuente[i] == '_')) {
                if (lex_idx < 127) {
                    lexema[lex_idx++] = codigo_fuente[i];
                }
                i++;
            }
            lexema[lex_idx] = '\0';

            int kw_idx = buscar_palabra_reservada(lexema);
            if (kw_idx >= 0) {
                /* ¡Palabra reservada encontrada! */
                (*total_reservadas_encontradas)++;
                int con = TABLA_KEYWORDS[kw_idx].conteo;
                if (con < MAX_LINEAS_OCURRENCIA) {
                    TABLA_KEYWORDS[kw_idx].lineas[con] = linea_actual;
                }
                TABLA_KEYWORDS[kw_idx].conteo++;

                /* Escribir traducción al español en el buffer de salida */
                APPEND_STR(TABLA_KEYWORDS[kw_idx].traduccion_es);
            } else {
                /* Identificador común (variables, nombres de función, macros) */
                APPEND_STR(lexema);
            }
            continue;
        }

        /* Cualquier otro carácter (espacios, operadores, puntuación) */
        APPEND_CHAR(c);
        i++;
    }

    salida[idx_out] = '\0';
    return salida;
}

int main(int argc, char* argv[]) {
    const char* ruta_entrada = (argc > 1) ? argv[1] : "ejemplo_entrada.c";
    const char* ruta_salida = (argc > 2) ? argv[2] : "ejemplo_traducido.c";

    printf("======================================================================\n");
    printf("UNIVERSIDAD NACIONAL EXPERIMENTAL DE GUAYANA (UNEG)\n");
    printf("LENGUAJES Y COMPILADORES - PRUEBA DIAGNOSTICA 2026-II\n");
    printf("EJERCICIO 3 (C): DETECCION Y TRADUCCION DE PALABRAS RESERVADAS EN C\n");
    printf("======================================================================\n\n");

    printf("[1] Cargando archivo '%s' en memoria dinamica (Heap)...\n", ruta_entrada);
    long tamano_bytes = 0;
    char* codigo_en_memoria = cargar_archivo_en_memoria_dinamica(ruta_entrada, &tamano_bytes);

    if (!codigo_en_memoria) {
        printf("Error: No se pudo abrir o cargar el archivo '%s'.\n", ruta_entrada);
        return 1;
    }

    printf("    -> Exito: %ld bytes cargados dinamicamente en direccion: %p\n\n", tamano_bytes, (void*)codigo_en_memoria);

    printf("[2] Ejecutando analisis lexico y traduccion de palabras reservadas...\n");
    int total_encontradas = 0;
    char* codigo_traducido = procesar_y_traducir_c(codigo_en_memoria, tamano_bytes, &total_encontradas);

    if (!codigo_traducido) {
        printf("Error: Falla en asignacion de memoria dinamica para traduccion.\n");
        free(codigo_en_memoria);
        return 1;
    }

    /* Mostrar reporte detallado de palabras reservadas detectadas */
    printf("\n======================================================================\n");
    printf("REPORTE DE PALABRAS RESERVADAS ENCONTRADAS\n");
    printf("======================================================================\n");
    printf("%-15s | %-15s | %-8s | %s\n", "PALABRA (C)", "TRADUCCION (ES)", "CANTIDAD", "LINEAS DONDE APARECE");
    printf("----------------------------------------------------------------------\n");

    int tipos_distintos = 0;
    for (int i = 0; i < NUM_KEYWORDS; i++) {
        if (TABLA_KEYWORDS[i].conteo > 0) {
            tipos_distintos++;
            printf("%-15s | %-15s | %-8d | ", 
                   TABLA_KEYWORDS[i].palabra_c, 
                   TABLA_KEYWORDS[i].traduccion_es, 
                   TABLA_KEYWORDS[i].conteo);
            
            int max_print = (TABLA_KEYWORDS[i].conteo < 10) ? TABLA_KEYWORDS[i].conteo : 10;
            for (int k = 0; k < max_print; k++) {
                printf("%d%s", TABLA_KEYWORDS[i].lineas[k], (k == max_print - 1) ? "" : ", ");
            }
            if (TABLA_KEYWORDS[i].conteo > 10) printf("...");
            printf("\n");
        }
    }
    printf("----------------------------------------------------------------------\n");
    printf("Resumen: %d apariciones de palabras reservadas detectadas (%d tipos distintos).\n\n", 
           total_encontradas, tipos_distintos);

    /* Guardar archivo traducido */
    printf("[3] Guardando codigo traducido al espanol en '%s'...\n", ruta_salida);
    FILE* f_out = fopen(ruta_salida, "wb");
    if (f_out) {
        fwrite(codigo_traducido, 1, strlen(codigo_traducido), f_out);
        fclose(f_out);
        printf("    -> Archivo generado exitosamente (%zu bytes).\n", strlen(codigo_traducido));
    } else {
        printf("Error al crear archivo de salida '%s'.\n", ruta_salida);
    }

    /* Mostrar vista previa del código traducido */
    printf("\n======================================================================\n");
    printf("VISTA PREVIA DEL CODIGO TRADUCIDO:\n");
    printf("======================================================================\n");
    printf("%s\n", codigo_traducido);

    /* Liberación estricta de memoria dinámica */
    free(codigo_en_memoria);
    free(codigo_traducido);
    printf("Memoria dinamica liberada correctamente.\n");

    return 0;
}
