#include "resultado_csv.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include "configs.hpp"

void escribir(Resultado resultado) {
  // Puntero al archivo
  std::fstream streamEscritura;

  // Crea o abre un archivo existente
  streamEscritura.open(getAssetsPath("resultados.csv"),
                       std::ios::out | std::ios::app);

  streamEscritura << resultado.estado << "," << resultado.jugador1 << ","
                  << resultado.jugador2 << "," << resultado.tiempo << "\n";

  streamEscritura.close();
}

std::vector<Resultado> leer() {
  // Puntero de lectura
  std::fstream streamLectura;
  std::vector<Resultado> resultados;
  std::string linea, palabra;

  // Abre un archivo EXISTENTE
  streamLectura.open(getAssetsPath("resultados.csv"), std::ios::in);

  while (streamLectura >> linea) {
    std::vector<std::string> fila;

    // used for breaking words
    std::stringstream s(linea);

    // read every column data of a row and
    // store it in a string variable, 'word'
    while (std::getline(s, palabra, ',')) {
      // add all the column data
      // of a row to a vector
      fila.push_back(palabra);
    }

    resultados.push_back(Resultado(fila));
  }
  streamLectura.close();

  return resultados;
}
