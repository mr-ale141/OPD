add_executable(03 main.cpp)

target_include_directories(03 PRIVATE "${SFML_ROOT}/include")
target_compile_features(03 PUBLIC cxx_std_17)
target_compile_definitions(03 PRIVATE SFML_STATIC)

target_link_libraries(03 sfml-graphics sfml-window sfml-system)