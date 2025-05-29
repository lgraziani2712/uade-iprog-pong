cmake_minimum_required(VERSION 3.15)
project(pong)

find_package(SDL2 REQUIRED CONFIG)

set(CMAKE_WIN32_EXECUTABLE TRUE)  # <- Esto es opcional, pero ayuda a evitar que espere `main()`

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2main SDL2::SDL2)
