# GUION TÉCNICO Y ESTRUCTURA DE DEFENSA AUDIOVISUAL (MÁXIMO 5 MINUTOS)
## UNIVERSIDAD NACIONAL EXPERIMENTAL DE GUAYANA (UNEG)
**Asignatura:** Lenguajes y Compiladores  
**Docente:** Msc. Félix Márquez  
**Periodo Lectivo:** 2026-II  
**Ponderación Defensa:** 5% (Total Prueba Diagnóstica: 10%)

---

### RECOMENDACIONES PREVIAS PARA LA GRABACIÓN:
1. **Formato:** Video horizontal (16:9), resolución 1080p o 720p. Prohibido video vertical (shorts/reels).
2. **Cámara y Micrófono:** Es condición indispensable que aparezcas visible (en una esquina o en pantalla completa) y con audio claro durante toda la grabación (OBS Studio, Zoom o grabador de pantalla).
3. **Temporizador:** Monitorea el cronómetro para no exceder los **5:00 minutos**. La estructura a continuación está calibrada para 4 minutos y 30 segundos.

---

### CRONOGRAMA MINUTO A MINUTO

#### [00:00 - 00:30] 1. PRESENTACIÓN FORMAL Y ENCUADRE
> *"Muy buenos días / tardes, profesor Félix Márquez y compañeros. Mi nombre es **Carlos Alejandro Zorrilla Figuera**, titular de la cédula de identidad **V-28.783.889**, estudiante de Ingeniería en Informática de la UNEG, Sección **[Tu Sección]**. Pertenezco al grupo **Zero Warnings**, cuyo eslogan es: **\"0 errores, 0 advertencias, 100% de fe.\"**  
> El día de hoy presento la defensa práctica de la Prueba Diagnóstica de Lenguajes y Compiladores, abordando tres problemas fundamentales: validación léxico-geométrica de movimientos, generación de polinomios con memoria dinámica y análisis léxico de código fuente en C."*

---

#### [00:30 - 01:45] 2. EJERCICIO 1: VALIDADOR DE CABALLO Y BENCHMARK (LENGUAJE C)
*(Mostrar pantalla con la terminal ejecutando `caballo.exe`)*

> *"En el **Ejercicio 1**, considerando que la consigna permitía el lenguaje de preferencia, seleccionamos **Lenguaje C** por su velocidad y control de memoria. Diseñamos un validador que toma la posición inicial $A_k$ y una cadena $C$ de $n$ movimientos en notación ajedrecística 'K + columna + fila'.  
> **Fundamento técnico:** El algoritmo analiza léxicamente cada token: primero verifica que la pieza sea 'K' (detectando errores si aparece otra letra como 'Q'), luego verifica que la casilla esté en el rango de 'a1' a 'h8', y finalmente comprueba la regla de salto en 'L': $|\Delta col| = 1 \land |\Delta fila| = 2$ o viceversa. Al primer fallo, la ejecución se detiene y reporta el movimiento exacto.  
> Como observamos en pantalla, el programa valida al 100% los 9 casos de prueba del enunciado.  
> **Medición de Tiempos:** Para los 500 movimientos completos desde la posición inicial a2 verificados 10 veces consecutivas, en C tomó apenas **0.32 milisegundos**, demostrando una altísima eficiencia de procesamiento. Asimismo, para $n=100$ movimientos, C promedió tan solo **6.16 microsegundos** por verificación gracias a la ejecución en código máquina nativo y memoria contigua."*

---

#### [01:45 - 03:00] 3. EJERCICIO 2: POLINOMIO $(x+1)^n$, MEMORIA DINÁMICA Y COMPARACIÓN $n=100$
*(Mostrar la ejecución de `pascal_polinomio.exe` y el cálculo paso a paso)*

> *"En el **Ejercicio 2**, implementamos la generación de los coeficientes del polinomio $(x+1)^n$ mediante el Triángulo de Pascal utilizando **memoria dinámica**.  
> **Aspecto clave de arquitectura:** Se solicitó memoria dinámica con `malloc()` y `free()`. Además, para $n=100$, el coeficiente central $\binom{100}{50}$ posee 29 dígitos decimales ($1.0089 \times 10^{29}$), desbordando enteros de 64 bits. Para resolver esto en C sin librerías externas, implementamos aritmética con enteros nativos de 128 bits (`unsigned __int128`), permitiendo calcular la fila 100 con total precisión.  
> Mostramos en pantalla el cálculo paso a paso para $x=2, n=3$ obteniendo 27, y para $x=3, n=4$ obteniendo 256, verificando algebraicamente con $(x+1)^n$.  
> **Comparativa de Tiempos para $n=100$:** En C, generar la fila 100 tomó **5.07 microsegundos** promedio, mientras que en Python tomó **538 microsegundos**. C resultó **106 veces más rápido**, debido a que C opera en un bloque de memoria contiguo en el Heap con tipos primitivos de 128 bits, mientras que Python utiliza objetos `PyLongObject` dinámicos con indirección de punteros y recolección de basura."*

---

#### [03:00 - 04:15] 4. EJERCICIO 3: ANÁLISIS LÉXICO Y TRADUCCIÓN DE PALABRAS RESERVADAS EN C
*(Mostrar la ejecución de `traductor_c.exe`, la tabla resumen y el archivo `ejemplo_traducido.c`)*

> *"En el **Ejercicio 3**, implementamos un compilador preliminar / analizador léxico que carga un programa fuente en C en memoria dinámica mediante `malloc()` y busca palabras reservadas para traducirlas a su equivalente en español.  
> **Rigor de Compiladores:** Un simple reemplazo de texto fallaría porque alteraría palabras dentro de cadenas o comentarios, o reemplazaría 'int' dentro de 'printf' o 'point'. Nuestro analizador recorre el código carácter por carácter como un autómata finito: discrimina cadenas literales entre comillas, comentarios de una línea y de bloque, y aísla identificadores reales.  
> En pantalla vemos el reporte: detectó 32 palabras reservadas de 18 tipos distintos con sus líneas exactas (como `int` -> `entero`, `if` -> `si`, `while` -> `mientras`, `return` -> `retornar`), generando el archivo traducido preservando la sintaxis y los nombres de variables intactos."*

---

#### [04:15 - 04:50] 5. CONCLUSIÓN Y CIERRE
> *"En conclusión, esta prueba diagnóstica consolida las bases de Lenguajes y Compiladores: análisis léxico robusto, manejo estricto de memoria dinámica y comprensión de las diferencias de rendimiento entre lenguajes compilados de bajo nivel (C) e interpretados de alto nivel (Python). Todos los códigos fuente, scripts de ejecución por lotes y resultados en archivos txt están debidamente organizados en las tres carpetas requeridas.  
> Muchas gracias por su atención."*
