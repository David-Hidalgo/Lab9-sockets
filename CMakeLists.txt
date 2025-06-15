cmake_minimum_required(VERSION 3.30.0)
project(lab9-sockets VERSION 0.1.0 LANGUAGES C CXX)

# add_executable(lab9-sockets main.cpp)
add_executable(server server.cpp)
add_executable(client client.cpp)

target_compile_features(server PRIVATE cxx_std_23)
target_compile_features(client PRIVATE cxx_std_23)
# target_compile_features(lab9-sockets PRIVATE cxx_std_23)
# target_compile_options(lab9-sockets PRIVATE -Wall -Wextra -Wpedantic)
# target_link_libraries(lab9-sockets PRIVATE stdc++exp)
target_link_libraries(server PRIVATE stdc++exp)
target_link_libraries(client PRIVATE stdc++exp)
# Set the C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
# Set the C++ standard to C++23
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Set the C++ standard to C++23
set(CMAKE_CXX_EXTENSIONS OFF)