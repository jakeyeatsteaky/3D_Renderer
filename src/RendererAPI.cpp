#include "RendererAPI.h"
#include "Texture.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

// =================================== RENDERER_OPEN_GL ===================================
Renderer_GL::Renderer_GL() : 
	m_window(nullptr),
	m_renderer(nullptr),
	m_context(NULL)
{

}     

Renderer_GL::~Renderer_GL()
{
	SDL_GL_DeleteContext(m_context);
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void Renderer_GL::Init() const 
{
	OpenWindow();

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	SetupShaders();
	SetupTextures();

	// Right now vertex buffer info is populated in the constructor for a mesh
	// What shoiuld happen is vertex info should be passed in and mesh should be created that way
	m_mesh = new Mesh(m_shaders[0], m_textures[0]);

}

void Renderer_GL::Input() const
{

}

void Renderer_GL::Update() 
{
	m_mesh->SetShader();

	float time = static_cast<float>(SDL_GetTicks())/1000;
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	model 	   = glm::rotate(model, time * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f)); 
	view  	   = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    projection = glm::perspective(glm::radians(45.0f), (float)Renderer::WindowWidth / (float)Renderer::WindowHeight, 0.1f, 100.0f);
        
	unsigned int modelLoc = glGetUniformLocation(m_mesh->GetShader()->getID(), "model");
    unsigned int viewLoc  = glGetUniformLocation(m_mesh->GetShader()->getID(), "view");
	unsigned int projLoc   = glGetUniformLocation(m_mesh->GetShader()->getID(), "projection");

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, &projection[0][0]);
    
}

void Renderer_GL::Render() const {

	ClearScreen();
	
	m_mesh->Render();
	
	SDL_GL_SwapWindow(m_window);
}


void Renderer_GL::OpenWindow() const {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cerr << "Error initializing SDL\n";
		return;
	}

	// Set the desired OpenGL version
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	// Create the window using SDL
	m_window = SDL_CreateWindow(Renderer::WINDOW_TITLE, 
							  SDL_WINDOWPOS_UNDEFINED, 
							  SDL_WINDOWPOS_UNDEFINED, 
							  (int)Renderer::WindowWidth,
							  (int)Renderer::WindowHeight, 
							  SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	if (!m_window) {
		std::cerr << "Error creating SDL window\n";
		return;
	}

	// OpenGL context
	m_context = SDL_GL_CreateContext(m_window);
	if (!m_context)
	{
		std::cerr << "Error creating OpenGL Context\n";
		return;
	}

	// Enable glew experimental, this enables some more OpenGL extensions.
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Error initializing glewExperimental\n";
	}

	glViewport(0, 0, (GLsizei)Renderer::WindowWidth, (GLsizei)Renderer::WindowHeight);

	std::cout << "GL VERSION: " << glGetString(GL_VERSION) << std::endl;
	
}

void Renderer_GL::ClearScreen() const 
{
	glClearColor((GLclampf)0.5,(GLclampf) 0.3, (GLclampf)1.0,(GLclampf) 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer_GL::SetupShaders() const 
{
	std::shared_ptr<Shader> shader = std::make_shared<Shader>(Renderer::VERTEX_PATH, Renderer::FRAGMENT_PATH);
	m_shaders.push_back(shader);
}

void Renderer_GL::SetupTextures() const
{
	std::shared_ptr<Texture> texture = std::make_shared<Texture>(Renderer::TEXTURE_PATH, Extension_Type_JPG);
	std::shared_ptr<Texture> texture2 = std::make_shared<Texture>(Renderer::TEXTURE_PATH2, Extension_Type_PNG);
	m_textures.push_back(texture);
	m_textures.push_back(texture2);
}
















// =================================== RENDERER_VULKAN ===================================

Renderer_Vulk::Renderer_Vulk()
{

}

Renderer_Vulk::~Renderer_Vulk()
{

}

void Renderer_Vulk::Init() const {

}

void Renderer_Vulk::Render() const {

}

void Renderer_Vulk::Update() 
{

}

void Renderer_Vulk::Input() const
{

}

void Renderer_Vulk::OpenWindow() const {

}

void Renderer_Vulk::ClearScreen() const {

}

void Renderer_Vulk::SetupShaders() const
{
	
}

void Renderer_Vulk::SetupTextures() const
{

}


// =================================== RENDERER_DX3D ===================================

Renderer_DX::Renderer_DX()
{

}

Renderer_DX::~Renderer_DX()
{

}

void Renderer_DX::Init() const {

}

void Renderer_DX::Render() const {

}

void Renderer_DX::OpenWindow() const {

}

void Renderer_DX::Update() 
{

}

void Renderer_DX::ClearScreen() const {

}

void Renderer_DX::SetupShaders() const
{
	
}

void Renderer_DX::SetupTextures() const
{

}

void Renderer_DX::Input() const
{

}


