/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad Computacional
 *
 * @author Marco Aguiar Álvarez
 * @date Sep 23, 2026
 * @brief Declaration of utility tools. Includes command-line parsing to 
 *        extract program options like configuration files and trace mode.
 */

#ifndef TOOLS_H_
#define TOOLS_H_

#include <string>


namespace tools {

// Structure to hold the parsed command line arguments.
struct ProgramOptions {
  std::string config_file;
  bool trace_mode = false;
  std::string input_file;   // Optional
  std::string output_file;  // Optional
};

// Parses argc and argv to extract the program options.
// Throws std::invalid_argument if mandatory flags are missing or malformed.
ProgramOptions ParseCommandLine(int argc, char* argv[]);

}  // namespace tools

#endif  // TOOLS_H_