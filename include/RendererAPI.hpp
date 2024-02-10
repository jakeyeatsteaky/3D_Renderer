#ifndef RENDERER_API_HPP
#define RENDERER_API_HPP

//#define USING_GL
//#define USING_VULKAN
#include "RendererInterface.hpp"
#include "DeletionQueue.hpp"

#define GLEW_STATIC
#include "GL/glew.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <vulkan/vulkan.h>

#include <memory>
#include "enumerations.h"
#include "Shaders.hpp"
#include "Texture.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "VertexLayout.hpp"
#include "Mesh.hpp"
#include "VulkShader.hpp"


namespace Renderer
{
	// the constexpr prevents a multiple definition error since these are defined in the header file.

	constexpr const char* WINDOW_TITLE = "Sovereign Engine";
	constexpr int WindowWidth = 800;
	constexpr int WindowHeight = 600;
	constexpr uint32_t CLEAR_COLOR = 0xff00ffff;
	constexpr const char* VERTEX_PATH_0 = "../shaders/shader0.vert";
	constexpr const char* FRAGMENT_PATH_0 = "../shaders/shader0.frag";
	constexpr const char* VERTEX_PATH_1 = "../shaders/shader1.vert";
	constexpr const char* FRAGMENT_PATH_1 = "../shaders/shader1.frag";
	constexpr const char* VERTEX_PATH_2 = "../shaders/shader2.vert";
	constexpr const char* FRAGMENT_PATH_2 = "../shaders/shader2.frag";
	constexpr const char* TEXTURE_PATH = "../assets/textures/wall.jpg";
	constexpr const char* TEXTURE_PATH2 = "../assets/textures/awesomeface.png";
	constexpr const char* VERTEX_DATA_PATH = "../assets/vertex_data/";
	constexpr const char* INDEX_DATA_PATH = "../assets/index_data/";

	constexpr const char* VULKAN_VERT_SHADER_0 = "../shaders/binaries/vert.spv";
	constexpr const char* VULKAN_FRAG_SHADER_0 = "../shaders/binaries/frag.spv";

	constexpr const char* VULKAN_VERT_SHADER_1 = "../shaders/binaries/vert2.spv";
	constexpr const char* VULKAN_FRAG_SHADER_1 = "../shaders/binaries/frag2.spv";

	constexpr const char* VULKAN_VERT_SHADER_2 = "../shaders/binaries/vert3.spv";
	constexpr const char* VULKAN_FRAG_SHADER_2 = "../shaders/binaries/frag3.spv";
}

class Renderer_SDL : public RendererInterface
{
public:
	Renderer_SDL();
	~Renderer_SDL();

	virtual void Init()  override;
	virtual void Input(SDL_KeyCode) const override;
	virtual void Render() const override;
	virtual void Update() override;
	virtual void OpenWindow() const override {}
	virtual void ClearScreen() const override {}
	virtual void SetupShaders() const override {}
	virtual void SetupTextures() const override {}
	virtual bool InitSuccess() const override;
	virtual void SetupVertexData() const override {}
	virtual void SetupVertexLayouts() const override {}
	void GeneratePrimitives() const {}
	virtual void Cleanup() override {}

private:
	std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> m_window;
	std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> m_renderer;

	bool m_initSuccess;
};

class Renderer_GL : public RendererInterface {
public:

	Renderer_GL() {}
	virtual ~Renderer_GL() {}
	
	// RenderInterface virtual functions
	virtual void Init()  override {}
	virtual void Input(SDL_KeyCode) const override{}
	virtual void Render() const override{}
	virtual void Update() override{}
	virtual void OpenWindow() const override{}
	virtual void ClearScreen() const override{}
	virtual void SetupShaders() const override{}
	virtual void SetupTextures() const override{}
	virtual bool InitSuccess() const override { return false; }
	virtual void SetupVertexData() const override{}
	virtual void SetupVertexLayouts() const override{}
	void GeneratePrimitives() const {}
	virtual void Cleanup() override {}


