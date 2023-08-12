#include "RendererAPI.h"
#include "Texture.h"
#include <fstream>
#include <cstring>

#include <SDL2/SDL.h>
#ifdef USING_VULKAN
#include <SDL_vulkan.h>
#include "VkBootstrap.h"
#define VK_CHECK(x)														\
	do																	\
	{																	\
		VkResult err = x;												\
		if (err)														\
		{																\
			std::cout <<"Detected Vulkan error: " << err << std::endl;	\
			abort();													\
		}																\
	} while (0)

#endif

// =================================== RENDERER_OPEN_GL ===================================
#ifdef USING_GL
Renderer_GL::Renderer_GL() : m_window(nullptr),
							 m_renderer(nullptr),
							 m_context(NULL)
{
	Init();
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

	SetupVertexData();
	SetupShaders();
	SetupTextures();
	SetupVertexLayouts();
	GeneratePrimitives();

	// Square
	std::shared_ptr<Mesh> mesh1 = std::make_shared<Mesh>(m_vertexBuffers[0], 
														 m_indexBuffers[0], 
														 m_shaders[1], 
														 m_textures[1], 
														 m_vertexLayouts[2],
														 glm::vec3(-0.5f, -0.5f, -7.0f),
														 true);

	// Cube
	std::shared_ptr<Mesh> mesh2 = std::make_shared<Mesh>(m_vertexBuffers[1], 
														 m_indexBuffers[0], 
														 m_shaders[0], 
														 m_textures[0], 
														 m_vertexLayouts[1],
														 glm::vec3(0.5f, 0.5f, -17.0f));

	// Square, position only
	std::shared_ptr<Mesh> mesh3 = std::make_shared<Mesh>(m_vertexBuffers[2],
														 m_indexBuffers[0], 
														 m_shaders[2], 
														 m_textures[0], 
														 m_vertexLayouts[0],
														 glm::vec3(0.5f, 0.15f, -7.0f),
														 true);
	m_meshes.push_back(mesh1);
	m_meshes.push_back(mesh2);
	m_meshes.push_back(mesh3);
}

void Renderer_GL::Input() const
{
}

void Renderer_GL::Update()
{
	for (auto mesh : m_meshes)
	{

		float time = static_cast<float>(SDL_GetTicks()) / 1000;
		mesh->Update(time);
	}

}

void Renderer_GL::Render() const
{

	ClearScreen();
	for (auto mesh : m_meshes)
	{
		mesh->SetUpdate();
		mesh->Render();
	}

    SDL_GL_SwapWindow(m_window);

}

void Renderer_GL::OpenWindow() const
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
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
	if (!m_window)
	{
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
#ifdef __linux__
	glewExperimental = GL_TRUE;
#endif
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Error initializing glewExperimental\n";
	}

	glViewport(0, 0, (GLsizei)Renderer::WindowWidth, (GLsizei)Renderer::WindowHeight);

	std::cout << "GL VERSION: " << glGetString(GL_VERSION) << std::endl;
}

