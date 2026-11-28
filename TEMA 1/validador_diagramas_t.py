"""
Validador Formal de Acoplamiento para Diagramas T (Tombstone Diagrams)
Reto Evaluado - Sección 7.6: Compilación Asistida por IA y LLMs
Asignatura: Lenguajes y Compiladores (UNEG)
"""

from dataclasses import dataclass, field
from typing import List, Optional, Tuple


@dataclass(frozen=True)
class Programa:
    """Representa un programa o especificación escrita en un lenguaje dado."""
    nombre: str
    lenguaje: str


@dataclass(frozen=True)
class CompiladorT:
    """Representa un traductor T(S, O, I): Fuente, Objetivo, Implementación."""
    nombre: str
    fuente: str          # S (Source)
    objetivo: str        # O (Object)
    implementacion: str  # I (Implementation)


@dataclass(frozen=True)
class Interprete:
    """Representa un intérprete que ejecuta lenguaje L y está implementado en I."""
    nombre: str
    lenguaje_aceptado: str  # L
    implementacion: str     # I


@dataclass(frozen=True)
class Maquina:
    """Representa una máquina física terminal que ejecuta lenguaje M."""
    arquitectura: str  # M


@dataclass
class ResultadoValidacion:
    valido: bool
    errores: List[str] = field(default_factory=list)
    programa_salida: Optional[Programa] = None


def verificar_soporte_ejecucion(
    lenguaje_impl: str,
    maquina: Maquina,
    pila_interpretes: Optional[List[Interprete]] = None
) -> Tuple[bool, Optional[str]]:
    """
    Regla 1 (Ejecución sobre máquina):
    Verifica si un componente implementado en `lenguaje_impl` puede ejecutarse
    directamente sobre `maquina` (I == M) o mediante una pila válida de
    intérpretes/máquinas virtuales apoyada sobre `maquina`.
    """
    capa_actual = lenguaje_impl
    pila = pila_interpretes or []

    for interprete in pila:
        if capa_actual != interprete.lenguaje_aceptado:
            return (
                False,
                f"Regla 1 violada en intérprete '{interprete.nombre}': "
                f"se intenta ejecutar '{capa_actual}', pero solo acepta '{interprete.lenguaje_aceptado}'."
            )
        capa_actual = interprete.implementacion

    if capa_actual != maquina.arquitectura:
        return (
            False,
            f"Regla 1 violada (Ejecución): la implementación '{capa_actual}' "
            f"no coincide con la arquitectura de la máquina '{maquina.arquitectura}'."
        )

    return True, None


def validar_cadena_diagrama_t(
    programa_entrada: Programa,
    compiladores: List[CompiladorT],
    maquina: Maquina,
    pila_interpretes: Optional[List[Interprete]] = None
) -> ResultadoValidacion:
    """
    Valida una cadena de compilación (uno o más Diagramas T en cascada)
    verificando las reglas formales de acoplamiento:
      - Regla 1: Ejecución sobre máquina o pila de intérpretes (I == M).
      - Regla 2: Entrada de código fuente (Lenguaje del programa == S).
      - Regla 3 y 4: Salida y encadenamiento en cascada (O_i == S_{i+1}).
    """
    errores: List[str] = []

    if not compiladores:
        return ResultadoValidacion(False, ["No se proporcionó ningún compilador en la cadena."])

    lenguaje_actual = programa_entrada.lenguaje

    for idx, comp in enumerate(compiladores):
        # Verificación de Regla 1: soporte de ejecución para el compilador actual
        ok_ejecucion, err_ejecucion = verificar_soporte_ejecucion(
            comp.implementacion, maquina, pila_interpretes
        )
        if not ok_ejecucion and err_ejecucion:
            errores.append(f"[Paso {idx + 1} - {comp.nombre}] {err_ejecucion}")

        # Verificación de Regla 2 (primer paso) o Regla 4 (encadenamiento en cascada)
        if lenguaje_actual != comp.fuente:
            if idx == 0:
                errores.append(
                    f"[Paso 1 - {comp.nombre}] Regla 2 violada (Entrada): "
                    f"el programa '{programa_entrada.nombre}' está en '{lenguaje_actual}', "
                    f"pero el compilador exige '{comp.fuente}'."
                )
            else:
                errores.append(
                    f"[Paso {idx + 1} - {comp.nombre}] Regla 4 violada (Cascada): "
                    f"la salida del paso anterior es '{lenguaje_actual}', "
                    f"pero '{comp.nombre}' exige entrada '{comp.fuente}'."
                )

        # La salida de esta etapa pasa a ser el lenguaje disponible para la siguiente
        lenguaje_actual = comp.objetivo

    if errores:
        return ResultadoValidacion(valido=False, errores=errores, programa_salida=None)

    salida = Programa(
        nombre=f"{programa_entrada.nombre}_compilado",
        lenguaje=lenguaje_actual
    )
    return ResultadoValidacion(valido=True, errores=[], programa_salida=salida)


