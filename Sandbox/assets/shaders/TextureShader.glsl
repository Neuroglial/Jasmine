// Basic Texture Shader

#ShaderName TextureShader

#type vertex
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TexCoord;
layout(location = 3) in int a_TexIndex;
layout(location = 4) in float a_TilingFactor;

uniform mat4 u_ViewProjection;

smooth out vec4 v_Color;
smooth out vec2 v_TexCoord;
smooth out float v_TilingFactor;
flat out int v_TexIndex;


void main()
{
	v_Color = a_Color;
	v_TexCoord = a_TexCoord;
	v_TexIndex = a_TexIndex;
	v_TilingFactor = a_TilingFactor;
	gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
}

#type fragment
#version 330 core

layout(location = 0) out vec4 color;

smooth in vec4 v_Color;
smooth in vec2 v_TexCoord;
smooth in float v_TilingFactor;
flat in int v_TexIndex;

uniform sampler2D u_Textures[32];

void main()
{
	color = texture(u_Textures[v_TexIndex], v_TexCoord * v_TilingFactor) * v_Color;
}