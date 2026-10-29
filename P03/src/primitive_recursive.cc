/**
 * Universidad de La Laguna
 * Grado en Ingeniería Informática - Complejidad Computacional
 * @author Marco Aguiar Álvarez
 * @since Oct 10, 2026
 * @brief Definición formal de suma, producto y potencia.
 */
#include "primitive_recursive.h"

#include <memory>
#include <vector>

#include "basic_functions.h"
#include "composition.h"
#include "primitive_recursion.h"

FunctionPtr PrimitiveRecursive::Project(std::size_t index, std::size_t arity) {
  return std::make_shared<Projection>(index, arity, counter_);
}

PrimitiveRecursive::PrimitiveRecursive() {
  zero_ = std::make_shared<Zero>(counter_);
  successor_ = std::make_shared<Successor>(counter_);

  // suma(x, 0)   = P_1^1(x)
  // suma(x, y+1) = S(P_3^3(x, y, suma(x, y)))
  const FunctionPtr add_step = std::make_shared<Composition>(
      successor_, std::vector<FunctionPtr>{Project(3, 3)}, counter_);
  add_ = std::make_shared<PrimitiveRecursion>(Project(1, 1), add_step, counter_);

  // producto(x, 0)   = Z(x)
  // producto(x, y+1) = suma(P_3^3(x, y, p), P_1^3(x, y, p))
  const FunctionPtr multiply_step = std::make_shared<Composition>(
      add_, std::vector<FunctionPtr>{Project(3, 3), Project(1, 3)}, counter_);
  multiply_ = std::make_shared<PrimitiveRecursion>(zero_, multiply_step, counter_);

  // potencia(x, 0)   = S(Z(x))
  // potencia(x, y+1) = producto(P_3^3(x, y, q), P_1^3(x, y, q))
  const FunctionPtr power_base = std::make_shared<Composition>(
      successor_, std::vector<FunctionPtr>{zero_}, counter_);
  const FunctionPtr power_step = std::make_shared<Composition>(
      multiply_, std::vector<FunctionPtr>{Project(3, 3), Project(1, 3)}, counter_);
  power_ = std::make_shared<PrimitiveRecursion>(power_base, power_step, counter_);
}
