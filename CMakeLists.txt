cmake_minimum_required(VERSION 3.22)
project(barrett_multiplication VERSION 0.1.0 DESCRIPTION "A simple implementation of the Barrett modular multiplication")


# build the main library

add_library(
    barrett_mul STATIC
    src/lib/hello_world.cpp
)
set_property(TARGET barrett_mul PROPERTY CXX_STANDARD 20)
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


# build the examples

file(GLOB EXAMPLES examples/*.cpp)
foreach(file ${EXAMPLES} )
    get_filename_component(example_name ${file} NAME_WE)
    add_executable(${example_name} ${file})
    set_property(TARGET ${example_name} PROPERTY CXX_STANDARD 20)
    set_target_properties(${example_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "examples")
    target_link_libraries(${example_name} PRIVATE barrett_mul)
endforeach( file ${EXAMPLES} )
