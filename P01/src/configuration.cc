/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad Computacional
 *
 * @author Marco Aguiar Álvarez
 * @since Sep 18, 2026
 */


#include "Configuration.h"

/**
 * @brief Aplica una transición a la configuración actual y devuelve la nueva configuración resultante.
 * @param transition La transición a aplicar.
 * @return La nueva configuración resultante. (Configuración == Descripción instantanea == Estado actual, entrada restante, contenido de la pila actual)
 */
Configuration Configuration::ApplyTransition(const Transition& transition) const {
  std::string next_unread_input = remaining_input_;
  if (transition.GetInputSymbol() != Alphabet::EPSILON && !next_unread_input.empty()) {
    next_unread_input.erase(0, 1); // Remove the first character from the remaining input
  }
  
  AutomatonStack next_stack_content = stack_content_;
  next_stack_content.ReplaceTop(transition.GetReplacement());
  return Configuration(transition.GetDestinationState(), next_unread_input, std::move(next_stack_content));
}

/**
 * @brief Comprueba si la configuración actual es un estado final.
 * @param final_states El conjunto de estados finales.
 * @return true si la configuración actual es un estado final, false en caso contrario.
 */
bool Configuration::IsFinalState(const StateSet& final_states) const {
  return remaining_input_.empty() && final_states.Contains(current_state_);
}

/**
 * @brief Convierte la configuración en una cadena legible.
 * @return Una cadena que representa la configuración.
 */
std::string Configuration::ToString() const {
  std::string display_input = remaining_input_.empty() ? std::string(1, Alphabet::EPSILON) : remaining_input_;

  return "(" + current_state_ + ", " + display_input + ", " + stack_content_.ToString() + ")";
}
