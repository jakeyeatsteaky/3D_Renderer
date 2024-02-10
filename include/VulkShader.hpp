#ifndef VKSHADER_HPP
#define VKSHADER_HPP
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <glm/glm.hpp>
#include <SDL_vulkan.h>
#include "VkBootstrap.h"
#include "RendererAPI.hpp"


class Renderer_Vulk;
class VulkShader
{
public:
	VulkShader(const char* vertPath, const char* fragPath, Renderer_Vulk*  renderer);

	~VulkShader();

	VkShaderModule m_vertShader;
	VkShaderModule m_fragShader; 

	bool ShaderModulesDestroyed();
	void UpdateShaderModuleDestroyed();
	

private:
	bool m_shaderModulesDestroyed;
	bool LoadShaderModule(const char* filePath, const VkDevice& device, VkShaderModule* outShaderModule);


};


#endif // end VulkShader

