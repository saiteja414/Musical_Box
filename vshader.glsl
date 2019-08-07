#version 400

in vec4 vPosition;
in vec4 vColor;
in vec2 texCoord;
in vec2 tex_present;
in vec3 vNormal;

uniform mat4 viewMatrix;
uniform float light1;
uniform float light2;

out vec4 color;
uniform mat4 uModelViewMatrix;
uniform mat3 normalMatrix;
out vec2 tex;
out float tex_p;
out vec3 normal;
out vec4 eye;

out float l1;
out float l2;

void main (void) 
{
  gl_Position = uModelViewMatrix * vPosition; 
  color = vColor;
  tex = texCoord;
  normal = normalMatrix * normalize(vNormal);
  tex_p = tex_present[0];
  eye = - (uModelViewMatrix * gl_Position);
  l1 = light1;
  l2 = light2;
}
