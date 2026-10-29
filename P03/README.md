# **Complejidad Computacional**

## *Práctica 3: Funciones primitivas recursivas de números naturales*

Este proyecto implementa un programa en C++ que calcula la función `potencia(x, y)` como una función primitiva recursiva de números naturales. La función se construye únicamente a partir de las funciones recursivas básicas y de las operaciones de composición y recursión primitiva, sin utilizar operadores aritméticos para el cálculo.

El programa recibe la base y el exponente como parámetros y muestra el resultado de la operación junto con el número de llamadas a funciones realizadas durante el cálculo.

### *Criterio de conteo de llamadas*

- **Una llamada por evaluación**: se cuenta una llamada cada vez que se evalúa una función, ya sea básica (`Z`, `S`, `P`), compuesta o definida por recursión primitiva.
- **Pasos recursivos**: cada paso recursivo `f(x, y-1)` se contabiliza como una evaluación más de `f`.
- **Proyecciones del esquema formal**: las proyecciones que intervienen en la composición de cada paso recursivo también se cuentan.

El coste de cada función, con `a` y `b` los argumentos de `suma` y `producto`, es:

- `suma(a, b)`: $2 + 4b$ llamadas.
- `producto(a, b)`: $2 + b(6 + 4a)$ llamadas.
- `potencia(x, y)`: $4 + y(6 + 6x) + 4(x + x^2 + \ldots + x^y)$ llamadas.

Por ejemplo, para `2^3` se realizan $4 + 3 \cdot 18 + 4 \cdot (2 + 4 + 8) = 114$ llamadas.

### *Modo de uso*

#### 1. Compilación

El proyecto requiere `g++` con soporte para **C++17** y CMake 3.16 o superior. Desde la carpeta `practica3`, ejecute:

```bash
make
```

Si desea borrar los archivos compilados, ejecute lo siguiente:

```bash
make clean
```

#### 2. Ejecución

El proyecto acepta las siguientes flags:

```bash
./build/potencia -x <natural> -y <natural>
```

- **-x** \<n> (obligatorio): Valor natural que será la base de la potencia.
- **-y** \<n> (obligatorio): Valor natural que será el exponente de la potencia.

Las dos opciones pueden indicarse en cualquier orden, pero no pueden repetirse. Cada valor debe estar formado únicamente por dígitos y caber en un `uint64_t`; en caso contrario, el programa muestra un error y termina con código `1`.

Para cada ejecución, se muestra el resultado de la operación y el número de llamadas a funciones realizadas. Por ejemplo, para `2^3`, el programa muestra:

```text
Resultado: 2^3 = 8
Numero de llamadas a funciones: 114
```

Algunos resultados de ejemplo:

| Entrada | Resultado | Llamadas |
| --- | --- | --- |
| `-x 2 -y 3` | `8` | 114 |
| `-x 3 -y 4` | `81` | 580 |
| `-x 2 -y 10` | `1024` | 8368 |
| `-x 5 -y 1` | `5` | 60 |
| `-x 0 -y 5` | `0` | 34 |
| `-x 7 -y 0` | `1` | 4 |

Por definición de la función, `x^0 = 1` para cualquier `x`, incluido `0^0 = 1`.

Como las funciones se evalúan de forma recursiva, la profundidad de las llamadas crece con el valor de los operandos. Se limita a 1024 niveles para no agotar la pila de ejecución; por ejemplo, `2^10` se calcula correctamente y `2^12` informa de que se ha alcanzado el límite. Si el resultado o el contador de llamadas no caben en un `uint64_t`, el programa muestra un error de desbordamiento.

### *Definición de las funciones*

La función `potencia` se obtiene a partir de `suma` y `producto`, que a su vez se definen con las funciones básicas $Z(x) = 0$, $S(x) = x + 1$ y $P_i^n(x_1, \ldots, x_n) = x_i$:

