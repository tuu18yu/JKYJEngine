#shader vertex
#version 330 core

layout(location=0) in vec4 pos;

void main()
{
	gl_Position = pos;
}

#shader fragment
#version 330 core

layout(location=0) out vec4 color;

void main()
{
	color = vec4(1.0, 0.0, 0.0, 1.0);
}