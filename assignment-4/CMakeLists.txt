cmake_minimum_required(VERSION 3.0)
project(assignment_4)

set(CMAKE_CXX_STANDARD 11)
add_compile_options(-Wall -Wextra -pedantic -Werror -fstack-protector -fstack-protector-all)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
set(CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")

find_package(Threads)
find_package(OpenMP)

if (OPENMP_FOUND)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif ()


add_executable(sieve-of-eratosthenes sieve-of-eratosthenes.cpp)
target_link_libraries(sieve-of-eratosthenes ${CMAKE_THREAD_LIBS_INIT})
