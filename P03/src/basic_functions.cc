/**
 * Universidad de La Laguna
 * Grado en Ingeniería Informática - Complejidad Computacional
 * @author Marco Aguiar Álvarez
 * @since Oct 10, 2026
 * @brief Implementación de las funciones recursivas básicas.
 */
#include "basic_functions.h"

#include <limits>
#include <stdexcept>

Natural Zero::Compute(const std::vector<Natural>&) const { return 0; }

Natural Successor::Compute(const std::vector<Natural>& arguments) const {
  if (arguments[0] == std::numeric_limits<Natural>::max()) {
    throw std::overflow_error("El resultado excede el rango de uint64_t.");
  }
  return arguments[0] + 1;
}

Projection::Projection(std::size_t index, std::size_t arity,
                       CallCounter& counter)
    : Function(arity, counter), index_(index) {
  if (index == 0 || index > arity) {
    throw std::invalid_argument("Indice de proyeccion fuera de rango.");
  }
}

Natural Projection::Compute(const std::vector<Natural>& arguments) const {
  return arguments[index_ - 1];
}
