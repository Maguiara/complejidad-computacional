# **Complejidad Computacional**

## *Práctica 1: Autómata de pila (por estado final)*

Este proyecto implementa un simulador en C++ para un Autómata a Pila No Determinista (APf) por estados finales. La simulación es capaz de evaluar el reconocimiento de cadenas procesando reglas de transición complejas y bifurcaciones no deterministas mediante un algoritmo de búsqueda en profundidad (DFS).

### *Modo de uso*

#### 1. Compilación

El proyecto utiliza un Makefile para automatizar la compilación. Para compilarlo, ejecute:

```bash
make
```

Si desea borrar los archivos compilados, ejecute:

```bash
make clean
```

#### 2. Ejecución

El proyecto acepta las siguientes flags:

```bash
./build/apf_simulator -config <ruta_archivo_config> [-trace <y/n>] [-in <archivo_entrada>] [-out <archivo_salida>]
```

- **-config** <ruta archivo configuración> (obligatorio): Ruta al archivo .txt con la definicion formal del autómata
- **-trace** <y|n>: Muestra una tabla detallada paso a paso con la cofiguración del autómata y todas las trancisiones aplicadas para aceptar o rechazar una palabra
- **-in** \<ruta> Lee las cadenas a evaluar desde un archivo de entrada en vez de por teclado.
- **-out** \<ruta> Escribe los resultados y la traza en el archivo especificado en vez de por pantalla.

### *Estructuras usadas*

#### Componentes del autómata

1. ***Configuration***

Clase que representa la descripción instantánea del autómata en un momento dado de la forma $C = (q, w, \gamma)$. Almacena el estado actual, la subcadena que falta por leer y el contenido exacto de la pila, datos utilizados en la recursividad del DFS para explorar todas las ramas posibles.

2. ***AutomatonStack***

Clase que representa la pila del autómata. Es un envoltorio a un std::vector\<char> para modelar un comportamiento LIFO. Modela de forma segura el apilado de caracteres en la pila y maneja de forma segura el vaciado de la pila mediante epsilon transiciones.

3. ***Transition***

Clase que modela la transición $\delta(q, a, Z) = (p, \gamma)$. Se encarga de comprobar si una transicion es aplicable a una descripción instantanea.

4. ***StateSet y Alphabet***

Clases responsables de gestionar los conjuntos de estados y los alfabetos del autómata. Aunque en esencia son simples envoltorios sobre un std::set, su separación mejora notablemente la legibilidad del código y su autodocumentación. Al instanciar el motor, el uso de tipos explícitos como:

```C++
Automaton(StateSet estados, Alphabet alfabeto_entrada, StateSet estados_finales, Alphabet alfabeto_pila)
```

hace que la arquitectura sea mucho más limpia e intuitiva que si se agruparan todas estas responsabilidades.

#### El motor

1. ***ApfSimulator***

Clase que se encarga de la centralización de la simulación del autómata. Contiene el algoritmo DFS (ExplorePaths) que permite gestionar el no determinismo abriendo ramas paralelas de ejecución. Si el autómata lee un símbolo que activa múltiples transiciones simultáneas (o saltos épsilon), esta clase las explora recursivamente; si una rama falla (la pila se vacía incorrectamente o no hay transiciones), hace backtracking para probar el siguiente camino válido.

#### Procesamiento de la entrada

1. ***ApfParser***

Clase que se encarga de leer los archivos de configuración proporcionados por el usuario. Se encarga de validar cada linea de la configuración y determinar si las transiciones especificadas en el mismo archivos son válidas para el autómata especificado.

2. ***tools***

Archivo que contiene las funciones encargadas de procesar la entrada por teclado del usuario. Aisla la lectura desde la terminal (argc y argv) y delega el manejo de las flags del programa
