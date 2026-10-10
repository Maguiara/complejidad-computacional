/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad Computacional
 *
 * @author Marco Aguiar Álvarez
 * @since Oct 10, 2026
 * @brief Implementación de la clase TuringMachine. Gestiona la
 *        definición, validación y consulta de transiciones
 *        de una máquina de Turing multicinta determinista.
 */

#include "turing_machine.h"

#include <stdexcept>

/**
 * @brief Construye una máquina de Turing y valida su definición.
 * @param states Conjunto de estados.
 * @param input_alphabet Alfabeto de entrada.
 * @param tape_alphabet Alfabeto de cinta.
 * @param initial_state Estado inicial.
 * @param blank_symbol Símbolo blanco.
 * @param final_states Conjunto de estados finales.
 * @param tape_count Número de cintas.
 * @param transitions Transiciones de la máquina.
 * @throws std::invalid_argument Si la máquina no es válida.
 */
TuringMachine::TuringMachine(
    const StateSet& states,
    const Alphabet& input_alphabet,
    const Alphabet& tape_alphabet,
    const std::string& initial_state,
    char blank_symbol,
    const StateSet& final_states,
    size_t tape_count,
    const std::vector<Transition>& transitions)
    : states_(states),
      input_alphabet_(input_alphabet),
      tape_alphabet_(tape_alphabet),
      initial_state_(initial_state),
      blank_symbol_(blank_symbol),
      final_states_(final_states),
      tape_count_(tape_count),
      transitions_(transitions) {}


/**
 * @brief Busca una transición aplicable a la configuración actual.
 * @param current_state Estado actual.
 * @param read_symbols Símbolos leídos en todas las cintas.
 * @return Puntero a la transición o nullptr si no existe.
 */
const Transition* TuringMachine::FindApplicableTransition(
    const std::string& current_state,
    const std::vector<char>& read_symbols) const {
  for (const auto& transition : transitions_) {
    if (transition.IsApplicable(current_state, read_symbols)) {
      return &transition;
    }
  }

  return nullptr;
}

/**
 * @brief Comprueba si un estado es de aceptación.
 * @param state Estado que se desea comprobar.
 * @return true si el estado pertenece al conjunto de estados finales.
 */
bool TuringMachine::IsFinalState(const std::string& state) const {
  return final_states_.Contains(state);
}

/**
 * @brief Obtiene el estado inicial de la máquina.
 * @return Referencia al estado inicial.
 */
const std::string& TuringMachine::GetInitialState() const {
  return initial_state_;
}

/**
 * @brief Obtiene el símbolo blanco de la máquina.
 * @return Símbolo blanco.
 */
char TuringMachine::GetBlankSymbol() const {
  return blank_symbol_;
}

/**
 * @brief Obtiene el número de cintas.
 * @return Número de cintas.
 */
size_t TuringMachine::GetTapeCount() const {
  return tape_count_;
}

/**
 * @brief Comprueba si una cadena pertenece al alfabeto de entrada.
 * @param input Cadena que se desea validar.
 * @return true si todos sus símbolos pertenecen al alfabeto.
 */
bool TuringMachine::IsValidInput(const std::string& input) const {
  return input_alphabet_.ValidateWord(input);
}