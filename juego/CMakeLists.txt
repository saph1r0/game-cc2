cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto
project(juego)

# Especificar el estándar de C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Añadir los archivos de código fuente
# Asegúrate de incluir todos los archivos fuente relevantes, como Player.cpp y Platform.cpp
add_executable(juego 
    main.cpp
    Player.cpp
    Platform.cpp
    Fireball.cpp
    # Agrega aquí otros archivos fuente si los tienes
)

# Buscar la librería SFML
find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

# Enlazar la librería SFML con el ejecutable
target_link_libraries(juego sfml-graphics)

# Opcional: Enlazar otras bibliotecas SFML si las necesitas
# target_link_libraries(juego sfml-window sfml-system)
