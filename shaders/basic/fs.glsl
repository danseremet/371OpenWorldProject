#version 330 core

uniform vec3 lightColor = vec3(1.0, 1.0, 1.0);
uniform vec3 lightPos = vec3(5.0, 10.0, 5.0);

uniform vec3 viewPos;

uniform float ambientStrength = 0.1;
uniform float diffuseStrength = 0.8;
uniform float specularStrength = 0.5;

in vec3 FragPos;
in vec3 Normal;
in vec3 vertexColor;
out vec4 FragColor;

void main() {
   vec3 ambient = ambientStrength * lightColor;

   vec3 norm = normalize(Normal);
   vec3 lightDir = normalize(lightPos - FragPos);
   float diff = diffuseStrength * max(dot(norm, lightDir), 0.0);
   vec3 diffuse = diff * lightColor;

   vec3 viewDir = normalize(viewPos - FragPos);
   vec3 reflectDir = reflect(-lightDir, norm);
   float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
   vec3 specular = specularStrength * spec * lightColor;

   vec3 result = (ambient + diffuse + specular) * vertexColor;
   FragColor = vec4(result, 1.0);
}