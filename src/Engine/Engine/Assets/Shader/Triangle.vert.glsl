#version 410 core

layout (location=0) in vec3 vertexPositionUniform;
layout (location=2) in vec2 textureCoordsUniform;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

out vec2 textureCoords;

void main()
{
     gl_Position = proj * view * model * vec4(vertexPositionUniform, 1.0f);
     textureCoords = textureCoordsUniform;
}
