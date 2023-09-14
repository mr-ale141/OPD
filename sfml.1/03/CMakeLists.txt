add_executable(03 main.cpp)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "C:/Program Files (x86)/SFML/")

find_package(Freetype)
find_package(JPEG)
find_package(SFML 2.6 COMPONENTS window graphics system)

target_compile_features(03 PUBLIC cxx_std_17)
target_compile_definitions(03 PRIVATE SFML_STATIC)

target_link_libraries(03 sfml-graphics sfml-window sfml-system)