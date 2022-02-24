/* Start Header**********************************************************************************/
/*
@file    SimpleDepth.frag
@author  Chia Yi da		c.yida@digipen.edu
@date    02/06/22

Used for depth calculation for Shadow Mapping (Lights and Shadows)
*/
/* End Header **********************************************************************************/

#version 450 core

uniform sampler2D uShadowMap;
uniform sampler2D uDiffuseTexture;
uniform vec2 uLightPos;
uniform vec2 uViewPos;

layout (location=0) in vec2 vTexture;

in VS_OUT {
    vec3 fragPos;
    vec3 normal;
    vec2 texCoords;
    vec4 fragPosLightSpace;
} fs_in;

layout (location=0) out vec4 fColor;


float ShadowCalculation(vec4 fragPosLightSpace)
{
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;

    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;

    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(uShadowMap, projCoords.xy).r; 

    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;

    // check whether current frag pos is in shadow
    float shadow = currentDepth > closestDepth ? 1.0 : 0.0;

    return shadow;
}


void main()
{       
    vec3 color = texture(uDiffuseTexture, fs_in.texCoords).rgb;
    vec3 normal = normalize(fs_in.normal);
    vec3 lightColor = vec3(1.0);

    // ambient
    vec3 ambient = 0.15 * lightColor;

    // diffuse
    vec3 lightDir = normalize(vec3(uLightPos, 0.0f) - fs_in.fragPos);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * lightColor;

    // specular
    vec3 viewDir = normalize(vec3(uViewPos, 0.0f) - fs_in.fragPos);
    float spec = 0.0;
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    spec = pow(max(dot(normal, halfwayDir), 0.0), 64.0);
    vec3 specular = spec * lightColor;   
    
    // calculate shadow
    float shadow = ShadowCalculation(fs_in.fragPosLightSpace);       
    vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * color;    
    
    fColor = vec4(lighting, 1.0);
}  