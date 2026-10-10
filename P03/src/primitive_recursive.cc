/**
 * Universidad de La Laguna
 * Grado en Ingeniería Informática - Complejidad Computacional
 * @author Marco Aguiar Álvarez
 * @since Oct 10, 2026
 * @brief Implementación por composición y recursión primitiva.
 */
#include "primitive_recursive.h"

#include <iterator>
#include <limits>
#include <stdexcept>

PrimitiveRecursive::CallGuard::CallGuard(PrimitiveRecursive& owner)
    : owner_(owner) {
  if (owner_.depth_ >= kMaxDepth) {
    throw std::runtime_error("Se ha alcanzado el limite de profundidad recursiva (1024).");
  }
  if (owner_.call_count_ == std::numeric_limits<Natural>::max()) {
    throw std::overflow_error("El contador de llamadas excede el rango disponible.");
  }
  ++owner_.depth_;
  ++owner_.call_count_;
}

PrimitiveRecursive::CallGuard::~CallGuard() { --owner_.depth_; }

PrimitiveRecursive::Natural PrimitiveRecursive::Zero() {
  CallGuard guard(*this);
  return 0;
}

PrimitiveRecursive::Natural PrimitiveRecursive::Successor(Natural value) {
  CallGuard guard(*this);
  if (value == std::numeric_limits<Natural>::max()) {
    throw std::overflow_error("El resultado excede el rango de uint64_t.");
  }
  return value + 1;
}

PrimitiveRecursive::Natural PrimitiveRecursive::Projection(
    std::size_t index, std::initializer_list<Natural> arguments) {
  CallGuard guard(*this);
  if (index == 0 || index > arguments.size()) {
    throw std::invalid_argument("Indice de proyeccion fuera de rango.");
  }
  return *std::next(arguments.begin(), index - 1);
}

// suma(x, 0) = P_1^1(x); suma(x, y+1) = S(suma(x, y)).
PrimitiveRecursive::Natural PrimitiveRecursive::Add(Natural x, Natural y) {
  CallGuard guard(*this);
  if (y == 0) return Projection(1, {x});
  return Successor(Add(x, y - 1));
}

// producto(x, 0) = Z; producto(x, y+1) = suma(producto(x, y), x).
PrimitiveRecursive::Natural PrimitiveRecursive::Multiply(Natural x, Natural y) {
  CallGuard guard(*this);
  if (y == 0) return Zero();
  const Natural previous = Multiply(x, y - 1);
  return Add(previous, x);
}

// potencia(x, 0) = S(Z); potencia(x, y+1) = producto(potencia(x, y), x).
PrimitiveRecursive::Natural PrimitiveRecursive::Power(Natural x, Natural y) {
  CallGuard guard(*this);
  if (y == 0) return Successor(Zero());
  const Natural previous = Power(x, y - 1);
  return Multiply(previous, x);
}
