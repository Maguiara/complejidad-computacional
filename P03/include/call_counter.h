/**
 * Universidad de La Laguna
 * Grado en Ingeniería Informática - Complejidad Computacional
 * @author Marco Aguiar Álvarez
 * @since Oct 10, 2026
 * @brief Contador de llamadas a funciones y control de la profundidad.
 */
#ifndef CALL_COUNTER_H_
#define CALL_COUNTER_H_

#include <cstddef>

#include "natural.h"

/**
 * Cuenta cada evaluación de una función (básica, compuesta o definida por
 * recursión primitiva) y vigila la profundidad de anidamiento para no agotar
 * la pila de ejecución ante entradas demasiado grandes.
 */
class CallCounter {
 public:
  /** Registra una llamada mientras el objeto está vivo (RAII). */
  class Scope {
   public:
    explicit Scope(CallCounter& counter);
    ~Scope();
    Scope(const Scope&) = delete;
    Scope& operator=(const Scope&) = delete;

   private:
    CallCounter& counter_;
  };

  Natural GetCount() const { return count_; }
  void Reset() { count_ = 0; }

 private:
  static constexpr std::size_t kMaxDepth = 1024;
  Natural count_ = 0;
  std::size_t depth_ = 0;
};

#endif  // CALL_COUNTER_H_
