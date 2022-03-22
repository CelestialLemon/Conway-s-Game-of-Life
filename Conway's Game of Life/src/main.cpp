#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Grid.h"
#include "helper/Shader.h"

#include <iostream>

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(720, 720, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
        std::cout << "ERROR";


    float vertexData[] = {
        -1.0f, -1.0f,
        1.0f, -1.0f,
        1.0f, 1.0f,
        -1.0f, 1.0f
    };

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vb;
    glGenBuffers(1, &vb);
    glBindBuffer(GL_ARRAY_BUFFER, vb);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 4 * 2, vertexData, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);


    
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    GLuint ib;
    glGenBuffers(1, &ib);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 2 * 3, indices, GL_STATIC_DRAW);

    GLuint shader = CreateShader("E:/Repos/Graphics/Conway's Game of Life/res/shaders/Basic.glsl");
    glUseProgram(shader);

    GLuint H_loc = glGetUniformLocation(shader, "H");
    GLuint W_loc = glGetUniformLocation(shader, "W");
    
    glUniform1f(H_loc, 720.0f);
    glUniform1f(W_loc, 720.0f);

    Grid newGrid(10, 10);
    newGrid.Clear();
    newGrid.SetCell(9, 5, true);
    newGrid.Print();


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}