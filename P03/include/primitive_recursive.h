/**
 * Universidad de La Laguna
 * Grado en Ingeniería Informática - Complejidad Computacional
 * @author Marco Aguiar Álvarez
 * @since Oct 10, 2026
 * @brief Funciones primitivas recursivas sobre números naturales.
 */
#ifndef PRIMITIVE_RECURSIVE_H_
#define PRIMITIVE_RECURSIVE_H_

#include <cstddef>
#include <cstdint>
#include <initializer_list>

class PrimitiveRecursive {
 public:
  using Natural = std::uint64_t;

  Natural Zero();
  Natural Successor(Natural value);
  Natural Projection(std::size_t index,
                     std::initializer_list<Natural> arguments);
  Natural Add(Natural x, Natural y);
  Natural Multiply(Natural x, Natural y);
  Natural Power(Natural x, Natural y);

  Natural GetCallCount() const { return call_count_; }
  void ResetCallCount() { call_count_ = 0; }

 private:
  // Evita agotar la pila de ejecución ante entradas demasiado grandes.
  static constexpr std::size_t kMaxDepth = 1024;
  class CallGuard {
   public:
    explicit CallGuard(PrimitiveRecursive& owner);
    ~CallGuard();
    CallGuard(const CallGuard&) = delete;
    CallGuard& operator=(const CallGuard&) = delete;
   private:
    PrimitiveRecursive& owner_;
  };
  Natural call_count_ = 0;
  std::size_t depth_ = 0;
};

#endif  // PRIMITIVE_RECURSIVE_H_
