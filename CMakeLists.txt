# Minimum version number
cmake_minimum_required(VERSION 3.10)

set(SOURCE_DIR src)

project(Juego)
# Especificar el estándar de C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(Juego ${SOURCE_DIR}/main.cpp ${SOURCE_DIR}/Platform.cpp ${SOURCE_DIR}/Player.cpp ${SOURCE_DIR}/Fireball.cpp  ${SOURCE_DIR}/Item.cpp 
${SOURCE_DIR}/Subject.cpp ${SOURCE_DIR}/ItemFactory.cpp )

target_link_libraries(Juego sfml-system sfml-window sfml-graphics)



