/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad Computacional
 *
 * @author Marco Aguiar Álvarez
 * @since Oct 10, 2026
 * @brief Implementation of the Alphabet class. Provides operations
 *        to store and validate Turing machine alphabet symbols.
 */

#include "alphabet.h"

/**
 * @brief Adds a symbol to the alphabet.
 * @param symbol Symbol to add.
 */
void Alphabet::Add(char symbol) {
  symbols_.insert(symbol);
}

/**
 * @brief Checks whether a symbol belongs to the alphabet.
 * @param symbol Symbol to check.
 * @return true if the symbol exists, false otherwise.
 */
bool Alphabet::Contains(char symbol) const {
  return symbols_.find(symbol) != symbols_.end();
}

/**
 * @brief Checks whether every symbol of a word belongs to the alphabet.
 * @param word Word to validate.
 * @return true if all symbols belong to the alphabet, false otherwise.
 */
bool Alphabet::ValidateWord(const std::string& word) const {
  for (char symbol : word) {
    if (!Contains(symbol)) {
      return false;
    }
  }
  return true;
}

/**
 * @brief Returns the set of symbols in the alphabet.
 * @return Reference to the set of symbols.
 */
const std::set<char>& Alphabet::GetSymbols() const {
  return symbols_;
}