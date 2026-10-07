/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad Computacional
 *
 * @author Marco Aguiar Álvarez
 * @date Sep 23, 2026
 * @brief Entry point for the Pushdown Automaton simulator.
 */

#include <iostream>
#include <fstream>
#include <string>

#include "tools.h"
#include "parse.h"
#include "apf_simulator.h"


int main(int argc, char* argv[]) {
  try {
    // Primero parseamos las opciones de línea de comandos
    tools::ProgramOptions options = tools::ParseCommandLine(argc, argv);
    
    // Segundo parseamos el archivo de configuración para construir el simulador
    ApfSimulator simulator = ApfParser::Parse(options.config_file);

    // Tercero configuramos el flujo de entrada (archivo o consola)
    std::istream* input_stream = &std::cin;
    std::ifstream file_in;
    if (!options.input_file.empty()) {
      file_in.open(options.input_file);
      if (!file_in.is_open()) {
        throw std::runtime_error("Cannot open input file: " + options.input_file);
      }
      input_stream = &file_in;
    }

    //Cuarto configuramos el flujo de salida (archivo o consola)
    std::ostream* output_stream = &std::cout;
    std::ofstream file_out;
    if (!options.output_file.empty()) {
      file_out.open(options.output_file);
      // if (!file_out.is_open()) {
      //   throw std::runtime_error("Cannot open output file: " + options.output_file);
      // }
      output_stream = &file_out;
    }

    // Quinto leemos las palabras y simulamos
    std::string word;
    while (*input_stream >> word) { 
      if (options.trace_mode) {
        *output_stream << "Comprobando: " << word << "\n";
      }
      
      bool accepted = simulator.IsAccepted(word, options.trace_mode, *output_stream);
      
      *output_stream << word << " --- " << (accepted ? "Aceptado" : "Rechazado") << "\n\n";
    }

  } catch (const std::exception& e) {
    // Manejo de errores: mostramos el mensaje de error y terminamos con un código de error
    std::cerr << "Execution Error: " << e.what() << '\n';
    return 1;
  }

  return 0;
}