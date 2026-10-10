
/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad Computacional
 *
 * @author Marco Aguiar Álvarez
 * @since Oct 10, 2026
 * @brief Implementación de la clase Parser. Extrae y valida los
 *        elementos necesarios para construir una máquina de Turing.
 */

#include "parse.h"

#include <limits>
#include <sstream>
#include <stdexcept>

/**
 * @brief Lee la siguiente línea válida, ignorando comentarios y espacios.
 * @param file Archivo de entrada.
 * @param line Línea leída.
 * @return true si existe una línea válida, false si termina el archivo.
 */
bool Parser::GetNextValidLine(std::ifstream& file, std::string& line) {
  while (std::getline(file, line)) {
    size_t comment_position = line.find('#');
    if (comment_position != std::string::npos) {
      line = line.substr(0, comment_position);
    }

    if (line.find_first_not_of(" \t\r\n") == std::string::npos) {
      continue;
    }

    return true;
  }

  return false;
}

/**
 * @brief Lee el conjunto de estados.
 * @param file Archivo de entrada.
 * @return Conjunto de estados.
 */
StateSet Parser::ReadStates(std::ifstream& file) {
  std::string line, token;
  StateSet states;

  if (!GetNextValidLine(file, line)) {
    throw std::runtime_error("Falta el conjunto de estados.");
  }

  std::istringstream iss(line);
  while (iss >> token) {
    states.Add(token);
  }

  if (states.IsEmpty()) {
    throw std::runtime_error("El conjunto de estados esta vacio.");
  }

  return states;
}

/**
 * @brief Lee un alfabeto del archivo.
 * @param file Archivo de entrada.
 * @param error_msg Mensaje de error si falta el alfabeto.
 * @return Alfabeto leído.
 */
Alphabet Parser::ReadAlphabet(
    std::ifstream& file, const std::string& error_msg) {
  std::string line, token;
  Alphabet alphabet;

  if (!GetNextValidLine(file, line)) {
    throw std::runtime_error(error_msg);
  }

  std::istringstream iss(line);
  while (iss >> token) {
    if (token.size() != 1) {
      throw std::runtime_error(
          "Los simbolos del alfabeto deben tener un caracter.");
    }

    alphabet.Add(token[0]);
  }

  return alphabet;
}

/**
 * @brief Lee y valida el estado inicial.
 * @param file Archivo de entrada.
 * @param states Conjunto de estados válidos.
 * @return Estado inicial.
 */
std::string Parser::ReadInitialState(
    std::ifstream& file, const StateSet& states) {
  std::string line, initial_state, extra;

  if (!GetNextValidLine(file, line)) {
    throw std::runtime_error("Falta el estado inicial.");
  }

  std::istringstream iss(line);
  if (!(iss >> initial_state) || (iss >> extra)) {
    throw std::runtime_error("Formato del estado inicial no valido.");
  }

  if (!states.Contains(initial_state)) {
    throw std::runtime_error(
        "El estado inicial no pertenece al conjunto de estados.");
  }

  return initial_state;
}

/**
 * @brief Lee y valida el símbolo blanco.
 * @param file Archivo de entrada.
 * @param input_alphabet Alfabeto de entrada.
 * @param tape_alphabet Alfabeto de cinta.
 * @return Símbolo blanco.
 */
char Parser::ReadBlankSymbol(
    std::ifstream& file,
    const Alphabet& input_alphabet,
    const Alphabet& tape_alphabet) {
  std::string line, token, extra;

  if (!GetNextValidLine(file, line)) {
    throw std::runtime_error("Falta el simbolo blanco.");
  }

  std::istringstream iss(line);
  if (!(iss >> token) || (iss >> extra) || token.size() != 1) {
    throw std::runtime_error("Simbolo blanco no valido.");
  }

  char blank_symbol = token[0];

  if (!tape_alphabet.Contains(blank_symbol)) {
    throw std::runtime_error(
        "El simbolo blanco no pertenece al alfabeto de cinta.");
  }

  if (input_alphabet.Contains(blank_symbol)) {
    throw std::runtime_error(
        "El simbolo blanco no puede pertenecer al alfabeto de entrada.");
  }

  return blank_symbol;
}

/**
 * @brief Lee y valida los estados finales.
 * @param file Archivo de entrada.
 * @param states Conjunto de estados válidos.
 * @return Conjunto de estados finales.
 */
StateSet Parser::ReadFinalStates(
    std::ifstream& file, const StateSet& states) {
  std::string line, token;
  StateSet final_states;

  if (!GetNextValidLine(file, line)) {
    throw std::runtime_error("Faltan los estados finales.");
  }

  std::istringstream iss(line);
  while (iss >> token) {
    final_states.Add(token);
  }

  states.CheckIfFinalStatesAreSubsetOfStates(final_states);

  return final_states;
}

/**
 * @brief Lee y valida el número de cintas.
 * @param file Archivo de entrada.
 * @return Número de cintas.
 */
size_t Parser::ReadTapeCount(std::ifstream& file) {
  std::string line, token, extra;

  if (!GetNextValidLine(file, line)) {
    throw std::runtime_error("Falta el numero de cintas.");
  }

  std::istringstream iss(line);
  if (!(iss >> token) || (iss >> extra) ||
      token.empty() || token[0] == '-') {
    throw std::runtime_error("Numero de cintas no valido.");
  }

  try {
    size_t processed = 0;
    unsigned long long count = std::stoull(token, &processed);

    if (processed != token.size() || count == 0 ||
        count > std::numeric_limits<size_t>::max()) {
      throw std::runtime_error("Numero de cintas no valido.");
    }

    return static_cast<size_t>(count);
  } catch (const std::invalid_argument&) {
    throw std::runtime_error("Numero de cintas no valido.");
  } catch (const std::out_of_range&) {
    throw std::runtime_error("Numero de cintas fuera de rango.");
  }
}

