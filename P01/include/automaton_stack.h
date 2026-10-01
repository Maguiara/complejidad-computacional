/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad Computacional
 *
 * @author Marco Aguiar Álvarez
 * @since Sep 18, 2026
 */

#ifndef AUTOMATON_STACK_H
#define AUTOMATON_STACK_H

#include <vector>
#include <string>
#include <stdexcept>
#include "alphabet.h"

class AutomatonStack {
  public: 
  AutomatonStack(char initial_symbol) { stack_.push_back(initial_symbol);}
  char GetTop() const;
  bool IsEmpty() const;
  void ReplaceTop(const std::string& replacement);
  std::string ToString() const; // Para la parte de la traza 

  private:
    std::vector<char> stack_{};
}; 


#endif // AUTOMATON_STACK_H