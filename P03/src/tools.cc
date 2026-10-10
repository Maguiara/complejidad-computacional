/** @brief Validación estricta de las opciones -x e -y. */
#include "tools.h"

#include <charconv>
#include <stdexcept>
#include <string>
#include <system_error>

Options ParseArguments(int argc, char* argv[]) {
  Options options;
  bool has_x = false;
  bool has_y = false;
  for (int i = 1; i < argc; ++i) {
    const std::string flag = argv[i];
    if (flag != "-x" && flag != "-y") {
      throw std::invalid_argument("Opcion desconocida: " + flag);
    }
    bool& present = flag == "-x" ? has_x : has_y;
    if (present) throw std::invalid_argument("Opcion repetida: " + flag);
    if (++i >= argc) throw std::invalid_argument("Falta el valor de " + flag);
    const std::string token = argv[i];
    if (token.empty() || token.find_first_not_of("0123456789") != std::string::npos) {
      throw std::invalid_argument("El valor de " + flag + " debe ser un numero natural.");
    }
    PrimitiveRecursive::Natural value = 0;
    const auto result = std::from_chars(token.data(), token.data() + token.size(), value);
    if (result.ec != std::errc{} || result.ptr != token.data() + token.size()) {
      throw std::invalid_argument("El valor de " + flag + " excede el rango de uint64_t.");
    }
    (flag == "-x" ? options.x : options.y) = value;
    present = true;
  }
  if (!has_x || !has_y) {
    throw std::invalid_argument("Es obligatorio indicar -x e -y.");
  }
  return options;
}
