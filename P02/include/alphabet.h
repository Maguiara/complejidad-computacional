/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad Computacional
 *
 * @author Marco Aguiar Álvarez
 * @since Oct 10, 2026
 * @brief Declaration of the Alphabet class. Manages the symbols
 *        belonging to a Turing machine alphabet.
 */

#ifndef ALPHABET_H_
#define ALPHABET_H_

#include <set>
#include <string>

/**
 * @class Alphabet
 * @brief Represents a set of symbols used by a Turing machine.
 *
 * This class can represent both the input alphabet and the
 * tape alphabet.
 */
class Alphabet {
 public:
  Alphabet() = default;
  void Add(char symbol);
  bool Contains(char symbol) const;
  bool ValidateWord(const std::string& word) const; // Veremos si lo uso o no
  const std::set<char>& GetSymbols() const;

 private:
  std::set<char> symbols_;
};

#endif  // ALPHABET_H_