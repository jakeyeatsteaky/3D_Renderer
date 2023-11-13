#include "RendererAPI.hpp"
#include "Texture.hpp"
#include <fstream>
#include <cstring>

#include <SDL2/SDL.h>
#ifdef USING_VULKAN
#include <SDL_vulkan.h>
#include "VkBootstrap.h"
#include "VulkanUtil.hpp"
#include "PipelineBuilder.hpp"

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

void Renderer_GL::Input(SDL_KeyCode) const
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
	m_isInitialized(false),
	m_updateShader(false),
	m_activePipeline(0)
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
	
	Init_Vulkan();
	Init_Swapchain();
	Init_Commands();
	Init_Default_RenderPass();
	Init_Framebuffers();
	Init_Sync();
	Init_Shaders();
	Init_Pipelines();

	//everything went fine
	m_isInitialized = true;

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

	// Queue
	m_graphicsQueueFamilyIdx = vkbDevice.get_queue_index(vkb::QueueType::graphics).value();
	m_graphicsQueue = vkbDevice.get_queue(vkb::QueueType::graphics).value();

	std::cout << "Number of Queue families: " << vkbDevice.queue_families.size() << std::endl;
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

void Renderer_Vulk::Init_Commands()
{
	VkCommandPoolCreateInfo commandPoolInfo = vk_util::cmd_pool_create_info(
		m_graphicsQueueFamilyIdx, 
		VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT);

	VK_CHECK(vkCreateCommandPool(m_device, &commandPoolInfo, nullptr, &m_commandPool), "Create Command Pool", true);

	VkCommandBufferAllocateInfo cmdBufAllocInfo = vk_util::cmd_buf_alloc_info(m_commandPool);

	VK_CHECK(vkAllocateCommandBuffers(m_device, &cmdBufAllocInfo, &m_commandBuffer), "Allocate Command Buffer", true);

}

void Renderer_Vulk::Init_Default_RenderPass()
{
	VkAttachmentDescription colorAttachment = {};
	colorAttachment.format = m_swapchainFormat;
	colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
	colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR; // after render pass, image has to be in a layout ready for display

	// Above was defining the main image target.  Now add a subpass that will render into it
	VkAttachmentReference colorRef = {  };
	colorRef.attachment = 0;
	colorRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

	VkSubpassDescription subpass = {};
	subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
	subpass.colorAttachmentCount = 1;
	subpass.pColorAttachments = &colorRef;

	VkRenderPassCreateInfo renderPassInfo = vk_util::cmd_renderpass_create_info(&colorAttachment, &subpass);

	VK_CHECK(vkCreateRenderPass(m_device, &renderPassInfo, nullptr, &m_renderPass), "Create Render Pass", true);
}

void Renderer_Vulk::Init_Framebuffers()
{
	std::vector<std::string> text = {
		"Create Frame Buffer #1",
		"Create Frame Buffer #2",
		"Create Frame Buffer #3"
	};

	VkFramebufferCreateInfo fb_info = vk_util::cmd_framebuffer_create_info(m_renderPass);

	// grab number of images in the swapchain
	const size_t swapchainImageCount = m_swapchainImages.size();
	m_frameBuffers = std::vector<VkFramebuffer>(swapchainImageCount);

	// create framebuffers for each swapchain image view
	for (int i = 0; i < swapchainImageCount; ++i)
	{
		fb_info.pAttachments = &m_swapchainImageViews[i];
		VK_CHECK(vkCreateFramebuffer(m_device, &fb_info, nullptr, &m_frameBuffers[i]), text[i], true);
	}
}

void Renderer_Vulk::Init_Sync()
{
	VkFenceCreateInfo fenceCreateInfo = vk_util::cmd_fence_create_info();
	VkSemaphoreCreateInfo semaphoreCreateInfo_render = vk_util::cmd_semaphore_create_info();
	VkSemaphoreCreateInfo semaphoreCreateInfo_present = vk_util::cmd_semaphore_create_info();

	VK_CHECK(vkCreateFence(m_device, &fenceCreateInfo, nullptr, &m_renderFence), "Create Fence", true);
	VK_CHECK(vkCreateSemaphore(m_device, &semaphoreCreateInfo_present, nullptr, &m_presentSemaphore), "Create Present Semaphore", true);
	VK_CHECK(vkCreateSemaphore(m_device, &semaphoreCreateInfo_render, nullptr, &m_renderSemaphore), "Create Render Semaphore", true);


}

void Renderer_Vulk::Init_Shaders()
{
	m_vulkShaderPair = std::make_shared<VulkShader>(
		Renderer::VULKAN_VERT_SHADER_0, 
		Renderer::VULKAN_FRAG_SHADER_0, 
		this);

	m_shaders.push_back(m_vulkShaderPair);

	m_vulkShaderPair = std::make_shared<VulkShader>(
		Renderer::VULKAN_VERT_SHADER_1,
		Renderer::VULKAN_FRAG_SHADER_1,
		this);

	m_shaders.push_back(m_vulkShaderPair);

	m_vulkShaderPair = std::make_shared<VulkShader>(
		Renderer::VULKAN_VERT_SHADER_2,
		Renderer::VULKAN_FRAG_SHADER_2,
		this);

	m_shaders.push_back(m_vulkShaderPair);

}

