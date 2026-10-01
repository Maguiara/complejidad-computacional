/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad Computacional
 *
 * @author Marco Aguiar Álvarez
 * @since Sep 18, 2026
 */


#include "automaton_stack.h"


/**
 * @brief Obtiene el símbolo en la parte superior de la pila.
 * @return El símbolo en la parte superior de la pila.
 */
char AutomatonStack::GetTop() const {
  if (IsEmpty()) {
    throw std::runtime_error("Stack is empty.");
  }
  return stack_.back();
}

/**
 * @brief Comprueba si la pila está vacía.
 * @return true si la pila está vacía, false en caso contrario.
 */
bool AutomatonStack::IsEmpty() const {
  return stack_.empty();
}

/**
 * @brief Reemplaza el símbolo en la parte superior de la pila con una cadena de símbolos.
 * @param replacement La cadena de símbolos para reemplazar el símbolo superior.
 */
void AutomatonStack::ReplaceTop(const std::string& replacement) {
  if (IsEmpty()) {
    throw std::runtime_error("Stack is empty.");
  }
  stack_.pop_back();
  if (replacement == std::string(1, Alphabet::EPSILON)) return;
  for (auto it = replacement.rbegin(); it != replacement.rend(); ++it) {
    stack_.push_back(*it);
  }
}

/**
 * @brief Convierte la pila en una cadena de símbolos.
 * @return Una cadena que representa la pila.
 */
std::string AutomatonStack::ToString() const {
  std::string result;
  for (const auto& symbol : stack_) {
    result += symbol;
  }
  return result;
}