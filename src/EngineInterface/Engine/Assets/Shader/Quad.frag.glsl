#version 410

in vec2 outTexCoord;

out vec4 fragColor;

uniform sampler2D sampler1;


void main()
{
    fragColor = vec4(vec3(texture(sampler1, outTexCoord)), 1.0f);
}

