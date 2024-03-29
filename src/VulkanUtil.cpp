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

VkCommandBufferBeginInfo vk_util::cmd_buf_begin_info(
	VkCommandBufferInheritanceInfo* inheritanceInfo,
	VkFlags flags)
{
	VkCommandBufferBeginInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	info.pNext = nullptr;
	info.pInheritanceInfo = inheritanceInfo;
	info.flags = flags;

	return info;
}

VkRenderPassBeginInfo vk_util::cmd_renderpass_begin_info(
	VkRenderPass renderPass,
	VkExtent2D extent,
	VkFramebuffer framebuffer,
	VkClearValue* pClearValue,
	uint32_t offsetX /*= 0*/,
	uint32_t offsetY /*= 0*/)
{
	VkRenderPassBeginInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	info.pNext = nullptr;
	info.renderPass = renderPass;
	info.renderArea.offset.x = offsetX;
	info.renderArea.offset.y = offsetY;
	info.renderArea.extent = extent;
	info.framebuffer = framebuffer;

	info.clearValueCount = 1;
	info.pClearValues = pClearValue;

	return info;
}

VkSubmitInfo vk_util::cmd_submit_info(
	VkPipelineStageFlags waitStage,
	uint32_t waitSemaphoreCount,
	VkSemaphore* waitSemaphore,
	uint32_t signalSemaphoreCount,
	VkSemaphore* signalSemaphore,
	uint32_t commandBufferCount,
	VkCommandBuffer* pCmdBuf)
{
	VkSubmitInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	info.pNext = nullptr;
	info.pWaitDstStageMask = &waitStage;
	info.waitSemaphoreCount = waitSemaphoreCount;
	info.pWaitSemaphores = waitSemaphore;
	info.signalSemaphoreCount = signalSemaphoreCount;
	info.pSignalSemaphores = signalSemaphore;
	info.commandBufferCount = commandBufferCount;
	info.pCommandBuffers = pCmdBuf;

	return info;
}

VkPresentInfoKHR vk_util::cmd_present_info(
	VkSwapchainKHR* swapchain,
	uint32_t swapchainCount,
	VkSemaphore* waitSemaphore,
	uint32_t semaphoreCount,
	uint32_t* swapchainImageIdx)
{
	VkPresentInfoKHR info = {};
	info.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
	info.pNext = nullptr;

	info.pSwapchains = swapchain;
	info.swapchainCount = swapchainCount;
	info.pWaitSemaphores = waitSemaphore;
	info.waitSemaphoreCount = semaphoreCount;
	info.pImageIndices = swapchainImageIdx;

	return info;
}

////////////////////////////////////////////////////////////////////
/////////////// Vulkan Pipeline Builder Create Info ////////////////
////////////////////////////////////////////////////////////////////

VkPipelineShaderStageCreateInfo vk_util::pipeline_shader_stage_create_info(
	VkShaderStageFlagBits stage,
	VkShaderModule shaderModule)
{
	VkPipelineShaderStageCreateInfo info{};
	info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	info.pNext = nullptr;

	// shader stage
	info.stage = stage;
	// VkShaderModule which contains the code for this shader stage
	info.module = shaderModule;
	// entry point of the shader
	info.pName = "main";
	return info;
}

VkPipelineVertexInputStateCreateInfo vk_util::vertex_input_state_create_info()
{
	VkPipelineVertexInputStateCreateInfo inputStateCreateInfo{};

	inputStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	inputStateCreateInfo.pNext = nullptr;

	// currently not using vertex bindings or attributes
	inputStateCreateInfo.vertexBindingDescriptionCount = 0;
	inputStateCreateInfo.vertexAttributeDescriptionCount = 0;
	return inputStateCreateInfo;
}

VkPipelineInputAssemblyStateCreateInfo vk_util::input_assembly_create_info(VkPrimitiveTopology topology)
{
	VkPipelineInputAssemblyStateCreateInfo info{};
	info.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	info.pNext = nullptr;

	info.topology = topology;
	// no primitive restart used right now
	info.primitiveRestartEnable = VK_FALSE;
	return info;
}

VkPipelineRasterizationStateCreateInfo vk_util::rasterization_state_create_info(VkPolygonMode polygonMode)
{
	VkPipelineRasterizationStateCreateInfo info{};
	info.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	info.pNext = nullptr;
	info.depthClampEnable = VK_FALSE;
	
	// discards all primitives before rasterization if enabled
	info.rasterizerDiscardEnable = VK_FALSE;

	info.polygonMode = polygonMode;
	info.lineWidth = 1.0f;
	info.cullMode = VK_CULL_MODE_NONE;
	info.frontFace = VK_FRONT_FACE_CLOCKWISE;
	info.depthBiasEnable = VK_FALSE;
	info.depthBiasConstantFactor = 0.0f;
	info.depthBiasClamp = 0.0f;
	info.depthBiasSlopeFactor = 0.0f;

	return info;
}

VkPipelineMultisampleStateCreateInfo vk_util::multisampling_state_create_info()
{
	VkPipelineMultisampleStateCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	info.pNext = nullptr;

	info.sampleShadingEnable = VK_FALSE;
	//multisampling defaulted to no multisampling (1 sample per pixel)
	info.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
	info.minSampleShading = 1.0f;
	info.pSampleMask = nullptr;
	info.alphaToCoverageEnable = VK_FALSE;
	info.alphaToOneEnable = VK_FALSE;
	return info;
}

VkPipelineColorBlendAttachmentState vk_util::color_blend_attachment_state() {
	VkPipelineColorBlendAttachmentState colorBlendAttachment = {};

	// Does not have sType or pNext

	colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | 
										  VK_COLOR_COMPONENT_G_BIT |
										  VK_COLOR_COMPONENT_B_BIT | 
										  VK_COLOR_COMPONENT_A_BIT;

	colorBlendAttachment.blendEnable = VK_FALSE;
	return colorBlendAttachment;
}

VkPipelineLayoutCreateInfo vk_util::pipeline_layout_create_info() {

	VkPipelineLayoutCreateInfo info{};
	info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	info.pNext = nullptr;

	//empty defaults
	info.flags = 0;
	info.setLayoutCount = 0;
	info.pSetLayouts = nullptr;
	info.pushConstantRangeCount = 0;
	info.pPushConstantRanges = nullptr;
	return info;
}



