#ifndef PIPELINE_BUILDER_HPP
#define PIPELINE_BUILDER_HPP
#include <vector>
#include <vulkan/vulkan.h> 
#include "VulkanUtil.hpp"

// Basic set of vulkan structs for building a graphics pipeline
// All of the initializers for these vulkan structs are in vulkanUtil

class PipelineBuilder
{
public:
	std::vector<VkPipelineShaderStageCreateInfo> m_shaderStages;
	VkPipelineVertexInputStateCreateInfo m_vertexInputInfo;
	VkPipelineInputAssemblyStateCreateInfo m_inputAssembly;
	VkViewport m_viewport;
	VkRect2D m_scissor;
	VkPipelineRasterizationStateCreateInfo m_rasterizer;
	VkPipelineColorBlendAttachmentState m_colorBlendAttachment;
	VkPipelineMultisampleStateCreateInfo m_multisampling;
	VkPipelineLayout m_pipelineLayout;

	VkPipeline BuildPipeline(VkDevice device, VkRenderPass pass);
};

#endif // End pipelinebuilder.hpp