#version 330 core

in vec4 vertex;
in vec4 colour;
uniform mat4 transMatrix;

out vec4 oColor;

void main()                    
{
	gl_Position = transMatrix * vertex;
    oColor = colour;
}