cmake_minimum_required(VERSION 3.0.2)
project(lab1)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_COMPILER /usr/bin/aarch64-linux-gnu-g++)

# Specify the target system and processor
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR aarch64)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")

set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# Set the output directory for all executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(pi_taylor_sequential src/pi_taylor_sequential.cc)
add_executable(pi_taylor_parallel src/pi_taylor_parallel.cc)
add_executable(pi_taylor_parallel_kahan  src/pi_taylor_parallel_kahan.cc)

target_link_libraries(pi_taylor_parallel PRIVATE pthread)
target_link_libraries(pi_taylor_parallel_kahan PRIVATE pthread)
