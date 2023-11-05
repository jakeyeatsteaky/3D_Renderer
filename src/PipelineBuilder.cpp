#include "PipelineBuilder.hpp"

VkPipeline PipelineBuilder::BuildPipeline(VkDevice device, VkRenderPass pass)
{
	// make viewport state using the viewport and scissor of this pipeline builder object
	VkPipelineViewportStateCreateInfo viewportStateInfo{};
	viewportStateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	viewportStateInfo.pNext = nullptr;

	viewportStateInfo.viewportCount = 1;
	viewportStateInfo.pViewports = &m_viewport;
	viewportStateInfo.scissorCount = 1;
	viewportStateInfo.pScissors = &m_scissor;

	// This iteration of blending does not support transparent objects
	// !!! This one has to match the fragment shader outputs
	VkPipelineColorBlendStateCreateInfo colorBlending = {};
	colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	colorBlending.pNext = nullptr;

	colorBlending.logicOpEnable = VK_FALSE;
	colorBlending.logicOp = VK_LOGIC_OP_COPY;
	colorBlending.attachmentCount = 1;
	colorBlending.pAttachments = &m_colorBlendAttachment;

	// Build the actual pipeline!
	// Use all of the info structs into this struct to create the pipeline

	VkGraphicsPipelineCreateInfo pipelineInfo = {};
	pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	pipelineInfo.pNext = nullptr;

	pipelineInfo.stageCount = (uint32_t)m_shaderStages.size();
	pipelineInfo.pStages = m_shaderStages.data();
	pipelineInfo.pVertexInputState = &m_vertexInputInfo;
	pipelineInfo.pInputAssemblyState = &m_inputAssembly;
	pipelineInfo.pViewportState = &viewportStateInfo;
	pipelineInfo.pRasterizationState = &m_rasterizer;
	pipelineInfo.pMultisampleState = &m_multisampling;
	pipelineInfo.pColorBlendState = &colorBlending;
	pipelineInfo.layout = m_pipelineLayout;
	pipelineInfo.renderPass = pass;
	pipelineInfo.subpass = 0;
	pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;

	// Gets its own error checking since its easy to error out here.
	VkPipeline newPipeline;
	if (vkCreateGraphicsPipelines(device,
		VK_NULL_HANDLE,
		1,
		&pipelineInfo,
		nullptr,
		&newPipeline) != VK_SUCCESS) {
		std::cout << "ERROR: Failed to create graphics pipeline" << std::endl;
		return VK_NULL_HANDLE;
	}
	else
		return newPipeline;


}