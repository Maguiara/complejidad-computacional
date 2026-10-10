# **Complejidad Computacional**

Repositorio de prácticas de la asignatura **Complejidad Computacional**, del cuarto curso del Grado en Ingeniería Informática de la **Universidad de La Laguna**, durante el curso **2026/2027**.

Las prácticas trasladan a código distintos modelos formales de computación. A través de autómatas de pila, máquinas de Turing y funciones primitivas recursivas, se estudia cómo reconocer lenguajes, representar procesos de cálculo y construir operaciones a partir de funciones básicas.

## *Sobre la asignatura*

La asignatura aborda los fundamentos de la computación: qué problemas pueden resolverse mediante algoritmos, cuáles son sus límites y qué recursos requiere su resolución. En este contexto, los modelos de computación permiten definir con precisión cómo se procesa una entrada, cuándo termina un cálculo y qué significa obtener un resultado o aceptar una cadena.

Los proyectos de este repositorio trabajan estos conceptos mediante implementaciones en **C++**, con un diseño orientado a objetos y ejecución por consola. Cada práctica incluye su enunciado, código fuente y documentación de uso.

## *Prácticas realizadas*

### [Práctica 1: Autómata de pila por estado final](P01/README.md)

Implementación de un simulador de **autómatas de pila no deterministas**, con aceptación por estado final. La definición del autómata se carga desde un archivo de configuración y las cadenas se procesan mediante una búsqueda en profundidad (DFS), explorando las distintas transiciones posibles y realizando backtracking cuando una rama no permite aceptar la entrada.

La práctica trabaja la gestión de la pila, las transiciones épsilon y el no determinismo. Permite introducir cadenas por teclado o desde un archivo, mostrar una traza de ejecución y guardar los resultados en un archivo de salida.

### [Práctica 2: Máquina de Turing multicinta](P02/README.md)

Implementación de un simulador de **máquinas de Turing deterministas multicinta**. Cada transición determina los símbolos que se leen y escriben en las cintas, los movimientos de sus cabezas y el siguiente estado de la máquina.

La entrada se carga en la primera cinta y la simulación continúa hasta que no existe una transición aplicable. Entonces se muestra si la cadena ha sido aceptada, el estado de parada y el contenido final de las cintas. Los ejemplos incluidos permiten reconocer cadenas binarias con un número impar de ceros y calcular el doble de un número representado en unario.

### [Práctica 3: Funciones primitivas recursivas de números naturales](P03/README.md)

Implementación de la función **potencia** a partir de las funciones básicas cero, sucesor y proyección. Sobre ellas se construyen la suma y el producto mediante recursión primitiva, y finalmente la potencia mediante el producto.

La base y el exponente se introducen como parámetros por consola. El programa muestra el resultado y el número de llamadas a las funciones matemáticas, lo que permite observar el trabajo que requiere esta construcción. Incluye validación de argumentos, control de desbordamientos, un límite de profundidad recursiva y pruebas automatizadas.

## *Organización del repositorio*

```text
complejidad-computacional/
├── P01/       # Autómata de pila no determinista
├── P02/       # Máquina de Turing determinista multicinta
├── P03/       # Funciones primitivas recursivas
└── README.md
```

Las prácticas siguen una organización común:

- **docs/**: Enunciado de la práctica y material de apoyo.
- **include/**: Declaraciones de clases y funciones.
- **src/**: Implementación y programa principal.
- **entrada/**: Cadenas de prueba o comandos de ejemplo, según la práctica.
- **bin/** y **obj/**: Ejecutables y archivos objeto generados durante la compilación.
- **Makefile**: Reglas de compilación y limpieza.
- **README.md**: Descripción de la práctica, modo de uso y explicación de sus componentes.

P01 y P02 también incluyen una carpeta **config/** con las definiciones de los autómatas y máquinas. P01 dispone de **salida/** para ejemplos de resultados, y P03 incluye **tests/** para sus pruebas automatizadas.

## *Compilación y ejecución*

Los proyectos utilizan **C++20**, `g++` y GNU Make. Los Makefiles están preparados para un entorno de shell compatible, como Linux, WSL o MSYS2.

Cada práctica se compila de forma independiente desde su carpeta. Por ejemplo:

```bash
cd P03
make
./bin/p03 -x 2 -y 3
```

Para eliminar los archivos compilados de la práctica actual:

```bash
make clean
```

Los argumentos de ejecución y ejemplos específicos se detallan en el README de cada práctica.

## *Autor*

**Marco Aguiar Álvarez** — Grado en Ingeniería Informática, Universidad de La Laguna.
