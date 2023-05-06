#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
GLFWwindow* createWindow(int width, int height, const char* title);
unsigned int compileShader(const char* source, int type);
unsigned int createShaderProgram(unsigned int vertex_shader, unsigned int fragment_shader);

class Shader {
public:
    unsigned int ID;
    Shader(const char* vertex_path, const char* fragment_path);
    void use();
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
};