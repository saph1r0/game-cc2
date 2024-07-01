# Minimum version number
cmake_minimum_required(VERSION 3.10)

set(SOURCE_DIR src)

project(juego)
# Especificar el estándar de C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(juego ${SOURCE_DIR}/main.cpp ${SOURCE_DIR}/Platform.cpp ${SOURCE_DIR}/Player.cpp ${SOURCE_DIR}/Fireball.cpp ${SOURCE_DIR}/Item.cpp)

target_link_libraries(juego sfml-system sfml-window sfml-graphics)




