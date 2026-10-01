/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad Computacional
 *
 * @author Marco Aguiar Álvarez
 * @since Sep 18, 2026
 */

#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <string>
#include <utility>

#include "transition.h"
#include "state_set.h"
#include "automaton_stack.h"
#include "alphabet.h"

class Configuration {
  public:
    Configuration(const std::string& state, const std::string& remaining_input, AutomatonStack stack_content)
      : current_state_(state), remaining_input_(remaining_input), stack_content_(std::move(stack_content)) {}

    Configuration ApplyTransition(const Transition& transition) const;
    bool IsFinalState(const StateSet& final_states) const;

    std::string ToString() const;

    std::string GetCurrentState() const { return current_state_; }
    std::string GetRemainingInput() const { return remaining_input_; }
    const AutomatonStack& GetStackContent() const { return stack_content_; }

  private:
    std::string current_state_;
    std::string remaining_input_;
    AutomatonStack stack_content_;
};

#endif  // CONFIGURATION_H