# Game Engines

## Principales paradigmas

- Programación Estructurada
  - Implementación de algoritmos
- Programación modular
  - Bibliotecas utilitarias
  - Funciones auxiliares
  - Definición de constantes
  - Abstracción de entidades del Juego
- Programación Orientada a Objetos
  - Abstracción de entidades del Juego

## Principales Components

- Carga de assets
- motor gráfico
- manejo de input
- simulación física
- motor de colisiones
- jerarquía de Entidades (OOP)
- Game loop

## Game Loop (Pattern)

- Más básico del desarrollo de videojuegos.
- Controla el flow completo de nuestro programa.
- Se lo denomina loop (bucle) porque se ejecuta una y otra vez hasta que el programa finaliza.
- El patrón loop tiene ciertos pasos que se repiten en cada vuelta:
  1. Procesamiento del input.
  2. Actualización del mundo del juego
     - Físicas.
     - Colisiones.
     - Lógicas.
  3. Procesamiento de outputs.

PREGUNTA EXAMEN: Qué es el game loop

Cada vuelta del bucle realiza el proceso del **input** y **actualiza** las variables para luego **dibujar** en pantalla el estado del juego en ese momento.
