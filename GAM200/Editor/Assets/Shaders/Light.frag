/* Start Header**********************************************************************************/
/*
@file    Light.frag
@author  Chia Yi da		c.yida@digipen.edu
@date    07/06/2021
*/
/* End Header **********************************************************************************/

#version 450 core


struct Light
{
    //vec3 direction;
    vec3 position;

    float ambient;
    vec3 diffuse;
    float specular;

	float constant;
	float linear;
	float specularValue;

    vec3 colour;
};


uniform sampler2D u_Textures[32];
uniform Light light;


layout (location=0) in vec4 vColor;
layout (location=1) in vec2 vTexture;
layout (location=2) in float vTextureIndex;
layout (location=3) in vec3 vFragPosition;
layout (location=4) in vec3 vNormal;

layout (location=0) out vec4 fColor;



void main () 
{
    vec3 ViewPosition = {0.0f, 0.0f, 1.0f};

    // Ambient
    vec3 ambient = light.ambient * light.colour;
    
    // Diffuse
    vec3 normal = normalize(vNormal);
    vec3 lightDir = normalize(light.position - vFragPosition);
    //vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(normal, lightDirection), 0.0);
    vec3 diffuse = diff * light.colour;

    // Specular
    vec3 viewDir = normalize(ViewPosition - vFragPosition);
    vec3 reflectDir = reflect(-lightDirection, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = light.specular * spec * light.colour;

    // Attenuation 
    float distance = length(light.position - vFragPosition);
    float attenuation =  1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;


	// Object colour, with lighting
    int index = int(vTextureIndex);
	vec4 texColor = texture(u_Textures[index], vTexture) * vColor;

    vec4 result = vec4((ambient + diffuse + specular), 1.0f);
    fColor = result * texColor;
}