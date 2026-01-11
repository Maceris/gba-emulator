#include "rendering/device.h"

#include <set>
#include <vector>

#include "debugging/logger.h"
#include "rendering/instance.h"
#include "rendering/pipeline.h"
#include "rendering/render_state.h"
#include "rendering/window.h"

namespace render {
	/// <summary>
	/// The extensions that we require on a device.
	/// </summary>
	const std::vector<const char*> REQUIRED_EXTENSIONS = {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};

	/// <summary>
	/// Find all the queue family indices we care about for a device.
	/// </summary>
	/// <param name="device">The device we are checking.</param>
	/// <param name="surface">The Vulkan surface.</param>
	/// <param name="graphics_family">Output for the graphics family</param>
	/// <param name="preseent_family">Output for the present family</param>
	/// <returns>If we found the queue families.</returns>
	[[nodiscard]]
	static bool find_queue_families(
		const VkPhysicalDevice device, const VkSurfaceKHR surface,
		uint32_t* graphics_family, uint32_t* present_family)
	{
		LOG_ASSERT(graphics_family != nullptr);
		LOG_ASSERT(present_family != nullptr);
		if (graphics_family == nullptr || present_family == nullptr) {
			LOG_FATAL("Internal error: Null pointer finding queue families");
		}

		uint32_t queue_family_count = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queue_family_count,
			nullptr);

