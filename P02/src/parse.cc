
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
 * @brief Comprueba que un símbolo ocupa exactamente un carácter.
 * @param token Símbolo leído del archivo.
 * @throws std::runtime_error Si el símbolo no tiene longitud uno.
 */
void Parser::ValidateSymbol(const std::string& token) {
  if (token.size() != 1) {
    throw std::runtime_error("Simbolo no valido. Debe tener un caracter "
                             "(simbolo: '" + token + "').");
  }
}

/**
 * @brief Comprueba la inclusión del alfabeto de entrada en el de cinta.
 * @param input_alphabet Alfabeto de entrada.
 * @param tape_alphabet Alfabeto de cinta.
 * @throws std::runtime_error Si algún símbolo de entrada no está en la cinta.
 */
void Parser::ValidateAlphabetInclusion(const Alphabet& input_alphabet,
                                       const Alphabet& tape_alphabet) {
  for (char symbol : input_alphabet.GetSymbols()) {
    if (!tape_alphabet.Contains(symbol)) {
      throw std::runtime_error("Simbolo de entrada fuera del alfabeto de "
                               "cinta (simbolo: '" +
                               std::string(1, symbol) + "').");
    }
  }
}

/**
 * @brief Comprueba que el estado inicial pertenece a Q.
 * @param initial_state Estado inicial declarado.
 * @param states Estados de la máquina.
 * @throws std::runtime_error Si el estado inicial no está declarado.
 */
void Parser::ValidateInitialState(const std::string& initial_state,
                                  const StateSet& states) {
  if (!states.Contains(initial_state)) {
    throw std::runtime_error("Estado inicial no declarado (estado: '" +
                             initial_state + "').");
  }
}

/**
 * @brief Comprueba que el blanco pertenece a la cinta y no a la entrada.
 * @param blank_symbol Símbolo blanco.
 * @param input_alphabet Alfabeto de entrada.
 * @param tape_alphabet Alfabeto de cinta.
 * @throws std::runtime_error Si el blanco incumple alguna restricción.
 */
void Parser::ValidateBlankSymbol(char blank_symbol,
                                 const Alphabet& input_alphabet,
                                 const Alphabet& tape_alphabet) {
  if (!tape_alphabet.Contains(blank_symbol)) {
    throw std::runtime_error("El blanco no pertenece al alfabeto de cinta "
                             "(simbolo: '" +
                             std::string(1, blank_symbol) + "').");
  }
  if (input_alphabet.Contains(blank_symbol)) {
    throw std::runtime_error("El blanco pertenece al alfabeto de entrada "
                             "(simbolo: '" +
                             std::string(1, blank_symbol) + "').");
  }
}

/**
 * @brief Comprueba que todos los estados finales pertenecen a Q.
 * @param final_states Estados finales declarados.
 * @param states Estados de la máquina.
 * @throws std::runtime_error Si algún estado final no está declarado.
 */
void Parser::ValidateFinalStates(const StateSet& final_states,
                                 const StateSet& states) {
  for (const auto& state : final_states.GetStates()) {
    if (!states.Contains(state)) {
      throw std::runtime_error("Estado final no declarado (estado: '" +
                               state + "').");
    }
  }
}

/**
 * @brief Comprueba el número exacto de campos de una transición.
 * @param tokens Campos de una línea de transición.
 * @param tape_count Número de cintas declarado.
 * @throws std::runtime_error Si faltan o sobran campos.
 */
void Parser::ValidateTransitionFormat(
    const std::vector<std::string>& tokens, size_t tape_count) {
  if (tape_count > (tokens.max_size() - 2) / 3 ||
      tokens.size() != 3 * tape_count + 2) {
    throw std::runtime_error("Numero de campos de transicion no valido.");
  }
}

/**
 * @brief Comprueba los estados de origen y destino de una transición.
 * @param transition Transición que se valida.
 * @param states Conjunto Q.
 * @throws std::runtime_error Si algún estado no pertenece a Q.
 */
void Parser::ValidateTransitionStates(const Transition& transition,
                                      const StateSet& states) {
  for (const auto& state : {transition.GetSourceState(),
                            transition.GetDestinationState()}) {
    if (!states.Contains(state)) {
      throw std::runtime_error("Estado de transicion no declarado (estado: '" +
                               state + "').");
    }
  }
}

/**
 * @brief Comprueba los símbolos de lectura o escritura en todas las cintas.
 * @param symbols Símbolos que se validan.
 * @param tape_alphabet Alfabeto de cinta.
 * @param operation Nombre de la operación para el diagnóstico.
 * @throws std::runtime_error Si algún símbolo no pertenece al alfabeto.
 */
void Parser::ValidateTransitionSymbols(const std::vector<char>& symbols,
                                       const Alphabet& tape_alphabet,
                                       const std::string& operation) {
  for (char symbol : symbols) {
    if (!tape_alphabet.Contains(symbol)) {
      throw std::runtime_error("Simbolo de " + operation +
                               " fuera del alfabeto de cinta (simbolo: '" +
                               std::string(1, symbol) + "').");
    }
  }
}

/**
 * @brief Comprueba que todos los movimientos sean L, R o S.
 * @param movements Movimientos de las cabezas.
 * @throws std::runtime_error Si algún movimiento es inválido.
 */
void Parser::ValidateTransitionMovements(const std::vector<char>& movements) {
  for (char movement : movements) {
    if (movement != 'L' && movement != 'R' && movement != 'S') {
      throw std::runtime_error("Movimiento no valido (movimiento: '" +
                               std::string(1, movement) + "').");
    }
  }
}

/**
 * @brief Comprueba las cantidades de elementos por cinta en la transición.
 * @param transition Transición que se valida.
 * @param tape_count Número de cintas declarado.
 * @throws std::runtime_error Si las cantidades no coinciden.
 */
