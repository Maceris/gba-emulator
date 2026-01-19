#include "rendering/render.h"

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

#include <format>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_vulkan.h"

#include "debugging/logger.h"
#include "memory/memory_util.h"
#include "rendering/device.h"
#include "rendering/instance.h"
#include "rendering/pipeline.h"
#include "rendering/render_state.h"
#include "rendering/window.h"

template <>
struct std::formatter<VkResult, char> : std::formatter<int> {

	constexpr auto parse(std::format_parse_context& ctx) {
		return std::formatter<int>::parse(ctx);
	}

	auto format(VkResult result, std::format_context& ctx) const {
		auto out = ctx.out();

		switch (result) {
			case VK_SUCCESS:
				std::format_to(out, "VK_SUCCESS");
				return out;
			case VK_NOT_READY:
				std::format_to(out, "VK_NOT_READY");
				return out;
			case VK_TIMEOUT:
				std::format_to(out, "VK_TIMEOUT");
				return out;
			case VK_EVENT_SET:
				std::format_to(out, "VK_EVENT_SET");
				return out;
			case VK_EVENT_RESET:
				std::format_to(out, "VK_EVENT_RESET");
				return out;
			case VK_INCOMPLETE:
				std::format_to(out, "VK_INCOMPLETE");
				return out;
			case VK_ERROR_OUT_OF_HOST_MEMORY:
				std::format_to(out, "VK_ERROR_OUT_OF_HOST_MEMORY");
				return out;
			case VK_ERROR_OUT_OF_DEVICE_MEMORY:
				std::format_to(out, "VK_ERROR_OUT_OF_DEVICE_MEMORY");
				return out;
			case VK_ERROR_INITIALIZATION_FAILED:
				std::format_to(out, "VK_ERROR_INITIALIZATION_FAILED");
				return out;
			case VK_ERROR_DEVICE_LOST:
				std::format_to(out, "VK_ERROR_DEVICE_LOST");
				return out;
			case VK_ERROR_MEMORY_MAP_FAILED:
				std::format_to(out, "VK_ERROR_MEMORY_MAP_FAILED");
				return out;
			case VK_ERROR_LAYER_NOT_PRESENT:
				std::format_to(out, "VK_ERROR_LAYER_NOT_PRESENT");
				return out;
			case VK_ERROR_EXTENSION_NOT_PRESENT:
				std::format_to(out, "VK_ERROR_EXTENSION_NOT_PRESENT");
				return out;
			case VK_ERROR_FEATURE_NOT_PRESENT:
				std::format_to(out, "VK_ERROR_FEATURE_NOT_PRESENT");
				return out;
			case VK_ERROR_INCOMPATIBLE_DRIVER:
				std::format_to(out, "VK_ERROR_INCOMPATIBLE_DRIVER");
				return out;
			case VK_ERROR_TOO_MANY_OBJECTS:
				std::format_to(out, "VK_ERROR_TOO_MANY_OBJECTS");
				return out;
			case VK_ERROR_FORMAT_NOT_SUPPORTED:
				std::format_to(out, "VK_ERROR_FORMAT_NOT_SUPPORTED");
				return out;
			case VK_ERROR_FRAGMENTED_POOL:
				std::format_to(out, "VK_ERROR_FRAGMENTED_POOL");
				return out;
			case VK_ERROR_UNKNOWN:
				std::format_to(out, "VK_ERROR_UNKNOWN");
				return out;
			case VK_ERROR_OUT_OF_POOL_MEMORY:
				std::format_to(out, "VK_ERROR_OUT_OF_POOL_MEMORY");
				return out;
			case VK_ERROR_INVALID_EXTERNAL_HANDLE:
				std::format_to(out, "VK_ERROR_INVALID_EXTERNAL_HANDLE");
				return out;
			case VK_ERROR_FRAGMENTATION:
				std::format_to(out, "VK_ERROR_FRAGMENTATION");
				return out;
			case VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS:
				std::format_to(out, "VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS");
				return out;
			case VK_PIPELINE_COMPILE_REQUIRED:
				std::format_to(out, "VK_PIPELINE_COMPILE_REQUIRED");
				return out;
			case VK_ERROR_SURFACE_LOST_KHR:
				std::format_to(out, "VK_ERROR_SURFACE_LOST_KHR");
				return out;
			case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:
				std::format_to(out, "VK_ERROR_NATIVE_WINDOW_IN_USE_KHR");
				return out;
			case VK_SUBOPTIMAL_KHR:
				std::format_to(out, "VK_SUBOPTIMAL_KHR");
				return out;
			case VK_ERROR_OUT_OF_DATE_KHR:
				std::format_to(out, "VK_ERROR_OUT_OF_DATE_KHR");
				return out;
			case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
				std::format_to(out, "VK_ERROR_INCOMPATIBLE_DISPLAY_KHR");
				return out;
			case VK_ERROR_VALIDATION_FAILED_EXT:
				std::format_to(out, "VK_ERROR_VALIDATION_FAILED_EXT");
				return out;
			case VK_ERROR_INVALID_SHADER_NV:
				std::format_to(out, "VK_ERROR_INVALID_SHADER_NV");
				return out;
			case VK_ERROR_IMAGE_USAGE_NOT_SUPPORTED_KHR:
				std::format_to(out, "VK_ERROR_IMAGE_USAGE_NOT_SUPPORTED_KHR");
				return out;
			case VK_ERROR_VIDEO_PICTURE_LAYOUT_NOT_SUPPORTED_KHR:
				std::format_to(out, "VK_ERROR_VIDEO_PICTURE_LAYOUT_NOT_SUPPORTED_KHR");
				return out;
			case VK_ERROR_VIDEO_PROFILE_OPERATION_NOT_SUPPORTED_KHR:
				std::format_to(out, "VK_ERROR_VIDEO_PROFILE_OPERATION_NOT_SUPPORTED_KHR");
				return out;
			case VK_ERROR_VIDEO_PROFILE_FORMAT_NOT_SUPPORTED_KHR:
				std::format_to(out, "VK_ERROR_VIDEO_PROFILE_FORMAT_NOT_SUPPORTED_KHR");
				return out;
			case VK_ERROR_VIDEO_PROFILE_CODEC_NOT_SUPPORTED_KHR:
				std::format_to(out, "VK_ERROR_VIDEO_PROFILE_CODEC_NOT_SUPPORTED_KHR");
				return out;
			case VK_ERROR_VIDEO_STD_VERSION_NOT_SUPPORTED_KHR:
				std::format_to(out, "VK_ERROR_VIDEO_STD_VERSION_NOT_SUPPORTED_KHR");
				return out;
			case VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT:
				std::format_to(out, "VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT");
				return out;
			case VK_ERROR_NOT_PERMITTED_KHR:
				std::format_to(out, "VK_ERROR_NOT_PERMITTED_KHR");
				return out;
			case VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT:
				std::format_to(out, "VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT");
				return out;
			case VK_THREAD_IDLE_KHR:
				std::format_to(out, "VK_THREAD_IDLE_KHR");
				return out;
			case VK_THREAD_DONE_KHR:
				std::format_to(out, "VK_THREAD_DONE_KHR");
				return out;
			case VK_OPERATION_DEFERRED_KHR:
				std::format_to(out, "VK_OPERATION_DEFERRED_KHR");
				return out;
			case VK_OPERATION_NOT_DEFERRED_KHR:
				std::format_to(out, "VK_OPERATION_NOT_DEFERRED_KHR");
				return out;
#ifdef VK_ENABLE_BETA_EXTENSIONS
			case VK_ERROR_INVALID_VIDEO_STD_PARAMETERS_KHR:
				std::format_to(out, "VK_ERROR_INVALID_VIDEO_STD_PARAMETERS_KHR");
				return out;
#endif
			case VK_ERROR_COMPRESSION_EXHAUSTED_EXT:
				std::format_to(out, "VK_ERROR_COMPRESSION_EXHAUSTED_EXT");
				return out;
			case VK_ERROR_INCOMPATIBLE_SHADER_BINARY_EXT:
				std::format_to(out, "VK_ERROR_INCOMPATIBLE_SHADER_BINARY_EXT");
				return out;
			case VK_RESULT_MAX_ENUM:
				std::format_to(out, "VK_RESULT_MAX_ENUM");
				return out;
			default:
				return std::formatter<int>::format(static_cast<int>(result), ctx);
		}
	}
};

