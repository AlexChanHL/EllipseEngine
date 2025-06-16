#version 410 core

in vec3 outNormalDirection;
in vec3 outFragmentPosition;
in vec2 outTexCoord;

out vec4 fragColor;


struct Light
{
    bool m_isDirectional; 

    vec3 m_ambient;
    vec3 m_diffuse;
    vec3 m_specular;

    vec3 m_lightColor;
    vec3 m_lightPosition;
    vec3 m_lightDirection;

    bool m_isSpotlight;
};

struct Specular
{
    vec3 m_specular;
    float m_reflectiveness;
};

struct Material
{
    vec3 m_ambient; 
    vec3 m_diffuse; 
    Specular m_specular; 
};

// uniform mat3 normalMatrixObject;

uniform sampler2D sampler1;
// uniform sampler2D sampler2;
// uniform float phiUser;
// uniform float outerRadiusObject;
// uniform vec3 cameraFrontObject;
uniform vec3 cameraPositionObject;
uniform Material materialObject;

uniform Light lightObject;

vec3 ambientValues(Light lightObject,
                   vec3 textureAmbient
                   )
{
   return lightObject.m_ambient * textureAmbient;
}

vec3 diffuseValues(Light lightObject,
                   vec3 lightDirection,
                   vec3 normalDirection,
                   vec3 textureDiffuse)
{
   vec3 diffuse = max(dot(lightDirection, normalDirection), 0) * materialObject.m_diffuse * lightObject.m_diffuse;

   return diffuse * textureDiffuse;
}

vec3 specularValues(Light lightObject,
                    vec3 lightDirection,
                    vec3 viewPosition,
                    vec3 fragmentPosition,
                    vec3 normalDirection,
                    vec3 textureSpecular
                    )
{
   vec3 viewDirection = normalize(viewPosition - fragmentPosition);

   vec3 reflectedLightDirection = reflect(-lightDirection, normalDirection);

   vec3 specular = pow(max(dot(reflectedLightDirection, viewDirection), 0.0f), materialObject.m_specular.m_reflectiveness) * materialObject.m_specular.m_specular * lightObject.m_specular;

   // return specular * textureSpecular;
   return specular;
}


void main()
{
   vec3 ambient = vec3(0.0f);
   vec3 specular = vec3(0.0f);
   vec3 diffuse = vec3(0.0f);


   vec3 objectLight = vec3(1.0f, 1.0f, 1.0f);

   // vec3 previousLight = vec3(0.0f, 0.0f, 0.0f);
   //
   vec3 normalDirection = normalize(outNormalDirection);
   // normalDirection = normalDirection * normalMatrixObject;
   // 
   vec3 lightDirection = vec3(0.0f, 0.0f, 0.0f);
   // if(light.m_isDirectional)
   // {
   // lightDirection = lightObject.m_lightDirection;
   // }
   // if(!lightObject.m_isDirectional)
   // {
   lightDirection = normalize(lightObject.m_lightPosition - outFragmentPosition);
   // }
   // // if(light.m_isSpotlight)
   // // {
   // //
   // // }
   //
   float lightIntensity = 1.0f;
   // if(!lightObject.m_isDirectional)
   // {
   float lightDistance = length(outFragmentPosition - lightObject.m_lightPosition);

   float kq = 0.1f;
   float kl = 0.252f;
   float kc = 1.0f;

   lightIntensity = pow((kq * pow(lightDistance, 2) + kl * lightDistance + kc), -1);
   // }

   ambient = ambientValues(lightObject,
                           vec3(texture(sampler1, outTexCoord))
                          );
   diffuse = diffuseValues(lightObject,
                           lightDirection,
                           normalDirection,
                           vec3(texture(sampler1, outTexCoord))
                          );
   specular = specularValues(lightObject,
                             lightDirection,
                             cameraPositionObject,
                             outFragmentPosition,
                             normalDirection,
                             vec3(texture(sampler1, outTexCoord)) 
                             );

                             // vec3(texture(sampler2, outTexCoord)) 

   // // if(lightObject.m_isSpotlight)
   // // {
   // // float phi = phiUser;
   // // float theta = acos(dot(-lightDirection, cameraFrontUser));
   // // vec3 spotlight = vec3(1.0f, 1.0f, 1.0f);
   // //
   // // float epsilon = outerRadiusUser - phiUser;
   // // float spotlightStrength = (theta - outerRadiusUser) / epsilon;
   // //
   // // spotlight = spotlight * max(-spotlightStrength, 0.0001f);
   // //
   // // ambient = ambient * spotlight.x;
   // // diffuse = diffuse * spotlight.y;
   // // specular = specular * spotlight.z;
   // // }

   vec3 lightElements = (ambient + diffuse + specular) * lightIntensity;

   objectLight = lightElements;
   // }
   //
   
   vec3 objectColor = objectLight;

   fragColor = vec4(objectColor, 1.0f);
} 