void Renderer_Vulk::Init_Pipelines()
{
	////////////////////////////////////////////////////////////////////////
	////////////////// How Pipelines Work Right Now ////////////////////////
	////////////////////////////////////////////////////////////////////////
	// I am doing this so I can use the space bar to toggle the shader on an object.
	// 
	// A shader module requires a pipeline (which requires a pipeline layout)
	// 
	// Here, the pipeline layout is configured and the pipeline is built
	// Both are added to the m_pipelines vector.
	// 
	// m_pipelines is used in the DRAW function under vkCmdBindPipeline
	////////////////////////////////////////////////////////////////////////

	int numShaders = (int)m_shaders.size();
	for(int i = 0; i < numShaders; i++)
	{
		// Build the pipeline Layout that controls inputs and outputs of the shader;
		VkPipelineLayoutCreateInfo pipelineLayoutInfo = vk_util::pipeline_layout_create_info();
		VkPipelineLayout pipelineLayout;
		VK_CHECK(vkCreatePipelineLayout(m_device, &pipelineLayoutInfo, nullptr, &pipelineLayout),
			"Create Pipeline Layout",
			LOG_STATUS);

		// With Pipline Layout specified, build the pipeline;
		PipelineBuilder pipelineBuilder;
		pipelineBuilder.m_shaderStages.push_back(
			vk_util::pipeline_shader_stage_create_info(
				VK_SHADER_STAGE_VERTEX_BIT,
				m_shaders[i]->m_vertShader));

		pipelineBuilder.m_shaderStages.push_back(
			vk_util::pipeline_shader_stage_create_info(
				VK_SHADER_STAGE_FRAGMENT_BIT,
				m_shaders[i]->m_fragShader));

		// Vertex input controls how to read vertices from vertex buffers
		// NOT BEING USED YET
		pipelineBuilder.m_vertexInputInfo = vk_util::vertex_input_state_create_info();

		//input assembly is the configuration for drawing triangle lists, strips, or individual points.
		//we are just going to draw triangle list
		pipelineBuilder.m_inputAssembly = vk_util::input_assembly_create_info   (VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST);

		//build viewport and scissor from the swapchain extents
		pipelineBuilder.m_viewport.x = 0.0f;
		pipelineBuilder.m_viewport.y = 0.0f;
		pipelineBuilder.m_viewport.width = (float)m_windowExtent.width;
		pipelineBuilder.m_viewport.height = (float)m_windowExtent.height;
		pipelineBuilder.m_viewport.minDepth = 0.0f;
		pipelineBuilder.m_viewport.maxDepth = 1.0f;

		pipelineBuilder.m_scissor.offset = { 0, 0 };
		pipelineBuilder.m_scissor.extent = m_windowExtent;

		//configure the rasterizer to draw filled triangles
		pipelineBuilder.m_rasterizer = vk_util::rasterization_state_create_info(VK_POLYGON_MODE_FILL);

		//we don't use multisampling, so just run the default one
		pipelineBuilder.m_multisampling = vk_util::multisampling_state_create_info();

		//a single blend attachment with no blending and writing to RGBA
		pipelineBuilder.m_colorBlendAttachment = vk_util::color_blend_attachment_state();

		//use the triangle layout we created
		pipelineBuilder.m_pipelineLayout = pipelineLayout;

		//finally build the pipeline
		VkPipeline pipeline;
		pipeline = pipelineBuilder.BuildPipeline(m_device, m_renderPass);

		m_pipelines.push_back(std::pair<VkPipelineLayout, VkPipeline>(pipelineLayout, pipeline));
		pipelineBuilder.m_shaderStages.clear();
	}
}

