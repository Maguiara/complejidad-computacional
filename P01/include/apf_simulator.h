/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad Computacional
 *
 * @author Marco Aguiar Álvarez
 * @date Sep 23, 2026
 * @brief Declaration of the ApfSimulator class. Orchestrates the APf 
 *        components and executes the non-deterministic simulation.
 */

#ifndef APF_SIMULATOR_H_
#define APF_SIMULATOR_H_

#include <string>
#include <vector>

#include "alphabet.h"
#include "state_set.h"
#include "transition.h"
#include "Configuration.h"

class ApfSimulator {
 public:
  ApfSimulator(StateSet states, Alphabet input_alphabet,
               Alphabet stack_alphabet, std::string initial_state,
               char initial_stack_symbol, StateSet final_states,
               std::vector<Transition> transitions);
               
  bool IsAccepted(const std::string& input_string, bool trace_mode) const;

 private:
  bool ExplorePaths(const Configuration& current_config, bool trace_mode, int step) const;

  StateSet states_;
  Alphabet input_alphabet_;
  Alphabet stack_alphabet_;
  std::string initial_state_;
  char initial_stack_symbol_;
  StateSet final_states_;
  std::vector<Transition> transitions_;
};

#endif  // APF_SIMULATOR_H_