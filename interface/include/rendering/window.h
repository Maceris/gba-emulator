#pragma once

#include <atomic>
#include <vector>

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

namespace render {
	struct Device;
	struct SwapChain;
	struct WindowSurface;

	/// <summary>
	/// A wrapper around the GLFW window.
	/// </summary>
	struct Window
	{
		friend struct WindowSurface;
	public:
		Window();
		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;
		Window(const Window&&) = delete;
		Window& operator=(const Window&&) = delete;
		~Window();

		[[nodiscard]] int get_height() const;
		[[nodiscard]] int get_width() const;

		/// <summary>
		/// Reset the resized flag.
		/// </summary>
		void reset_resized();

		[[nodiscard]] bool should_close() const;

		/// <summary>
		/// If the window has recently been resized. Gets reset once we
		/// regenerate frame buffers.
		/// </summary>
		/// <returns>If the window has been resized.</returns>
		[[nodiscard]] bool was_resized() const;

		GLFWwindow* glfw_window = nullptr;

		static void callback_resized(GLFWwindow* window, int width, int height);
	private:
		std::atomic<int> width;
		std::atomic<int> height;
		std::atomic_bool resized = false;
	};

	/// <summary>
	/// Stores the state information for a window.
	/// </summary>
	struct WindowState
	{
		Window* window = nullptr;
		WindowSurface* surface = nullptr;
		SwapChain* swap_chain = nullptr;

		WindowState() = default;
		WindowState(const WindowState&) = delete;
		WindowState& operator=(const WindowState&) = delete;
		WindowState(const WindowState&&) = delete;
		WindowState& operator=(const WindowState&&) = delete;
		~WindowState();

		/// <summary>
		/// Check if we currently have a window. We should not be able to create
		/// two windows.
		/// </summary>
		/// <returns>If there is currently a window created.</returns>
		[[nodiscard]] bool constexpr has_window() const
		{
			return window != nullptr;
		}
	};

	/// <summary>
	/// A wrapper around the Vulkan surface.
	/// </summary>
	struct WindowSurface
	{
		friend struct Device;
		friend struct SwapChain;
	public:
		WindowSurface(Window* window);
		WindowSurface(const WindowSurface&) = delete;
		WindowSurface& operator=(const WindowSurface&) = delete;
		WindowSurface(const WindowSurface&&) = delete;
		WindowSurface& operator=(const WindowSurface&&) = delete;
		~WindowSurface();

	private:
		VkSurfaceKHR vulkan_surface = nullptr;
		VkSurfaceFormatKHR* surface_format = nullptr;
		VkPresentModeKHR present_mode = VK_PRESENT_MODE_FIFO_KHR;

		/// <summary>
		/// Select the best present mode from a list, and store it in this struct.
		/// </summary>
		/// <param name="available_present_modes">The present modes to choose from,
		/// which is determined by device support.</param>
		void select_present_mode(
			const std::vector<VkPresentModeKHR>& available_present_modes);

		/// <summary>
		/// Select the best format from a list, and store it in this struct.
		/// </summary>
		/// <param name="available_formats">The formats to choose from,
		/// which is determined by device support.</param>
		void select_surface_format(
			const std::vector<VkSurfaceFormatKHR>& available_formats);
	};

	/// <summary>
	/// Create a vulkan window, including associated things like the window 
	/// surface.
	/// </summary>
	void create_vulkan_window();
}
