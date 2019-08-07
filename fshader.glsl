#version 400

in vec4 eye;
in vec3 normal;
in vec4 color;
in vec2 tex;
in float tex_p;
in float l1;
in float l2;

uniform mat4 viewMatrix;

out vec4 frag_color;

uniform sampler2D texture1;

void main () 
{
    vec4 texImage = texture(texture1, tex);
    
    vec4 specular = vec4(0.5);
    vec4 d = vec4(0.45, 0.45, 0.45, 1.0);
    vec4 a = vec4(0.2, 0.2, 0.2, 1.0);
    vec4 s = vec4(0.2, 0.2, 0.2, 1.0);
    float reflectivity = 1.0;

    vec4 light1 = vec4(-8.0, 13.0, 12.0, 0.0);
    vec3 lightD1 = vec3(viewMatrix * light1);
    lightD1 = normalize(lightD1);

    vec4 light2 = vec4(100.0, -100.0, 1000.0, 0.0);
    vec3 lightD2 = vec3(viewMatrix * light2);
    lightD2 = normalize(lightD2);

    vec4 color1 = vec4(0.0);
    vec4 color2 = vec4(0.0);
    vec3 normal1 = normalize(vec3(normal));
    if(l1 > 0.1){
    float intensity ;
    if(dot(normal1, lightD1) > 0.0) intensity = dot(normal1, lightD1);
    else intensity = 0;

    if(intensity > 0.0) {
        vec3 eye = normalize(vec3(eye));
        vec3 h = normalize(lightD1 + eye );
        float spec_int = max(dot(h,normal1), 0.0);
        specular = s * pow(spec_int, reflectivity);
    }

    color2 += (intensity * d  + specular)*color-vec4(0,0,0,color[3]*(intensity * d  + specular) - color[3]);
    color1 += (intensity * d  + specular)*texImage; // All
    }


    if(l2 > 0.5) {
    float intensity ;
        if(dot(normal1, lightD2) > 0) intensity = dot(normal1, lightD2);
    else intensity = 0;

    if(intensity > 0.0) {
        vec3 eye = normalize(vec3(eye));
        vec3 h = normalize(lightD2 + eye );
        float spec_int = max(dot(h,normal1), 0.0);
        specular = s * pow(spec_int, reflectivity);
    }

    color2 += (intensity * d  + specular)*color-vec4(0,0,0,color[3]*(intensity * d  + specular) - color[3]);
    color1 += (intensity * d  + specular)*texImage; // All
    }

    color1[3] = 1;
    //color2[3] = 1;

  if(tex_p < 0.5) frag_color = color2;
  else frag_color = color1;
}

