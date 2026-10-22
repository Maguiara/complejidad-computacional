# **Complejidad Computacional**

## *Práctica 2: Máquina de Turing multicinta*

Este proyecto implementa un simulador en C++ para una Máquina de Turing Determinista multicinta. La simulación permite evaluar cadenas de entrada y realizar transformaciones sobre las cintas mediante reglas de transición que especifican los símbolos leídos, los símbolos escritos y los movimientos de cada cabeza.

La máquina se detiene cuando no existe una transición aplicable. En ese momento, la cadena se acepta si el estado actual pertenece al conjunto de estados finales; en caso contrario, se rechaza.

### *Variantes elegidas*

- **Escritura y movimiento simultáneos**: cada transición especifica los símbolos que se escriben y el movimiento de cada cabeza en un mismo paso.
- **Movimientos `L`, `R` y `S`**: las cabezas pueden desplazarse a la izquierda, a la derecha o permanecer en su posición.
- **Cintas infinitas en ambas direcciones**: se representan mediante celdas que se almacenan conforme se necesitan, permitiendo posiciones a ambos lados del origen, dentro de los recursos disponibles.

### *Modo de uso*

#### 1. Compilación

El proyecto requiere `g++` con soporte para **C++20**, GNU Make y un entorno de shell compatible con el Makefile, como Linux, WSL o MSYS2. Desde la carpeta `P02`, ejecute:

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
./bin/p02 -config <ruta_archivo_config> [-in <archivo_entrada>]
```

- **-config** \<ruta> (obligatorio): Ruta al archivo de texto con la definición formal de la máquina de Turing.
- **-in** \<ruta> (opcional): Lee las cadenas desde un archivo de entrada, una por línea. Si no se especifica, las cadenas se introducen por teclado hasta finalizar la entrada estándar (`Ctrl+D` en Linux o WSL).

Una línea vacía representa la cadena vacía. Cada cadena debe contener únicamente símbolos del alfabeto de entrada; si se encuentra un símbolo no válido, el programa muestra un error y termina.

Para cada cadena, se muestra si ha sido aceptada o rechazada, el estado en el que se ha detenido la ejecución y el contenido final de todas las cintas. Los corchetes indican la posición de cada cabeza de lectura y escritura.

Para ejecutar las máquinas de los ejercicios del enunciado e introducir cadenas por teclado:

```bash
./bin/p02 -config docs/mt_ejercicio1.txt
./bin/p02 -config docs/mt_ejercicio2.txt
```

También se conservan configuraciones de ejemplo en `config/`: `Ejemplo1_MT.txt` reconoce cadenas binarias con un número impar de ceros y `Ejemplo2_MT.txt` está planteada para duplicar un número positivo en unario. Los archivos `entrada/entrada1.txt` y `entrada/entrada2.txt` corresponden a estos ejemplos, no a los ejercicios del enunciado.

#### 3. Archivo de configuración

El archivo contiene los siguientes elementos, en este orden:

1. Conjunto de estados, separados por espacios.
2. Alfabeto de entrada, con sus símbolos separados por espacios.
3. Alfabeto de cinta, incluyendo el símbolo blanco.
4. Estado inicial.
5. Símbolo blanco.
6. Conjunto de estados finales, separados por espacios.
7. Número de cintas, que debe ser mayor que cero.
8. Transiciones, una por línea.

Se permiten comentarios introducidos por `#` y líneas en blanco, que el analizador ignora. Los símbolos de los alfabetos deben tener un único carácter.

Para una máquina con `k` cintas, cada transición sigue este formato:

```text
estado_origen lectura_1 ... lectura_k estado_destino escritura_1 ... escritura_k movimiento_1 ... movimiento_k
```

Los movimientos permitidos son `L` (izquierda), `R` (derecha) y `S` (sin desplazamiento). Por ejemplo, esta transición de una máquina de dos cintas lee `1` en la primera y `.` en la segunda, escribe `1` en ambas y desplaza las dos cabezas a la derecha:

```text
q0 1 . q1 1 1 R R
```

### *Máquinas de los ejercicios*

El [enunciado](docs/CC_2627_Practica2.pdf) propone las siguientes máquinas. Ambas configuraciones utilizan `.` como símbolo blanco.

#### 1. Reconocimiento del lenguaje

**Configuración:** [docs/mt_ejercicio1.txt](docs/mt_ejercicio1.txt).

Reconoce el lenguaje $L = \{a^n b^m \mid m \geq n,\ n > 0\}$ utilizando una cinta. Marca una `a` como `X`, busca una `b` disponible y la marca como `Y`. Después vuelve a la izquierda y repite el proceso. Cuando todas las `a` están emparejadas, comprueba que solo quedan marcas `Y` o símbolos `b` hasta el blanco final y acepta en `q4`. Si faltan `b` o el orden es incorrecto, se detiene en un estado no final.

| Entrada | Resultado esperado |
| --- | --- |
| `ab` | ACEPTADA |
| `aabb` | ACEPTADA |
| `aabbb` | ACEPTADA |
| `aab` | RECHAZADA |
| `abab` | RECHAZADA |
| Cadena vacía | RECHAZADA |

Por ejemplo, para `aabb`, el programa muestra:

```text
Cadena: aabb
Resultado: ACEPTADA
Estado final de la ejecucion: q4
Cinta 1: XXYY[.]
```

#### 2. Recuento de símbolos

**Configuración:** [docs/mt_ejercicio2.txt](docs/mt_ejercicio2.txt).

