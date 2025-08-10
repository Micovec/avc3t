#shader vertex
#version 300 es

in vec3 i_Position;
in vec3 i_Color;

uniform mat4 u_MVP;

out vec3 v_Color;

void main()
{
	gl_Position = u_MVP * vec4(i_Position, 1);
	v_Color = i_Color;
}

#shader fragment
#version 300 es

precision highp float;
precision highp sampler2D;

in vec3 v_Color;

out vec4 o_Color;

void main()
{
	o_Color = vec4(v_Color, 1);
}