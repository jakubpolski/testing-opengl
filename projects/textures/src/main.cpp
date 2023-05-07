#include "simpler_renderer.h"

using namespace std;

int main() {
    int win_width = 800, win_height = 600;
    const char title[] = "textures";
    GLFWwindow* window = createWindow(win_width, win_height, title);
    if (window == nullptr)
        return -1;

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,     0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
         0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
         0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,   1.0f, 1.0f, // top right
        -0.5f,  0.5f, 0.0f,     1.0f, 0.0f, 0.0f,   0.0f, 1.0f  // top left
    };

    unsigned int indices[] {
        0, 1, 2,
        0, 2, 3
    };

    float border_color[] = { 1.0f, 1.0f, 0.0f, 1.0f };
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border_color);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    const char vshader_path[] = "D:\\coding\\cpp\\testing-opengl\\projects\\textures\\src\\shader.vs";  // hardcoded because reasons
    const char fshader_path[] = "D:\\coding\\cpp\\testing-opengl\\projects\\textures\\src\\shader.fs";
    Shader our_shader(vshader_path, fshader_path);
    our_shader.use();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border_color);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    const char tex_path1[] = "D:\\piwo.bmp";
    const char tex_path2[] = "D:\\tf.bmp";

    unsigned int texture1 = create2DTexture(tex_path1, GL_TEXTURE0);
    unsigned int texture2 = create2DTexture(tex_path2, GL_TEXTURE1);
    our_shader.setInt("texture1", 0);
    our_shader.setInt("texture2", 1);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        our_shader.use();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}