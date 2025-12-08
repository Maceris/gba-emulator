#include "rendering/render_state.h"

#include "memory/memory_util.h"
#include "rendering/device.h"
#include "rendering/instance.h"
#include "rendering/pipeline.h"
#include "rendering/render.h"
#include "rendering/window.h"

namespace render {

	RenderState* g_render_state = ALLOC RenderState();

	void unload_debug_messenger();

	RenderState::~RenderState()
	{
		destroy_draw_state();
		if (pipeline) {
			delete pipeline;
		}
		pipeline = nullptr;

		if (window_state)
		{
			delete window_state;
		}
		window_state = nullptr;
		if (device)
		{
			delete device;
		}
		device = nullptr;
		if (debug_messenger)
		{
			unload_debug_messenger();
		}

		if (instance)
		{
			vkDestroyInstance(instance, nullptr);
			instance = nullptr;
		}
	}

	bool load_debug_messenger()
	{
		VkDebugUtilsMessengerCreateInfoEXT create_info;
		popualate_debug_info(create_info);

		VkResult result = VK_SUCCESS;

		VkAllocationCallbacks* allocator = nullptr;
		call_extension_function("vkCreateDebugUtilsMessengerEXT", &result,
			g_render_state->instance, &create_info, allocator,
			&g_render_state->debug_messenger);

		return result == VK_SUCCESS;
	}

	void unload_debug_messenger()
	{
		if (g_render_state->debug_messenger == nullptr)
		{
			LOG_WARNING("Trying to unload a debug messenger that is not loaded");
			return;
		}

		VkAllocationCallbacks* allocator = nullptr;
		call_extension_function("vkDestroyDebugUtilsMessengerEXT", nullptr,
			g_render_state->instance, g_render_state->debug_messenger, allocator);
	}

	[[nodiscard]] bool RenderState::should_close() const
	{
		return close_requested || window_state->window->should_close();
	}
}
