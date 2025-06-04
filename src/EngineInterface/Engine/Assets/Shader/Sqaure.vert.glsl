#version 410 core

layout (location=0) in vec3 vertexPosition;
layout (location=1) in vec3 normalDirection;
layout (location=2) in vec2 texCoord;

uniform mat4 proj;
uniform mat4 view; 
uniform mat4 model; 

out vec3 outNormalDirection;
out vec3 outFragmentPOsition;