namespace render {
	
	void imgui_result_callback(VkResult err)
	{
		if (err != VK_SUCCESS) {
			LOG_ERROR(std::vformat("Issue with ImGui, error code {}", 
				std::make_format_args(err)));
		}
	}

	void draw_frame()
	{
		DrawState* draw_state = g_render_state->draw_state;

		if (!draw_state->rendering_active)
		{
			return;
		}

		const auto& device = g_render_state->device->logical_device;
		const SwapChain* swap_chain = g_render_state->window_state->swap_chain;
		const uint32_t current_frame = draw_state->current_frame;

		vkWaitForFences(device, 1,
			&draw_state->frame_in_flight_fences[current_frame],
			VK_TRUE, UINT64_MAX);

		uint32_t image_index;
		VkResult result = vkAcquireNextImageKHR(device,
			swap_chain->vulkan_swap_chain, UINT64_MAX,
			draw_state->image_available_semaphores[current_frame],
			VK_NULL_HANDLE, &image_index);

		if (result == VK_ERROR_OUT_OF_DATE_KHR
			|| result == VK_SUBOPTIMAL_KHR
			|| g_render_state->window_state->window->was_resized())
		{
			g_render_state->window_state->window->reset_resized();
			recreate_swap_chain();
			return;
		}
		else if (result != VK_SUCCESS)
		{
			LOG_FATAL("Failed to acquire swap chain image");
		}

		vkResetFences(device, 1,
			&draw_state->frame_in_flight_fences[current_frame]);

		const VkCommandBuffer buffer =
			g_render_state->draw_state->current_command_buffer();
		vkResetCommandBuffer(buffer, 0);
		record_command_buffer(buffer, g_render_state->pipeline, image_index);

		VkSubmitInfo submit_info{};
		submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

		VkSemaphore wait_semaphores[] = {
			draw_state->image_available_semaphores[current_frame]
		};
		VkPipelineStageFlags wait_stages[] = {
			VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT
		};
		submit_info.waitSemaphoreCount = 1;
		submit_info.pWaitSemaphores = wait_semaphores;
		submit_info.pWaitDstStageMask = wait_stages;
		submit_info.commandBufferCount = 1;
		submit_info.pCommandBuffers = &buffer;

		VkSemaphore signal_semaphores[] = {
			draw_state->render_finished_semaphores[current_frame]
		};
		submit_info.signalSemaphoreCount = 1;
		submit_info.pSignalSemaphores = signal_semaphores;
		if (vkQueueSubmit(g_render_state->device->graphics_queue, 1,
			&submit_info, draw_state->frame_in_flight_fences[current_frame])
			!= VK_SUCCESS)
		{
			LOG_FATAL("Failed to submit draw command buffer");
		}

		VkPresentInfoKHR present_info{};
		present_info.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
		present_info.waitSemaphoreCount = 1;
		present_info.pWaitSemaphores = signal_semaphores;

		VkSwapchainKHR swapChains[] = {
			g_render_state->window_state->swap_chain->vulkan_swap_chain
		};
		present_info.swapchainCount = 1;
		present_info.pSwapchains = swapChains;
		present_info.pImageIndices = &image_index;
		present_info.pResults = nullptr;

		vkQueuePresentKHR(g_render_state->device->graphics_queue,
			&present_info);

		draw_state->current_frame =
			(current_frame + 1) % MAX_FRAMES_IN_FLIGHT;
	}

