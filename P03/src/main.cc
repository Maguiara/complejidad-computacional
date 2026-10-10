/**
 * Universidad de La Laguna
 * Grado en Ingeniería Informática - Complejidad Computacional
 * @author Marco Aguiar Álvarez
 * @since Oct 10, 2026
 * @brief Cálculo de potencia mediante funciones primitivas recursivas.
 */
#include <exception>
#include <iostream>

#include "primitive_recursive.h"
#include "tools.h"

int main(int argc, char* argv[]) {
  try {
    const Options options = ParseArguments(argc, argv);
    PrimitiveRecursive functions;
    const auto result = functions.Power(options.x, options.y);
    std::cout << "Resultado: " << options.x << '^' << options.y
              << " = " << result << '\n'
              << "Numero de llamadas a funciones: " << functions.GetCallCount() << '\n';
  } catch (const std::exception& error) {
    std::cerr << "Error: " << error.what() << '\n'
              << "Uso: " << argv[0] << " -x <natural> -y <natural>\n";
    return 1;
  }
  return 0;
}
