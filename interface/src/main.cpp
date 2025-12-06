#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

#include "debugging/logger.h"
#include "gui/gui.h"
#include "rendering/device.h"
#include "rendering/instance.h"
#include "rendering/pipeline.h"
#include "rendering/render.h"
#include "rendering/swap_chain.h"
#include "rendering/window.h"

namespace gba {
	/// <summary>
	/// The main method, called from any entrypoint.
	/// </summary>
	/// <returns></returns>
	int main();

	/// <summary>
	/// Setup the program and rendering information.
	/// </summary>
	void initialize();

	/// <summary>
	/// Clean up the scene and rendering pipeline, prepare to end the program.
	/// </summary>
	void cleanup();
}

int main(int argc, char* argv[])
{
	return gba::main();
}

int gba::main()
{
	initialize();

	while (!render::g_render_state->should_close())
	{
		glfwPollEvents();
		gui::draw_ui();
		render::draw_frame();
	}

	cleanup();
	return 0;
}

void gba::initialize() {
	Logger::init();
	Logger::set_display_flags("Debug", FLAG_WRITE_TO_DEBUGGER);

	glfwInitHint(GLFW_COCOA_CHDIR_RESOURCES, GLFW_TRUE);
	glfwInit();

	if (!glfwVulkanSupported())
	{
		LOG_FATAL("Vulkan is not supported on this system!");
	}

	render::create_vulkan_instance();
	render::create_vulkan_window();
	render::g_render_state->device = new render::Device();
	//TODO(ches) use common allocator?
	render::create_swap_chain();
	render::create_pipeline();

	render::create_draw_state();

	render::init_UI();
}

void gba::cleanup()
{
	vkDeviceWaitIdle(render::g_render_state->device->logical_device);
	render::teardown_UI();

	safe_delete(render::g_render_state);
	glfwTerminate();
	Logger::destroy();
}
