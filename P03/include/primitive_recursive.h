/**
 * Universidad de La Laguna
 * Grado en Ingeniería Informática - Complejidad Computacional
 * @author Marco Aguiar Álvarez
 * @since Oct 10, 2026
 * @brief Construcción de suma, producto y potencia como funciones primitivas
 *        recursivas a partir de Z, S y P_i^n.
 */
#ifndef PRIMITIVE_RECURSIVE_H_
#define PRIMITIVE_RECURSIVE_H_

#include "call_counter.h"
#include "function.h"
#include "natural.h"

class PrimitiveRecursive {
 public:
  using Natural = ::Natural;

  PrimitiveRecursive();
  PrimitiveRecursive(const PrimitiveRecursive&) = delete;
  PrimitiveRecursive& operator=(const PrimitiveRecursive&) = delete;

  Natural Add(Natural x, Natural y) { return (*add_)({x, y}); }
  Natural Multiply(Natural x, Natural y) { return (*multiply_)({x, y}); }
  Natural Power(Natural x, Natural y) { return (*power_)({x, y}); }

  Natural GetCallCount() const { return counter_.GetCount(); }
  void ResetCallCount() { counter_.Reset(); }

 private:
  FunctionPtr Project(std::size_t index, std::size_t arity);

  CallCounter counter_;
  FunctionPtr zero_;
  FunctionPtr successor_;
  FunctionPtr add_;
  FunctionPtr multiply_;
  FunctionPtr power_;
};

#endif  // PRIMITIVE_RECURSIVE_H_
