//
// Created by francisco on 7/5/20.
//

#ifndef METABALLS_CELL_H
#define METABALLS_CELL_H

#include <glm/glm.hpp>

class Cell {
public:
    glm::vec3 position{};

    explicit Cell(glm::vec3 position);
};


#endif //METABALLS_CELL_H
