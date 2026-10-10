/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad Computacional
 *
 * @author Marco Aguiar Álvarez
 * @since Oct 10, 2026
 * @brief Implementación de la clase Tape. Gestiona las celdas,
 *        las operaciones de lectura y escritura y los movimientos
 *        de la cabeza.
 */

#include "tape.h"

#include <algorithm>
#include <stdexcept>

/**
 * @brief Construye una cinta vacía.
 * @param blank_symbol Símbolo que representa una celda vacía.
 */
Tape::Tape(char blank_symbol) : blank_symbol_(blank_symbol) {}

/**
 * @brief Carga una cadena de entrada en la cinta.
 * @param input Cadena que se escribirá en la cinta.
 */
void Tape::LoadInput(const std::string& input) {
  cells_.clear();
  head_position_ = 0;

  for (size_t i = 0; i < input.size(); ++i) {
    if (input[i] != blank_symbol_) {
      cells_[static_cast<long long>(i)] = input[i];
    }
  }
}

/**
 * @brief Lee el símbolo situado bajo la cabeza.
 * @return Símbolo de la posición actual.
 */
char Tape::Read() const {
  auto it = cells_.find(head_position_);
  if (it == cells_.end()) return blank_symbol_;
  return it->second;
}

/**
 * @brief Escribe un símbolo en la posición actual.
 * @param symbol Símbolo que se escribirá.
 */
void Tape::Write(char symbol) {
  if (symbol == blank_symbol_) {
    cells_.erase(head_position_);
  } else {
    cells_[head_position_] = symbol;
  }
}

/**
 * @brief Desplaza la cabeza de lectura y escritura.
 * @param direction Dirección del movimiento: L, R o S.
 * @throws std::invalid_argument Si la dirección no es válida.
 */
void Tape::Move(char direction) {
  switch (direction) {
    case 'L':
      --head_position_;
      break;
    case 'R':
      ++head_position_;
      break;
    case 'S':
      break;
    default:
      throw std::invalid_argument("Invalid tape movement.");
  }
}

/**
 * @brief Devuelve el contenido de la cinta indicando la posición
 *        de la cabeza mediante corchetes.
 * @return Cadena que representa el contenido de la cinta.
 */
std::string Tape::ToString() const {
  long long first = head_position_;
  long long last = head_position_;

  if (!cells_.empty()) {
    first = std::min(first, cells_.begin()->first);
    last = std::max(last, cells_.rbegin()->first);
  }

  std::string result;

  for (long long i = first; ; ++i) {
    auto it = cells_.find(i);
    char symbol = (it == cells_.end()) ? blank_symbol_ : it->second;

    if (i == head_position_) {
      result += "[";
      result += symbol;
      result += "]";
    } else {
      result += symbol;
    }

    if (i == last) {
      break;
    }
  }

  return result;
}