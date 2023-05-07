#include "simpler_renderer.h"
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace std;

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

GLFWwindow* createWindow(int width, int height, const char* title) {
    if (width <= 0 || height <= 0) {
        cout << "invalid window dimensions\n";
        return nullptr;
    }
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (window == NULL) {
        cout << "failed to create glfw window" << std::endl;
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cout << "failed to initialize glad" << endl;
        return nullptr;
    }
    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    return window;
}

unsigned int compileShader(const char* source, int type) {
    if (type != GL_FRAGMENT_SHADER && type != GL_VERTEX_SHADER) {
        cout << "invalid shader type";
        return 0;
    }

    unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    int success;
    char info_log[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(shader, 512, NULL, info_log);
        if (type == GL_VERTEX_SHADER)
            cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << info_log;
        else {
            cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << info_log;
        }
    }

    return shader;
}

unsigned int createShaderProgram(unsigned int vertex_shader, unsigned int fragment_shader) {
    unsigned int shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    int success;
    char info_log[512];
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shader_program, 512, NULL, info_log);
        cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << info_log;
    } else {
        glUseProgram(shader_program);
        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
    }

    return shader_program;
}

unsigned int create2DTexture(const char* tex_path, int texture_number) {
    if (texture_number < GL_TEXTURE0 || texture_number > GL_TEXTURE31) {
        cout << "Invalid texture number" << endl;
        return 0;
    }


    int width, height, nr_channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(tex_path, &width, &height, &nr_channels, 0);

    unsigned int texture;
    glGenTextures(1, &texture);
    glActiveTexture(texture_number);
    glBindTexture(GL_TEXTURE_2D, texture);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    return texture;
}

Shader::Shader(const char* vertex_path, const char* fragment_path) {
    std::string vertex_code;
    std::string fragment_code;
    std::ifstream vshader_file;
    std::ifstream fshader_file;
    vshader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fshader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        vshader_file.open(vertex_path);
        fshader_file.open(fragment_path);
        std::stringstream vshader_stream, fshader_stream;
        vshader_stream << vshader_file.rdbuf();
        fshader_stream << fshader_file.rdbuf();
        vshader_file.close();
        fshader_file.close();

        vertex_code = vshader_stream.str();
        fragment_code = fshader_stream.str();
    } catch(std::ifstream::failure e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
    }
    const char* vshader_code = vertex_code.c_str();
    const char* fshader_code = fragment_code.c_str();

    unsigned int vertex = compileShader(vshader_code, GL_VERTEX_SHADER);
    unsigned int fragment = compileShader(fshader_code, GL_FRAGMENT_SHADER);

    ID = createShaderProgram(vertex, fragment);

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use() {
    glUseProgram(ID);
}

void Shader::setBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
