//
// Created by francisco on 5/5/20.
//

#ifndef METABALLS_CIRCLE_H
#define METABALLS_CIRCLE_H

#include <vector>
#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>


class Circle {
public:
    std::vector<float> vertices;
    unsigned int rendering_program{};
    unsigned int vbo{};
    glm::vec3 position{}, size{}, velocity{};

    Circle();
    Circle(unsigned int rendering_program, glm::vec3 position, glm::vec3 size, glm::vec3 velocity);
    void initialize(unsigned int vao);
    void draw();
    void move();

private:
    static std::vector<float> calc_vertices();

    void bounce_on_screen_limit();
};


#endif //METABALLS_CIRCLE_H
