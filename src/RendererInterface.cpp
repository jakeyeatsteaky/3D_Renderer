#include "RendererInterface.h"
#include "RendererAPI.h"

RendererInterface::~RendererInterface() {
	for (auto& meshes : m_meshMap) {
		delete meshes.second;
		std::cout << "Deleted " << meshes.first << " from the Mesh Map\n";
	}
}

std::unique_ptr<RendererInterface> RendererInterface::MakeRenderer(RENDERER_API api)
{
    std::string renderer;
    std::unique_ptr<RendererInterface> ret = nullptr;
    switch (api)
    {
    case Renderer_Api_None:
    {
        std::cout << "No Renderer API Selected\n";
        break;
    }
    case Renderer_API_Open_GL:
    {
        ret = std::make_unique<Renderer_GL>();
        renderer = "Open GL";
        break;
    }
    case Renderer_API_Vulkan:
    {
        ret = std::make_unique<Renderer_Vulk>();
        renderer = "Vulkan";
        break;
    }

    case Renderer_API_DX3D:
    {
        ret = std::make_unique<Renderer_DX>();
        renderer = "Direct X 3D";
        break;
    }

    }

    std::cout << "Created Renderer: " << renderer << std::endl;
    return ret;
}


