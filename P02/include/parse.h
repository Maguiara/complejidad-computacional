
/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad Computacional
 *
 * @author Marco Aguiar Álvarez
 * @since Oct 10, 2026
 * @brief Declaración de la clase Parser. Lee y valida archivos
 *        de configuración de máquinas de Turing multicinta.
 */

#ifndef PARSE_H_
#define PARSE_H_

#include <cstddef>
#include <fstream>
#include <string>
#include <vector>

#include "turing_machine.h"

/**
 * @class Parser
 * @brief Interpreta y valida archivos de máquinas de Turing.
 *
 * Lee los componentes de la máquina y comprueba que cumplen
 * las restricciones de una máquina de Turing determinista.
 */
class Parser {
 public:
  /**
   * @brief Lee un archivo y construye una máquina de Turing.
   * @param filename Ruta del archivo de configuración.
   * @return Máquina de Turing construida.
   * @throws std::runtime_error Si el archivo no es válido.
   */
  static TuringMachine Parse(const std::string& filename);

 private:
  /**
   * @brief Obtiene la siguiente línea válida del archivo.
   * @param file Archivo de entrada.
   * @param line Línea leída.
   * @return true si existe una línea válida, false si termina el archivo.
   */
  static bool GetNextValidLine(std::ifstream& file, std::string& line);

  /**
   * @brief Valida una transición de la máquina.
   * @param transition Transición que se desea comprobar.
   * @param states Conjunto de estados válidos.
   * @param tape_alphabet Alfabeto de cinta.
   * @param tape_count Número de cintas.
   * @param transitions Transiciones leídas anteriormente.
   * @throws std::runtime_error Si la transición no es válida.
   */
  static void ValidateTransition(
      const Transition& transition,
      const StateSet& states,
      const Alphabet& tape_alphabet,
      size_t tape_count,
      const std::vector<Transition>& transitions);

  /**
   * @brief Lee el conjunto de estados.
   * @param file Archivo de entrada.
   * @return Conjunto de estados.
   */
  static StateSet ReadStates(std::ifstream& file);

  /**
   * @brief Lee un alfabeto del archivo.
   * @param file Archivo de entrada.
   * @param error_msg Mensaje de error si falta el alfabeto.
   * @return Alfabeto leído.
   */
  static Alphabet ReadAlphabet(
      std::ifstream& file, const std::string& error_msg);

  /**
   * @brief Lee y valida el estado inicial.
   * @param file Archivo de entrada.
   * @param states Conjunto de estados válidos.
   * @return Estado inicial.
   */
  static std::string ReadInitialState(
      std::ifstream& file, const StateSet& states);

  /**
   * @brief Lee y valida el símbolo blanco.
   * @param file Archivo de entrada.
   * @param input_alphabet Alfabeto de entrada.
   * @param tape_alphabet Alfabeto de cinta.
   * @return Símbolo blanco.
   */
  static char ReadBlankSymbol(
      std::ifstream& file,
      const Alphabet& input_alphabet,
      const Alphabet& tape_alphabet);

  /**
   * @brief Lee y valida los estados finales.
   * @param file Archivo de entrada.
   * @param states Conjunto de estados válidos.
   * @return Conjunto de estados finales.
   */
  static StateSet ReadFinalStates(
      std::ifstream& file, const StateSet& states);

  /**
   * @brief Lee y valida el número de cintas.
   * @param file Archivo de entrada.
   * @return Número de cintas.
   */
  static size_t ReadTapeCount(std::ifstream& file);

  /**
   * @brief Lee y valida las transiciones.
   * @param file Archivo de entrada.
   * @param states Conjunto de estados válidos.
   * @param tape_alphabet Alfabeto de cinta.
   * @param tape_count Número de cintas.
   * @return Vector de transiciones.
   */
  static std::vector<Transition> ReadTransitions(
      std::ifstream& file,
      const StateSet& states,
      const Alphabet& tape_alphabet,
      size_t tape_count);
};

#endif  // PARSE_H_
