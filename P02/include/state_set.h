/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Complejidad Computacional
 *
 * @author Marco Aguiar Álvarez
 * @since Sep 18, 2026
 */


#ifndef STATE_SET_H
#define STATE_SET_H

#include <set>
#include <string>
#include <stdexcept>

class StateSet {
  public:
    StateSet() = default;

    void Add(const std::string& state);
    bool Contains(const std::string& state) const;

    void CheckIfFinalStatesAreSubsetOfStates(const StateSet& final_states) const;
    bool IsEmpty() const { return states_.empty(); }
    std::string ToString() const {
      std::string result;
      for (const auto& state : states_) {
        result += state + " ";
      }
      return result;
    }

    std::set<std::string> GetStates() const { return states_; }

  private:
    std::set<std::string> states_{};
};

#endif  // STATE_SET_H