Utiliza tres cintas. Recorre la entrada de la primera cinta y acumula un `1` por cada `b` en la segunda y un `1` por cada `a` en la tercera. Después borra la entrada y construye el resultado en la primera cinta: copia primero el contador de `a` hacia la izquierda, deja un blanco separador y copia el de `b` aún más a la izquierda. De esta forma, el resultado se lee como contador de `b`, blanco y contador de `a`. Si falta alguno de los símbolos, escribe `0` para su contador. Termina en `q6` con la cabeza de la primera cinta al principio del resultado.

| Entrada | Contenido final de la primera cinta |
| --- | --- |
| `abbabaabb` | `[1]1111.1111` |
| `aa` | `[0].11` |
| `bb` | `[1]1.0` |
| `abab` | `[1]1.11` |
| Cadena vacía | `[0].0` |

El comportamiento para la cadena vacía es una extensión de esta configuración; el enunciado no especifica expresamente ese caso. Los corchetes de la tabla indican la cabeza, no forman parte del resultado.

**Grafos:** las imágenes de los grafos de ambas máquinas están pendientes de incorporación en `docs/`. Actualmente se incluyen sus definiciones en texto, pero todavía no los archivos gráficos exigidos para la entrega.

### *Validación de las configuraciones*

`Parser` comprueba todos los campos de la definición y todas las líneas de
transiciones antes de construir la máquina. Cada comprobación está separada en
una función: inclusión del alfabeto de entrada en el de cinta, pertenencia del
estado inicial y de todos los estados finales a los estados declarados, validez
del blanco, símbolos de un carácter, número de cintas, formato de las
transiciones, estados de origen y destino, símbolos de lectura y escritura,
movimientos `L/R/S` y determinismo.

La lectura se detiene en el primer error e indica el archivo, la línea física y
el motivo. Los comentarios y las líneas vacías se ignoran como datos, pero se
cuentan para localizar el error. Las transiciones se comprueban hasta el final
del archivo, aunque no sean alcanzables durante una simulación.

El dato que provoca el error se indica entre paréntesis. Por ejemplo:

```text
Error: archivo.txt: linea 22: Simbolo de escritura fuera del alfabeto de cinta (simbolo: 'z').
```

### *Estructuras usadas*

#### Componentes de la máquina

1. ***Tape***

Clase que representa una cinta extensible en ambas direcciones y gestiona la posición de su cabeza. Utiliza un `std::map<long long, char>` para almacenar únicamente las celdas que contienen símbolos distintos del blanco. Las posiciones no almacenadas se interpretan como celdas vacías. Permite cargar la entrada, leer, escribir y desplazar la cabeza.

2. ***Transition***

Clase que modela una transición de la forma $\delta(q, a_1, \ldots, a_k) = (p, b_1, \ldots, b_k, d_1, \ldots, d_k)$. Almacena los estados de origen y destino, junto con los vectores de símbolos leídos, símbolos escritos y movimientos. Comprueba si una transición es aplicable al estado actual y a los símbolos situados bajo las cabezas.

3. ***StateSet y Alphabet***

Clases responsables de gestionar los conjuntos de estados y los alfabetos de la máquina mediante `std::set`. `StateSet` permite comprobar la pertenencia de los estados y validar que los estados finales forman un subconjunto de los estados de la máquina. `Alphabet` gestiona los símbolos y comprueba que las cadenas pertenecen al alfabeto de entrada.

4. ***TuringMachine***

Clase que reúne la definición de la máquina: estados, alfabetos, estado inicial, símbolo blanco, estados finales, número de cintas y transiciones. Proporciona las operaciones necesarias para validar la entrada, identificar estados finales y buscar la transición aplicable al estado y a los símbolos leídos.

#### El motor

1. ***Simulator***

Clase que centraliza la simulación. Antes de procesar cada cadena, reinicia el estado y todas las cintas, carga la entrada únicamente en la primera y deja las demás en blanco. En cada paso, lee los símbolos bajo las cabezas, busca una transición aplicable, escribe los nuevos símbolos, mueve las cabezas y actualiza el estado.

La aceptación se comprueba cuando la máquina se detiene, incluso si ha pasado anteriormente por un estado final. El simulador no establece un límite de pasos ni detecta ciclos, por lo que una máquina que no se detenga mantendrá la ejecución activa.

#### Procesamiento de la entrada

1. ***Parser***

Clase encargada de leer e interpretar los archivos de configuración, aplicar las comprobaciones descritas en la sección de validación y construir la máquina de Turing. Mantiene el número de línea física para localizar los errores.

2. ***main.cc***

Archivo que procesa los argumentos de la línea de comandos y gestiona la lectura desde un archivo o desde el teclado. La función `ProcessInput` ejecuta el simulador para cada cadena y muestra el resultado, el estado de parada y el contenido de las cintas.

### *Pruebas de validación*

Desde la carpeta `P02`, ejecute:

```bash
python3 tests/test_parser.py
```

Se requiere Python 3 y `g++` con C++20. Las pruebas de [tests/test_parser.py](tests/test_parser.py) compilan el programa real en una carpeta temporal y verifican configuraciones válidas e inválidas mediante su interfaz de consola, sin sobrescribir el ejecutable de `bin/`.

Comprueban los campos de la cabecera, los estados y símbolos de las transiciones, los movimientos de cada cinta, el determinismo, los campos ausentes o sobrantes y la localización de errores tras comentarios o líneas vacías, incluida la última transición. También comprueban que las definiciones de ambos ejercicios se cargan correctamente; estas pruebas no verifican los resultados de las simulaciones de las máquinas.