	void cleanup() {
		vkDeviceWaitIdle(g_render_state->device->logical_device);
		teardown_UI();

		safe_delete(g_render_state);
		glfwTerminate();
	}

	void initialize() {
		glfwInitHint(GLFW_COCOA_CHDIR_RESOURCES, GLFW_TRUE);
		glfwInit();

		if (!glfwVulkanSupported())
		{
			LOG_FATAL("Vulkan is not supported on this system!");
		}

		create_vulkan_instance();
		create_vulkan_window();
		g_render_state->device = ALLOC Device();
		create_swap_chain();
		create_pipeline();
		create_draw_state();

		init_UI();
	}

	void init_UI()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

		ImGui::StyleColorsDark();

		ImGui_ImplGlfw_InitForVulkan(
			g_render_state->window_state->window->glfw_window, true);
		ImGui_ImplVulkan_InitInfo init_info = {};
		init_info.Instance = g_render_state->instance;
		init_info.PhysicalDevice = g_render_state->device->physical_device;
		init_info.Device = g_render_state->device->logical_device;
		init_info.QueueFamily = g_render_state->device->graphics_family;
		init_info.Queue = g_render_state->device->graphics_queue;
		init_info.PipelineCache = VK_NULL_HANDLE;
		init_info.DescriptorPool = g_render_state->device->descriptor_pool;
		static_assert(MAX_FRAMES_IN_FLIGHT >= 2,
			"We don't have enough frames to satisfy ImGui's MinImageCount min of 2");
		init_info.MinImageCount = MAX_FRAMES_IN_FLIGHT;
		init_info.ImageCount = MAX_FRAMES_IN_FLIGHT;
		init_info.Allocator = nullptr;
		init_info.CheckVkResultFn = imgui_result_callback;
		init_info.PipelineInfoMain.Subpass = 0;
		init_info.PipelineInfoMain.MSAASamples = VK_SAMPLE_COUNT_1_BIT;
		init_info.PipelineInfoMain.RenderPass = g_render_state->pipeline->render_pass;

