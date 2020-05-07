//
// Created by francisco on 5/5/20.
//

#include "circle.h"

Circle::Circle() = default;

Circle::Circle(unsigned int rendering_program, glm::vec3 position, glm::vec3 size, glm::vec3 velocity) {
    this->rendering_program = rendering_program;
    this->size = size;
    this->position = position;
    this->velocity = velocity;
}

void Circle::initialize(unsigned int vao) {
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);

    this->vertices = calc_vertices();

    // create position vector
    // create color vector
    // calculate which line to color
    // merge position and color vectors into one vector
    // convert vector to array

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);
}


void Circle::move() {
    bounce_on_screen_limit();
    this->velocity = glm::normalize(velocity) * 0.005f;
    this->position += this->velocity;
}

void Circle::bounce_on_screen_limit() {
    if (std::abs(position.x + velocity.x) > 1) {
        velocity.x = -velocity.x;
    }
    if (std::abs(position.y + velocity.y) > 1) {
        velocity.y = -velocity.y;
    }
}

void Circle::draw() {

    glUseProgram(rendering_program);

    // get uniform location
    GLuint view_loc = glGetUniformLocation(rendering_program, "view");
    GLuint model_loc = glGetUniformLocation(rendering_program, "model");

    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 model = glm::mat4(1.0f);

    view = glm::translate(view, this->position);
    model = glm::scale(model, size);

    // set shader uniforms
    glUniformMatrix4fv(view_loc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(model_loc, 1, GL_FALSE, glm::value_ptr(model));

    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glDrawArrays(GL_LINE_STRIP, 0, 48);
}

std::vector<float> Circle::calc_vertices() {

    float doublePi = 2.0f * M_PI;

    float number_of_sides = 24.0f;
    unsigned int number_of_vertices = (int) number_of_sides * 2;

    float circleVerticesX[number_of_vertices];
    float circleVerticesY[number_of_vertices];

    float radius = 0.8f;

    for (int i = 0; i < number_of_vertices; i++) {
        // vertex_x = r * cos(i * 2pi / num_of_sides)
        circleVerticesX[i] = radius * std::cos((float) i * doublePi / number_of_sides);
        circleVerticesY[i] = radius * std::sin((float) i * doublePi / number_of_sides);
    }

    std::vector<float> all_vertices;

    for (int i = 0; i < number_of_vertices; i++) {
        for (int j = 0; j < 2; j++) {
            all_vertices.push_back(circleVerticesX[i]);
            all_vertices.push_back(circleVerticesY[i]);
        }
    }

    all_vertices.erase(all_vertices.begin(), all_vertices.begin() + 2);

    return all_vertices;
}




