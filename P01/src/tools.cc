/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad Computacional
 *
 * @author Marco Aguiar Álvarez
 * @date Sep 23, 2026
 * @brief Implementation of command-line parsing utilities.
 */

#include "tools.h"

#include <stdexcept>
#include <vector>

namespace tools {

/**
 * @brief Parsea los argumentos de la línea de comandos y devuelve las opciones del programa.
 * @param argc Número de argumentos.
 * @param argv vector de argumentos.
 * @return Estructura ProgramOptions con las opciones del programa.
 */
ProgramOptions ParseCommandLine(int argc, char* argv[]) {
  ProgramOptions options;
  std::vector<std::string> args(argv + 1, argv + argc);

  for (size_t i = 0; i < args.size(); ++i) {
    if (args[i] == "-config" && i + 1 < args.size()) {
      options.config_file = args[++i];
    } else if (args[i] == "-trace" && i + 1 < args.size()) {
      std::string trace_val = args[++i];
      if (trace_val == "y") {
        options.trace_mode = true;
      } else if (trace_val == "n") {
        options.trace_mode = false;
      } else {
        throw std::invalid_argument("Flag -trace must be followed by 'y' or 'n'.");
      }
    } else if (args[i] == "-in" && i + 1 < args.size()) {
      options.input_file = args[++i];
    } else if (args[i] == "-out" && i + 1 < args.size()) {
      options.output_file = args[++i];
    } else {
      throw std::invalid_argument("Unknown or incomplete flag: " + args[i]);
    }
  }

  if (options.config_file.empty()) {
    throw std::invalid_argument("Mandatory flag -config <file> is missing.");
  }

  return options;
}

}  // namespace tools