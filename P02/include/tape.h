/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad Computacional
 *
 * @author Marco Aguiar Álvarez
 * @since Oct 10, 2026
 * @brief Declaración de la clase Tape. Representa una cinta infinita
 *        en ambas direcciones para una máquina de Turing.
 */

#ifndef TAPE_H_
#define TAPE_H_

#include <map>
#include <string>

/**
 * @class Tape
 * @brief Representa una cinta infinita en ambas direcciones.
 *
 * Almacena los símbolos de la cinta y gestiona la posición
 * de la cabeza de lectura y escritura.
 */
class Tape {
 public:
  explicit Tape(char blank_symbol);
  void LoadInput(const std::string& input);
  char Read() const;
  void Write(char symbol);
  void Move(char direction);
  std::string ToString() const;

 private:
  std::map<long long, char> cells_;
  long long head_position_ = 0;
  char blank_symbol_;
};

#endif  // TAPE_H_