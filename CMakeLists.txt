cmake_minimum_required (VERSION 3.20)
project (my_allocators)
set(CMAKE_CXX_STANDARD 17)

set(SOURCES src/Allocator.cpp
		src/FreeListAllocator.cpp
   		src/Benchmark.cpp
		main.cpp)

add_executable(main ${SOURCES})
target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/includes)