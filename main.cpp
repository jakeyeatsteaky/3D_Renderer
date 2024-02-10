#include "App.hpp"
#include "enumerations.h"
/////////////////// GLOBAL TODO ///////////////////
#if 0
	SDL Renderer

		[ ] Start making some shapes
		[ ] Dependency injection --> shapes register with app upon creation
			- app has a vector of shapes
			- app.render itrerates through this vector and calls renderer->drawShape(shape);


		[ ] clean up vulkan shit that needs to build at the start

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


// TODO for OpenGL Renderer
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

// TODO for Vulkan Renderer
#if 0

		1)[x] Update the VK_CHECK so that the checks called in the Draw() method do not spam print messages
		2)[] Look at making tha Draw() method a little tighter
		[] Make some documentation on how that process works first and then clean it up
		3)[x] Finish the tut Chapter 2
		[x] The render pipeline
		[x] Setting up Trangle shaders
		[x] Setting up render pipeline
		[x] Passing data between shader stages
		[x] Toggling shaders
		[x] Did My Own Implementation
		[x] As an exercise, add a third shader, and iterate through all three using spacebar
		[x] Read the docs on vkguide just to see what he did(Section: Multiple Pipelines)
		[x] cleanup and deletion queue
		4)[] Chapter 3
		[] Vertex Buffers

		5)[] Implement the command pattern for updating game objects ? ?


		NOTE FOR WHEN YOU COME BACK
		Right now I am curious about how to handle the toggling of a shader.SHould the updateShaderIdx function be called from App.Input ? Or should I append a command ?

		I would like to implement the command pattern here, and maybe even make it multithreaded.Somewthing to think about.


#endif
