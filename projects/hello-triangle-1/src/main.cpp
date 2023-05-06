#include "simpler_renderer.h"

using namespace std;

int main() {
    int width = 800, height = 600;
    const char title[] = "triangle1";
    GLFWwindow* window = createWindow(800, 600, title);
    if (window == nullptr)
        return -1;

    float vertices[] = {
        -1.0f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f,
         0.0f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
         1.0f, -0.5f, 0.0f
    };

    const char *vertex_shader_source = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main() {\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";

    const char *fragment_shader_source = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main() {\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "};";

    unsigned int vertex_shader = compileShader(vertex_shader_source, GL_VERTEX_SHADER);
    unsigned int fragment_shader = compileShader(fragment_shader_source, GL_FRAGMENT_SHADER);
    unsigned int shader_program = createShaderProgram(vertex_shader, fragment_shader); // shaders are not valid at this point

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader_program);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawArrays(GL_TRIANGLES, 2, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}