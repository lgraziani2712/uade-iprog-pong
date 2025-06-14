cmake_minimum_required(VERSION 3.15)
project(pong)

find_package(SDL2 REQUIRED CONFIG)
find_package(SDL2_ttf REQUIRED CONFIG)

set(CMAKE_WIN32_EXECUTABLE TRUE)  # <- Esto es opcional, pero ayuda a evitar que espere `main()`

file(GLOB SOURCES
    src/*.cpp
    src/*.hpp
    src/renders/*.cpp
    src/renders/*.hpp
    src/models/*.cpp
    src/models/*.hpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

# Copio assets a la carpeta output
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/src/assets"
    "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets")

target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2main SDL2::SDL2 SDL2_ttf::SDL2_ttf-static)
