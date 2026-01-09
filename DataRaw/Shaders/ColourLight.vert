$input a_position, a_color0, a_normal,
$output v_color0, v_normal, v_position

#include <bgfx_shader.sh>

uniform mat4 u_OBJtoWorld;
uniform mat4 u_WorldToVeiw;
uniform mat4 u_MatProj;
uniform mat4 u_MatWorldRotation;

vec2 TransformIntoWorldSpace(vec2 pos);

void main()
{
	
	vec4 objectSpacePosition = vec4(a_position,1.0);  // Apply object transform. 
	vec4 worldSpacePosition = mul(u_OBJtoWorld,objectSpacePosition); // Apply world transform.
	vec4 viewSpacePosition = mul(u_WorldToVeiw,worldSpacePosition); // Apply view transform.
	vec4 clipSpacePosition = mul(u_MatProj,viewSpacePosition); // Apply projection transform. 
	gl_Position = clipSpacePosition ;

    v_color0 = a_color0;

	vec3 rotatedNormal = mul( u_MatWorldRotation, vec4(a_normal,0) ).xyz;

	v_normal = rotatedNormal;

	v_position = worldSpacePosition.xyz;
}

