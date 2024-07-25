cmake_minimum_required(VERSION 3.10)

set(SOURCE_DIR src)

project(Juego)


find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(1 ${SOURCE_DIR}/main.cpp ${SOURCE_DIR}/Platform.cpp ${SOURCE_DIR}/Player.cpp ${SOURCE_DIR}/Fireball.cpp  ${SOURCE_DIR}/Item.cpp 
${SOURCE_DIR}/Subject.cpp ${SOURCE_DIR}/ItemFactory.cpp)

target_link_libraries(1 sfml-system sfml-window sfml-graphics)




