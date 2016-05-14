cmake_minimum_required (VERSION 2.6)
project (vec CXX)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(vec vec.cpp)
add_executable(add tests/add.cpp)
add_executable(norm tests/norm.cpp)
add_executable(cross tests/cross.cpp)
add_executable(conj tests/conj.cpp)

enable_testing()
add_test(add add)
add_test(norm norm)
add_test(cross cross)
add_test(conj conj)

set(INSTALL_CMAKE_DIR CMake)
configure_file (vecConfig.cmake.in vecConfig.cmake)
install (FILES ${PROJECT_BINARY_DIR}/vecConfig.cmake
         DESTINATION ${INSTALL_CMAKE_DIR})
install (FILES vec.hpp DESTINATION include)
