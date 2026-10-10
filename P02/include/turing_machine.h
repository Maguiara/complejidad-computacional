/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad Computacional
 *
 * @author Marco Aguiar Álvarez
 * @since Oct 10, 2026
 * @brief Declaración de la clase TuringMachine. Representa y valida
 *        una máquina de Turing multicinta determinista.
 */

#ifndef TURING_MACHINE_H_
#define TURING_MACHINE_H_

#include <cstddef>
#include <string>
#include <vector>

#include "alphabet.h"
#include "state_set.h"
#include "transition.h"

/**
 * @class TuringMachine
 * @brief Representa una máquina de Turing multicinta determinista.
 *
 * Almacena los estados, alfabetos, estado inicial, símbolo blanco,
 * estados finales, número de cintas y función de transición.
 */
class TuringMachine {
 public:
  TuringMachine(const StateSet& states,
                const Alphabet& input_alphabet,
                const Alphabet& tape_alphabet,
                const std::string& initial_state,
                char blank_symbol,
                const StateSet& final_states,
                size_t tape_count,
                const std::vector<Transition>& transitions);
  const Transition* FindApplicableTransition(const std::string& current_state, const std::vector<char>& read_symbols) const;
  bool IsFinalState(const std::string& state) const;
  const std::string& GetInitialState() const;
  char GetBlankSymbol() const;
  size_t GetTapeCount() const;
  bool IsValidInput(const std::string& input) const;

 private:
  StateSet states_;
  Alphabet input_alphabet_;
  Alphabet tape_alphabet_;
  std::string initial_state_;
  char blank_symbol_;
  StateSet final_states_;
  size_t tape_count_;
  std::vector<Transition> transitions_;
};

#endif  // TURING_MACHINE_H_