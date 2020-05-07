//
// Created by francisco on 6/5/20.
//

#ifndef METABALLS_GRID_H
#define METABALLS_GRID_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>

#include <vector>
#include "cell.h"

class Grid {
public:
    std::vector<float> vertices;
    unsigned int rendering_program{}, vbo{};
    std::vector<Cell> cells;

    Grid();

    explicit Grid(unsigned int rendering_program);

    void initialize(unsigned int vao);
    void initialize_cells();

    void draw();

private:
    std::vector<float> get_cell_vertices();
};


#endif //METABALLS_GRID_H
