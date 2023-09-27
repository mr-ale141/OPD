add_executable(02 main.cpp)

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
find_package(SFML 2.6 COMPONENTS window graphics system)

target_compile_features(02 PUBLIC cxx_std_17)
target_compile_definitions(02 PRIVATE SFML_STATIC)

target_link_libraries(02 sfml-graphics sfml-window sfml-system)