void Renderer_GL::ClearScreen() const
{
	glClearColor((GLclampf)0.5, (GLclampf)0.3, (GLclampf)1.0, (GLclampf)1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer_GL::SetupShaders() const
{
	std::shared_ptr<Shader> shader0 = std::make_shared<Shader>(Renderer::VERTEX_PATH_0, Renderer::FRAGMENT_PATH_0);
	std::shared_ptr<Shader> shader1 = std::make_shared<Shader>(Renderer::VERTEX_PATH_1, Renderer::FRAGMENT_PATH_1);
	std::shared_ptr<Shader> shader2 = std::make_shared<Shader>(Renderer::VERTEX_PATH_2, Renderer::FRAGMENT_PATH_2);
	
	m_shaders.push_back(shader0);
	m_shaders.push_back(shader1);
	m_shaders.push_back(shader2);
}

void Renderer_GL::SetupTextures() const
{
	std::shared_ptr<Texture> texture = std::make_shared<Texture>(Renderer::TEXTURE_PATH, Extension_Type_JPG);
	std::shared_ptr<Texture> texture2 = std::make_shared<Texture>(Renderer::TEXTURE_PATH2, Extension_Type_PNG);
	m_textures.push_back(texture);
	m_textures.push_back(texture2);
}

void Renderer_GL::SetupVertexData() const
{
	size_t numImports = 3; 

	std::vector<const char*> paths_to_vertexdata = {};
	paths_to_vertexdata.push_back("../assets/vertex_data/square.txt");
	paths_to_vertexdata.push_back("../assets/vertex_data/cube.txt");
	paths_to_vertexdata.push_back("../assets/vertex_data/square_no_color.txt");
	paths_to_vertexdata.push_back("../assets/index_data/square_indices.txt");
	paths_to_vertexdata.push_back("../assets/index_data/cube_indices.txt");

	// import data
	for(size_t i = 0; i < numImports; ++i)
	{
		std::vector<float> datavec = {};
		try {
			std::ifstream file(paths_to_vertexdata[i], std::ios::in);
			if (!file)
				std::cerr << "Failed to open the file.\n";
			else { 
		 		float number;
				while (file >> number) {
					if(number == '#') 
            			file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					else
						datavec.push_back(number);
				}
			}	 
		}
		catch (const std::ifstream::failure &e) { std::cerr << "Exception occurred while handling the file: " << e.what() << '\n'; }
		std::shared_ptr<VertexBuffer> square = std::make_shared<VertexBuffer>(datavec);
		m_vertexBuffers.push_back(square);
	}

	size_t numIdx = 2;

	for(size_t i = numImports; i < (numImports + numIdx); ++i)
	{
		std::vector<unsigned> datavec = {};
		try {
			std::ifstream file(paths_to_vertexdata[i], std::ios::in);
			if (!file)
				std::cerr << "Failed to open the file.\n";
			else { 
		 		unsigned number;
				while (file >> number) {
					if(number == '#') 
            			file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					else
						datavec.push_back(number);
				}
			}	
		} 
		catch (const std::ifstream::failure &e) { std::cerr << "Exception occurred while handling the file: " << e.what() << '\n'; }

		std::shared_ptr<IndexBuffer> square = std::make_shared<IndexBuffer>(datavec);
		m_indexBuffers.push_back(square);
	}

}

void Renderer_GL::SetupVertexLayouts() const
{
	
}

std::vector<std::shared_ptr<Mesh>> Renderer_GL::GetMeshes() const
{
	return m_meshes;
}

void Renderer_GL::GeneratePrimitives() const
{
	const double PI = 3.14159265358979323846;
	const int numLatitude = 20;
	const int numLongitude = 20;

	std::vector<float> vertices;

	for (int lat = 0; lat <= numLatitude; ++lat) {
	    float theta = lat * PI / numLatitude;
	    float sinTheta = std::sin(theta);
	    float cosTheta = std::cos(theta);

	    for (int lon = 0; lon <= numLongitude; ++lon) {
	        float phi = lon * 2 * PI / numLongitude;
	        float sinPhi = std::sin(phi);
	        float cosPhi = std::cos(phi);

	        float x = cosPhi * sinTheta;
	        float y = cosTheta;
	        float z = sinPhi * sinTheta;

	        // Add the vertex to the vector
	        vertices.push_back(x);
	        vertices.push_back(y);
	        vertices.push_back(z);
	    }
	}
	std::shared_ptr<VertexBuffer> sphere = std::make_shared<VertexBuffer>(vertices);
	m_vertexBuffers.push_back(sphere);

}

bool Renderer_GL::InitSuccess() const
{
	return true;
}

#endif
// =================================== RENDERER_VULKAN ===================================

Renderer_Vulk::Renderer_Vulk() :
	m_window(nullptr),
	m_isInitialized(false)
{
	Init();
	
}

Renderer_Vulk::~Renderer_Vulk()
{
	
}

void Renderer_Vulk::Init()  
{
    // We initialize SDL and create a window with it. 
	SDL_Init(SDL_INIT_VIDEO);

	SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE);
	
    //create blank SDL window for our application
	m_window = SDL_CreateWindow(
		"3D Vulkan Renderer", 
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, 
		Renderer::WindowWidth, 
		Renderer::WindowHeight, 
		window_flags 
	);
	
	//everything went fine
	m_isInitialized = true;

	Init_Vulkan();
	Init_Swapchain();

}

void Renderer_Vulk::Init_Vulkan()
{
	vkb::InstanceBuilder builder;

	auto inst_ret = builder.set_app_name("3D Vulkan Engine")
		.request_validation_layers(true)
		.require_api_version(1, 1, 0)
		.use_default_debug_messenger()
		.build();

	// init a vkinstance object from the builder, and use values from it for member variables
	vkb::Instance vkb_inst = inst_ret.value();
	m_instance = vkb_inst.instance;
	m_debugMessenger = vkb_inst.debug_messenger;

	SDL_Vulkan_CreateSurface(m_window, m_instance, &m_surface);
	vkb::PhysicalDeviceSelector selector { vkb_inst };
	vkb::PhysicalDevice physicalDevice = selector
		.set_minimum_version(1, 1)
		.set_surface(m_surface)
		.select()
		.value();

	vkb::DeviceBuilder deviceBuilder{ physicalDevice };
	vkb::Device vkbDevice = deviceBuilder.build().value();
	m_device = vkbDevice.device;
	m_physicalDevice = physicalDevice.physical_device;

	std::cout << "Choosing Physical Device: " << physicalDevice.properties.deviceName << std::endl;

}

void Renderer_Vulk::Init_Swapchain()
{
	vkb::SwapchainBuilder scBuilder{ m_physicalDevice, m_device, m_surface };

	vkb::Swapchain vkbSwapchain = scBuilder
		.use_default_format_selection()
		.set_desired_present_mode(VK_PRESENT_MODE_FIFO_KHR)
		.set_desired_extent(Renderer::WindowWidth, Renderer::WindowHeight) // If window is resized, swapchain needs rebuilding
		.build()
		.value();

	m_swapchain = vkbSwapchain.swapchain;
	m_swapchainImages = vkbSwapchain.get_images().value();
	m_swapchainImageViews = vkbSwapchain.get_image_views().value();
	m_swapchainFormat = vkbSwapchain.image_format;
}

void Renderer_Vulk::Cleanup()
{

	//order of creation -> SDL_Window, Instance, Surface, Device, Swapchain
	if (m_isInitialized)
	{
		// swapchain
		vkDestroySwapchainKHR(m_device, m_swapchain, nullptr);
		for (size_t i = 0; i < m_swapchainImageViews.size(); ++i)
		{
			vkDestroyImageView(m_device, m_swapchainImageViews[i], nullptr);
			// no need to destroy images because images are owned and destroyed in the swapchain
		}

		// device
		vkDestroyDevice(m_device, nullptr);

		// surface
		vkDestroySurfaceKHR(m_instance, m_surface, nullptr);

		// util debug
		vkb::destroy_debug_utils_messenger(m_instance, m_debugMessenger);

		// Instance 
		vkDestroyInstance(m_instance, nullptr);
		
		// SDL Window
		SDL_DestroyWindow(m_window);

	}
	std::cout << "Sucessfully deleted SDL Window\n";
}

void Renderer_Vulk::Render() const
{
}

void Renderer_Vulk::Update()
{
}

void Renderer_Vulk::Input() const
{
}

void Renderer_Vulk::OpenWindow() const
{
}

void Renderer_Vulk::ClearScreen() const
{
}

void Renderer_Vulk::SetupShaders() const
{
}

void Renderer_Vulk::SetupTextures() const
{
}

bool Renderer_Vulk::InitSuccess() const
{
	return m_isInitialized;
}

void Renderer_Vulk::SetupVertexData() const
{
}

void Renderer_Vulk::SetupVertexLayouts() const 
{
}

// =================================== RENDERER_DX3D ===================================

Renderer_DX::Renderer_DX()
{
}

Renderer_DX::~Renderer_DX()
{
}

void Renderer_DX::Init() 
{
}

void Renderer_DX::Render() const
{
}

void Renderer_DX::OpenWindow() const
{
}

void Renderer_DX::Update()
{
}

void Renderer_DX::ClearScreen() const
{
}

void Renderer_DX::SetupShaders() const
{
}

void Renderer_DX::SetupTextures() const
{
}

void Renderer_DX::SetupVertexData() const
{
}

void Renderer_DX::SetupVertexLayouts() const 
{
}

void Renderer_DX::Input() const
{
}

bool Renderer_DX::InitSuccess() const
{
	return true;
}


