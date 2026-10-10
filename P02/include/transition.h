/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad Computacional
 *
 * @author Marco Aguiar Álvarez
 * @since Oct 10, 2026
 * @brief Declaración de la clase Transition. Representa una
 *        transición de una máquina de Turing multicinta.
 */

#ifndef TRANSITION_H_
#define TRANSITION_H_

#include <string>
#include <vector>

/**
 * @class Transition
 * @brief Representa una transición de una máquina de Turing multicinta.
 *
 * Almacena el estado de origen, los símbolos leídos, el estado
 * de destino, los símbolos escritos y los movimientos de las cabezas.
 */
class Transition {
 public:
  /**
   * @brief Construye una transición de la máquina de Turing.
   * @param source_state Estado de origen.
   * @param read_symbols Símbolos que deben leer las cabezas.
   * @param destination_state Estado de destino.
   * @param write_symbols Símbolos que se escribirán en las cintas.
   * @param movements Movimientos de las cabezas: L, R o S.
   * @throws std::invalid_argument Si las cantidades de símbolos
   *         y movimientos no coinciden o algún movimiento no es válido.
   */
  Transition(const std::string& source_state,
             const std::vector<char>& read_symbols,
             const std::string& destination_state,
             const std::vector<char>& write_symbols,
             const std::vector<char>& movements);

  /**
   * @brief Comprueba si la transición puede aplicarse.
   * @param current_state Estado actual de la máquina.
   * @param current_symbols Símbolos leídos en las cintas.
   * @return true si la transición es aplicable, false en caso contrario.
   */
  bool IsApplicable(const std::string& current_state,
                    const std::vector<char>& current_symbols) const;

  /**
   * @brief Obtiene el estado de origen.
   * @return Referencia al estado de origen.
   */
  const std::string& GetSourceState() const;

  /**
   * @brief Obtiene los símbolos que debe leer la transición.
   * @return Referencia al vector de símbolos leídos.
   */
  const std::vector<char>& GetReadSymbols() const;

  /**
   * @brief Obtiene el estado de destino.
   * @return Referencia al estado de destino.
   */
  const std::string& GetDestinationState() const;

  /**
   * @brief Obtiene los símbolos que deben escribirse.
   * @return Referencia al vector de símbolos escritos.
   */
  const std::vector<char>& GetWriteSymbols() const;

  /**
   * @brief Obtiene los movimientos de las cabezas.
   * @return Referencia al vector de movimientos.
   */
  const std::vector<char>& GetMovements() const;

 private:
  std::string source_state_;
  std::vector<char> read_symbols_;
  std::string destination_state_;
  std::vector<char> write_symbols_;
  std::vector<char> movements_;
};

#endif  // TRANSITION_H_