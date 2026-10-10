/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad Computacional
 *
 * @author Marco Aguiar Álvarez
 * @since Oct 10, 2026
 * @brief Declaración de la clase Simulator. Ejecuta una máquina
 *        de Turing determinista multicinta.
 */

#ifndef SIMULATOR_H_
#define SIMULATOR_H_

#include <string>
#include <vector>

#include "tape.h"
#include "turing_machine.h"

/**
 * @class Simulator
 * @brief Simula la ejecución de una máquina de Turing multicinta.
 *
 * Gestiona las cintas, el estado actual y la aplicación de
 * transiciones hasta que la máquina se detiene.
 */
class Simulator {
 public:
  /**
   * @brief Construye un simulador a partir de una máquina de Turing.
   * @param machine Máquina que se desea simular.
   */
  explicit Simulator(const TuringMachine& machine);

  /**
   * @brief Ejecuta la máquina con una cadena de entrada.
   * @param input Cadena que se desea procesar.
   * @return true si la máquina se detiene en un estado final,
   *         false si se detiene en un estado no final.
   * @throws std::invalid_argument Si la cadena contiene símbolos
   *         que no pertenecen al alfabeto de entrada.
   */
  bool Run(const std::string& input);

  /**
   * @brief Obtiene el contenido de todas las cintas.
   * @return Vector con las representaciones de las cintas.
   */
  std::vector<std::string> GetTapeContents() const;

  /**
   * @brief Obtiene el estado actual de la máquina.
   * @return Referencia al estado actual.
   */
  const std::string& GetCurrentState() const;

 private:
  TuringMachine machine_;
  std::vector<Tape> tapes_;
  std::string current_state_;
};

#endif  // SIMULATOR_H_