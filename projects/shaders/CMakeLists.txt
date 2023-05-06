cmake_minimum_required(VERSION 3.13.0)
project(shaders VERSION 0.1.0)

add_executable(shaders
    "src/glad.c"
    "src/shader.h"
    "src/main.cpp"
)
