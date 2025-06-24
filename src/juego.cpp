#include "juego.hpp"
#include <SDL2/SDL_image.h>
#include <array>
#include <format>
#include <memory>
#include "configs.hpp"
#include "creation.hpp"
#include "game_loop.hpp"
#include "models/texto.hpp"
#include "renders/pong_render.hpp"
#include "resultado_csv.hpp"

Juego::Juego() {
  window = createWindow();
  renderer = createRenderer(window);

  // Seteo ícono del juego
  SDL_Surface *iconSurface = IMG_Load(getAssetsPath("logo.webp").c_str());

  if (iconSurface == NULL) {
    throw std::runtime_error(SDL_GetError());
  }
  SDL_SetWindowIcon(window, iconSurface);
  SDL_FreeSurface(iconSurface);

  // Instancio las cosas que necesito
  fuente = TTF_OpenFont(getAssetsPath("HurmitNerdFont-Bold.otf").c_str(), 40);
  autorFuente =
      TTF_OpenFont(getAssetsPath("HurmitNerdFont-Bold.otf").c_str(), 16);
  fuenteTitulo = TTF_OpenFont(getAssetsPath("Blanka.otf").c_str(), 120);
  menuOpcion = Mix_LoadWAV(getAssetsPath("radio-338296.mp3").c_str());
  menuSeleccion =
      Mix_LoadWAV(getAssetsPath("8-bit-victory-sound-101319.mp3").c_str());

  TTF_SetFontOutline(fuenteTitulo, 2);

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
  if (autorFuente != NULL) {
    TTF_CloseFont(autorFuente);
  }
  if (fuenteTitulo != NULL) {
    TTF_CloseFont(fuenteTitulo);
  }
  if (menuOpcion != NULL) {
    Mix_FreeChunk(menuOpcion);
  }
  if (menuSeleccion != NULL) {
    Mix_FreeChunk(menuSeleccion);
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
  const SDL_Color SELECTED_OPTION = {0xAA, 0x44, 0x33, 0xFF};
  const SDL_Color NON_SELECTED_OPTION = {0xFF, 0xFF, 0xFF, 0xFF};

  std::array<const char *, 4> textosNoSeleccionados = {
      "Jugar Solo", "Jugar 1v1", "Ranking", "Salir"};
  std::array<const char *, 4> textosSeleccionados = {"JUGAR SOLO", "JUGAR 1v1",
                                                     "RANKING", "SALIR"};

  auto titulo = Texto(renderer, fuenteTitulo, "PONG", Alineacion::Centro,
                      Vec(width / 2, 100));
  auto autor = Texto(renderer, autorFuente,
                     "Luciano Graziani <lgraziani@uade.edu.ar> 2025 para "
                     "Introduccion a la programacion, UADE.",
                     Alineacion::Centro, Vec(width / 2, height - 40));

  titulo.Color(SELECTED_OPTION);

  std::array<Texto, 4> textos = {
      Texto(renderer, fuente, textosSeleccionados[0], Alineacion::Centro,
            Vec(width / 2, (height / 2) - 150)),
      Texto(renderer, fuente, textosNoSeleccionados[1], Alineacion::Centro,
            Vec(width / 2, (height / 2) - 50)),
      Texto(renderer, fuente, textosNoSeleccionados[2], Alineacion::Centro,
            Vec(width / 2, (height / 2) + 50)),
      Texto(renderer, fuente, textosNoSeleccionados[3], Alineacion::Centro,
            Vec(width / 2, (height / 2) + 150))};

  // Inicializo el primer texto seleccionado con color
  textos[posicion].Color(SELECTED_OPTION);

  while (estado == JuegoEstado::MENU) {
    while (SDL_PollEvent(&event)) {
      // conditional continue
      if (event.type != SDL_KEYUP) {
        continue;
      }
      switch (event.key.keysym.sym) {
        case SDLK_UP:
          Mix_PlayChannel(2, menuOpcion, 0);
          // Corrijo el texto actual para que figure como deseleccionado
          textos[posicion].Actualizar(textosNoSeleccionados[posicion]);
          textos[posicion].Color(NON_SELECTED_OPTION);

          posicion--;
          posicion = posicion < 0 ? 3 : posicion;

          // Corrijo el texto actual para que figure como seleccionado
          textos[posicion].Actualizar(textosSeleccionados[posicion]);
          textos[posicion].Color(SELECTED_OPTION);
          break;
        case SDLK_DOWN:
          Mix_PlayChannel(2, menuOpcion, 0);
          // Corrijo el texto actual para que figure como deseleccionado
          textos[posicion].Actualizar(textosNoSeleccionados[posicion]);
          textos[posicion].Color(NON_SELECTED_OPTION);

          posicion = (posicion + 1) % 4;

          // Corrijo el texto actual para que figure como seleccionado
          textos[posicion].Actualizar(textosSeleccionados[posicion]);
          textos[posicion].Color(SELECTED_OPTION);
          break;
        case SDLK_RETURN:
          Mix_PlayChannel(2, menuSeleccion, 0);

          switch (posicion) {
            case 0:
              render->Iniciar(TipoJugador::CPU);
              estado = JuegoEstado::PLAY;
              break;
            case 1:
              render->Iniciar(TipoJugador::PERSONA);
              estado = JuegoEstado::PLAY;
              break;
            case 2:
              estado = JuegoEstado::RANKING;
              break;
            case 3:
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

    titulo.Dibujar();
    autor.Dibujar();

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
  // Inicializo el game loop y paso el puntero a la instancia que renderiza el
  // juego que quiero correr. No muevo el unique_ptr, ya que éste es
  // el owner y es donde se declaran todos los recursos.
  gameLoop(window, renderer, render.get());

  switch (render->Estado()) {
    case PongEstado::PAUSAR:
      estado = JuegoEstado::PAUSA;
      break;

    case PongEstado::FIN:
      estado = JuegoEstado::FINALIZADO;
      break;
  }
}
void Juego::Pausa() {
  SDL_Event event;

  auto texto1 = Texto(renderer, fuente, "Apreta ENTER para continuar",
                      Alineacion::Centro, Vec(width / 2, (height / 2) - 30));
  auto texto2 = Texto(renderer, fuente, "o ESC para terminar la partida",
                      Alineacion::Centro, Vec(width / 2, (height / 2) + 30));

  while (estado == JuegoEstado::PAUSA) {
    while (SDL_PollEvent(&event)) {
      // conditional continue
      if (event.type != SDL_KEYUP) {
        continue;
      }
      switch (event.key.keysym.sym) {
        case SDLK_ESCAPE:
          render->FinalizarPartida(true);
          estado = JuegoEstado::FINALIZADO;
          return;
        case SDLK_UP:
          break;
        case SDLK_DOWN:
          break;
        case SDLK_RETURN:
          render->Pausar(false);
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

void Juego::Finalizado() {
  Resultado resultado = render->ResultadoUltimaPartida();

  // Escribo resultado en archivo, siempre.
  escribir(resultado);

  if (resultado.estado == PartidaEstado::QUIT) {
    estado = JuegoEstado::MENU;

    // Early return porque no queremos mostrar la pantalla de finalizado cuando
    // se canceló, pero sí queremos los datos para guardar
    return;
  }
  SDL_Event event;

  auto titulo =
      Texto(renderer, fuente, "Apreta ENTER o ESC para volver al menu.",
            Alineacion::Centro, Vec(width / 2, (height / 3) - 40));
  auto resultadoTexto = Texto(
      renderer, fuente,
      ("- Resultado:  " +
       (std::string)(resultado.estado == PartidaEstado::QUIT     ? "Cancelada"
                     : resultado.estado == PartidaEstado::Empate ? "Empate"
                     : resultado.estado == PartidaEstado::JUGADOR_1
                         ? "Victoria P1"
                         : "Victoria P2") +
       ".")
          .c_str(),
      Alineacion::Izq, Vec(width / 4, (height / 3) + 100));
  auto puntosP1 = Texto(
      renderer, fuente,
      ("- Puntaje P1: " + std::to_string(resultado.jugador1) + ".").c_str(),
      Alineacion::Izq, Vec(width / 4, ((height / 3) + 100) + 40));
  auto puntosP2 = Texto(
      renderer, fuente,
      ("- Puntaje P2: " + std::to_string(resultado.jugador2) + ".").c_str(),
      Alineacion::Izq, Vec(width / 4, ((height / 3) + 100) + 80));
  auto tiempoTexto = Texto(
      renderer, fuente,
      ("- Tiempo:     " + std::format("{:.2f}", resultado.tiempo) + "seg.")
          .c_str(),
      Alineacion::Izq, Vec(width / 4, ((height / 3) + 100) + 120));

  while (estado == JuegoEstado::FINALIZADO) {
    while (SDL_PollEvent(&event)) {
      // conditional continue
      if (event.type != SDL_KEYUP) {
        continue;
      }
      switch (event.key.keysym.sym) {
        case SDLK_ESCAPE:
        case SDLK_RETURN:
          estado = JuegoEstado::MENU;
          // Early return para este caso. Evitamos renderizar la vista de menú
          // para inmediatamente transicionar a la siguiente vista.
          return;
      }
    }
    // Limpia la pantalla en negro
    SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xFF);
    SDL_RenderClear(renderer);

    // Renderizar vista
    titulo.Dibujar();
    resultadoTexto.Dibujar();
    puntosP1.Dibujar();
    puntosP2.Dibujar();
    tiempoTexto.Dibujar();

    SDL_RenderPresent(renderer);
    // Al pausar, tampoco vale la pena preocuparse por los fps. De hecho se
    // optimiza para menos de 60fps.
    SDL_Delay(41);
  }
};

void Juego::Ranking() {
  SDL_Event event;
  auto resultados = leer();
  auto titulo =
      Texto(renderer, fuente,
            "| Resultado    | Jugador1     | Jugador2/CPU | Tiempo       |",
            Alineacion::Izq, Vec(5, 40));
  auto subtitulo =
      Texto(renderer, fuente,
            "|==============|==============|==============|==============|",
            Alineacion::Izq, Vec(5, 77));
  std::vector<std::unique_ptr<Texto>> textos;

  for (int i = 0; i < resultados.size(); i++) {
    auto resultado = resultados[i];
    std::string estado = resultado.estado == PartidaEstado::QUIT ? "Cancelada"
                         : resultado.estado == PartidaEstado::Empate ? "Empate"
                         : resultado.estado == PartidaEstado::JUGADOR_1 ? "P1"
                         : resultado.estado == PartidaEstado::P_CPU     ? "CPU"
                                                                        : "P2";
    auto resP1 = std::to_string(resultado.jugador1);
    auto resP2 = std::to_string(resultado.jugador2);
    auto tiempo = std::format("{:.2f}", resultado.tiempo);

    if (estado.size() < 12) {
      estado.append(12 - estado.size(), ' ');
    }
    resP1.append(12 - resP1.size(), ' ');
    resP2.append(12 - resP2.size(), ' ');
    tiempo.append(12 - tiempo.size(), ' ');

    textos.push_back(std::make_unique<Texto>(
        renderer, fuente,
        ("| " + estado + " | " + resP1 + " | " + resP2 + " | " + tiempo + " |")
            .c_str(),
        Alineacion::Izq, Vec(5, 114 + i * 37)));
  }

  while (estado == JuegoEstado::RANKING) {
    while (SDL_PollEvent(&event)) {
      // conditional continue
      if (event.type != SDL_KEYUP) {
        continue;
      }
      switch (event.key.keysym.sym) {
        case SDLK_ESCAPE:
        case SDLK_RETURN:
          estado = JuegoEstado::MENU;
          // Early return para este caso. Evitamos renderizar la vista de menú
          // para inmediatamente transicionar a la siguiente vista.
          return;
      }
    }
    // Limpia la pantalla en negro
    SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xFF);
    SDL_RenderClear(renderer);

    // Renderizar vista
    titulo.Dibujar();
    subtitulo.Dibujar();

    for (int i = 0; i < textos.size(); i++) {
      textos[i]->Dibujar();
    }

    SDL_RenderPresent(renderer);
    // Al pausar, tampoco vale la pena preocuparse por los fps. De hecho se
    // optimiza para menos de 60fps.
    SDL_Delay(41);
  }
};
