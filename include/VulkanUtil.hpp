#ifndef VULKAN_UTIL_HPP
#define VULKAN_UTIL_HPP
#include "RendererAPI.hpp"
#include <vulkan/vulkan.h>

#define VK_CHECK(x, y, z)													\
	do																		\
	{																		\
		VkResult err = x;													\
		if (err)															\
		{																	\
			std::cout <<"Detected Vulkan error: " << err << std::endl;		\
			abort();														\
		}																	\
		else {																\
			if(z)															\
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

	VkFenceCreateInfo cmd_fence_create_info(VkFlags flags = VK_FENCE_CREATE_SIGNALED_BIT);

	VkSemaphoreCreateInfo cmd_semaphore_create_info(VkFlags flags = 0);

	VkCommandBufferBeginInfo cmd_buf_begin_info(VkCommandBufferInheritanceInfo* inheritanceInfo, VkFlags flags);

	VkRenderPassBeginInfo cmd_renderpass_begin_info(
		VkRenderPass renderPass,
		VkExtent2D extent,
		VkFramebuffer framebuffer,
		VkClearValue* pClearValue,
		uint32_t offsetX = 0,
		uint32_t offsetY = 0);

	VkSubmitInfo cmd_submit_info(
		VkPipelineStageFlags waitStage,
		uint32_t waitSemaphoreCount,
		VkSemaphore* waitSemaphore,
		uint32_t signalSemaphoreCount,
		VkSemaphore* signalSemaphore,
		uint32_t commandBufferCount,
		VkCommandBuffer* pCmdBuf);

	VkPresentInfoKHR cmd_present_info(
		VkSwapchainKHR* swapchain,
		uint32_t swapchainCount,
		VkSemaphore* waitSemaphore,
		uint32_t semaphoreCount,
		uint32_t* swapchainImageIdx);
}





#endif