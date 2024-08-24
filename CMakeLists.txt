cmake_minimum_required(VERSION 3.15)

project(lox)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

add_library(lox_a OBJECT)
target_include_directories(lox_a PUBLIC src/ src/lexer src/parser src/utils)
target_sources(lox_a
        PRIVATE
            src/lib/test.cpp
            src/lexer/lexer.cpp
        INTERFACE
            $<TARGET_OBJECTS:lox_a>
        )
target_link_libraries(lox_a PUBLIC
)

add_executable(lox
    src/main.cpp
)
target_link_libraries(lox lox_a)
