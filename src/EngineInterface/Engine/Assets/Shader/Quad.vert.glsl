#version 410 core

layout (location=0) in vec3 pos;
layout (location=1) in vec3 normal;
layout (location=2) in vec2 texCoord;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;


void main()
{
    gl_Position = proj * view * model * vec4(pos, 1.0f);
}

