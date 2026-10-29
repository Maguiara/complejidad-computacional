/**
 * Universidad de La Laguna
 * Grado en Ingeniería Informática - Complejidad Computacional
 * @author Marco Aguiar Álvarez
 * @since Oct 10, 2026
 * @brief Operación de composición (con combinación de las funciones internas).
 */
#ifndef COMPOSITION_H_
#define COMPOSITION_H_

#include <vector>

#include "function.h"

/**
 * f(x_1, ..., x_n) = h(g_1(x_1, ..., x_n), ..., g_m(x_1, ..., x_n)),
 * con h: N^m -> N y g_i: N^n -> N.
 */
class Composition : public Function {
 public:
  Composition(FunctionPtr outer, std::vector<FunctionPtr> inner,
              CallCounter& counter);

 protected:
  Natural Compute(const std::vector<Natural>& arguments) const override;

 private:
  static std::size_t InnerArity(const std::vector<FunctionPtr>& inner);

  FunctionPtr outer_;
  std::vector<FunctionPtr> inner_;
};

#endif  // COMPOSITION_H_
