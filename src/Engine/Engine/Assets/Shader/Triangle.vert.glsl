#version 410 core

layout (location=0) in vec3 vertPos;

uniform float offset;

void main()
{
     gl_Position = vec4(vertPos.x + offset, vertPos.yz, 1.0f);
}
