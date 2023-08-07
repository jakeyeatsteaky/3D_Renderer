#version 330 core

in vec2 pos;
out vec4 FragColor;

bool isSquare(vec2 posi)
{
	if(posi.x > -0.25 && pos.x < 0.25)
	{
		if(posi.y > -0.25 && posi.y < 0.25)
		{
			return true;
		}
	}
	return false;
}

void main()
{
	if(isSquare(pos))
	{
		FragColor = vec4(1.0,0.0,0.0,1.0);
	}
	else
	{
		FragColor = vec4(0.0,0.0,1.0,1.0);
	}
}