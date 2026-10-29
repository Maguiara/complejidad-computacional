/**
 * Universidad de La Laguna
 * Grado en Ingeniería Informática - Complejidad Computacional
 * @author Marco Aguiar Álvarez
 * @since Oct 10, 2026
 * @brief Operación de recursión primitiva.
 */
#ifndef PRIMITIVE_RECURSION_H_
#define PRIMITIVE_RECURSION_H_

#include <vector>

#include "function.h"

/**
 * f(x_1, ..., x_n, 0)   = g(x_1, ..., x_n)
 * f(x_1, ..., x_n, y+1) = h(x_1, ..., x_n, y, f(x_1, ..., x_n, y))
 * con g: N^n -> N y h: N^(n+2) -> N.
 */
class PrimitiveRecursion : public Function {
 public:
  PrimitiveRecursion(FunctionPtr base, FunctionPtr step, CallCounter& counter);

 protected:
  Natural Compute(const std::vector<Natural>& arguments) const override;

 private:
  FunctionPtr base_;
  FunctionPtr step_;
};

#endif  // PRIMITIVE_RECURSION_H_
