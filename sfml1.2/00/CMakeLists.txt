add_executable(00 main.cpp)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "/home/ale141/SFML-2.6.0/SFML-2.6.0-build/")

find_package(Freetype)
find_package(JPEG)
find_package(SFML 2.6 COMPONENTS window graphics system)

target_compile_features(00 PUBLIC cxx_std_17)
target_compile_definitions(00 PRIVATE SFML_STATIC)

target_link_libraries(00 sfml-graphics sfml-window sfml-system)