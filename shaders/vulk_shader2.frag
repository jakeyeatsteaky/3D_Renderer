#version 450


// output 
layout (location = 0) out vec4 outFragColor;

// input from the vertex shader
layout (location = 0) in vec3 inputColor;


void main()
{
	outFragColor = vec4(inputColor, 1.0f);
}
