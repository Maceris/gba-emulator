#pragma once

#include <optional>
#include <vector>

#include <vulkan/vulkan.h>

#include "swap_chain.h"

namespace render {
	/// <summary>
	/// Stores information about a device and what we need to interact with it.
	/// </summary>
	struct Device
	{
		friend struct SwapChain;
		friend struct CommandBuffer;
	public:
		VkPhysicalDevice physical_device = VK_NULL_HANDLE;
		VkDevice logical_device = VK_NULL_HANDLE;
		VkQueue graphics_queue = nullptr;
		VkQueue present_queue = nullptr;
		uint32_t graphics_family;
		uint32_t present_family;
		VkDescriptorPool descriptor_pool = nullptr;
		SwapChainSupport swap_chain_support;

		Device();
		Device(const Device&) = delete;
		Device& operator=(const Device&) = delete;
		Device(const Device&&) = delete;
		Device& operator=(const Device&&) = delete;
		~Device();

	private:
		/// <summary>
		/// Set up the device queues.
		/// </summary>
		void create_queues();

		/// <summary>
		/// Select a logical device to use among the system devices, and store it
		/// in the game state. Might have a fatal problem if we can't pick a
		/// device.
		/// </summary>
		void select_logical_device();

		/// <summary>
		/// Select a physical device to use among the system devices, and store it
		/// in the game state. Might have a fatal problem if we can't find a GPU.
		/// </summary>
		void select_physical_device();
	};
}
