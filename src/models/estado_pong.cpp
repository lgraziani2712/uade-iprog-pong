#include "estado_pong.hpp"
#include <stdexcept>

Resultado::Resultado() {}

Resultado::Resultado(std::vector<std::string> datos) {
  if (datos.size() != 4) {
    throw std::runtime_error(
        "Resultado tiene que ser un vector de exactamente 4 datos.");
  }
  estado = (PartidaEstado)std::stoi(datos[0]);
  jugador1 = std::stoi(datos[1]);
  jugador2 = std::stoi(datos[2]);
  tiempo = std::stod(datos[3]);
}
