/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad Computacional
 *
 * @author Marco Aguiar Álvarez
 * @since Sep 20, 2026
 * @brief Implementation of the ApfParser class. Extracts states, alphabets,
 *        and transitions from a text file to build the simulator.
 */

#include "parse.h"

#include <fstream>
#include <sstream>
#include <stdexcept>

/**
 * @brief Lee la siguiente línea válida del archivo, ignorando líneas vacías y comentarios.
 * @param file El archivo de entrada.
 * @param line La línea leída.
 * @return true si se leyó una línea válida, false si se llegó al final del archivo.
 */
bool ApfParser::GetNextValidLine(std::ifstream& file, std::string& line) {
  while (std::getline(file, line)) {
    if (line.empty() || line[0] == '#') continue;
    return true;
  }
  return false;
}

/**
 * @brief Valida una transición asegurándose de que los estados y símbolos estén en los conjuntos correctos.
 * @param source El estado fuente.
 * @param input El símbolo de entrada.
 * @param stack El símbolo de la pila.
 * @param dest El estado de destino.
 * @param replacement La cadena de reemplazo para la pila.
 * @param states El conjunto de estados válidos.
 * @param input_alph El alfabeto de entrada válido.
 * @param stack_alph El alfabeto de la pila válido.
 */
void ApfParser::ValidateTransition(const std::string& source, char input, 
                                   char stack, const std::string& dest, 
                                   const std::string& replacement, 
                                   const StateSet& states, 
                                   const Alphabet& input_alph, 
                                   const Alphabet& stack_alph) {
  if (!states.Contains(source) || !states.Contains(dest)) 
    throw std::runtime_error("Transition states must be in the set of states (" + source + " or " + dest + " is not in " + states.ToString() + ")");
  if (!input_alph.Contains(input) && input != Alphabet::EPSILON) 
    throw std::runtime_error("Input symbol must be in the input alphabet or epsilon (" + std::string(1, input) + " is not in  " + input_alph.ToString() + ")");
  if (!stack_alph.Contains(stack) && stack != Alphabet::EPSILON) 
    throw std::runtime_error("Stack symbol must be in the stack alphabet or epsilon (" + std::string(1, stack) + " is not in  " + stack_alph.ToString() + ")");
  for (char c : replacement) {
    if (!stack_alph.Contains(c) && c != Alphabet::EPSILON) {
      throw std::runtime_error("Replacement symbols must be in the stack alphabet or epsilon (" + replacement + " is not in  " + stack_alph.ToString() + ")");
    }
  }
}

/**
 * @brief Lee el conjunto de estados desde el archivo.
 * @param file El archivo de entrada.
 * @return El conjunto de estados leídos.
 */
StateSet ApfParser::ReadStates(std::ifstream& file) {
  std::string line, token;
  StateSet states;
  if (!GetNextValidLine(file, line)) throw std::runtime_error("Missing states");
  std::istringstream iss(line);
  while (iss >> token) states.Add(token);
  return states;
}

/**
 * @brief Lee un alfabeto desde el archivo.
 * @param file El archivo de entrada.
 * @param error_msg El mensaje de error a mostrar si falta el alfabeto.
 * @return El alfabeto leído.
 */
Alphabet ApfParser::ReadAlphabet(std::ifstream& file, const std::string& error_msg) {
  std::string line, token;
  Alphabet alphabet;
  if (!GetNextValidLine(file, line)) throw std::runtime_error(error_msg);
  std::istringstream iss(line);
  while (iss >> token) {
    if (token.length() != 1) throw std::runtime_error("Alphabet symbol must be a single character");
    alphabet.Add(token[0]);
  }
  return alphabet;
}

/**
 * @brief Lee el estado inicial desde el archivo.
 * @param file El archivo de entrada.
 * @param states El conjunto de estados válidos.
 * @return El estado inicial leído.
 */
