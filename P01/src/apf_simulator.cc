/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad Computacional
 *
 * @author Marco Aguiar Álvarez
 * @date Sep 23, 2026
 * @brief Implementation of the ApfSimulator class. Contains the core
 *        logic for tracing and simulating the automaton's execution.
 */

#include "apf_simulator.h"

#include <iostream>
#include <iomanip>
#include <utility>
#include <stdexcept>

/**
 * @brief Constructor para la clase ApfSimulator.
 * @param states Conjunto de estados del autómata.
 * @param input_alphabet Alfabeto de entrada.
 * @param stack_alphabet Alfabeto de la pila.
 * @param initial_state Estado inicial del autómata.
 * @param initial_stack_symbol Símbolo inicial de la pila.
 * @param final_states Conjunto de estados finales.
 * @param transitions Vector de transiciones del autómata.
 */
ApfSimulator::ApfSimulator(StateSet states, Alphabet input_alphabet,
                           Alphabet stack_alphabet, std::string initial_state,
                           char initial_stack_symbol, StateSet final_states,
                           std::vector<Transition> transitions)
    : states_(std::move(states)),
      input_alphabet_(std::move(input_alphabet)),
      stack_alphabet_(std::move(stack_alphabet)),
      initial_state_(std::move(initial_state)),
      initial_stack_symbol_(initial_stack_symbol),
      final_states_(std::move(final_states)),
      transitions_(std::move(transitions)) { 
  if (final_states_.GetStates().empty()) throw std::runtime_error("Final states cannot be empty"); 
  if (!states_.Contains(initial_state_)) throw std::runtime_error("Initial state must be in the set of states");
}

/**
 * @brief Determina si una cadena de entrada es aceptada por el autómata.
 * @param input_string Cadena de entrada a verificar.
 * @param trace_mode Si es true, se muestra el proceso de simulación.
 * @return true si la cadena es aceptada, false en caso contrario.
 */
bool ApfSimulator::IsAccepted(const std::string& input_string, bool trace_mode) const {
  if (trace_mode) {
    std::cout << std::left 
              << std::setw(6)  << "Paso" 
              << "| " << std::setw(8)  << "Estado" 
              << "| " << std::setw(10) << "Cadena" 
              << "| " << std::setw(10) << "Pila" 
              << "| Transiciones aplicables\n";
    std::cout << std::string(80, '-') << "\n";
  }

  AutomatonStack initial_stack(initial_stack_symbol_);
  Configuration initial_config(initial_state_, input_string, std::move(initial_stack));
  return ExplorePaths(initial_config, trace_mode, 1);
}

/**
 * @brief Explora recursivamente todos los caminos posibles del autómata desde la configuración actual.
 * @param current_config Configuración actual del autómata. (Descripcion Instantanea del autómata)
 * @param trace_mode Si es true, se muestra el proceso de simulación.
 * @param step Número de paso actual en la simulación.
 * @return true si se encuentra un camino que lleva a un estado final, false en caso
 */
bool ApfSimulator::ExplorePaths(const Configuration& current_config, bool trace_mode, int step) const {
  char stack_top = Alphabet::EPSILON;
  bool stack_empty = false;
  
  try {
    stack_top = current_config.GetStackContent().GetTop();
  } catch (const std::runtime_error&) {
    stack_empty = true;
  }

  std::string current_state = current_config.GetCurrentState();
  std::string unread_input = current_config.GetRemainingInput();

  if (trace_mode) {
    std::string display_input = unread_input.empty() ? std::string(1, Alphabet::EPSILON) : unread_input;
    std::string applicable_trans = "";

    if (!stack_empty) {
      for (const auto& t : transitions_) {
        bool is_eps = t.IsApplicable(current_state, Alphabet::EPSILON, stack_top);
        bool is_char = !unread_input.empty() && t.IsApplicable(current_state, unread_input[0], stack_top);
        
        if (is_eps || is_char) {
          applicable_trans += "d(" + current_state + "," + (is_eps ? std::string(1, Alphabet::EPSILON) : std::string(1, unread_input[0])) + 
                              "," + std::string(1, stack_top) + ")->(" + t.GetDestinationState() + "," + t.GetReplacement() + ")  ";
        }
      }
    }

    std::cout << std::left << std::setw(6)  << step << "| " << std::setw(8)  << current_state << "| " << std::setw(10) << display_input 
              << "| " << std::setw(10) << current_config.GetStackContent().ToString() << "| " << applicable_trans << "\n";
  }

  if (current_config.IsFinalState(final_states_)) return true;
  if (stack_empty) return false;
  // 1. Probamos las epsilon trancisiones primero
  for (const auto& transition : transitions_) {
    if (transition.IsApplicable(current_state, Alphabet::EPSILON, stack_top)) {
      Configuration next_config = current_config.ApplyTransition(transition);
      if (ExplorePaths(next_config, trace_mode, step + 1)) {
        return true;
      }
    }
  }
  // 2. Probamos las transiciones con el primer simbolo de la cadena
  if (!unread_input.empty()) {
    char current_input_symbol = unread_input[0];
    for (const auto& transition : transitions_) {
      if (transition.IsApplicable(current_state, current_input_symbol, stack_top)) {
        Configuration next_config = current_config.ApplyTransition(transition);
        if (ExplorePaths(next_config, trace_mode, step + 1)) {
          return true;
        }
      }
    }
  }
  return false;
}