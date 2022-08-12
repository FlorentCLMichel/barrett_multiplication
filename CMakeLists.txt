cmake_minimum_required(VERSION 3.22)
project(barrett_multiplication VERSION 0.1.0 DESCRIPTION "A simple implementation of the Barrett modular multiplication")


add_library(
    barrett_mul STATIC
    src/lib/hello_world.cpp
)
set_target_properties(barrett_mul PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(barrett_mul PROPERTIES PUBLIC_HEADER src/include/barrett_mul.h)
target_include_directories(barrett_mul PRIVATE src/include)
target_include_directories(barrett_mul PRIVATE src/lib)

include(GNUInstallDirs)

install(TARGETS barrett_mul
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
configure_file(barrett_mul.pc.in barrett_mul.pc @ONLY)
install(FILES ${CMAKE_BINARY_DIR}/mylib.pc DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)


add_executable(hello_world examples/hello_world.cpp)
set_target_properties(hello_world PROPERTIES RUNTIME_OUTPUT_DIRECTORY "examples")
target_link_libraries(hello_world PRIVATE barrett_mul)
