#ifndef VULKAN_UTIL_HPP
#define VULKAN_UTIL_HPP

#include <vulkan/vulkan.h>
#include "RendererAPI.h"

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
	VkRenderPassCreateInfo cmd_renderpass_create_info(VkAttachmentDescription* pColorAttachment, 
													  VkSubpassDescription* pSubpasses,
													  uint32_t attachmentCount = 1,
												      uint32_t subpassCount = 1);

	VkFramebufferCreateInfo cmd_framebuffer_create_info(VkRenderPass renderPass, 
														uint32_t windowWidth = Renderer::WindowWidth,
														uint32_t windowHeight = Renderer::WindowHeight,
														uint32_t attachmentCount = 1,
														uint32_t layers = 1);
}


#endif