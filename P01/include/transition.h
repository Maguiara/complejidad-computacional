/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad Computacional
 *
 * @author Marco Aguiar Álvarez
 * @since Sep 18, 2026
 */


#ifndef TRANSITION_H
#define TRANSITION_H

#include <string>

class Transition {
  public:
  Transition(const std::string& source_state,
             char input_symbol,
             char stack_symbol,
             const std::string& destination_state,
             const std::string& replacement) : source_state_(source_state),
               input_symbol_(input_symbol),
               stack_symbol_(stack_symbol),
               destination_state_(destination_state),
               replacement_(replacement) {};

  bool IsApplicable(const std::string& current_state, char input_symbol, char stack_symbol) const {
    return current_state == source_state_ && input_symbol == input_symbol_ && stack_symbol == stack_symbol_;
  }

  char GetInputSymbol() const { return input_symbol_; }
  char GetStackSymbol() const { return stack_symbol_; }
  std::string GetDestinationState() const { return destination_state_; }
  std::string GetReplacement() const { return replacement_; }
  
  private:
    std::string source_state_;
    char input_symbol_;
    char stack_symbol_;
    std::string destination_state_;
    std::string replacement_;
};

#endif  // TRANSITION_H