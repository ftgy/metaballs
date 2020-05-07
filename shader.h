//
// Created by francisco on 2/5/20.
//

#ifndef COMPUTER_GRAPHICS_PROGRAMMING_BOOK_SHADER_H
#define COMPUTER_GRAPHICS_PROGRAMMING_BOOK_SHADER_H

#include <string>
#include <iostream>
#include <fstream>
#include <GL/glew.h>

using namespace std;

class Shader {

public:
    GLuint createShaderProgram();

    string readShaderSource(const char *filePath);

private:
    static bool checkOpenGLError();
    static void printShaderLog(GLuint shader);
    static void printProgramLog(int program);
};

#endif //COMPUTER_GRAPHICS_PROGRAMMING_BOOK_SHADER_H
