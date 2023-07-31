#include "App.h"
#include "enumerations.h"
/////////////////// GLOBAL TODO ///////////////////
#if 0

 1) [x] Create Vertex Buffer Object
 2) [x] Create Index Buffer Object
 3) [x] Create Vertex Array Object
 4) [x] Create Vertex Layout Object
 5) [x] Create Mesh Class
 6) [x] Init a mesh and draw it
		[x] Passing the VertexArray into the Mesh object via pointer works, but try to pass via rvalue reference (RendererApi.cpp, Renderer_GL::Init())
 7) [ ] Check destruction of objects and verify with print statements
 7) [x] Make Texture Class
 8) [x] Put all that vertex stuff inside a mesh object.  Mesh should have a shader, texture and vertex info

** Copy ctor / assignops and Move ctor / assignops for all existing classes
 9) [ ] Rule of 5 for my existing render classes (vbuf, ibuf, varray, vlayout, mesh)
10) [ ] Make some primitive shapes.

11) [x] Make Vertex structs to pass into Mesh objects
12) [x] Get the Cube to work being passed into a Mesh - Main issue is with the attribtue layout(since the cube vertices dont use a color), and also the indices buffer
		Retrospective: What ended up happening is that when I was updating the meshes, it did 
		some calculations on their matrices.  The last shader to have been set was the prevuious 
		mesh so it was never showing the first one
		I just had to add SetShader() in the update function.

	*****START HERE NEXT TIME *****
13) [ ] Get some more meshes in here and verify all VertesLayouts
		[ ] More vertices added and test layouts in all forms with different m_viewMatric (position)
		[ ] The vectors probably need to be better because its getting confusing
14) [ ] Continue on with the OpenGL tutorial.  Mesh objects are created - now work on 3d objects and cameras
		[ ] Coordinate Systems Section
15) [ ] Imgui integration
16) [ ] Shader Practice mode 

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
How this renderer works so I can quickly get up to speed

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

