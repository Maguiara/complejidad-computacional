/**
 * Universidad de La Laguna
 * Grado en Ingeniería Informática - Complejidad Computacional
 * @author Marco Aguiar Álvarez
 * @since Oct 10, 2026
 * @brief Implementación de la recursión primitiva.
 */
#include "primitive_recursion.h"

#include <stdexcept>
#include <utility>

PrimitiveRecursion::PrimitiveRecursion(FunctionPtr base, FunctionPtr step,
                                       CallCounter& counter)
    : Function(base->GetArity() + 1, counter),
      base_(std::move(base)),
      step_(std::move(step)) {
  if (step_->GetArity() != base_->GetArity() + 2) {
    throw std::invalid_argument("La aridad de h debe ser la de g mas 2.");
  }
}

Natural PrimitiveRecursion::Compute(const std::vector<Natural>& arguments) const {
  const Natural y = arguments.back();
  std::vector<Natural> parameters(arguments.begin(), arguments.end() - 1);
  if (y == 0) return (*base_)(parameters);

  // f(x, y) = h(x, y - 1, f(x, y - 1)): la llamada recursiva es una
  // evaluación más de esta misma función.
  std::vector<Natural> previous_arguments = parameters;
  previous_arguments.push_back(y - 1);
  const Natural previous = (*this)(previous_arguments);

  parameters.push_back(y - 1);
  parameters.push_back(previous);
  return (*step_)(parameters);
}
