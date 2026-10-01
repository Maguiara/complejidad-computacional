/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad Computacional
 *
 * @author Marco Aguiar Álvarez
 * @since Sep 18, 2026
 */



#include "alphabet.h"


/**
 * @brief Añade un símbolo al alfabeto.
 * @param symbol El símbolo a añadir.
*/
void Alphabet::Add(const char symbol) {
  symbols_.insert(symbol);
}

/**
 * @brief Comprueba si un símbolo está presente en el alfabeto.
 * @param symbol El símbolo a comprobar.
 * @return true si el símbolo está presente, false en caso contrario.
 */
bool Alphabet::Contains(const char symbol) const {
  return symbols_.find(symbol) != symbols_.end();
}

/**
 * @brief Sobrecarga del operador de inserción para imprimir el alfabeto.
 * @param os El flujo de salida.
 * @param alphabet El alfabeto a imprimir.
 * @return El flujo de salida.
 */
std::ostream& operator<<(std::ostream& os, const Alphabet& alphabet) {
  os << "{";
  for (const auto& symbol : alphabet.symbols_) 
    os << symbol << ' ';
  os << "}";
  return os;
}