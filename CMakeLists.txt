cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 23)

project(Kamisado VERSION 0.1.0)

if(MSVC)
    add_compile_options(/Wall /Wx)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_executable(${PROJECT_NAME} src/main.cpp)

target_sources(${PROJECT_NAME} 
    PRIVATE 
        src/KamisadoGame.cpp
        src/TerminalDisplay.cpp)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        inc
)