std::string ApfParser::ReadInitialState(std::ifstream& file, const StateSet& states) {
  std::string line, initial_state;
  if (!GetNextValidLine(file, line)) throw std::runtime_error("Missing initial state");
  std::istringstream iss(line);
  iss >> initial_state;
  if (!states.Contains(initial_state)) 
    throw std::runtime_error("Initial state must be in the set of states (" + initial_state + " is not in " + states.ToString() + ")");
  return initial_state;
}

/**
 * @brief Lee el símbolo inicial de la pila desde el archivo.
 * @param file El archivo de entrada.
 * @param stack_alphabet El alfabeto de la pila válido.
 * @return El símbolo inicial de la pila leído.
 */
char ApfParser::ReadInitialStackSymbol(std::ifstream& file, const Alphabet& stack_alphabet) {
  std::string line;
  char initial_stack_symbol;
  if (!GetNextValidLine(file, line)) throw std::runtime_error("Missing initial stack symbol");
  std::istringstream iss(line);
  iss >> initial_stack_symbol;
  if (iss.fail() || !stack_alphabet.Contains(initial_stack_symbol)) 
    throw std::runtime_error("Initial stack symbol must be a single character from the stack alphabet (" + std::string(1, initial_stack_symbol) + " is not in " + stack_alphabet.ToString() + ")");
  return initial_stack_symbol;
}

/**
 * @brief Lee los estados finales desde el archivo.
 * @param file El archivo de entrada.
 * @param states El conjunto de estados válidos.
 * @return El conjunto de estados finales leídos.
 */
StateSet ApfParser::ReadFinalStates(std::ifstream& file, const StateSet& states) {
  std::string line, token;
  StateSet final_states;
  if (!GetNextValidLine(file, line)) throw std::runtime_error("Missing final states");
  std::istringstream iss(line);
  while (iss >> token) final_states.Add(token);
  states.CheckIfFinalStatesAreSubsetOfStates(final_states);
  return final_states;
}

/**
 * @brief Lee las transiciones desde el archivo.
 * @param file El archivo de entrada.
 * @param states El conjunto de estados válidos.
 * @param input_alph El alfabeto de entrada válido.
 * @param stack_alph El alfabeto de la pila válido.
 * @return El conjunto de transiciones leídas.
 */
std::vector<Transition> ApfParser::ReadTransitions(std::ifstream& file, const StateSet& states, 
                                                   const Alphabet& input_alph, const Alphabet& stack_alph) {
  std::vector<Transition> transitions;
  std::string line;
  while (GetNextValidLine(file, line)) {
    std::istringstream iss(line);
    std::string source_state, destination_state, replacement;
    char input_symbol, stack_symbol;
    if (iss >> source_state >> input_symbol >> stack_symbol >> destination_state >> replacement) {
      ValidateTransition(source_state, input_symbol, stack_symbol, destination_state, replacement, states, input_alph, stack_alph);
      transitions.emplace_back(source_state, input_symbol, stack_symbol, destination_state, replacement);
    }
  }
  return transitions;
}

/**
 * @brief Parsea un archivo de entrada para crear un simulador APF.
 * @param filename El nombre del archivo de entrada.
 * @return El simulador APF creado.
 */
ApfSimulator ApfParser::Parse(const std::string& filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    throw std::runtime_error("Could not open file: " + filename);
  }

  StateSet states = ReadStates(file);
  Alphabet input_alphabet = ReadAlphabet(file, "Missing input alphabet");
  Alphabet stack_alphabet = ReadAlphabet(file, "Missing stack alphabet");
  std::string initial_state = ReadInitialState(file, states);
  char initial_stack_symbol = ReadInitialStackSymbol(file, stack_alphabet);
  StateSet final_states = ReadFinalStates(file, states);
  std::vector<Transition> transitions = ReadTransitions(file, states, input_alphabet, stack_alphabet);

  return ApfSimulator(states, input_alphabet, stack_alphabet, initial_state,
                      initial_stack_symbol, final_states, transitions);
}