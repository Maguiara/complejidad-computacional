/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad Computacional
 *
 * @author Marco Aguiar Álvarez
 * @since Oct 10, 2026
 * @brief Implementación de la clase Simulator. Ejecuta las
 *        transiciones de una máquina de Turing multicinta.
 */

#include "simulator.h"

#include <stdexcept>

/**
 * @brief Construye un simulador a partir de una máquina de Turing.
 * @param machine Máquina que se desea simular.
 */
Simulator::Simulator(const TuringMachine& machine)
    : machine_(machine),
      current_state_(machine.GetInitialState()) {
  for (size_t i = 0; i < machine_.GetTapeCount(); ++i) {
    tapes_.emplace_back(machine_.GetBlankSymbol());
  }
}

/**
 * @brief Ejecuta la máquina con una cadena de entrada.
 * @param input Cadena que se desea procesar.
 * @return true si la máquina se detiene en un estado final,
 *         false si se detiene en un estado no final.
 * @throws std::invalid_argument Si la entrada no es válida.
 */
bool Simulator::Run(const std::string& input) {
  // Comprobamos que la cadena pertenece al alfabeto de entrada.
  if (!machine_.IsValidInput(input)) {
    throw std::invalid_argument(
        "La cadena contiene simbolos que no pertenecen "
        "al alfabeto de entrada.");
  }

  // Reiniciamos el estado actual.
  current_state_ = machine_.GetInitialState();

  // Reiniciamos todas las cintas.
  for (auto& tape : tapes_) {
    tape.LoadInput("");
  }

  // Cargamos la entrada únicamente en la primera cinta.
  tapes_[0].LoadInput(input);

  // Ejecutamos hasta que no exista una transición aplicable.
  while (true) {
    std::vector<char> read_symbols;

    // Leemos el símbolo bajo cada cabeza.
    for (const auto& tape : tapes_) {
      read_symbols.push_back(tape.Read());
    }

    // Buscamos una transición aplicable.
    const Transition* transition =
        machine_.FindApplicableTransition(current_state_, read_symbols);

    // Si no existe, la máquina se detiene.
    if (transition == nullptr) {
      break;
    }

    // Obtenemos los elementos de la transición.
    const std::vector<char>& write_symbols =
        transition->GetWriteSymbols();

    const std::vector<char>& movements =
        transition->GetMovements();

    // Escribimos los símbolos en todas las cintas.
    for (size_t i = 0; i < tapes_.size(); ++i) {
      tapes_[i].Write(write_symbols[i]);
    }

    // Movemos las cabezas de todas las cintas.
    for (size_t i = 0; i < tapes_.size(); ++i) {
      tapes_[i].Move(movements[i]);
    }

    // Actualizamos el estado actual.
    current_state_ = transition->GetDestinationState();
  }

  // Solo comprobamos la aceptación cuando la máquina se detiene.
  return machine_.IsFinalState(current_state_);
}

/**
 * @brief Obtiene el contenido de todas las cintas.
 * @return Vector con las representaciones de las cintas.
 */
std::vector<std::string> Simulator::GetTapeContents() const {
  std::vector<std::string> contents;

  for (const auto& tape : tapes_) {
    contents.push_back(tape.ToString());
  }

  return contents;
}

/**
 * @brief Obtiene el estado actual de la máquina.
 * @return Referencia al estado actual.
 */
const std::string& Simulator::GetCurrentState() const {
  return current_state_;
}