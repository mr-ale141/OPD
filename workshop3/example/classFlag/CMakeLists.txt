cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(RussianFlag)

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

add_executable(flag main.cpp RussianFlag.h RussianFlag.cpp)

target_include_directories(flag PRIVATE "${SFML_ROOT}/include")
target_compile_features(flag PUBLIC cxx_std_17)
target_compile_definitions(flag PRIVATE SFML_STATIC)

target_link_libraries(flag sfml-graphics sfml-window sfml-system)