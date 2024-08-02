#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

void processInput(GLFWwindow *window);

// settings
const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 800;

// vertices coordinates and colors
// x, y, z, r, g, a, b
GLfloat vertices[] =
    {
        -0.5f, -0.2f, 0.0f, 0.8f, 0.3f, 0.02f, //
        0.5f, -0.5f, 0.0f, 0.8f, 0.3f, 0.02f, //
        0.0f, 0.5f, 0.0f, 1.0f, 0.6f, 0.32f,  //
};

GLuint indices[] = {0, 1, 2};

int main()
{
    // initialize and configure glfw for OpenGL 3.3
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // only includes modern functions from the CORE profile
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    GLFWwindow *window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Aquarium", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // introduce the window into the current context
    glfwMakeContextCurrent(window);

    // glad initialization
    gladLoadGL();
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    // creates shader object
    Shader shader("../res/default.vert", "../res/default.frag");

    // creates VAO, VBO, and EBO objects
    VAO VAO;
    VAO.Bind();

    VBO VBO(vertices, sizeof(vertices));
    EBO EBO(indices, sizeof(indices));

    // maps vbo attributes such as coordinates and colors to the VAO
    VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, 6 * sizeof(float), (void *)0);
    VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, 6 * sizeof(float), (void *)(3 * sizeof(float)));

    // unbinds all objects to prevent accidental modification
    VAO.Unbind();
    VBO.Unbind();
    EBO.Unbind();

    GLuint uni_id = glGetUniformLocation(shader.id, "scale");

    // render loop
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        // cleans buffer background with a color
        glClearColor(0.5f, 0.75f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // specifies OpenGL to use the shader and VAO to draw
        shader.Activate();
        glUniform1f(uni_id, 0);

        VAO.Bind();
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

        // swaps back buffer with the front buffer
        glfwSwapBuffers(window);

        // handles glfw events
        glfwPollEvents();
    }

    VAO.Delete();
    VBO.Delete();
    EBO.Delete();
    shader.Delete();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}
