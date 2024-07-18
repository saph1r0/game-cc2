cmake_minimum_required(VERSION 3.10)

set(SOURCE_DIR src)

project(Juego)

set(SFML_DIR "\\Users\\Kathy\\Documents\\1. UNSA\\2. AULA VIRTUAL\\1. Ciencia de la Computacion II\\Wizard-Training-Game-master\\SFML\\lib\\cmake\\SFML")

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(Juego ${SOURCE_DIR}/main.cpp ${SOURCE_DIR}/Platform.cpp ${SOURCE_DIR}/Player.cpp ${SOURCE_DIR}/Fireball.cpp  ${SOURCE_DIR}/Item.cpp 
${SOURCE_DIR}/Subject.cpp ${SOURCE_DIR}/ItemFactory.cpp)

target_link_libraries(Juego sfml-system sfml-window sfml-graphics)




