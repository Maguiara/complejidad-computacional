/**
 * Universidad de La Laguna
 * Grado en Ingeniería Informática - Complejidad Computacional
 * @author Marco Aguiar Álvarez
 * @since Oct 10, 2026
 * @brief Implementación del contador de llamadas.
 */
#include "call_counter.h"

#include <limits>
#include <stdexcept>

CallCounter::Scope::Scope(CallCounter& counter) : counter_(counter) {
  if (counter_.depth_ >= kMaxDepth) {
    throw std::runtime_error(
        "Se ha alcanzado el limite de profundidad recursiva (1024).");
  }
  if (counter_.count_ == std::numeric_limits<Natural>::max()) {
    throw std::overflow_error("El contador de llamadas excede el rango disponible.");
  }
  ++counter_.depth_;
  ++counter_.count_;
}

CallCounter::Scope::~Scope() { --counter_.depth_; }
