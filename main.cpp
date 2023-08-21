#include "App.h"
#include "enumerations.h"
/////////////////// GLOBAL TODO ///////////////////
#if 0

1) [x] Update the VK_CHECK so that the checks called in the Draw() method do not spam print messages
2) [ ] Look at making tha Draw() method a little tighter
3) [ ] Finish the tut(chapter 2 is next);

#endif


int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
	App app;
	app.Setup();

	while (app.IsRunning())
	{
		app.Input();
		app.Update();
		app.Render();
	}

	app.Destroy();

	return 0;

}


#if 0
How this renderer works so I can quickly get up to speed for OpenGL

- Main Application loop will initialize objects in the Scene	
	- TODO: Create Scene class.  Right now all I have is the Renderer_API

- Main application loop calls input handling, update, and rendering

- Renderer Singleton: unique pointer to renderer interface object.  renderer api is determined in App::Setup
	- m_renderer->init() will set up API specific things
	- this is also where renderer specific data is initialized

- Vertex data, shaders, textures, vertex layouts, and meshes are all constructed in this function 
	- they are all stored in a container (vector) for access by meshes
	- all meshes stored in a vector 
	- renderer loop iterates through meshes and input, update, renders them

- How meshes work:
	- meshes take a pointer to vertex and index containers, pointer toa shader program, pointer to a texture, pointer to a vertex layout to _ConstructiblePair
		- meshes have MVP matricies
		- on construction, the VAO is bound so the vertex info can be bound to that vertex array 
		- when rendering you just need to bind the vertex array 


#endif

