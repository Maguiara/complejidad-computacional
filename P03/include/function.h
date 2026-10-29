/**
 * Universidad de La Laguna
 * Grado en Ingeniería Informática - Complejidad Computacional
 * @author Marco Aguiar Álvarez
 * @since Oct 10, 2026
 * @brief Clase base abstracta de las funciones de números naturales.
 */
#ifndef FUNCTION_H_
#define FUNCTION_H_

#include <cstddef>
#include <memory>
#include <vector>

#include "call_counter.h"
#include "natural.h"

/**
 * Función f: N^k -> N. Toda evaluación pasa por operator(), que comprueba la
 * aridad y registra la llamada; cada subclase define su cálculo en Compute().
 */
class Function {
 public:
  Function(std::size_t arity, CallCounter& counter)
      : arity_(arity), counter_(counter) {}
  virtual ~Function() = default;

  Natural operator()(const std::vector<Natural>& arguments) const;
  std::size_t GetArity() const { return arity_; }

 protected:
  virtual Natural Compute(const std::vector<Natural>& arguments) const = 0;

 private:
  std::size_t arity_;
  CallCounter& counter_;
};

using FunctionPtr = std::shared_ptr<const Function>;

#endif  // FUNCTION_H_
