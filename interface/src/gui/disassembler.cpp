#include "gui/disassembler.h"

#include <cstdlib>
#include <cstdint>

#include "imgui.h"

#include "gui/gui.h"
#include "memory/memory_util.h"

namespace gui {

	static int disassembler_mode = 0;
	static int disassembler_address = 0;
	static constexpr size_t CONTENT_ROWS = 20;
	static constexpr size_t CONTENT_COLUMNS = 80;
	static constexpr size_t CONTENTS_SIZE = CONTENT_ROWS * CONTENT_COLUMNS + 1 /* \0 */;
	static char* disassembler_contents = nullptr;

	static bool disassembler_n = false;
	static bool disassembler_z = false;
	static bool disassembler_c = false;
	static bool disassembler_v = false;
	static bool disassembler_i = false;
	static bool disassembler_f = false;
	static bool disassembler_t = false;

	void draw_window_disassembler() {
		ImGui::SetNextWindowPos(ImVec2(10, 30), ImGuiCond_Once);
		ImGui::SetNextWindowSize(ImVec2(500, 500), ImGuiCond_Once);

		if (ImGui::Begin("Disassembler", &g_gui_state.show_window_disassembler)) {
			if (ImGui::BeginTable("DisassemblerLayout", 2, ImGuiTableFlags_None)) {
				ImGui::TableNextColumn();
				if (ImGui::RadioButton("Automatic", &disassembler_mode, 0)) {

				}
				ImGui::SameLine();
				if (ImGui::RadioButton("ARM", &disassembler_mode, 1)) {

				}
				ImGui::SameLine();
				if (ImGui::RadioButton("THUMB", &disassembler_mode, 2)) {

				}
				if (ImGui::InputInt("Address", &disassembler_address, 1, 1000)) {

				}
				ImGui::SameLine();
				if (ImGui::Button("Go")) {

				}

				if (ImGui::InputTextMultiline("##DisassemblerText",
					disassembler_contents, CONTENTS_SIZE, ImVec2(0, 0),
					ImGuiInputTextFlags_ReadOnly)) {

				}

				ImGui::Button("Goto PC");
				ImGui::SameLine();
				ImGui::Button("Refresh");
				ImGui::SameLine();
				ImGui::Button("Next");

				ImGui::TableNextColumn();

				ImGui::Text("R0: ");
				ImGui::Text("R1: ");
				ImGui::Text("R2: ");
				ImGui::Text("R3: ");
				ImGui::Text("R4: ");
				ImGui::Text("R5: ");
				ImGui::Text("R6: ");
				ImGui::Text("R7: ");
				ImGui::Text("R8: ");
				ImGui::Text("R9: ");
				ImGui::Text("R10: ");
				ImGui::Text("R11: ");
				ImGui::Text("R12: ");
				ImGui::Text("R13: ");
				ImGui::Text("R14: ");
				ImGui::Text("R15: ");
				ImGui::Text("R16: ");

				ImGui::BeginDisabled();
				ImGui::Checkbox("N", &disassembler_n);
				ImGui::SameLine();
				ImGui::Checkbox("I", &disassembler_i);
				ImGui::Checkbox("Z", &disassembler_z);
				ImGui::SameLine();
				ImGui::Checkbox("F", &disassembler_f);
				ImGui::Checkbox("C", &disassembler_c);
				ImGui::SameLine();
				ImGui::Checkbox("T", &disassembler_t);
				ImGui::Checkbox("V", &disassembler_v);
				ImGui::EndDisabled();
				ImGui::SameLine();
				ImGui::Text("Mode: ");

				ImGui::EndTable();
			}

			ImGui::End();
		}
	}

	void initialize_disassembler() {
		disassembler_contents = (char*)calloc(CONTENTS_SIZE, sizeof(char));
	}
}