	std::vector<std::shared_ptr<Mesh>> GetMeshes() const;

private:
#ifdef USING_GL
	mutable struct SDL_Window* m_window;
	mutable struct SDL_Renderer* m_renderer;
	mutable struct SDL_GLContext m_context;
	mutable std::vector<std::shared_ptr<VertexBuffer>> m_vertexBuffers;
	mutable std::vector<std::shared_ptr<IndexBuffer>> m_indexBuffers;
	mutable std::vector<std::shared_ptr<Mesh>> m_meshes;
	mutable std::vector<std::shared_ptr<Shader>>m_shaders;
	mutable std::vector<std::shared_ptr<Texture>> m_textures;
	mutable std::vector<std::shared_ptr<VertexLayout>> m_vertexLayouts;
#endif

};

class VulkShader;
class Renderer_Vulk : public RendererInterface {
public:
	Renderer_Vulk();
	virtual ~Renderer_Vulk();
	virtual void Init()  override; // intializes SDL windowing
	virtual void Input(SDL_KeyCode sdlKey) const override;
	virtual void Render() const override;
	virtual void Update() override;
	virtual void OpenWindow() const override;
	virtual void ClearScreen() const override;
	virtual void SetupShaders() const override;
	virtual void SetupTextures() const override;
	virtual bool InitSuccess() const override;
	virtual void SetupVertexData() const override;
	virtual void SetupVertexLayouts() const override;  
	virtual void Cleanup() override;
	void Init_Vulkan();
	void Init_Swapchain();
	void Init_Commands();
	void Init_Default_RenderPass();
	void Init_Framebuffers();
	void Init_Sync();
	void Init_Shaders();
	void Init_Pipelines();
	void Draw() const;

	void ToggleShaderPipeline();

	VkDevice GetDevice() const;

private:

	mutable struct SDL_Window* m_window;
	mutable bool m_isInitialized;
	mutable bool m_updateShader; 
	mutable int m_frameNumber;
	VkExtent2D m_windowExtent{ 800, 600 };

	// Core Init
	VkInstance m_instance;
	VkDebugUtilsMessengerEXT m_debugMessenger;
	VkPhysicalDevice m_physicalDevice;
	VkDevice m_device;
	VkSurfaceKHR m_surface;

	//SwapChain
	VkSwapchainKHR m_swapchain;
	VkFormat m_swapchainFormat; 
	std::vector<VkImage> m_swapchainImages;
	std::vector<VkImageView> m_swapchainImageViews;

	// Commands
	VkCommandPool m_commandPool;
	VkCommandBuffer m_commandBuffer;
	VkQueue m_graphicsQueue;
	uint32_t m_graphicsQueueFamilyIdx;

	// Render Pass
	VkRenderPass m_renderPass;
	std::vector<VkFramebuffer> m_frameBuffers;

	// Sync
	VkSemaphore m_presentSemaphore;
	VkSemaphore m_renderSemaphore;
	VkFence m_renderFence;

	// Graphics Pipeline
	std::vector<std::shared_ptr<VulkShader>> m_shaders;					
	std::shared_ptr<VulkShader> m_vulkShaderPair;
	int m_activePipeline;
	std::vector<std::pair<VkPipelineLayout, VkPipeline>> m_pipelines;

	// Cleanup
	std::shared_ptr<DeletionQueue> m_mainDeletionQueue;
};

class Renderer_DX : public RendererInterface {
public:
	Renderer_DX();
	virtual ~Renderer_DX();
	virtual void Init() override;
	virtual void Input(SDL_KeyCode) const override;
	virtual void Render() const override;
	virtual void Update() override;
	virtual void OpenWindow() const override;
	virtual void ClearScreen() const override;
	virtual void SetupShaders() const override;
	virtual void SetupTextures() const override;
	virtual void SetupVertexData() const override;
	virtual void SetupVertexLayouts() const override;
	virtual bool InitSuccess() const override;
	virtual void Cleanup() override {}
};


#endif