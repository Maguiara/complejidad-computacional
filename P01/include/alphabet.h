/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad Computacional
 *
 * @author Marco Aguiar Álvarez
 * @since Sep 18, 2026
 */


#ifndef ALPHABET_H
#define ALPHABET_H

#include <set>
#include <ostream>

class Alphabet {
  public:
  //constante estatica para epsilon = '.'
  static const char EPSILON = '.';
  Alphabet() = default;

  void Add(char symbol);
  bool Contains(char symbol) const;
  std::string ToString() const {
    std::string result;
    for (const auto& symbol : symbols_) {
      result += symbol;
    }
    return result;
  }

  friend std::ostream& operator<<(std::ostream& os, const Alphabet& alphabet);

  private:
    std::set<char> symbols_{};
};

#endif  // ALPHABET_H