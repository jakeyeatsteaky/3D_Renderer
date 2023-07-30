#version 330 core

out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texSample;

void main()
{
	vec4 tex = texture(texSample, TexCoord);
	FragColor = tex;


}