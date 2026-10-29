/**
 * Universidad de La Laguna
 * Grado en Ingeniería Informática - Complejidad Computacional
 * @author Marco Aguiar Álvarez
 * @since Oct 10, 2026
 * @brief Funciones recursivas básicas: cero, sucesor y proyecciones.
 */
#ifndef BASIC_FUNCTIONS_H_
#define BASIC_FUNCTIONS_H_

#include <cstddef>
#include <vector>

#include "function.h"

/** Z: N -> N, Z(x) = 0. */
class Zero : public Function {
 public:
  explicit Zero(CallCounter& counter) : Function(1, counter) {}

 protected:
  Natural Compute(const std::vector<Natural>& arguments) const override;
};

/** S: N -> N, S(x) = x + 1. */
class Successor : public Function {
 public:
  explicit Successor(CallCounter& counter) : Function(1, counter) {}

 protected:
  Natural Compute(const std::vector<Natural>& arguments) const override;
};

/** P_i^n: N^n -> N, P_i^n(x_1, ..., x_n) = x_i. */
class Projection : public Function {
 public:
  Projection(std::size_t index, std::size_t arity, CallCounter& counter);

 protected:
  Natural Compute(const std::vector<Natural>& arguments) const override;

 private:
  std::size_t index_;
};

#endif  // BASIC_FUNCTIONS_H_
