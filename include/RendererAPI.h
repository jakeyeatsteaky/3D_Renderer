#ifndef RENDERER_API_H
#define RENDERER_API_H

#include "RendererInterface.h"

#define GLEW_STATIC
#include "GL/glew.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "enumerations.h"
#include "Shaders.h"
#include "Texture.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexLayout.h"
#include "Mesh.h"

namespace Renderer
{
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
}


class Renderer_GL : public RendererInterface {
public:

	Renderer_GL();
	virtual ~Renderer_GL();
	
	// RenderInterface virtual functions
	virtual void Init() const override;
	virtual void Input() const override;
	virtual void Render() const override;
	virtual void Update() override;
	virtual void OpenWindow() const override;
	virtual void ClearScreen() const override;
	virtual void SetupShaders() const override;
	virtual void SetupTextures() const override;
	virtual bool InitSuccess() const override;
	virtual void SetupVertexData() const override;
	virtual void SetupVertexLayouts() const override;
	void GeneratePrimitives() const;
	std::vector<std::shared_ptr<Mesh>> GetMeshes() const;

private:

	mutable SDL_Window* m_window;
	mutable SDL_Renderer* m_renderer;
	mutable SDL_GLContext m_context;
	mutable std::vector<std::shared_ptr<VertexBuffer>> m_vertexBuffers;
	mutable std::vector<std::shared_ptr<IndexBuffer>> m_indexBuffers;
	mutable std::vector<std::shared_ptr<Mesh>> m_meshes;
	mutable std::vector<std::shared_ptr<Shader>>m_shaders;
	mutable std::vector<std::shared_ptr<Texture>> m_textures;
	mutable std::vector<std::shared_ptr<VertexLayout>> m_vertexLayouts;

};


class Renderer_Vulk : public RendererInterface {
public:
	Renderer_Vulk();
	virtual ~Renderer_Vulk();
	virtual void Init() const override;
	virtual void Input() const override;
	virtual void Render() const override;
	virtual void Update() override;
	virtual void OpenWindow() const override;
	virtual void ClearScreen() const override;
	virtual void SetupShaders() const override;
	virtual void SetupTextures() const override;
	virtual bool InitSuccess() const override;
	virtual void SetupVertexData() const override;
	virtual void SetupVertexLayouts() const override;

private:
	mutable SDL_Window* m_window;
	mutable bool m_isInitialized;

};

class Renderer_DX : public RendererInterface {
public:
	Renderer_DX();
	virtual ~Renderer_DX();
	virtual void Init() const override;
	virtual void Input() const override;
	virtual void Render() const override;
	virtual void Update() override;
	virtual void OpenWindow() const override;
	virtual void ClearScreen() const override;
	virtual void SetupShaders() const override;
	virtual void SetupTextures() const override;
	virtual void SetupVertexData() const override;
	virtual void SetupVertexLayouts() const override;
	virtual bool InitSuccess() const override;
};


#endif