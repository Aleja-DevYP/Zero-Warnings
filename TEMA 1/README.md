# Tema 1 — Planteamiento 18: Evolución de los Diagramas T, Casos Prácticos de Compilación e Investigaciones Recientes en Arquitecturas de Traducción

**Equipo:** Zero Warnings  
**Docente:** Ing. Félix Márquez, M.Sc.  
**Asignatura:** Lenguajes y Compiladores (UNEG — 2026-II)

---

## Contenido de la carpeta

- **`Informe_Tema1_ZeroWarnings_final.pdf`** — Informe de investigación completo bajo normas APA, incluyendo el desarrollo del Planteamiento 18 y la sección del Reto Evaluado (Sección 7.6).
- **`validador_diagramas_t.py`** — Implementación en Python del *Validador Formal de Acoplamiento para Diagramas T (Tombstone Diagrams)* correspondiente al Reto Evaluado de la Sección 7.6.
- **`enlace_video_drive.txt`** — Registro del enlace de Google Drive del video de defensa integrado del grupo.

## Ejecución del Validador de Diagramas T

Requiere Python 3.10+ (sin dependencias externas):

```bash
python validador_diagramas_t.py
```

Ejecuta la batería determinista de 5 casos de prueba verificando las reglas de Earley y Sturgis (1970):
1. Compilación nativa válida `T(C, x86, x86)` sobre máquina `x86`.
2. Compilador en Python ejecutado mediante pila de intérprete `CPython(Python, x86)` sobre `x86`.
3. Encadenamiento en cascada válido con metacompilador `Yacc -> C -> x86`.
4. Detección de acoplamiento inválido (violación de Regla 1 y Regla 2).
5. Detección de cascada rota (violación de Regla 4).
