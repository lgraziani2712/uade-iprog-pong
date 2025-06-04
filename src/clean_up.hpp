// Dice al compilador que solo lo incluya una vez aún cuando se quiera incluir
// múltiples veces en múltiples archivos
#pragma once

#include <functional>

class FinalAction {
 public:
  // Constructor. Recibe una función lambda como primer y único parámetro.
  // La lógica después de los dos puntos es la inicialización del atributo
  // cleanUp. Es la forma abreviadad de `this->cleanUp = std::move(fn);`. Con
  // `std::move` le decimos al compilador que ya dejamos de usar el parámetro
  // `fn`, y que lo puede mover como atributo de la clase en vez de copiarlo.
  // Copiar `std::function` es caro.
  FinalAction(std::function<void()> fn);
  // Destructor:
  // Ejecuta la función lambda cleanUp() (que almacenamos al instanciar esta
  // clase) antes de destruir la instancia. Justamente esto simula ser la
  // últimam acción antes de cerrar la ejecución. Así, podemos ejecutar las
  // operaciones de limpieza de datos de SDL, como la pantalla o el renderer
  // justo antes de cerrar.
  ~FinalAction();

 private:
  // Declara el atributo "cleanUp", de tipo std::function, siendo además una
  // función vacía: no tiene parámetros y su retorno es void. Este atributo se
  // almacena al construir una instancia de esta clase para después invocarla en
  // el destructor.
  std::function<void()> cleanUp;
};

// Esta función facilita la creación de la instancia de FinalAction.
FinalAction cleanUpCreation(std::function<void()> fn);
