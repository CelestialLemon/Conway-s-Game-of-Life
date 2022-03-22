#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Grid.h"
#include "Render.h"
#include "helper/Shader.h"

#include <iostream>
#include <random>
#include <Windows.h>

int nowRenderingGrid = 1;

const unsigned int GRID_WIDTH = 144, GRID_HEIGHT = 144;
const unsigned int SCREEN_WIDTH = 720, SCREEN_HEIGHT = 720;

double mousePositionX;
double mousePositionY;

Grid Grid1(GRID_WIDTH, GRID_HEIGHT);
Grid Grid2(GRID_WIDTH, GRID_HEIGHT);
    

void mouse_pos_callback(GLFWwindow* window, double xpos, double ypos)
{
    mousePositionX = xpos; mousePositionY = ypos;
}

void mouse_click_callback(GLFWwindow* window, int button, int action, int mods)
{
    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        unsigned int gridPosX = floorf(mousePositionX * GRID_WIDTH/ SCREEN_WIDTH);
        unsigned int gridPosY = floorf(mousePositionY * GRID_HEIGHT / SCREEN_HEIGHT);

        if(nowRenderingGrid == 1)
        Grid1.SetCell(gridPosX, gridPosY, true);
        else
        Grid2.SetCell(gridPosX, gridPosY, true);
    }
    else if(button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    {
        unsigned int gridPosX = floorf(mousePositionX * GRID_WIDTH/ SCREEN_WIDTH);
        unsigned int gridPosY = floorf(mousePositionY * GRID_HEIGHT / SCREEN_HEIGHT);

        if (nowRenderingGrid == 1)
            Grid1.SetCell(gridPosX, gridPosY, false);
        else
            Grid2.SetCell(gridPosX, gridPosY, false);
    }
}

enum class GameMode
{
    EDIT = 0,
    PLAY = 1
};

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Game of Life", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
        std::cout << "ERROR";

    std::random_device device;
    std::mt19937 rng(device());

    std::uniform_int_distribution<std::mt19937::result_type> RandomBool(0, 9);

    GameMode currentMode = GameMode::EDIT;
    std::cout << "EDIT MODE\n";

    Grid1.Clear();
    Grid2.Clear();
    
    GLuint shader = CreateShader("E:/Repos/Graphics/Conway's Game of Life/res/shaders/Basic.glsl");
    glUseProgram(shader);

    glfwSetCursorPosCallback(window, mouse_pos_callback);
    glfwSetMouseButtonCallback(window, mouse_click_callback);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        if(currentMode == GameMode::EDIT)
        {
            Grid1.Render();
            
            if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
            {
               currentMode = GameMode::PLAY;
            } 
        }
        else if(currentMode == GameMode::PLAY)
        {
            if(nowRenderingGrid == 1)
            {
                Grid1.Render();
                Grid2.ConwayMutate(Grid1);
                nowRenderingGrid = 2;
            }
            else if(nowRenderingGrid == 2)
            {
                Grid2.Render();
                Grid1.ConwayMutate(Grid2);
                nowRenderingGrid = 1;
            }
            else
            {
                std::cout << "very bad error occured\n";
            }   
        }

        Sleep(100);
        
        if(glfwGetKey(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
            std::cout << "Mouse 1 pressed\n";
        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}