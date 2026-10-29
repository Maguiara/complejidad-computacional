/**
 * Universidad de La Laguna
 * Grado en Ingeniería Informática - Complejidad Computacional
 * @author Marco Aguiar Álvarez
 * @since Oct 10, 2026
 * @brief Evaluación común a todas las funciones.
 */
#include "function.h"

#include <stdexcept>

Natural Function::operator()(const std::vector<Natural>& arguments) const {
  CallCounter::Scope scope(counter_);
  if (arguments.size() != arity_) {
    throw std::invalid_argument("Numero de argumentos incorrecto para la funcion.");
  }
  return Compute(arguments);
}
