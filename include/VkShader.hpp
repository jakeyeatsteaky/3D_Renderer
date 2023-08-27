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
class VkShader
{
public:
	VkShader(const char* vertPath, const char* fragPath, Renderer_Vulk*  renderer);
	~VkShader();
	

private:
	bool LoadShaderModule(const char* filePath, const VkDevice& device, VkShaderModule* outShaderModule);

};


#endif // end VkShader

