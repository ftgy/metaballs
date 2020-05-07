//
// Created by francisco on 6/5/20.
//

#include "grid.h"

Grid::Grid() {

};

Grid::Grid(unsigned int rendering_program) {
    this->rendering_program = rendering_program;
}

void Grid::initialize(unsigned int vao) {
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);

    this->vertices = get_cell_vertices();

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

    initialize_cells();
}

void Grid::draw() {
    glUseProgram(rendering_program);

    // get uniform location
    GLuint view_loc = glGetUniformLocation(rendering_program, "view");
    GLuint model_loc = glGetUniformLocation(rendering_program, "model");

    for (Cell cell : this->cells) {
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 model = glm::mat4(1.0f);

        model = glm::translate(model, cell.position);

        // set shader uniforms
        glUniformMatrix4fv(view_loc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(model_loc, 1, GL_FALSE, glm::value_ptr(model));

        glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);

        glDrawArrays(GL_LINE_STRIP, 0, 8);
    }
}

std::vector<float> Grid::get_cell_vertices() {
    std::vector<float> all_vertices = {
            // x   y
            0.0f, 0.0f,
            0.1f, 0.0f,

            0.1f, 0.0f,
            0.1f, 0.1f,

            0.1f, 0.1f,
            0.0f, 0.1f,

            0.0f, 0.1f,
            0.0f, 0.0f
    };

    return all_vertices;
}

void Grid::initialize_cells() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            glm::vec3 position = glm::vec3(0.1f * i, 0.1f * j, 0.0f);
            Cell cell(position);
            this->cells.push_back(cell);
        }
    }
}