```text
suma(x, 0)       = P_1^1(x)
suma(x, y+1)     = S(P_3^3(x, y, suma(x, y)))

producto(x, 0)   = Z(x)
producto(x, y+1) = suma(P_3^3(x, y, producto(x, y)), P_1^3(x, y, producto(x, y)))

potencia(x, 0)   = S(Z(x))
potencia(x, y+1) = producto(P_3^3(x, y, potencia(x, y)), P_1^3(x, y, potencia(x, y)))
```

En cada paso recursivo, la función `h` es una composición de proyecciones con la función previamente definida, de modo que ninguna se calcula directamente con operadores del lenguaje.

### *Validación de los parámetros*

`ParseArguments` comprueba todas las opciones de la línea de comandos antes de ejecutar el cálculo. Cada comprobación detecta un caso distinto: opción desconocida, opción repetida, valor ausente, valor que no es un número natural, valor que excede el rango de `uint64_t` y ausencia de `-x` o de `-y`.

La lectura se detiene en el primer error, que se muestra por la salida de error junto con el modo de uso. El dato que provoca el error se indica en el propio mensaje. Por ejemplo:

```text
Error: El valor de -y debe ser un numero natural.
Uso: ./build/potencia -x <natural> -y <natural>
```

### *Estructuras usadas*

#### Componentes de las funciones

1. ***Function***

Clase base abstracta que representa una función $f: \mathbb{N}^k \to \mathbb{N}$. Almacena su aridad y una referencia al contador de llamadas. Su operador `operator()` comprueba que el número de argumentos coincide con la aridad, registra la llamada y delega el cálculo en el método virtual `Compute`, que implementa cada subclase.

2. ***Zero, Successor y Projection***

Clases que modelan las funciones recursivas básicas. `Zero` devuelve siempre `0`, `Successor` devuelve el siguiente natural y lanza un error de desbordamiento si el valor no puede incrementarse, y `Projection` devuelve el argumento situado en la posición `i` de una función de aridad `n`, comprobando que el índice es válido al construirse.

3. ***Composition***

Clase que modela la operación de composición $f(x_1, \ldots, x_n) = h(g_1(x_1, \ldots, x_n), \ldots, g_m(x_1, \ldots, x_n))$. Almacena la función exterior `h` y los vectores de funciones interiores `g_i`. Comprueba al construirse que la aridad de `h` coincide con el número de funciones interiores y que todas las `g_i` tienen la misma aridad.

4. ***PrimitiveRecursion***

Clase que modela la recursión primitiva a partir de una función base `g` y una función de paso `h`. Comprueba que la aridad de `h` es la de `g` más dos. Para evaluar `f(x, y+1)`, se evalúa recursivamente `f(x, y)` y su resultado se pasa a `h` junto con `x` e `y`.

#### El motor

1. ***PrimitiveRecursive***

Clase que centraliza la construcción de las funciones del enunciado. En su constructor crea `Zero` y `Successor`, y a partir de ellas define `suma`, `producto` y `potencia` mediante objetos `Composition` y `PrimitiveRecursion`. Expone los métodos `Add`, `Multiply` y `Power`, junto con `GetCallCount` y `ResetCallCount`.

2. ***CallCounter***

Clase que acumula el número de llamadas realizadas por todas las funciones, que lo comparten. Su clase interna `Scope` registra cada llamada al crearse y libera su nivel de profundidad al destruirse, lo que permite limitar la profundidad de la recursión sin agotar la pila de ejecución.

#### Procesamiento de la entrada

1. ***tools***

Módulo que define la estructura `Options` y la función `ParseArguments`, encargada de leer y validar las opciones `-x` e `-y` aplicando las comprobaciones descritas en la sección de validación.

2. ***main.cc***

Archivo que procesa los argumentos de la línea de comandos, ejecuta `Power` y muestra el resultado y el número de llamadas a funciones. Si se produce cualquier error, lo muestra junto con el modo de uso y termina con código `1`.