def ejecutar_pruebas() -> None:
    """Suite de verificación determinista con 5 escenarios de prueba."""
    maquina_x86 = Maquina("x86")

    casos = [
        (
            "Caso 1: Compilación nativa válida T(C, x86, x86)",
            Programa("app.c", "C"),
            [CompiladorT("GCC_x86", "C", "x86", "x86")],
            maquina_x86,
            None,
            True,
        ),
        (
            "Caso 2: Compilador ejecutado mediante intérprete Python sobre x86",
            Programa("app.c", "C"),
            [CompiladorT("MiniCC_Py", "C", "x86", "Python")],
            maquina_x86,
            [Interprete("CPython", "Python", "x86")],
            True,
        ),
        (
            "Caso 3: Encadenamiento en cascada válido (Metacompilador Yacc -> C -> x86)",
            Programa("gramatica.y", "Yacc"),
            [
                CompiladorT("Yacc_bin", "Yacc", "C", "x86"),
                CompiladorT("GCC_x86", "C", "x86", "x86"),
            ],
            maquina_x86,
            None,
            True,
        ),
        (
            "Caso 4: Acoplamiento inválido (viola Regla 1 y Regla 2)",
            Programa("programa.pas", "Pascal"),
            [CompiladorT("GCC_ARM", "C", "x86", "ARM")],
            maquina_x86,
            None,
            False,
        ),
        (
            "Caso 5: Cascada rota (viola Regla 4: O1 != S2)",
            Programa("programa.pas", "Pascal"),
            [
                CompiladorT("P2C", "Pascal", "C", "x86"),
                CompiladorT("RustC_x86", "Rust", "x86", "x86"),
            ],
            maquina_x86,
            None,
            False,
        ),
    ]

    print("=" * 72)
    print("RESULTADOS DE VALIDACIÓN DE DIAGRAMAS T (RETO 7.6)")
    print("=" * 72)

    aprobadas = 0
    for titulo, prog, comps, maq, interp, esperado in casos:
        res = validar_cadena_diagrama_t(prog, comps, maq, interp)
        assert res.valido == esperado, f"Fallo en {titulo}: se esperaba {esperado}, dio {res.valido}"
        aprobadas += 1

        estado = "VÁLIDO" if res.valido else "INVÁLIDO (detectado correctamente)"
        print(f"\n> {titulo}")
        print(f"  Estado: {estado}")
        if res.valido and res.programa_salida:
            print(f"  Salida generada: {res.programa_salida.nombre} [{res.programa_salida.lenguaje}]")
        else:
            for err in res.errores:
                print(f"  - {err}")

    print("\n" + "=" * 72)
    print(f"Resumen: {aprobadas}/{len(casos)} pruebas deterministas superadas con éxito.")
    print("=" * 72)


if __name__ == "__main__":
    ejecutar_pruebas()