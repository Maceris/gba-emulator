#include "rendering/swap_chain.h"

#include <cstdint>
#include <limits>
#include <algorithm>

#include "debugging/logger.h"
#include "memory/memory_util.h"
#include "rendering/device.h"
#include "rendering/pipeline.h"
#include "rendering/render.h"
#include "rendering/render_state.h"
#include "rendering/window.h"

namespace render {

	SwapChain::SwapChain()
	{
		initialize_swap_chain();
		initialize_image_views();
	}

	SwapChain::~SwapChain()
	{
		const VkDevice& device = g_render_state->device->logical_device;
		for (auto view : image_views)
		{
			vkDestroyImageView(device, view, nullptr);
		}
		/*
		  NOTE(ches) Images are freed when the swap chain are destroyed,
		  and the vector will be cleaned up when this object is freed.
		 */
		vkDestroySwapchainKHR(g_render_state->device->logical_device,
			vulkan_swap_chain, nullptr);
	}

	void SwapChain::initialize_swap_chain()
	{
		const WindowSurface& surface = *g_render_state->window_state->surface;
		Device& device = *g_render_state->device;
		check_swap_chain_support(device.physical_device, surface.vulkan_surface,
			device.swap_chain_support);
		const SwapChainSupport& support = device.swap_chain_support;

		VkExtent2D selected_extent = select_extent(support.capabilities);
		uint32_t image_count = support.capabilities.minImageCount + 1;
		if (support.capabilities.maxImageCount > 0
			&& image_count > support.capabilities.maxImageCount)
		{
			image_count = support.capabilities.maxImageCount;
		}

		VkSwapchainCreateInfoKHR create_info{};
		create_info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		create_info.surface = surface.vulkan_surface;
		create_info.minImageCount = image_count;
		create_info.imageFormat = surface.surface_format->format;
		create_info.imageColorSpace = surface.surface_format->colorSpace;
		create_info.imageExtent = selected_extent;
		create_info.imageArrayLayers = 1;
		create_info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
		create_info.preTransform = support.capabilities.currentTransform;
		create_info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		create_info.presentMode = surface.present_mode;
		create_info.clipped = VK_TRUE;
		//TODO(ches) This will eventually need handling
		create_info.oldSwapchain = VK_NULL_HANDLE;

		uint32_t queue_family_indices[] = {
			device.graphics_family,
			device.present_family
		};

		if (device.graphics_family != device.present_family)
		{
			create_info.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
			create_info.queueFamilyIndexCount = 2;
			create_info.pQueueFamilyIndices = queue_family_indices;
		}
		else
		{
			create_info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
			create_info.queueFamilyIndexCount = 0;
			create_info.pQueueFamilyIndices = nullptr;
		}
		if (vkCreateSwapchainKHR(device.logical_device, &create_info, nullptr,
			&vulkan_swap_chain) != VK_SUCCESS)
		{
			LOG_FATAL("Failed to create swap chain");
		}

		vkGetSwapchainImagesKHR(device.logical_device, vulkan_swap_chain,
			&image_count, nullptr);
		images.resize(image_count);
		vkGetSwapchainImagesKHR(device.logical_device, vulkan_swap_chain,
			&image_count, images.data());

		image_format = surface.surface_format->format;
		this->extent = selected_extent;
	}

	void SwapChain::initialize_image_views()
	{
		image_views.resize(images.size());

		const VkDevice& device = g_render_state->device->logical_device;

		for (size_t i = 0; i < images.size(); i++)
		{
			VkImageViewCreateInfo create_info{};
			create_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
			create_info.image = images[i];
			create_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
			create_info.format = image_format;
			create_info.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
			create_info.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
			create_info.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
			create_info.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
			create_info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			create_info.subresourceRange.baseMipLevel = 0;
			create_info.subresourceRange.levelCount = 1;
			create_info.subresourceRange.baseArrayLayer = 0;
			create_info.subresourceRange.layerCount = 1;

			if (vkCreateImageView(device, &create_info, nullptr,
				&image_views[i]) != VK_SUCCESS)
			{
				LOG_FATAL("Failed to create image views for the swap chain");
			}
		}
	}

	[[nodiscard]] VkExtent2D
		SwapChain::select_extent(const VkSurfaceCapabilitiesKHR& capabilities)
		const
	{
		if (capabilities.currentExtent.width
			!= std::numeric_limits<uint32_t>::max())
		{
			return capabilities.currentExtent;
		}
		else
		{
			Window* window = g_render_state->window_state->window;
			int width = window->get_width();
			int height = window->get_height();

			VkExtent2D actualExtent = {
				static_cast<uint32_t>(width),
				static_cast<uint32_t>(height)
			};

			actualExtent.width = std::clamp(actualExtent.width,
				capabilities.minImageExtent.width,
				capabilities.maxImageExtent.width);
			actualExtent.height = std::clamp(actualExtent.height,
				capabilities.minImageExtent.height,
				capabilities.maxImageExtent.height);

			return actualExtent;
		}
	}

	void create_swap_chain()
	{
		g_render_state->window_state->swap_chain = ALLOC SwapChain();
	}

	void recreate_swap_chain()
	{
		vkDeviceWaitIdle(g_render_state->device->logical_device);
		destroy_frame_buffers();
		if (g_render_state->window_state->swap_chain) {
			delete g_render_state->window_state->swap_chain;
		}
		g_render_state->window_state->swap_chain = nullptr;

		g_render_state->draw_state->recreate_synchronization_objects();

		create_swap_chain();
		create_frame_buffers();
	}

	[[nodiscard]]
	void check_swap_chain_support(
		const VkPhysicalDevice device, const VkSurfaceKHR surface,
		SwapChainSupport& output)
	{
		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface,
			&output.capabilities);

		uint32_t format_count;
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface,
			&format_count, nullptr);

		if (format_count != 0)
		{
			output.formats.clear();
			output.formats.resize(format_count);
			vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface,
				&format_count, output.formats.data());
		}

		uint32_t present_mode_count;
		vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface,
			&present_mode_count, nullptr);

		if (present_mode_count != 0)
		{
			output.present_modes.clear();
			output.present_modes.resize(present_mode_count);
			vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface,
				&present_mode_count, output.present_modes.data());
		}
	}
}