void Parser::ValidateTransitionTapeCount(const Transition& transition,
                                         size_t tape_count) {
  if (transition.GetReadSymbols().size() != tape_count ||
      transition.GetWriteSymbols().size() != tape_count ||
      transition.GetMovements().size() != tape_count) {
    throw std::runtime_error("La transicion no coincide con las cintas.");
  }
}

/**
 * @brief Impide dos transiciones para el mismo estado y símbolos leídos.
 * @param transition Nueva transición.
 * @param transitions Transiciones ya validadas.
 * @throws std::runtime_error Si existe una condición repetida.
 */
void Parser::ValidateDeterminism(
    const Transition& transition, const std::vector<Transition>& transitions) {
  for (const auto& previous : transitions) {
    if (previous.GetSourceState() == transition.GetSourceState() &&
        previous.GetReadSymbols() == transition.GetReadSymbols()) {
      throw std::runtime_error(
          "Maquina no determinista: transicion duplicada.");
    }
  }
}

/**
 * @brief Lee la siguiente línea de datos y cuenta todas las líneas físicas.
 * @param file Archivo de entrada.
 * @param line Línea leída.
 * @return true si existe una línea válida, false si termina el archivo.
 * @throws std::runtime_error Si falla la lectura del archivo.
 */
bool Parser::GetNextValidLine(std::ifstream& file, std::string& line) {
  while (std::getline(file, line)) {
    ++line_number_;
    size_t comment_position = line.find('#');
    if (comment_position != std::string::npos) {
      line = line.substr(0, comment_position);
    }

    if (line.find_first_not_of(" \t\r\n") == std::string::npos) {
      continue;
    }

    return true;
  }

  if (file.bad() || (file.fail() && !file.eof())) {
    throw std::runtime_error("Error de lectura del archivo.");
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
    ValidateSymbol(token);

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
    throw std::runtime_error("Formato del estado inicial no valido "
                             "(contenido: '" + line + "').");
  }

  ValidateInitialState(initial_state, states);

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
    throw std::runtime_error("Simbolo blanco no valido (contenido: '" +
                             line + "').");
  }

  char blank_symbol = token[0];

  ValidateBlankSymbol(blank_symbol, input_alphabet, tape_alphabet);

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

  ValidateFinalStates(final_states, states);

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
      token.empty() ||
      token.find_first_not_of("0123456789") != std::string::npos) {
    throw std::runtime_error("Numero de cintas no valido (contenido: '" +
                             line + "').");
  }

  try {
    size_t processed = 0;
    unsigned long long count = std::stoull(token, &processed);

    if (processed != token.size() || count == 0 ||
        count > std::numeric_limits<size_t>::max()) {
      throw std::runtime_error("Numero de cintas no valido (valor: '" +
                               token + "').");
    }

    return static_cast<size_t>(count);
  } catch (const std::invalid_argument&) {
    throw std::runtime_error("Numero de cintas no valido (valor: '" +
                             token + "').");
  } catch (const std::out_of_range&) {
    throw std::runtime_error("Numero de cintas fuera de rango (valor: '" +
                             token + "').");
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

    ValidateTransitionFormat(tokens, tape_count);

    std::string source_state = tokens[0];
    std::string destination_state = tokens[1 + tape_count];

    std::vector<char> read_symbols;
    std::vector<char> write_symbols;
    std::vector<char> movements;

    for (size_t i = 0; i < tape_count; ++i) {
      ValidateSymbol(tokens[1 + i]);
      ValidateSymbol(tokens[2 + tape_count + i]);
      ValidateSymbol(tokens[2 + 2 * tape_count + i]);

      read_symbols.push_back(tokens[1 + i][0]);
      write_symbols.push_back(tokens[2 + tape_count + i][0]);
      movements.push_back(tokens[2 + 2 * tape_count + i][0]);
    }

    ValidateTransitionMovements(movements);
    Transition transition(source_state, read_symbols,
                          destination_state, write_symbols, movements);

    ValidateTransitionStates(transition, states);
    ValidateTransitionTapeCount(transition, tape_count);
    ValidateTransitionSymbols(read_symbols, tape_alphabet, "lectura");
    ValidateTransitionSymbols(write_symbols, tape_alphabet, "escritura");
    ValidateDeterminism(transition, transitions);

    transitions.push_back(transition);
  }

  return transitions;
}

/**
 * @brief Lee un archivo y construye una máquina de Turing.
 * @param filename Ruta del archivo de configuración.
 * @return Máquina de Turing construida.
 * @throws std::runtime_error Si el archivo no se abre o contiene errores.
 * Los errores de contenido incluyen la ruta y el número de línea física.
 */
TuringMachine Parser::Parse(const std::string& filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    throw std::runtime_error("No se pudo abrir el archivo: " + filename);
  }
  Parser parser;
  try {
    return parser.ReadMachine(file);
  } catch (const std::exception& error) {
    throw std::runtime_error(filename + ": linea " +
                             std::to_string(parser.line_number_) + ": " +
                             error.what());
  }
}

/**
 * @brief Lee y valida todos los campos y todas las transiciones del archivo.
 * @param file Flujo del archivo de configuración.
 * @return Máquina completamente validada.
 * @throws std::runtime_error Si un campo es inválido o falta información.
 */
TuringMachine Parser::ReadMachine(std::ifstream& file) {
  StateSet states = ReadStates(file);
  Alphabet input_alphabet = ReadAlphabet(
      file, "Falta el alfabeto de entrada.");
  Alphabet tape_alphabet = ReadAlphabet(
      file, "Falta el alfabeto de cinta.");

  ValidateAlphabetInclusion(input_alphabet, tape_alphabet);

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
