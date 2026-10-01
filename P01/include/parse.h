/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad Computacional
 *
 * @author Marco Aguiar Álvarez
 * @since Sep 20, 2026
 * @brief Declaration of the ApfParser class. Responsible for reading 
 *        the .txt configuration file and building an ApfSimulator instance.
 */

#ifndef APF_PARSER_H
#define APF_PARSER_H

#include <string>

#include "apf_simulator.h"

class ApfParser {
 public:
  static ApfSimulator Parse(const std::string& filename);
private:
  static bool GetNextValidLine(std::ifstream& file, std::string& line);
  static void ValidateTransition(const std::string& source, char input, 
                                 char stack, const std::string& dest, 
                                 const std::string& replacement, 
                                 const StateSet& states, 
                                 const Alphabet& input_alph, 
                                 const Alphabet& stack_alph);

  static StateSet ReadStates(std::ifstream& file);
  static Alphabet ReadAlphabet(std::ifstream& file, const std::string& error_msg);
  static std::string ReadInitialState(std::ifstream& file, const StateSet& states);
  static char ReadInitialStackSymbol(std::ifstream& file, const Alphabet& stack_alphabet);
  static StateSet ReadFinalStates(std::ifstream& file, const StateSet& states);
  static std::vector<Transition> ReadTransitions(std::ifstream& file, const StateSet& states, const Alphabet& input_alph, const Alphabet& stack_alph);
};

#endif  // APF_PARSER_H_