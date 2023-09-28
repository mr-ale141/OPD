add_executable(02 main.cpp)

target_include_directories(02 PRIVATE "${SFML_ROOT}/include")
target_compile_features(02 PUBLIC cxx_std_17)
target_compile_definitions(02 PRIVATE SFML_STATIC)

target_link_libraries(02  sfml-graphics sfml-window sfml-system)