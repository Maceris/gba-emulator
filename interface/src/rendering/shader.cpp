#include "rendering/shader.h"

#include <filesystem>
#include <format>
#include <fstream>

#include "debugging/logger.h"
#include "rendering/device.h"
#include "rendering/render_state.h"

namespace fs = std::filesystem;

namespace render {

	ShaderModule::ShaderModule(std::string_view name)
	{
		//TODO(ches) cleaner shader loading
		std::filesystem::path resource_path{
				std::filesystem::current_path().append("resources").append(name)
		};
		std::filesystem::path full_resource_path =
			std::filesystem::canonical(resource_path);
		;
		const std::string full_path = full_resource_path.string();
		if (!fs::exists(full_path))
		{
			LOG_FATAL("Can not find the file " + full_path
				+ " in order to determine size");
			return;
		}
		if (!fs::is_regular_file(full_path))
		{
			LOG_FATAL(full_path + " is not a regular file, cannot determine size");
			return;
		}

		size_t size = fs::file_size(full_path);

		char* shader_data = new char[size];
		memset(shader_data, 0, size);
		std::ifstream file(full_path, std::ios::binary);

		if (!file.is_open()) {
			delete[] shader_data;
			LOG_FATAL("Can't open file " + full_path);
			return;
		}

		if (!file.read(shader_data, size)) {
			delete[] shader_data;
			LOG_FATAL("Can't read file " + full_path);
			return;
		}

		VkShaderModuleCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		createInfo.codeSize = size;
		createInfo.pCode = reinterpret_cast<const uint32_t*>(shader_data);

		if (vkCreateShaderModule(g_render_state->device->logical_device,
			&createInfo, nullptr, &shader_module) != VK_SUCCESS)
		{
			LOG_FATAL(std::format("Could not load shader module {}!", name));
		}
		delete[] shader_data;
	}

	ShaderModule::~ShaderModule()
	{
		if (shader_module)
		{
			vkDestroyShaderModule(g_render_state->device->logical_device,
				shader_module, nullptr);
		}
	}

	[[nodiscard]]
	constexpr VkShaderStageFlagBits stage_type(ShaderType stage)
	{
		switch (stage)
		{
		case ShaderType::fragment:
			return VK_SHADER_STAGE_FRAGMENT_BIT;
		case ShaderType::vertex:
			return VK_SHADER_STAGE_VERTEX_BIT;
		default:
			LOG_WARNING("Invalid shader stage provided");
			return VK_SHADER_STAGE_ALL;
		}
	}

	Shader::Shader(std::initializer_list<ShaderStage> stages)
	{
		LOG_ASSERT(stages.size() > 0
			&& "There were no shader stages provided");

		for (auto& stage : stages)
		{
			auto module = std::make_shared<ShaderModule>(stage.location);
			modules.push_back(module);

			VkPipelineShaderStageCreateInfo create_info{};
			create_info.sType =
				VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
			create_info.stage = stage_type(stage.type);
			create_info.module = module->shader_module;
			create_info.pName = "main";
			create_info.pSpecializationInfo = nullptr;

			create_info_list.push_back(create_info);
		}
	}

	Shader::~Shader() = default;
}
