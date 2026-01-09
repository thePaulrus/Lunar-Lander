$input a_position

#include <bgfx_shader.sh>

uniform mat4 u_OBJtoWorld;
uniform mat4 u_WorldToVeiw;
uniform mat4 u_MatProj;



void main()
{
	vec4 objectSpacePosition = vec4(a_position,1);  // Apply object transform. 
	vec4 worldSpacePosition = mul(u_OBJtoWorld,objectSpacePosition); // Apply world transform.
	vec4 viewSpacePosition = mul(u_WorldToVeiw,worldSpacePosition); // Apply view transform.
	vec4 clipSpacePosition = mul(u_MatProj,viewSpacePosition); // Apply projection transform. 
	gl_Position = clipSpacePosition ;
}




