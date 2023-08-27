#include "VkShader.hpp"
#include "VulkanUtil.hpp"
#include <fstream>

VkShader::VkShader(const char* vertPath, const char* fragPath, Renderer_Vulk* renderer)
{
	VkShaderModule outShaderModule;
	LoadShaderModule(vertPath, renderer->GetDevice(), &outShaderModule);
	LoadShaderModule(fragPath, renderer->GetDevice(), &outShaderModule);
}

VkShader::~VkShader()
{

}


bool VkShader::LoadShaderModule(const char* filePath, const VkDevice& device, VkShaderModule* outShaderModule)
{
	std::ifstream file(filePath, std::ios::ate | std::ios::binary);

	if (!file.is_open())
	{
		std::cout << "Failed to open file: " << filePath << std::endl;
		return false;
	}

	// find the size of the file from the stream
	size_t fileSize = static_cast<size_t>(file.tellg());

	// spirv expects uint32
	std::vector<uint32_t> buffer(fileSize / sizeof(uint32_t));

	// put the file cursor at the beginning
	file.seekg(0);

	// load the entire file into the buffer
	file.read((char*)buffer.data(), fileSize);

	// loaded data into the file, now it can be closed
	file.close();

	// load the buffer of spirv data into a vulkan module
	VkShaderModuleCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	createInfo.pNext = nullptr;

	createInfo.codeSize = fileSize; // codeSize is in bytes so use the size take from the file
	createInfo.pCode = buffer.data();

	VkShaderModule shaderModule;
	VK_CHECK(vkCreateShaderModule(device, &createInfo, nullptr, &shaderModule), "Create Shader Module", true);
	*outShaderModule = shaderModule;

	return true;
}