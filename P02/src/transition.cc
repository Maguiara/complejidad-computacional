/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad Computacional
 *
 * @author Marco Aguiar Álvarez
 * @since Oct 10, 2026
 * @brief Implementación de la clase Transition. Gestiona las
 *        transiciones de una máquina de Turing multicinta.
 */

#include "transition.h"

#include <stdexcept>

/**
 * @brief Construye una transición de la máquina de Turing.
 * @param source_state Estado de origen.
 * @param read_symbols Símbolos que deben leer las cabezas.
 * @param destination_state Estado de destino.
 * @param write_symbols Símbolos que se escribirán en las cintas.
 * @param movements Movimientos de las cabezas: L, R o S.
 * @throws std::invalid_argument Si la transición no tiene una
 *         estructura válida.
 */
Transition::Transition(const std::string& source_state,
                       const std::vector<char>& read_symbols,
                       const std::string& destination_state,
                       const std::vector<char>& write_symbols,
                       const std::vector<char>& movements)
                      : source_state_(source_state),
                        read_symbols_(read_symbols),
                        destination_state_(destination_state),
                        write_symbols_(write_symbols),
                        movements_(movements) {
  if (read_symbols_.empty() || read_symbols_.size() != write_symbols_.size() || read_symbols_.size() != movements_.size()) {
    throw std::invalid_argument("Las cantidades de simbolos y movimientos no coinciden. (read_symbols: " + std::to_string(read_symbols_.size()) +
                                ", write_symbols: " + std::to_string(write_symbols_.size()) +
                                ", movements: " + std::to_string(movements_.size()) + ")");
  }

  for (char movement : movements_) {
    if (movement != 'L' && movement != 'R' && movement != 'S') {
      throw std::invalid_argument("Movimiento de cinta no valido. (" + std::string(1, movement) + " is not L, R or S)");
    }
  }
}

/**
 * @brief Comprueba si la transición puede aplicarse.
 * @param current_state Estado actual de la máquina.
 * @param current_symbols Símbolos leídos en las cintas.
 * @return true si coincide el estado y todos los símbolos leídos.
 */
bool Transition::IsApplicable( const std::string& current_state, const std::vector<char>& current_symbols) const {
  return source_state_ == current_state && read_symbols_ == current_symbols;
}

/**
 * @brief Obtiene el estado de origen.
 * @return Referencia al estado de origen.
 */
const std::string& Transition::GetSourceState() const {
  return source_state_;
}

/**
 * @brief Obtiene los símbolos que debe leer la transición.
 * @return Referencia al vector de símbolos leídos.
 */
const std::vector<char>& Transition::GetReadSymbols() const {
  return read_symbols_;
}

/**
 * @brief Obtiene el estado de destino.
 * @return Referencia al estado de destino.
 */
const std::string& Transition::GetDestinationState() const {
  return destination_state_;
}

/**
 * @brief Obtiene los símbolos que deben escribirse.
 * @return Referencia al vector de símbolos escritos.
 */
const std::vector<char>& Transition::GetWriteSymbols() const {
  return write_symbols_;
}

/**
 * @brief Obtiene los movimientos de las cabezas.
 * @return Referencia al vector de movimientos.
 */
const std::vector<char>& Transition::GetMovements() const {
  return movements_;
}