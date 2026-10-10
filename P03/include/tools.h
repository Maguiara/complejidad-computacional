/** @brief Procesamiento de los parámetros naturales de la práctica 3. */
#ifndef TOOLS_H_
#define TOOLS_H_

#include "primitive_recursive.h"

struct Options {
  PrimitiveRecursive::Natural x = 0;
  PrimitiveRecursive::Natural y = 0;
};

Options ParseArguments(int argc, char* argv[]);

#endif  // TOOLS_H_
