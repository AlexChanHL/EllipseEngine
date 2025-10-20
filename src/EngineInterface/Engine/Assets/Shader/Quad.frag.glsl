#version 410

in vec2 outTexCoord;

out vec4 fragColor;

uniform sampler2D sampler1;

uniform vec3 colorKey;


void main()
{
    // 96.1, 96.9, 94.9
    vec3 tex = vec3(texture(sampler1, outTexCoord));
    vec3 compKey = vec3(0.961f, 0.969f, 0.949f);
    tex *= 100;
    tex = round(tex);
    compKey *= 100;
    compKey = round(compKey);

    if(tex == compKey) { 
     // fragColor = vec4(1.0f, 0.0f, 1.0f, 1.0f);
     discard;
    }
    if(tex != compKey) { 
     fragColor = vec4(vec3(texture(sampler1, outTexCoord)), 1.0f);
    }
}

