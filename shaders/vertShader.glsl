#version 430
layout (location=0) in vec2 position;

uniform mat4 view;
uniform mat4 model;

void main(void)
{
    gl_Position = view * model * vec4(position, 1.0 ,1.0);
}
