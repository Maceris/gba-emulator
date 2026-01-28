#include "gui/disassembler.h"

#include "imgui.h"

#include "gui/gui.h"

namespace gui {

	void draw_window_disassembler() {
		ImGui::SetNextWindowPos(ImVec2(10, 30), ImGuiCond_Once);
		ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_Once);
		ImGui::Begin("Disassembler", &g_gui_state.show_window_disassembler);

		ImGui::End();
	}
}
