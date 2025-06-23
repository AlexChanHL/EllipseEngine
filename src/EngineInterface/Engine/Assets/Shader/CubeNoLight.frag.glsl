#version 410 core

in vec3 outNormalDirection;
in vec3 outFragmentPosition;
in vec2 outTexCoord;

uniform sampler2D sampler1;

out vec4 fragColor;


void main()
{
                           
   fragColor = vec4(vec3(texture(sampler1, outTexCoord)), 1.0f);
} 
