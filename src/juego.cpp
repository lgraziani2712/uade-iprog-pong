#include "juego.hpp"
#include <array>
#include <memory>
#include "configs.hpp"
#include "creation.hpp"
#include "game_loop.hpp"
#include "models/texto.hpp"
#include "renders/pong_render.hpp"

Juego::Juego() {
  window = createWindow();
  renderer = createRenderer(window);
  // Instancio las cosas que necesito
  fuente = TTF_OpenFont(getAssetsPath("HurmitNerdFont-Bold.otf").c_str(), 40);

  if (fuente == NULL) {
    throw std::runtime_error(SDL_GetError());
  }
  // Se libera automáticamente al finalizar la función main
  render = std::make_unique<PongRender>(window, renderer, fuente);
}
Juego::~Juego() {
  if (renderer != NULL) {
    SDL_DestroyRenderer(renderer);
  }
  if (window != NULL) {
    SDL_DestroyWindow(window);
  }

  if (fuente != NULL) {
    TTF_CloseFont(fuente);
  }
}
// Inicializa el loop inicial del juego
void Juego::Init() {
  while (estado != JuegoEstado::EXIT) {
    switch (estado) {
      case JuegoEstado::MENU:
        Menu();
        break;
      case JuegoEstado::PLAY:
        Play();
        break;
      case JuegoEstado::PAUSA:
        Pausa();
        break;
      case JuegoEstado::FINALIZADO:
        Finalizado();
        break;
      case JuegoEstado::RANKING:
        Ranking();
        break;
    }
  }
};

// Sigue la misma lógica que el gameloop del pong:
// 1. Leo los inputs.
// 2. Calculo los cambios de lógica según los cambios de los inputs.
// 3. Renderizo el menú con el nuevo estado.
// 4. Duermo el proceso con la idea de que sean 24fps.
void Juego::Menu() {
  SDL_GetWindowSize(window, &width, &height);
  SDL_Event event;
  // 0 a 3
  int posicion = 0;
  std::array<const char *, 3> textosNoSeleccionados = {"Jugar", "Ranking",
                                                       "Salir"};
  std::array<const char *, 3> textosSeleccionados = {"JUGAR", "RANKING",
                                                     "SALIR"};

  std::array<Texto, 3> textos = {
      Texto(renderer, fuente, textosSeleccionados[0],
            Vec(width / 2, (height / 2) - 100)),
      Texto(renderer, fuente, textosNoSeleccionados[1],
            Vec(width / 2, height / 2)),
      Texto(renderer, fuente, textosNoSeleccionados[2],
            Vec(width / 2, (height / 2) + 100))};

  while (estado == JuegoEstado::MENU) {
    while (SDL_PollEvent(&event)) {
      // conditional continue
      if (event.type != SDL_KEYUP) {
        continue;
      }
      switch (event.key.keysym.sym) {
        case SDLK_UP:
          // Corrijo el texto actual para que figure como deseleccionado
          textos[posicion].Actualizar(textosNoSeleccionados[posicion]);

          posicion--;
          posicion = posicion < 0 ? 2 : posicion;

          // Corrijo el texto actual para que figure como seleccionado
          textos[posicion].Actualizar(textosSeleccionados[posicion]);
          break;
        case SDLK_DOWN:
          // Corrijo el texto actual para que figure como deseleccionado
          textos[posicion].Actualizar(textosNoSeleccionados[posicion]);

          posicion = (posicion + 1) % 3;

          // Corrijo el texto actual para que figure como seleccionado
          textos[posicion].Actualizar(textosSeleccionados[posicion]);
          break;
        case SDLK_RETURN:
          switch (posicion) {
            case 0:
              estado = JuegoEstado::PLAY;
              break;
            case 1:
              estado = JuegoEstado::RANKING;
              break;
            case 2:
              estado = JuegoEstado::EXIT;
              break;
          }
          // Early return para este caso. Evitamos renderizar la vista de menú
          // para inmediatamente transicionar a la siguiente vista.
          return;
      }
    }
    // Limpia la pantalla en negro
    SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xFF);
    SDL_RenderClear(renderer);

    for (int i = 0; i < textos.size(); i++) {
      textos[i].Dibujar();
    }
    SDL_RenderPresent(renderer);

    // En el menú no vale la pena preocuparse por los fps. De hecho se optimiza
    // para menos de 60fps.
    SDL_Delay(41);
  }
};

void Juego::Play() {
  render->Reiniciar();

  // Inicializo el game loop y paso el puntero a la instancia que renderiza el
  // juego que quiero correr. No muevo el unique_ptr, ya que éste es
  // el owner y es donde se declaran todos los recursos.
  gameLoop(window, renderer, render.get());

  estado = JuegoEstado::PAUSA;
}
void Juego::Pausa() {
  SDL_Event event;

  auto texto1 = Texto(renderer, fuente, "Apreta ENTER para continuar",
                      Vec(width / 2, (height / 2) - 30));
  auto texto2 = Texto(renderer, fuente, "o ESC para terminar la partida",
                      Vec(width / 2, (height / 2) + 30));

  while (estado == JuegoEstado::PAUSA) {
    while (SDL_PollEvent(&event)) {
      // conditional continue
      if (event.type != SDL_KEYUP) {
        continue;
      }
      switch (event.key.keysym.sym) {
        case SDLK_ESCAPE:
          estado = JuegoEstado::MENU;
          return;
        case SDLK_UP:
          break;
        case SDLK_DOWN:
          break;
        case SDLK_RETURN:
          estado = JuegoEstado::PLAY;
          // Early return para este caso. Evitamos renderizar la vista de menú
          // para inmediatamente transicionar a la siguiente vista.
          return;
      }
    }

    texto1.Dibujar();
    texto2.Dibujar();

    SDL_RenderPresent(renderer);

    // Al pausar, tampoco no vale la pena preocuparse por los fps. De hecho se
    // optimiza para menos de 60fps.
    SDL_Delay(41);
  }
};
void Juego::Finalizado() { estado = JuegoEstado::MENU; };
void Juego::Ranking() { estado = JuegoEstado::MENU; };
