#version 330 core
out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform float ambientStrength;

void main()
{
  vec3 ambient = ambientStrength * lightColor;

  vec3 result = ambient * objectColor;
  FragColor = vec4(result, 1.0);
}