		ImGui_ImplVulkan_Init(&init_info);
	}

	void stop_rendering()
	{
		g_render_state->draw_state->rendering_active = false;
	}

	void resume_rendering()
	{
		g_render_state->draw_state->rendering_active = true;
	}

	void teardown_UI()
	{
		ImGui_ImplVulkan_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	DrawState::DrawState()
	{
		create_synchronization_objects();
		create_command_buffers();
	}

	DrawState::~DrawState()
	{
		destroy_synchronization_objects();
		destroy_command_buffers();
	}

	VkCommandBuffer DrawState::current_command_buffer() const
	{
		return command_buffers[current_frame];
	}

	void DrawState::recreate_synchronization_objects()
	{
		destroy_synchronization_objects();
		create_synchronization_objects();
	}

	void DrawState::create_synchronization_objects()
	{
		VkSemaphoreCreateInfo semaphore_info{};
		semaphore_info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

		VkFenceCreateInfo fence_info{};
		fence_info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
		fence_info.flags = VK_FENCE_CREATE_SIGNALED_BIT;

		image_available_semaphores.resize(MAX_FRAMES_IN_FLIGHT);
		render_finished_semaphores.resize(MAX_FRAMES_IN_FLIGHT);
		frame_in_flight_fences.resize(MAX_FRAMES_IN_FLIGHT);

		auto& device = g_render_state->device->logical_device;

		for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; ++i)
		{
			if (vkCreateSemaphore(device, &semaphore_info, nullptr,
				&image_available_semaphores[i]) != VK_SUCCESS
				|| vkCreateSemaphore(device, &semaphore_info, nullptr,
					&render_finished_semaphores[i]) != VK_SUCCESS
				|| vkCreateFence(device, &fence_info, nullptr,
					&frame_in_flight_fences[i]) != VK_SUCCESS)
			{
				LOG_FATAL("Failed to create synchronization objects");
			}
		}
	}

	void DrawState::destroy_synchronization_objects()
	{
		auto& device = g_render_state->device->logical_device;

		for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; ++i)
		{
			vkDestroySemaphore(device, image_available_semaphores[i], nullptr);
			vkDestroySemaphore(device, render_finished_semaphores[i], nullptr);
			vkDestroyFence(device, frame_in_flight_fences[i], nullptr);
		}
	}

	void DrawState::create_command_buffers()
	{
		VkCommandPoolCreateInfo pool_info{};
		pool_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		pool_info.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
		pool_info.queueFamilyIndex = g_render_state->device->graphics_family;

		auto& device = g_render_state->device->logical_device;

		if (vkCreateCommandPool(device, &pool_info, nullptr,
			&command_pool) != VK_SUCCESS)
		{
			LOG_FATAL("Failed to create command pool");
		}

		command_buffers.resize(MAX_FRAMES_IN_FLIGHT);

		VkCommandBufferAllocateInfo allocate_info{};
		allocate_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocate_info.commandPool = command_pool;
		allocate_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocate_info.commandBufferCount = MAX_FRAMES_IN_FLIGHT;

		if (vkAllocateCommandBuffers(device, &allocate_info,
			command_buffers.data())
			!= VK_SUCCESS)
		{
			LOG_FATAL("Failed to create command buffer");
		}
	}

	void record_command_buffer(const VkCommandBuffer buffer,
		const Pipeline* pipeline, uint32_t image_index)
	{
		LOG_ASSERT(pipeline != nullptr);
		if (pipeline == nullptr) {
			LOG_FATAL("Internal error: null pipeline");
			return;
		}

		VkCommandBufferBeginInfo begin_info{};
		begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		begin_info.flags = 0;
		begin_info.pInheritanceInfo = nullptr;

		if (vkBeginCommandBuffer(buffer, &begin_info) != VK_SUCCESS)
		{
			LOG_FATAL("Failed to begin recording a command buffer");
		}

		const auto& extent = g_render_state->window_state->swap_chain->extent;

		VkRenderPassBeginInfo renderPassInfo{};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		renderPassInfo.renderPass = pipeline->render_pass;
		renderPassInfo.framebuffer = pipeline->frame_buffers[image_index];
		renderPassInfo.renderArea.offset = { 0, 0 };
		renderPassInfo.renderArea.extent = extent;

		VkClearValue clearColor = {{ 0.0f, 0.0f, 0.0f, 1.0f }};
		renderPassInfo.clearValueCount = 1;
		renderPassInfo.pClearValues = &clearColor;

		vkCmdBeginRenderPass(buffer, &renderPassInfo,
			VK_SUBPASS_CONTENTS_INLINE);

		vkCmdBindPipeline(buffer, VK_PIPELINE_BIND_POINT_GRAPHICS,
			pipeline->graphics_pipeline);

		VkViewport viewport{};
		viewport.x = 0.0f;
		viewport.y = 0.0f;
		viewport.width = static_cast<float>(extent.width);
		viewport.height = static_cast<float>(extent.height);
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;
		vkCmdSetViewport(buffer, 0, 1, &viewport);

		VkRect2D scissor{};
		scissor.offset = { 0, 0 };
		scissor.extent = extent;
		vkCmdSetScissor(buffer, 0, 1, &scissor);

		vkCmdDraw(buffer, 3, 1, 0, 0);

		ImGui::Render();
		ImDrawData* draw_data = ImGui::GetDrawData();
		const bool is_minimized = (extent.width == 0 || extent.height == 0);
		if (!is_minimized)
		{
			ImGui_ImplVulkan_RenderDrawData(draw_data,
				g_render_state->draw_state->current_command_buffer());
		}

		vkCmdEndRenderPass(g_render_state->draw_state->current_command_buffer());

		if (vkEndCommandBuffer(buffer) != VK_SUCCESS)
		{
			LOG_FATAL("Failed recording command buffer");
		}
	}

	void DrawState::destroy_command_buffers()
	{
		//NOTE(ches) Buffers get cleaned up with the pool.
		vkDestroyCommandPool(g_render_state->device->logical_device,
			command_pool, nullptr);
	}

	void create_draw_state()
	{
		g_render_state->draw_state = ALLOC DrawState();
	}

	void destroy_draw_state()
	{
		safe_delete(g_render_state->draw_state);
	}
}
