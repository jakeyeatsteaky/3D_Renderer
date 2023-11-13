#include "VulkShader.hpp"
#include "VulkanUtil.hpp"
#include <fstream>

VulkShader::VulkShader(const char* vertPath, const char* fragPath, Renderer_Vulk* renderer) :
	m_shaderModulesDestroyed(false)
{
	if (!LoadShaderModule(vertPath, renderer->GetDevice(), &m_vertShader))
		std::cout << "ERROR when Building VKShader Vertex" << std::endl;
	else
		std::cout << "\tSUCCESS: Built VKShader Vertex" << std::endl;

	if (!LoadShaderModule(fragPath, renderer->GetDevice(), &m_fragShader))
		std::cout << "ERROR when Building VkShader Fragment" << std::endl;
	else
		std::cout << "\tSUCCESS: Built VKShader Fragment" << std::endl;
}

VulkShader::~VulkShader()
{

}


bool VulkShader::LoadShaderModule(const char* filePath, const VkDevice& device, VkShaderModule* outShaderModule)
{
	// std::ios::ate --> open the file with the cursor "at the end"
	//		The cursor being at the end of the file lets us know how big the file is
	// std::ios::binary --> open in binary mode

	std::ifstream file(filePath, std::ios::ate | std::ios::binary);

	if (!file.is_open())
	{
		std::cout << "Failed to open file: " << filePath << std::endl;
		return false;
	}

	// find the size of the file from the stream
	size_t fileSize = static_cast<size_t>(file.tellg());

	// spirv expects uint32, create a vector big enough to hold the whole file
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
	VK_CHECK(vkCreateShaderModule(device, &createInfo, nullptr, &shaderModule), 
			 "Create Shader Module", 
			  DO_NOT_LOG_STATUS);
	*outShaderModule = shaderModule;

	return true;
}

bool VulkShader::ShaderModulesDestroyed()
{
	return m_shaderModulesDestroyed;
}

void VulkShader::UpdateShaderModuleDestroyed()
{
	m_shaderModulesDestroyed = true;
}