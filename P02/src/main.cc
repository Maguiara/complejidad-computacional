
/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad Computacional
 *
 * @author Marco Aguiar Álvarez
 * @since Oct 10, 2026
 * @brief Programa principal del simulador de máquinas de Turing.
 *        Gestiona los argumentos, las cadenas de entrada y
 *        muestra los resultados de las simulaciones.
 */

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "parse.h"
#include "simulator.h"

/**
 * @brief Muestra el modo de uso del programa.
 * @param program_name Nombre del ejecutable.
 */
void PrintUsage(const std::string& program_name) {
  std::cerr << "Uso: " << program_name
            << " -config <archivo> [-in <archivo>]\n";
}

/**
 * @brief Procesa las cadenas de entrada y muestra sus resultados.
 * @param input Flujo del que se leen las cadenas.
 * @param simulator Simulador de la máquina de Turing.
 */
void ProcessInput(std::istream& input, Simulator& simulator) {
  std::string word;

  while (std::getline(input, word)) {
    // Eliminamos el retorno de carro de archivos Windows.
    if (!word.empty() && word.back() == '\r') {
      word.pop_back();
    }

    bool accepted = simulator.Run(word);

    std::cout << "\nCadena: " << word << '\n';
    std::cout << "Resultado: "
              << (accepted ? "ACEPTADA" : "RECHAZADA") << '\n';

    std::cout << "Estado final de la ejecucion: "
              << simulator.GetCurrentState() << '\n';

    std::vector<std::string> tapes =
        simulator.GetTapeContents();

    for (size_t i = 0; i < tapes.size(); ++i) {
      std::cout << "Cinta " << i + 1 << ": "
                << tapes[i] << '\n';
    }
  }
}

/**
 * @brief Punto de entrada del simulador.
 * @param argc Número de argumentos.
 * @param argv Vector de argumentos.
 * @return 0 si la ejecución termina correctamente, 1 si hay errores.
 */
int main(int argc, char* argv[]) {
  std::string config_filename;
  std::string input_filename;

  // Procesamos los argumentos de la línea de comandos.
  for (int i = 1; i < argc; ++i) {
    std::string argument = argv[i];

    if (argument == "-config" && i + 1 < argc) {
      config_filename = argv[++i];
    } else if (argument == "-in" && i + 1 < argc) {
      input_filename = argv[++i];
    } else {
      PrintUsage(argv[0]);
      return 1;
    }
  }

  // El archivo de configuración es obligatorio.
  if (config_filename.empty()) {
    PrintUsage(argv[0]);
    return 1;
  }

  try {
    // Construimos la máquina a partir del archivo de configuración.
    TuringMachine machine = Parser::Parse(config_filename);

    // Creamos el simulador.
    Simulator simulator(machine);

    if (!input_filename.empty()) {
      // Leemos las cadenas desde un archivo.
      std::ifstream input_file(input_filename);

      if (!input_file.is_open()) {
        throw std::runtime_error(
            "No se pudo abrir el archivo: " + input_filename);
      }

      ProcessInput(input_file, simulator);
    } else {
      // Leemos las cadenas desde la entrada estándar.
      std::cout << "Introduce las cadenas (Ctrl+D para terminar):\n";
      ProcessInput(std::cin, simulator);
    }

  } catch (const std::exception& error) {
    std::cerr << "Error: " << error.what() << '\n';
    return 1;
  }

  return 0;
}
