
#version 410 core

layout (location=0) in vec3 vertexPosition;
layout (location=1) in vec3 normalDirection;
layout (location=2) in vec2 texCoord;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

out vec3 outNormalDirection;
out vec3 outFragmentPosition;
out vec2 outTexCoord;

void main()
{
     gl_Position = proj * view * model * vec4(vertexPosition, 1.0f);
     outFragmentPosition = vec3(model * vec4(vertexPosition, 1.0f));
     outNormalDirection = normalDirection;
     outTexCoord = texCoord;
}
