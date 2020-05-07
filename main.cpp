#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "shader.h"
#include "circle.h"
#include "grid.h"

using namespace std;

#define numVAOs 1

GLuint rendering_program;
GLuint vao[numVAOs];

Shader *shader;

void processInput(GLFWwindow *window);

void initial_setup(GLFWwindow *window);

void create_circles(Circle *circles, int num_circles);

int main() {
    std::cout << "Hello, metaballs!" << std::endl;

    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    GLFWwindow *window = glfwCreateWindow(800, 800, "opengl", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        exit(EXIT_FAILURE);
    }

    glfwSwapInterval(1);

    initial_setup(window);

    // create grid

    // create circle objects
    const unsigned int NUM_CIRCLES = 3;
    Circle circles[NUM_CIRCLES];
    create_circles(circles, NUM_CIRCLES);

    Grid grid(rendering_program);
    grid.initialize(vao[0]);

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClear(GL_COLOR_BUFFER_BIT);

        grid.draw();

        for (auto &circle : circles) {
            circle.move();
            circle.draw();
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

void create_circles(Circle *circles, int num_circles) {

    srand (static_cast <unsigned> (time(0)));
    float min = -0.1;
    float max = +0.1;
    for (int i = 0; i < num_circles; i++) {
        float rand_x = min + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(max-min)));
        float rand_y = min + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(max-min)));
        float rand_size = 0.1f + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(0.5f-0.1f)));

        // create circle objects
        glm::vec3 position(0.0f, 0.0f, 0.0f);
        glm::vec3 size(rand_size, rand_size, 0.0f);
        glm::vec3 velocity(rand_x, rand_y, 0.0f);

        Circle circle(rendering_program, position, size, velocity);
        circle.initialize(vao[0]);

        circles[i] = circle;
    }
}

void initial_setup(GLFWwindow *window) {
    rendering_program = shader->createShaderProgram();

    glGenVertexArrays(1, vao);
    glBindVertexArray(vao[0]);
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}