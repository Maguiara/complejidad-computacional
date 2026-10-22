
/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad Computacional
 *
 * @author Marco Aguiar Álvarez
 * @since Oct 10, 2026
 * @brief Declaración de la clase Parser. Lee y valida archivos
 *        de configuración de máquinas de Turing multicinta.
 */

#ifndef P02_INCLUDE_PARSE_H_
#define P02_INCLUDE_PARSE_H_

#include <cstddef>
#include <fstream>
#include <string>
#include <vector>

#include "alphabet.h"
#include "state_set.h"
#include "transition.h"
#include "turing_machine.h"

/**
 * @class Parser
 * @brief Interpreta y valida archivos de máquinas de Turing.
 *
 * Lee los componentes de la máquina y comprueba que cumplen
 * las restricciones de una máquina de Turing determinista.
 */
class Parser {
 public:
  static TuringMachine Parse(const std::string& filename);

 private:
  bool GetNextValidLine(std::ifstream& file, std::string& line);
  StateSet ReadStates(std::ifstream& file);

  Alphabet ReadAlphabet(
      std::ifstream& file, const std::string& error_msg);

  std::string ReadInitialState(
      std::ifstream& file, const StateSet& states);

  char ReadBlankSymbol(
      std::ifstream& file,
      const Alphabet& input_alphabet,
      const Alphabet& tape_alphabet);

  StateSet ReadFinalStates(
      std::ifstream& file, const StateSet& states);

  size_t ReadTapeCount(std::ifstream& file);

  std::vector<Transition> ReadTransitions(
      std::ifstream& file,
      const StateSet& states,
      const Alphabet& tape_alphabet,
      size_t tape_count);

  TuringMachine ReadMachine(std::ifstream& file);
  static void ValidateSymbol(const std::string& token);
  static void ValidateAlphabetInclusion(const Alphabet& input_alphabet,
                                       const Alphabet& tape_alphabet);
  static void ValidateInitialState(const std::string& initial_state,
                                   const StateSet& states);
  static void ValidateBlankSymbol(char blank_symbol,
                                  const Alphabet& input_alphabet,
                                  const Alphabet& tape_alphabet);
  static void ValidateFinalStates(const StateSet& final_states,
                                  const StateSet& states);
  static void ValidateTransitionFormat(
      const std::vector<std::string>& tokens, size_t tape_count);
  static void ValidateTransitionStates(const Transition& transition,
                                       const StateSet& states);
  static void ValidateTransitionSymbols(const std::vector<char>& symbols,
                                        const Alphabet& tape_alphabet,
                                        const std::string& operation);
  static void ValidateTransitionMovements(const std::vector<char>& movements);
  static void ValidateTransitionTapeCount(const Transition& transition,
                                          size_t tape_count);
  static void ValidateDeterminism(
      const Transition& transition, const std::vector<Transition>& transitions);

  std::size_t line_number_ = 0;
};

#endif  // P02_INCLUDE_PARSE_H_
