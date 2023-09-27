add_executable(01 main.cpp)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "/home/ale141/SFML-2.6.0/SFML-2.6.0-build/")

find_package(Freetype)
find_package(JPEG)
find_package(SFML 2.6 COMPONENTS window graphics system)

target_compile_features(01 PUBLIC cxx_std_17)
target_compile_definitions(01 PRIVATE SFML_STATIC)

target_link_libraries(01 sfml-graphics sfml-window sfml-system)