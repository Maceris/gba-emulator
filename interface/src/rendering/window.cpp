#include "rendering/window.h"

#include <format>

#include "GLFW/glfw3.h"

#include "debugging/logger.h"
#include "rendering/render.h"
#include "rendering/render_state.h"
#include "rendering/swap_chain.h"

constexpr int DEFAULT_WIDTH = 640;
constexpr int DEFAULT_HEIGHT = 480;

void callback_iconify(GLFWwindow* window, int iconified)
{
	if (iconified == GLFW_TRUE)
	{
		stop_rendering();
	}
	else if (iconified == GLFW_FALSE)
	{
		resume_rendering();
	}
}

void Window::callback_resized(GLFWwindow* glfw_window, int width,
	int height)
{
	Window* window = g_render_state->window_state->window;
	window->width = width;
	window->height = height;
	window->resized = true;
}

Window::Window()
	: width{ DEFAULT_WIDTH }
	, height{ DEFAULT_HEIGHT }
{
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	glfw_window = glfwCreateWindow(DEFAULT_WIDTH, DEFAULT_HEIGHT,
		"GBA Emulator v1.0.0", NULL, NULL);
	glfwSetWindowIconifyCallback(glfw_window, callback_iconify);
	glfwSetFramebufferSizeCallback(glfw_window, callback_resized);
}

Window::~Window()
{
	glfwDestroyWindow(glfw_window);
}

[[nodiscard]] int Window::get_height() const
{
	return height;
}

[[nodiscard]] int Window::get_width() const
{
	return width;
}

void Window::reset_resized()
{
	resized = false;
}

[[nodiscard]] bool Window::should_close() const
{
	return glfwWindowShouldClose(glfw_window);
}

[[nodiscard]] bool Window::was_resized() const
{
	return resized;
}

WindowState::~WindowState()
{
	safe_delete(swap_chain);
	safe_delete(surface);
	safe_delete(window);
}

void create_vulkan_window()
{
	if (g_render_state->has_window())
	{
		LOG_FATAL("We are trying to create a second window");
	}

	WindowState* state = new WindowState();
	g_render_state->window_state = state;
	state->window = new Window();
	state->surface = new WindowSurface(state->window);
	//TODO(ches) use common allocator?
}

WindowSurface::WindowSurface(Window* window)
{
	LOG_ASSERT(g_render_state != nullptr && g_render_state->has_instance()
		&& "We require a Vulkan instance before setting up a surface");
	LOG_ASSERT(window != nullptr && window->glfw_window
		&& "Trying to create a surface for a null window");

	if (glfwCreateWindowSurface(g_render_state->instance,
		window->glfw_window,
		NULL, &vulkan_surface) != VK_SUCCESS)
	{
		LOG_FATAL("Failed to create a window surface");
	}
}

WindowSurface::~WindowSurface()
{
	if (surface_format) {
		delete surface_format;
	}
	surface_format = nullptr;
	vkDestroySurfaceKHR(g_render_state->instance, vulkan_surface, nullptr);
}

void WindowSurface::select_present_mode(
	const std::vector<VkPresentModeKHR>& available_present_modes)
{
	if (available_present_modes.empty())
	{
		LOG_WARNING("We don't have any available present modes");
	}

	for (const auto& availablePresentMode : available_present_modes)
	{
		//NOTE(ches) reduces latency, but maybe at the expense of some power
		if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
		{
			present_mode = VK_PRESENT_MODE_MAILBOX_KHR;
			return;
		}
	}
	// NOTE(ches) VK_PRESENT_MODE_FIFO_KHR is guaranteed, and our default
}

void WindowSurface::select_surface_format(
	const std::vector<VkSurfaceFormatKHR>& available_formats)
{
	LOG_ASSERT(available_formats.size() > 0
		&& "We require available surface formats");

	surface_format = new VkSurfaceFormatKHR();
	//TODO(ches) use common allocator?
	for (const auto& choice : available_formats)
	{
		if (choice.format == VK_FORMAT_B8G8R8A8_UNORM
			&& choice.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
		{
			surface_format->colorSpace = choice.colorSpace;
			surface_format->format = choice.format;
			return;
		}
	}

	surface_format->colorSpace = available_formats[0].colorSpace;
	surface_format->format = available_formats[0].format;
}
