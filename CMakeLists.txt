cmake_minimum_required(VERSION 3.0.2)
project(lab1)
set(CMAKE_BUILD_TYPE Release)
set(DCMAKE_EXPORT_COMPILE_COMMANDS 1)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -O3")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(pi_taylor_sequential src/pi_taylor_sequential.cc)
add_executable(pi_taylor_parallel src/pi_taylor_parallel.cc)
add_executable(pi_taylor_parallel_kahan  src/pi_taylor_parallel_kahan.cc)
target_link_libraries(pi_taylor_parallel PRIVATE pthread)
target_link_libraries(pi_taylor_parallel_kahan PRIVATE pthread)