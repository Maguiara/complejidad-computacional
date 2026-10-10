/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad Computacional
 *
 * @author Marco Aguiar Álvarez
 * @since Sep 18, 2026
 */



#include "state_set.h"

/**
 * @brief Añade un estado al conjunto de estados.
 * @param state El estado a añadir.
 */
void StateSet::Add(const std::string& state) {
  states_.insert(state);
}

/**
 * @brief Comprueba si un estado está presente en el conjunto de estados.
 * @param state El estado a comprobar.
 * @return true si el estado está presente, false en caso contrario.
 */
bool StateSet::Contains(const std::string& state) const {
  return states_.find(state) != states_.end();
}

/**
 * @brief Comprueba si los estados finales son un subconjunto de los estados válidos.
 * @param final_states El conjunto de estados finales a comprobar.
 */
void StateSet::CheckIfFinalStatesAreSubsetOfStates(const StateSet& final_states) const {
  for (const auto& final_state : final_states.GetStates()) {
    if (!Contains(final_state)) {
      throw std::runtime_error("Final state is not in the set of states. (" + final_state + " is not in " + ToString() + ")");
    }
  }
}