/**
 * @brief Valida una transición de la máquina de Turing.
 * @param transition Transición que se desea comprobar.
 * @param states Conjunto de estados válidos.
 * @param tape_alphabet Alfabeto de cinta.
 * @param tape_count Número de cintas.
 * @param transitions Transiciones anteriores.
 */
void Parser::ValidateTransition(
    const Transition& transition,
    const StateSet& states,
    const Alphabet& tape_alphabet,
    size_t tape_count,
    const std::vector<Transition>& transitions) {
  if (!states.Contains(transition.GetSourceState()) ||
      !states.Contains(transition.GetDestinationState())) {
    throw std::runtime_error(
        "Una transicion contiene estados no validos.");
  }

  if (transition.GetReadSymbols().size() != tape_count ||
      transition.GetWriteSymbols().size() != tape_count ||
      transition.GetMovements().size() != tape_count) {
    throw std::runtime_error(
        "Los elementos de la transicion no coinciden con las cintas.");
  }

  for (char symbol : transition.GetReadSymbols()) {
    if (!tape_alphabet.Contains(symbol)) {
      throw std::runtime_error(
          "Simbolo de lectura fuera del alfabeto de cinta.");
    }
  }

  for (char symbol : transition.GetWriteSymbols()) {
    if (!tape_alphabet.Contains(symbol)) {
      throw std::runtime_error(
          "Simbolo de escritura fuera del alfabeto de cinta.");
    }
  }

  for (char movement : transition.GetMovements()) {
    if (movement != 'L' && movement != 'R' && movement != 'S') {
      throw std::runtime_error("Movimiento de cinta no valido.");
    }
  }

  // Comprobamos que no existan transiciones con la misma condición.
  for (const auto& previous : transitions) {
    if (previous.GetSourceState() == transition.GetSourceState() &&
        previous.GetReadSymbols() == transition.GetReadSymbols()) {
      throw std::runtime_error(
          "La maquina no es determinista: transicion duplicada.");
    }
  }
}

/**
 * @brief Lee y valida las transiciones.
 * @param file Archivo de entrada.
 * @param states Conjunto de estados válidos.
 * @param tape_alphabet Alfabeto de cinta.
 * @param tape_count Número de cintas.
 * @return Vector de transiciones.
 */
std::vector<Transition> Parser::ReadTransitions(
    std::ifstream& file,
    const StateSet& states,
    const Alphabet& tape_alphabet,
    size_t tape_count) {
  std::vector<Transition> transitions;
  std::string line;

  while (GetNextValidLine(file, line)) {
    std::istringstream iss(line);
    std::vector<std::string> tokens;
    std::string token;

    while (iss >> token) {
      tokens.push_back(token);
    }

    // Cada transición tiene 3 elementos por cinta y 2 estados.
    if (tape_count > (tokens.max_size() - 2) / 3 ||
        tokens.size() != 3 * tape_count + 2) {
      throw std::runtime_error(
          "Formato de transicion no valido.");
    }

    std::string source_state = tokens[0];
    std::string destination_state = tokens[1 + tape_count];

    std::vector<char> read_symbols;
    std::vector<char> write_symbols;
    std::vector<char> movements;

    for (size_t i = 0; i < tape_count; ++i) {
      if (tokens[1 + i].size() != 1 ||
          tokens[2 + tape_count + i].size() != 1 ||
          tokens[2 + 2 * tape_count + i].size() != 1) {
        throw std::runtime_error(
            "Los simbolos y movimientos deben tener un caracter.");
      }

      read_symbols.push_back(tokens[1 + i][0]);
      write_symbols.push_back(tokens[2 + tape_count + i][0]);
      movements.push_back(tokens[2 + 2 * tape_count + i][0]);
    }

    Transition transition(source_state, read_symbols,
                          destination_state, write_symbols, movements);

    ValidateTransition(transition, states, tape_alphabet,
                       tape_count, transitions);

    transitions.push_back(transition);
  }

  return transitions;
}

/**
 * @brief Lee un archivo y construye una máquina de Turing.
 * @param filename Ruta del archivo de configuración.
 * @return Máquina de Turing construida.
 */
TuringMachine Parser::Parse(const std::string& filename) {
  std::ifstream file(filename);

  if (!file.is_open()) {
    throw std::runtime_error(
        "No se pudo abrir el archivo: " + filename);
  }

  StateSet states = ReadStates(file);
  Alphabet input_alphabet = ReadAlphabet(
      file, "Falta el alfabeto de entrada.");
  Alphabet tape_alphabet = ReadAlphabet(
      file, "Falta el alfabeto de cinta.");

  // El alfabeto de entrada debe estar incluido en el de cinta.
  for (char symbol : input_alphabet.GetSymbols()) {
    if (!tape_alphabet.Contains(symbol)) {
      throw std::runtime_error(
          "El alfabeto de entrada no es subconjunto del de cinta.");
    }
  }

  std::string initial_state = ReadInitialState(file, states);
  char blank_symbol = ReadBlankSymbol(
      file, input_alphabet, tape_alphabet);
  StateSet final_states = ReadFinalStates(file, states);
  size_t tape_count = ReadTapeCount(file);

  std::vector<Transition> transitions = ReadTransitions(
      file, states, tape_alphabet, tape_count);

  return TuringMachine(states, input_alphabet, tape_alphabet,
                       initial_state, blank_symbol, final_states,
                       tape_count, transitions);
}
