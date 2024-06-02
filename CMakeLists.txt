cmake_minimum_required(VERSION 3.26)

project(clox VERSION 1.0)
set(CMAKE_C_STANDARD 99)

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB_RECURSE HEADER_FILES ${PROJECT_SOURCE_DIR}/include/*.h)
file(GLOB_RECURSE SOURCE_FILES ${PROJECT_SOURCE_DIR}/src/*.c)

add_executable(clox ${SOURCE_FILES} ${HEADER_FILES})

# add_executable(clox main.c
#         common.h
#         chunk.h
#         chunk.c
#         memory.h
#         memory.c
#         debug.h
#         debug.c
#         value.h
#         value.c
#         vm.h
#         vm.c
#         compiler.h
#         compiler.c
#         scanner.h
#         scanner.c
#         object.h
#         object.c
#         table.h
#         table.c
# )