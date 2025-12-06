#pragma once

#include <atomic>
#include <cstdint>
#include <vector>

#include <vulkan/vulkan.h>

struct Pipeline;

/// <summary>
/// Render a single frame.
/// </summary>
void draw_frame();

/// <summary>
/// Prepare things for the UI.
/// </summary>
void init_UI();

/// <summary>
/// Stop rendering for now, such as when minimized.
/// </summary>
void stop_rendering();

/// <summary>
/// Resume rendering, such as when restoring from being minimized.
/// </summary>
void resume_rendering();

/// <summary>
/// Destroy the UI while we are shutting down.
/// </summary>
void teardown_UI();

/// <summary>
/// Tracks the state of rendering.
/// </summary>
struct DrawState
{
	DrawState();
	~DrawState();
	DrawState(const DrawState&) = delete;
	DrawState& operator=(const DrawState&) = delete;
	DrawState(DrawState&&) = delete;
	DrawState& operator=(DrawState&&) = delete;

	std::vector<VkSemaphore> image_available_semaphores;
	std::vector<VkSemaphore> render_finished_semaphores;
	std::vector<VkFence> frame_in_flight_fences;
	std::atomic_bool rendering_active = true;
	uint32_t current_frame = 0;

	std::vector<VkCommandBuffer> command_buffers;
	VkCommandPool command_pool;

	/// <summary>
	/// Fetch the current command buffer.
	/// </summary>
	VkCommandBuffer current_command_buffer() const;

	/// <summary>
	/// Destroy and recreate all the synchronization objects.
	/// </summary>
	void recreate_synchronization_objects();

private:
	void create_synchronization_objects();
	void destroy_synchronization_objects();

	void create_command_buffers();
	
	void destroy_command_buffers();
};

void create_draw_state();
void destroy_draw_state();

void record_command_buffer(const VkCommandBuffer buffer,
	const Pipeline* pipeline, uint32_t image_index);