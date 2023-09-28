cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
#
project(sfml-lab-3)

set(SFML_STATIC_LIBRARIES TRUE)

if(WIN32)
    set(SFML_DIR "C:/Program Files (x86)/SFML/")
elseif(UNIX)
    set(SFML_DIR "/home/ale141/SFML-2.6.0/SFML-2.6.0-build/")
else()
    message(CMAKE_ERROR_DEPRECATED "Unknow operetion system")
endif()

find_package(Freetype)
find_package(JPEG)
find_package(SFML 2.6 COMPONENTS window graphics system REQUIRED)

add_subdirectory(00)
add_subdirectory(01)
add_subdirectory(02)
add_subdirectory(03)