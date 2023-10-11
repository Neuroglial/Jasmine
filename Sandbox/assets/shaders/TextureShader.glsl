// Basic Texture Shader

#ShaderName TextureShader

#type vertex
#version 330 core
layout(location = 0) in vec3 Position;
layout(location = 1) in vec2 TexCoord;

layout(location = 2) in vec3 s_Position;
layout(location = 3) in vec2 s_Size;
layout(location = 4) in float s_Rotate;
layout(location = 5) in vec4 s_Color;
layout(location = 6) in float s_TexIndex;
layout(location = 7) in float s_TilingFactor;

uniform mat4 u_ViewProjection;

out vec4 v_Color;
out vec2 v_TexCoord;
flat out int v_TexIndex;


void main()
{
	v_Color = s_Color;
	v_TexCoord = TexCoord * s_TilingFactor;
	v_TexIndex = int(s_TexIndex);
	
	float rotate = s_Rotate/180.0f*3.14159265;
	vec2 pos = Position.xy * s_Size;
	pos = vec2(pos.x*cos(rotate)-pos.y*sin(rotate),pos.y*cos(rotate)+pos.x*sin(rotate));
	gl_Position = u_ViewProjection * vec4(pos + s_Position.xy ,s_Position.z, 1.0);
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
	if (color.a == 0.0)
		discard;
}