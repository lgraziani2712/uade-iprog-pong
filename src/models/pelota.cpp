#include "pelota.hpp"

Pelota::Pelota(float x, float y)
    // A la posición que recibimos, restamos la mitad del alto y mitad del
    // ancho de la pelota para que ésta esté anclada en su centro
    : posicion(Vec(x, y)), velocidad(Vec(celeridad, 0.0f)) {
  rect.x = static_cast<int>(posicion.x);
  rect.y = static_cast<int>(posicion.y);
  rect.w = PELOTA_ANCHO;
  rect.h = PELOTA_ALTO;
}

void Pelota::Dibujar(SDL_Renderer* renderer) {
  rect.x = static_cast<int>(posicion.x);
  rect.y = static_cast<int>(posicion.y);

  SDL_RenderFillRect(renderer, &rect);
}

void Pelota::Actualizar(float dt) { posicion += velocidad * dt; }

std::array<float, 4> Pelota::Vertices() {
  return {posicion.x, posicion.x + PELOTA_ANCHO, posicion.y,
          posicion.y + PELOTA_ALTO};
}

void Pelota::Colision(Contacto contacto) {
  posicion.x += contacto.penetracion;
  velocidad.x = -velocidad.x;

  switch (contacto.tipo) {
    case Colision::Arriba:
      velocidad.y = -.75f * celeridad;
      break;
    case Colision::Abajo:
      velocidad.y = 0.75f * celeridad;
      break;
  }
}

Contacto Pelota::ColisionConPared(int windowWidth, int windowHeight) {
  auto vertices = Pelota::Vertices();
  Contacto contacto{};

  // Calculo el contacto que tuvo la pelota
  if (vertices[Lado::Izquierdo] < 0.0f) {
    contacto.tipo = Colision::Izquierda;
  } else if (vertices[Lado::Derecho] > windowWidth) {
    contacto.tipo = Colision::Derecha;
  } else if (vertices[Lado::Arriba] < 0.0f) {
    contacto.tipo = Colision::Arriba;
    contacto.penetracion = -vertices[Lado::Arriba];
  } else if (vertices[Lado::Abajo] > windowHeight) {
    contacto.tipo = Colision::Abajo;
    contacto.penetracion = windowHeight - vertices[Lado::Abajo];
  }

  // Aplico el contacto, corrijo posición y velocidad
  switch (contacto.tipo) {
    case Colision::Arriba:
    case Colision::Abajo:
      posicion.y += contacto.penetracion;
      velocidad.y = -velocidad.y;
      break;
    case Colision::Izquierda:
      posicion.x = windowWidth / 2.0f;
      posicion.y = windowHeight / 2.0f;
      velocidad.x = celeridad;
      velocidad.y = 0.75f * celeridad;
      break;
    case Colision::Derecha:
      posicion.x = windowWidth / 2.0f;
      posicion.y = windowHeight / 2.0f;
      velocidad.x = -celeridad;
      velocidad.y = 0.75f * celeridad;
      break;
  }

  return contacto;
}

Vec Pelota::Velocidad() { return velocidad; }
