cmake_minimum_required(VERSION 3.29)

# Nombre del proyecto
project(Integrador_tema4)

# Configuración del estándar de C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Archivos fuente del proyecto
add_executable(Integrador_tema4
        main.cpp
        Variant.h
        Variant.cpp
        Entorno.h
        libs/json11/json11.cpp  # Añadido para incluir json11 directamente
)

# Incluir la librería json11
include_directories(${PROJECT_SOURCE_DIR}/libs/json11)

# No es necesario add_subdirectory ahora