void Renderer_Vulk::Draw() const
{
	VkCommandBuffer cmd = m_commandBuffer;
	// wait until GPU has finished work
	VK_CHECK(vkWaitForFences(m_device, 1, &m_renderFence, true, 1000000000), "Wait for Fences", DO_NOT_LOG_STATUS);
	VK_CHECK(vkResetFences(m_device, 1, &m_renderFence), "Reset Fences", DO_NOT_LOG_STATUS);

	// Request an image from the swapchain and use a presentSemaphore which signals once the image is available for rendering
	uint32_t swapchainImageidx;
	VK_CHECK(vkAcquireNextImageKHR(m_device, m_swapchain, 1000000000, m_presentSemaphore, nullptr, &swapchainImageidx), "Acquire SC Idx", DO_NOT_LOG_STATUS);
	
	// Reset the command buffer and begin commands
	VK_CHECK(vkResetCommandBuffer(cmd, 0), "Reset Command Buffer", DO_NOT_LOG_STATUS);

	VkCommandBufferBeginInfo cmdBufBeginInfo = vk_util::cmd_buf_begin_info(nullptr, VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT);

	VK_CHECK(vkBeginCommandBuffer(cmd, &cmdBufBeginInfo), "Begin Command Buffer", DO_NOT_LOG_STATUS);

	// Create a fancy clear color
	VkClearValue val;
	float flash = abs(sin(m_frameNumber / 120.f));
	val.color = { {0.f, 0.f, flash, 1.f } }; 

	// Start main renderpass
	VkExtent2D extent = { Renderer::WindowWidth, Renderer::WindowHeight };
	VkRenderPassBeginInfo renderPassBeginInfo = vk_util::cmd_renderpass_begin_info(m_renderPass, extent, m_frameBuffers[swapchainImageidx], &val);

	vkCmdBeginRenderPass(cmd, &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);

	// RENDERING COMMANDS GO HERE
	vkCmdBindPipeline(cmd, VK_PIPELINE_BIND_POINT_GRAPHICS, m_pipelines[m_activePipeline].second);
	vkCmdDraw(cmd, 3, 1, 0, 0);

	vkCmdEndRenderPass(cmd);

	VK_CHECK(vkEndCommandBuffer(cmd), "End Command Buffer", DO_NOT_LOG_STATUS);

	// Execute commands by submitting them to the GPU
	// we are waiting on the PresentSemaphore (so we know the swapchain is ready)
	// we will signal the RenderSemaphore so signal that the rendering has finished

	VkSubmitInfo submitInfo = vk_util::cmd_submit_info(
		VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
		1,
		&const_cast<VkSemaphore>(m_presentSemaphore),
		1,
		&const_cast<VkSemaphore>(m_renderSemaphore),
		1,
		&const_cast<VkCommandBuffer>(cmd));

	VK_CHECK(vkQueueSubmit(m_graphicsQueue, 1, &submitInfo, m_renderFence), "Queue Submission", DO_NOT_LOG_STATUS);

	VkPresentInfoKHR presentInfo = vk_util::cmd_present_info(
		&const_cast<VkSwapchainKHR>(m_swapchain),
		1,
		&const_cast<VkSemaphore>(m_renderSemaphore),
		1,
		&swapchainImageidx);

	VK_CHECK(vkQueuePresentKHR(m_graphicsQueue, &presentInfo), "Queue Presentation", DO_NOT_LOG_STATUS);

	m_frameNumber++;

}

void Renderer_Vulk::Cleanup()
{

	//order of creation -> SDL_Window, Instance, Surface, Device, Swapchain, Render Pass, Command Pool, Fence, Semaphore, CommandBuffer
	if (m_isInitialized)
	{
		// Wait for commands to be in a destroyable state
		vkDeviceWaitIdle(m_device);

		//Semaphore
		vkDestroySemaphore(m_device, m_presentSemaphore, nullptr);
		vkDestroySemaphore(m_device, m_renderSemaphore, nullptr);

		// Fence
		vkDestroyFence(m_device, m_renderFence, nullptr);

		// command pool
		vkDestroyCommandPool(m_device, m_commandPool, nullptr);

		// swapchain
		vkDestroySwapchainKHR(m_device, m_swapchain, nullptr);

		// render pass 
		vkDestroyRenderPass(m_device, m_renderPass, nullptr);

		// image views and framebuffers should be done together
		for (size_t i = 0; i < m_swapchainImageViews.size(); ++i)
		{
			vkDestroyImageView(m_device, m_swapchainImageViews[i], nullptr);
			// no need to destroy images because images are owned and destroyed in the swapchain
			vkDestroyFramebuffer(m_device, m_frameBuffers[i], nullptr);
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
	Draw();
}

void Renderer_Vulk::Update()
{
	
	if (m_updateShader) {
		m_updateShader = false;
		ToggleShaderPipeline();
		
	}
}

void Renderer_Vulk::Input(SDL_KeyCode sdlKey) const
{
	switch (sdlKey)
	{
		case SDLK_SPACE:
		{
			m_updateShader = true;
			break;
		}
		default:
			break;
	}
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

VkDevice Renderer_Vulk::GetDevice() const
{
	return m_device;
}

void Renderer_Vulk::ToggleShaderPipeline()
{
	size_t numPipelines = m_pipelines.size(); 

	std::cout << "Current Pipeline Idx: " << m_activePipeline << std::endl;

	if (m_activePipeline < numPipelines - 1)
		m_activePipeline += 1;
	else
		m_activePipeline = 0;

	std::cout << "Changed to Pipeline Idx: " << m_activePipeline << std::endl;
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

void Renderer_DX::Input(SDL_KeyCode) const
{
}

bool Renderer_DX::InitSuccess() const
{
	return true;
}


