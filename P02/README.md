# **Complejidad Computacional**

## *Práctica 2: Máquina de Turing multicinta*

Este proyecto implementa un simulador en C++ para una Máquina de Turing Determinista multicinta. La simulación permite evaluar cadenas de entrada y realizar transformaciones sobre las cintas mediante reglas de transición que especifican los símbolos leídos, los símbolos escritos y los movimientos de cada cabeza.

La máquina se detiene cuando no existe una transición aplicable. En ese momento, la cadena se acepta si el estado actual pertenece al conjunto de estados finales; en caso contrario, se rechaza.

### *Modo de uso*

#### 1. Compilación

El proyecto utiliza un Makefile para automatizar la compilación, ejecute:

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

Por ejemplo, para ejecutar las configuraciones incluidas:

```bash
./bin/p02 -config config/Ejemplo1_MT.txt -in entrada/entrada1.txt
./bin/p02 -config config/Ejemplo2_MT.txt -in entrada/entrada2.txt
```

La primera máquina reconoce cadenas binarias con un número impar de ceros. La segunda calcula el doble de un número positivo representado en unario: transforma una entrada de la forma `1^n` en `1^(2n)`.

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

Clase encargada de leer los archivos de configuración y construir la máquina de Turing. Valida los estados, la inclusión del alfabeto de entrada en el de cinta, el símbolo blanco, el número de cintas y el formato de las transiciones. También comprueba que los símbolos y movimientos sean válidos y que no existan dos transiciones con el mismo estado de origen y los mismos símbolos leídos, garantizando el determinismo.

2. ***main.cc***

Archivo que procesa los argumentos de la línea de comandos y gestiona la lectura desde un archivo o desde el teclado. La función `ProcessInput` ejecuta el simulador para cada cadena y muestra el resultado, el estado de parada y el contenido de las cintas.
