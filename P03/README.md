# **Complejidad Computacional**

## *Práctica 3: Funciones primitivas recursivas de números naturales*

Este proyecto implementa en C++ la función potencia sobre números naturales mediante funciones primitivas recursivas. A partir de las funciones cero, sucesor y proyección, se construyen la suma, el producto y la potencia utilizando composición y recursión. El programa muestra el resultado y el número de llamadas a estas funciones durante el cálculo.

### *Modo de uso*

#### 1. Compilación

Desde la carpeta `P03`, con `g++` compatible con C++20, GNU Make y un entorno de shell como Linux, WSL o MSYS2:

```bash
make
```

Para compilar con información de depuración y avisos, ejecute `make debug`. Para volver al modo optimizado, ejecute `make release`. Ambos reconstruyen los archivos para aplicar las opciones correspondientes.

Para eliminar los archivos compilados:

```bash
make clean
```

#### 2. Ejecución

```bash
./bin/p03 -x <natural> -y <natural>
```

- **-x** \<natural> (obligatorio): Base de la potencia.
- **-y** \<natural> (obligatorio): Exponente de la potencia.

Las opciones se pueden introducir en cualquier orden. Se aceptan enteros decimales no negativos, incluido el cero. Los argumentos ausentes, repetidos, desconocidos o no válidos producen un error y un código de salida 1.

Ejemplo:

```bash
./bin/p03 -x 2 -y 3
```

```text
Resultado: 2^3 = 8
Numero de llamadas a funciones: 58
```

En `entrada/ejemplos.txt` se incluyen otros comandos de ejemplo. Las entradas se pasan como parámetros al programa; este archivo sirve de referencia y no se lee mediante una opción `-in`.

### *Definición de las funciones*

Se considera $\mathbb{N} = \{0, 1, 2, \ldots\}$. Las funciones básicas son:

- **Cero**: $Z() = 0$. Se usa la constante cero; sus extensiones a cualquier aridad ignoran los argumentos.
- **Sucesor**: $S(x) = x + 1$.
- **Proyección**: $P_i^n(x_1, \ldots, x_n) = x_i$, con índices desde 1.

Las funciones derivadas se definen mediante los siguientes casos base y pasos recursivos:

| Función | Caso base | Paso recursivo |
| --- | --- | --- |
| Suma | $A(x,0) = P_1^1(x)$ | $A(x,y+1) = S(A(x,y))$ |
| Producto | $M(x,0) = Z()$ | $M(x,y+1) = A(M(x,y),x)$ |
| Potencia | $E(x,0) = S(Z())$ | $E(x,y+1) = M(E(x,y),x)$ |

La composición aparece al aplicar el sucesor al resultado de la suma, la suma al resultado del producto y el producto al resultado de la potencia. El parámetro recursivo disminuye en una unidad en cada llamada hasta alcanzar cero. Los pasos se pueden expresar formalmente como funciones de los parámetros originales, el índice de recursión y el resultado anterior, seleccionando los argumentos necesarios mediante proyecciones.

Se adopta $0^0 = 1$, de acuerdo con el caso base de la potencia. El cálculo no utiliza `std::pow`, multiplicación nativa ni suma nativa entre los operandos: únicamente el sucesor incrementa un natural. Las operaciones del contador, los índices y la reducción del parámetro de control son parte de la implementación.

### *Estructuras usadas*

#### El motor

1. ***PrimitiveRecursive***

Clase que implementa `Zero`, `Successor`, `Projection`, `Add`, `Multiply` y `Power`. Centraliza el contador de llamadas y permite consultarlo o reiniciarlo. Los valores naturales se representan mediante `std::uint64_t`.

2. ***CallGuard***

Clase interna que registra cada entrada a una de las seis funciones matemáticas y controla la profundidad de la recursión. Al salir de una llamada, incluso cuando se lanza una excepción, restaura la profundidad activa.

#### Procesamiento de la entrada

1. ***Options y tools***

`Options` almacena la base y el exponente. `ParseArguments`, definida en `tools.cc`, valida las opciones y convierte sus valores mediante `std::from_chars`, comprobando el formato y el rango antes de iniciar el cálculo.

2. ***main.cc***

Procesa los argumentos, crea el motor, calcula la potencia y muestra el resultado y el número de llamadas. Captura los errores de entrada y de ejecución para informar por consola.

### *Conteo de llamadas y límites*

Se cuenta cada invocación a las seis funciones matemáticas, incluidos sus casos base y la llamada inicial a `Power`. No se cuentan el procesamiento de argumentos, la impresión, los constructores, los métodos de consulta ni las operaciones del propio contador. Por ejemplo, una potencia con exponente cero realiza tres llamadas: `Power`, `Zero` y `Successor`.

Los contadores pueden comprobarse con estas recurrencias, donde $C$ denota el número de llamadas de cada operación:

- $C_A(x,y) = 2y + 2$.
- $C_M(x,y) = 2 + y(2x + 3)$.
- $C_E(x,0) = 3$ y $C_E(x,y+1) = 1 + C_E(x,y) + C_M(x^y,x)$.

La representación admite valores hasta `18446744073709551615`. El sucesor detecta desbordamientos; el contador también tiene protección. Se establece un máximo de 1024 llamadas matemáticas simultáneamente activas para evitar agotar la pila. Si se alcanza, se informa de un error sin presentar un resultado parcial como válido.

Estas funciones realizan muchas llamadas incluso para resultados moderados. La representación finita, el límite de profundidad y los recursos de ejecución restringen los casos calculables por el programa; no modifican la definición matemática de la potencia. No se aplican atajos aritméticos que alteren el número de llamadas de las recurrencias descritas.

### *Pruebas*

```bash
make test
```

Las pruebas verifican las funciones básicas, sumas, productos y potencias para una colección de valores pequeños, los casos con cero, el conteo de llamadas de `2^3`, los errores de argumentos, los desbordamientos y la recuperación tras alcanzar el límite de recursión.

### *Organización del proyecto*

```text
P03/
├── docs/       # Enunciado original
├── entrada/    # Comandos de ejemplo
├── include/    # Declaraciones de las clases y herramientas
├── src/        # Implementación y programa principal
├── tests/      # Pruebas de las funciones y argumentos
├── bin/        # Ejecutables generados por make
├── obj/        # Objetos y dependencias generados por make
├── Makefile
└── README.md
```
