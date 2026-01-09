$input v_color0, v_normal,v_position




#include <bgfx_shader.sh>

uniform vec4 u_camPos;
void main()
{
vec3 normal = v_normal;
normal = normalize(v_normal);

//hard coded values. rip these out eventually
vec3 lightPos = vec3(50,5,50);
float shininess = 50.0; //how focused is the reflection
vec4 matcolor = vec4(1.0,0.0,0.0, 1.0);
vec3 lightcolor = vec3(1,0,0);
float ambientPerc = 0.2;
float LightRange = 20.0;
float fallOffExp = 0.5; 

vec3 litSurfaceColour = matcolor.xyz * lightcolor;

vec3 DirToLight = normalize(lightPos - v_position);
float diffusePercentage = dot(DirToLight, normal);

diffusePercentage = max(diffusePercentage, 0);

//attenuation
float DistenceFromLight = length(v_position - lightPos);
float attenuation = max((1-pow(DistenceFromLight /LightRange,fallOffExp )),0);

//specular
vec3 dirToCamera = normalize( u_camPos.xyz - v_position.xyz );
vec3 halfVector = normalize( dirToCamera + DirToLight );

float specularPerc = max(pow(dot(halfVector, v_normal), shininess),0);

vec3 ambient = litSurfaceColour * ambientPerc;
vec3 diffuse = litSurfaceColour * diffusePercentage;
vec3 specular = lightcolor * specularPerc;

vec3 finalColour = ambient + (diffuse + specular) * attenuation;

vec4 colour =vec4(finalColour, matcolor.w);
    gl_FragColor = vec4(colour);

    //matcolor.xyz * lightcolor * diffusePercentage * attenuation * specularPerc
}
