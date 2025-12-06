#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_vulkan.h"

constexpr ImVec4 RED = ImVec4(1.0f, 0.1f, 0.1f, 1.0f);

namespace gui {
	/// <summary>
	/// Draw the UI on top of a frame, intended to be called from the pipeline
	/// while it is generating commands for the buffer.
	/// </summary>
	void draw_ui();
}