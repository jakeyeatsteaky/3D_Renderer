#include "VulkanUtil.hpp"

VkCommandPoolCreateInfo vk_util::cmd_pool_create_info(uint32_t queueFamilyIndex, VkCommandPoolCreateFlags flags /*= 0*/)
{
	VkCommandPoolCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	info.pNext = nullptr;
	
	info.queueFamilyIndex = queueFamilyIndex;
	info.flags = flags;
	return info;
}

VkCommandBufferAllocateInfo vk_util::cmd_buf_alloc_info(VkCommandPool pool, uint32_t count /*= 1*/, VkCommandBufferLevel level /*= VK_COMMAND_BUFFER_LEVEL_PRIMARY*/)
{
	VkCommandBufferAllocateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	info.pNext = nullptr;

	info.commandPool = pool;
	info.commandBufferCount = count;
	info.level = level;
	return info;
}

VkRenderPassCreateInfo vk_util::cmd_renderpass_create_info(
	VkAttachmentDescription* pColorAttachment,
	VkSubpassDescription* pSubpasses,
	uint32_t attachmentCount /*= 1*/,
	uint32_t subpassCount /*= 1*/)
{
	VkRenderPassCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	info.attachmentCount = attachmentCount;
	info.pAttachments = pColorAttachment;
	info.subpassCount = subpassCount;
	info.pSubpasses = pSubpasses;

	return info;
}

VkFramebufferCreateInfo vk_util::cmd_framebuffer_create_info(
	VkRenderPass renderPass,
	uint32_t windowWidth /*= Renderer::WindowWidth*/,
	uint32_t windowHeight /*= Renderer::WindowHeight*/,
	uint32_t attachmentCount /*= 1*/,
	uint32_t layers /*= 1*/)
{
	VkFramebufferCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
	info.pNext = nullptr;

	info.renderPass = renderPass;
	info.attachmentCount = attachmentCount;
	info.width = windowWidth;
	info.height = windowHeight;
	info.layers = layers;

	return info;
}


VkFenceCreateInfo vk_util::cmd_fence_create_info(VkFlags flags /*= VK_FENCE_CREATE_SIGNALED_BIT*/)
{
	VkFenceCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	info.pNext = nullptr;
	info.flags = flags;

	return info;
}

VkSemaphoreCreateInfo vk_util::cmd_semaphore_create_info(VkFlags flags /*= 0*/)
{
	VkSemaphoreCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
	info.pNext = nullptr;
	info.flags = flags;

	return info;
}