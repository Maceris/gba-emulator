#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

#include "brain/brain.h"

#include "gui/gui.h"
#include "memory/memory_util.h"
#include "rendering/render.h"
#include "rendering/render_state.h"

namespace brain {
	BrainData* g_brain_data = ALLOC BrainData();

	BrainData::BrainData()
		: command_queue{}
	{}
	BrainData::~BrainData() = default;

	void run_application() {
		while (!render::g_render_state->should_close())
		{
			glfwPollEvents();
			gui::draw_ui();
			render::draw_frame();
		}
	}

}