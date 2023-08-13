#ifndef VULKAN_UTIL_HPP
#define VULKAN_UTIL_HPP

#include <vulkan/vulkan.h>

#define VK_CHECK(x, y)													\
	do																	\
	{																	\
		VkResult err = x;												\
		if (err)														\
		{																\
			std::cout <<"Detected Vulkan error: " << err << std::endl;	\
			abort();													\
		}																\
		else {															\
			std::cout << "\tSUCCESS: " << y << std::endl;}				\
	} while (0)


namespace vk_util
{
	VkCommandPoolCreateInfo cmd_pool_create_info(uint32_t queueFamilyIdx, VkCommandPoolCreateFlags flags = 0);

	VkCommandBufferAllocateInfo cmd_buf_alloc_info(VkCommandPool cmdPool, 
												   uint32_t count = 1, 
												   VkCommandBufferLevel level = VK_COMMAND_BUFFER_LEVEL_PRIMARY);
}


#endif