#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    const char *ingles;
    const char *espanol;
} PalabraReservada;

static const PalabraReservada DICCIONARIO[] = {
    {"auto", "auto"}, {"break", "romper"}, {"case", "caso"}, {"char", "caracter"},
    {"const", "constante"}, {"continue", "continuar"}, {"default", "defecto"},
    {"do", "hacer"}, {"double", "doble"}, {"else", "sino"}, {"enum", "enumeracion"},
    {"extern", "externo"}, {"float", "flotante"}, {"for", "para"}, {"goto", "ir_a"},
    {"if", "si"}, {"int", "entero"}, {"long", "largo"}, {"register", "registro"},
    {"return", "retornar"}, {"short", "corto"}, {"signed", "con_signo"},
    {"sizeof", "tamano_de"}, {"static", "estatico"}, {"struct", "estructura"},
    {"switch", "segun"}, {"typedef", "definir_tipo"}, {"union", "union"},
    {"unsigned", "sin_signo"}, {"void", "vacio"}, {"volatile", "volatil"}, {"while", "mientras"}
};

#define NUM_PALABRAS (sizeof(DICCIONARIO) / sizeof(PalabraReservada))

const char* traducir_word(const char *word) {
    for (size_t i = 0; i < NUM_PALABRAS; i++) {
        if (strcmp(word, DICCIONARIO[i].ingles) == 0) {
            return DICCIONARIO[i].espanol;
        }
    }
    return word;
}

void traducir_codigo_c(const char *codigo_fuente) {
    size_t len = strlen(codigo_fuente);
    char *buffer_in = (char *)malloc((len + 1) * sizeof(char));
    strcpy(buffer_in, codigo_fuente);

    char *buffer_out = (char *)malloc((len * 3 + 1) * sizeof(char));
    buffer_out[0] = '\0';

    size_t i = 0;
    while (i < len) {
        if (isalpha(buffer_in[i]) || buffer_in[i] == '_') {
            char temp[128];
            size_t t_idx = 0;
            while (i < len && (isalnum(buffer_in[i]) || buffer_in[i] == '_')) {
                temp[t_idx++] = buffer_in[i++];
            }
            temp[t_idx] = '\0';
            strcat(buffer_out, traducir_word(temp));
        } else {
            char token_str[2] = {buffer_in[i++], '\0'};
            strcat(buffer_out, token_str);
        }
    }

    printf("--- Codigo Traducido a Espanol ---\n%s\n", buffer_out);

    free(buffer_in);
    free(buffer_out);
}

int main() {
    const char *codigo_ejemplo = 
        "int main() {\n"
        "    int a = 10;\n"
        "    if (a > 5) {\n"
        "        return a;\n"
        "    } else {\n"
        "        while (a > 0) {\n"
        "            a--;\n"
        "        }\n"
        "    }\n"
        "    void *ptr = NULL;\n"
        "    return 0;\n"
        "}";

    traducir_codigo_c(codigo_ejemplo);
    return 0;
}