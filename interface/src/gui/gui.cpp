#include "gui/gui.h"

#include "rendering/render_state.h"

void gui::draw_ui()
{
	ImGui_ImplVulkan_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	bool unsupported = false;
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			bool scene_select = false;
			if (ImGui::MenuItem("Open", nullptr, &scene_select))
			{
				unsupported = true;
			}

			ImGui::EndMenu();
		}
		ImGui::PushStyleColor(ImGuiCol_Text, RED);
		if (ImGui::MenuItem("Exit"))
		{
			render::g_render_state->close_requested = true;
		}
		ImGui::PopStyleColor();
		ImGui::EndMainMenuBar();
	}

	if (unsupported)
	{
		ImGui::OpenPopup("Unsupported operation");
	}
	if (ImGui::BeginPopupModal("Unsupported operation", nullptr,
		ImGuiWindowFlags_NoResize))
	{
		ImGui::Text("Operation not yet supported");
		if (ImGui::Button("Sorry"))
		{
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	ImGui::ShowDemoWindow();

	ImGui::EndFrame();
}