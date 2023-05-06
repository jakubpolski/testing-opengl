#include "simpler_renderer.h"

using namespace std;

int main() {
    int width = 800, height = 600;
    const char title[] = "shaders2";
    GLFWwindow* window = createWindow(800, 600, title);
    if (window == nullptr)
        return -1;

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,
         0.0f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f
    };

    const char vshader_path[] = "D:\\coding\\cpp\\testing-opengl\\projects\\shaders-2\\src\\shader.vs";
    const char fshader_path[] = "D:\\coding\\cpp\\testing-opengl\\projects\\shaders-2\\src\\shader.fs";
    Shader our_shader(vshader_path, fshader_path);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    int iter = 0;
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        our_shader.use();
        our_shader.setFloat("offset", 0.1f * iter);
        if (iter++ == 5)
            iter = 0;
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}