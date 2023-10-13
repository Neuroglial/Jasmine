// Basic Texture Shader

#ShaderName TextureShader

#type vertex
#version 330 core
layout(location = 0) in vec4 Position;
layout(location = 1) in vec2 TexCoord;

layout(location = 2) in vec4 s_MatV1;
layout(location = 3) in vec4 s_MatV2;
layout(location = 4) in vec4 s_MatV3;
layout(location = 5) in vec4 s_MatV4;

layout(location = 6) in vec4 s_Color;
layout(location = 7) in float s_TexIndex;
layout(location = 8) in float s_TilingFactor;

uniform mat4 u_ViewProjection;

out vec4 v_Color;
out vec2 v_TexCoord;
flat out int v_TexIndex;


void main()
{
	v_Color = s_Color;
	v_TexCoord = TexCoord * s_TilingFactor;
	v_TexIndex = int(s_TexIndex);

	mat4 model = mat4(s_MatV1,s_MatV2,s_MatV3,s_MatV4);

	gl_Position = u_ViewProjection * model * Position;
}

#type fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec4 v_Color;
in vec2 v_TexCoord;
flat in int v_TexIndex;

uniform sampler2D u_Textures[32];

void main()
{
	color = texture(u_Textures[v_TexIndex], v_TexCoord) * v_Color;
}