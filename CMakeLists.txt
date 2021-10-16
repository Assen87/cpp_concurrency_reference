cmake_minimum_required(VERSION 3.0.0)
project(cpp_concurrency_reference VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -pthread" )

add_subdirectory(thread)
add_subdirectory(atomic)
add_subdirectory(mutex)
