/**
 * Universidad de La Laguna
 * Grado en Ingeniería Informática - Complejidad Computacional
 * @author Marco Aguiar Álvarez
 * @since Oct 10, 2026
 * @brief Implementación de la composición.
 */
#include "composition.h"

#include <stdexcept>
#include <utility>

std::size_t Composition::InnerArity(const std::vector<FunctionPtr>& inner) {
  if (inner.empty()) {
    throw std::invalid_argument("La composicion necesita al menos una funcion interna.");
  }
  return inner.front()->GetArity();
}

Composition::Composition(FunctionPtr outer, std::vector<FunctionPtr> inner,
                         CallCounter& counter)
    : Function(InnerArity(inner), counter),
      outer_(std::move(outer)),
      inner_(std::move(inner)) {
  if (outer_->GetArity() != inner_.size()) {
    throw std::invalid_argument("La aridad de h no coincide con el numero de funciones g_i.");
  }
  for (const FunctionPtr& function : inner_) {
    if (function->GetArity() != GetArity()) {
      throw std::invalid_argument("Todas las funciones g_i deben tener la misma aridad.");
    }
  }
}

Natural Composition::Compute(const std::vector<Natural>& arguments) const {
  std::vector<Natural> values;
  values.reserve(inner_.size());
  for (const FunctionPtr& function : inner_) {
    values.push_back((*function)(arguments));
  }
  return (*outer_)(values);
}