		std::vector<VkQueueFamilyProperties> queue_families(queue_family_count);
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queue_family_count,
			queue_families.data());

		bool found_graphics = false;
		bool found_present = false;

		uint32_t i = 0;
		for (const auto& queue_family : queue_families)
		{
			if (queue_family.queueFlags & VK_QUEUE_GRAPHICS_BIT)
			{
				*graphics_family = i;
				found_graphics = true;
			}
			VkBool32 present_support = false;
			vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface,
				&present_support);

			if (present_support)
			{
				*present_family = i;
				found_present = true;
			}

			++i;
			if (found_graphics && found_present)
			{
				break;
			}
		}

		return found_graphics && found_present;
	}

	/// <summary>
	/// Checks if a device supports all the extensions we need.
	/// </summary>
	/// <param name="device">The device to check.</param>
	/// <returns>If it supports the required extensions.</returns>
	[[nodiscard]]
	static bool supports_required_extensions(const VkPhysicalDevice device)
	{
		uint32_t extension_count;
		vkEnumerateDeviceExtensionProperties(device, nullptr,
			&extension_count, nullptr);

		std::vector<VkExtensionProperties> available_extensions(extension_count);
		vkEnumerateDeviceExtensionProperties(device, nullptr, &extension_count,
			available_extensions.data());

		std::set<std::string> required_extensions(REQUIRED_EXTENSIONS.begin(),
			REQUIRED_EXTENSIONS.end());

		for (const auto& extension : available_extensions)
		{
			required_extensions.erase(extension.extensionName);
		}

		return required_extensions.empty();
	}

	/// <summary>
	/// Calculate a score to represent how much desireable a device is. Will
	/// be zero if it's not usable for us.
	/// </summary>
	/// <param name="device">The device we are rating.</param>
	/// <param name="surface">The Vulkan surface.</param>
	/// <param name="graphics_family">Output for the graphics family.</param>
	/// <param name="preseent_family">Output for the present family.</param>
	/// <returns>A score for the device.</returns>
	[[nodiscard]]
	static int rate_device(const VkPhysicalDevice device, VkSurfaceKHR surface,
		uint32_t* graphics_family, uint32_t* present_family
		)
	{
		LOG_ASSERT(graphics_family != nullptr);
		LOG_ASSERT(present_family != nullptr);
		if (graphics_family == nullptr || present_family == nullptr) {
			LOG_FATAL("Internal error: Null pointer finding queue families");
		}

		int score = 0;

		VkPhysicalDeviceProperties device_properties;
		vkGetPhysicalDeviceProperties(device, &device_properties);
		VkPhysicalDeviceFeatures device_features;
		vkGetPhysicalDeviceFeatures(device, &device_features);

		if (!device_features.geometryShader)
		{
			return 0;
		}

		bool found_families = find_queue_families(device, surface, 
			graphics_family, present_family);

		if (!found_families)
		{
			return 0;
		}

		if (!supports_required_extensions(device))
		{
			return 0;
		}

		SwapChainSupport swap_chain_support;
		
		check_swap_chain_support(device, surface, swap_chain_support);
		if (swap_chain_support.formats.empty()
			|| swap_chain_support.present_modes.empty())
		{
			return 0;
		}

		//NOTE(ches) Discrete GPU is much better than on-chip
		if (device_properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
		{
			score += 1000;
		}

		//NOTE(ches) Largest possible size of a texture
		score += device_properties.limits.maxImageDimension2D;

		return score;
	}

	Device::Device()
	{
		select_physical_device();
		select_logical_device();
		create_queues();
		
		WindowSurface* surface = g_render_state->window_state->surface;
		check_swap_chain_support(physical_device, surface->vulkan_surface,
			swap_chain_support);

		surface->select_present_mode(swap_chain_support.present_modes);
		surface->select_surface_format(swap_chain_support.formats);

		VkDescriptorPoolSize pool_sizes[] =
		{
			{ VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1 * MAX_FRAMES_IN_FLIGHT },
			{ VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER, 2 * MAX_FRAMES_IN_FLIGHT },
			{ VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER, 2 * MAX_FRAMES_IN_FLIGHT },
		};

		constexpr uint32_t pool_sizes_count =
			static_cast<uint32_t>(sizeof(pool_sizes) / sizeof(*pool_sizes));

		VkDescriptorPoolCreateInfo descriptor_pool_info{};
		descriptor_pool_info.sType =
			VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		descriptor_pool_info.poolSizeCount = pool_sizes_count;
		descriptor_pool_info.pPoolSizes = pool_sizes;
		descriptor_pool_info.maxSets = MAX_FRAMES_IN_FLIGHT;
		descriptor_pool_info.flags =
			VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;

		if (vkCreateDescriptorPool(logical_device, &descriptor_pool_info,
			nullptr, &descriptor_pool) != VK_SUCCESS)
		{
			LOG_FATAL("Failed to create descriptor pool");
		}
	}

	Device::~Device()
	{
		vkDestroyDescriptorPool(logical_device, descriptor_pool, nullptr);

		//NOTE(ches) queues are implicity destroyed when the logical device is
		//NOTE(ches) physical device gets destroyed implicitly with the instance
		if (logical_device != VK_NULL_HANDLE)
		{
			vkDestroyDevice(logical_device, nullptr);
		}
	}

	void Device::create_queues()
	{
		const uint32_t queue_index = 0;
		vkGetDeviceQueue(logical_device, present_family, queue_index,
			&present_queue);
		vkGetDeviceQueue(logical_device, graphics_family, queue_index,
			&graphics_queue);
	}
	

	void Device::select_physical_device()
	{
		uint32_t device_count = 0;
		vkEnumeratePhysicalDevices(g_render_state->instance, &device_count,
			nullptr);

		if (device_count == 0)
		{
			LOG_FATAL("No GPUs support Vulkan");
		}

		std::vector<VkPhysicalDevice> devices(device_count);
		vkEnumeratePhysicalDevices(g_render_state->instance, &device_count,
			devices.data());

		int best_score = 0;
		VkPhysicalDevice best_device = VK_NULL_HANDLE;
		uint32_t temp_graphics_family = 0;
		uint32_t temp_present_family = 0;

		for (const auto& device : devices)
		{
			int score = rate_device(device, 
				g_render_state->window_state->surface->vulkan_surface,
				&temp_graphics_family, &temp_present_family);
			if (score > best_score)
			{
				best_score = score;
				best_device = device;
				graphics_family = temp_graphics_family;
				present_family = temp_present_family;
			}
		}

		if (best_score == 0) {
			LOG_FATAL("No GPUs are suitable for this program");
		}

		physical_device = best_device;
	}

	void Device::select_logical_device()
	{
		std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
		std::set<uint32_t> uniqueQueueFamilies = {
			graphics_family,
			present_family
		};

		float queuePriority = 1.0f;
		for (uint32_t queueFamily : uniqueQueueFamilies)
		{
			VkDeviceQueueCreateInfo queueCreateInfo{};
			queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueCreateInfo.queueFamilyIndex = queueFamily;
			queueCreateInfo.queueCount = 1;
			queueCreateInfo.pQueuePriorities = &queuePriority;
			queueCreateInfos.push_back(queueCreateInfo);
		}

		VkPhysicalDeviceFeatures device_features{};
		//TODO(ches) Select device features

		VkDeviceCreateInfo create_info{};
		create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		create_info.pQueueCreateInfos = queueCreateInfos.data();
		create_info.queueCreateInfoCount =
			static_cast<uint32_t>(queueCreateInfos.size());;
		create_info.pEnabledFeatures = &device_features;
		create_info.enabledExtensionCount =
			static_cast<uint32_t>(REQUIRED_EXTENSIONS.size());
		create_info.ppEnabledExtensionNames = REQUIRED_EXTENSIONS.data();

		if (ENABLE_VALIDATION_LAYERS)
		{
			create_info.enabledLayerCount =
				static_cast<uint32_t>(VALIDATION_LAYERS.size());
			create_info.ppEnabledLayerNames = VALIDATION_LAYERS.data();
		}
		else
		{
			create_info.enabledLayerCount = 0;
		}

		if (vkCreateDevice(physical_device, &create_info, nullptr,
			&logical_device) != VK_SUCCESS)
		{
			LOG_FATAL("Could not create a logical device");
		}
	}
	
}
