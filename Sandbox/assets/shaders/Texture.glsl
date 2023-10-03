// Basic Texture Shader

#ShaderName Texture

#type vertex
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;

layout(location = 2) in vec4	a_Color;
layout(location = 3) in float   a_TexIndex;
layout(location = 4) in float	a_TilingFactor;

layout(location = 5) in vec4	a_M1;
layout(location = 6) in vec4	a_M2;
layout(location = 7) in vec4	a_M3;
layout(location = 8) in vec4	a_M4;

uniform mat4 u_ViewProjection;

out vec4 v_Color;
out vec2 v_TexCoord;
out float v_TexIndex;
out float v_TilingFactor;


void main()
{
	v_Color = a_Color;
	mat4 model = mat4(a_M1,a_M2,a_M3,a_M4);
	v_TexCoord = a_TexCoord;
	v_TexIndex = a_TexIndex;
	v_TilingFactor = a_TilingFactor;
	gl_Position = u_ViewProjection * model * vec4(a_Position, 1.0f);
}

#type fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec4 v_Color;
in vec2 v_TexCoord;
in float v_TexIndex;
in float v_TilingFactor;

uniform sampler2D u_Textures[32];

void main()
{
	//color = v_Color;
	vec4 tex = texture(u_Textures[int(v_TexIndex)], v_TexCoord * v_TilingFactor);
	color = tex * v_Color;
}