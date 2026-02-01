#include "gui/disassembler.h"

#include <cstdlib>
#include <cstdint>

#include "imgui.h"

#include "brain/brain.h"
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
			const emulator::GBA& gba = brain::g_brain_data->gba;

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

				const emulator::ArmMode mode = gba.agb.gba_cpu.get_flag_mode();

				disassembler_n = gba.agb.gba_cpu.get_flag_N();
				disassembler_z = gba.agb.gba_cpu.get_flag_Z();
				disassembler_c = gba.agb.gba_cpu.get_flag_C();
				disassembler_v = gba.agb.gba_cpu.get_flag_V();
				disassembler_i = gba.agb.gba_cpu.get_flag_I();
				disassembler_f = gba.agb.gba_cpu.get_flag_F();
				disassembler_t = gba.agb.gba_cpu.get_flag_T();

				//TODO(ches) different modes (GBC, GBA ARM, GBA THUMB)
				ImGui::Text("R0: %08X", gba.agb.gba_cpu.read_register(0));
				ImGui::Text("R1: %08X", gba.agb.gba_cpu.read_register(1));
				ImGui::Text("R2: %08X", gba.agb.gba_cpu.read_register(2));
				ImGui::Text("R3: %08X", gba.agb.gba_cpu.read_register(3));
				ImGui::Text("R4: %08X", gba.agb.gba_cpu.read_register(4));
				ImGui::Text("R5: %08X", gba.agb.gba_cpu.read_register(5));
				ImGui::Text("R6: %08X", gba.agb.gba_cpu.read_register(6));
				ImGui::Text("R7: %08X", gba.agb.gba_cpu.read_register(7));
				ImGui::Text("R8: %08X", gba.agb.gba_cpu.read_register(8));
				ImGui::Text("R9: %08X", gba.agb.gba_cpu.read_register(9));
				ImGui::Text("R10: %08X", gba.agb.gba_cpu.read_register(10));
				ImGui::Text("R11: %08X", gba.agb.gba_cpu.read_register(11));
				ImGui::Text("R12: %08X", gba.agb.gba_cpu.read_register(12));
				ImGui::Text("R13: %08X", gba.agb.gba_cpu.read_register(13));
				ImGui::Text("R14: %08X", gba.agb.gba_cpu.read_register(14));
				ImGui::Text("R15: %08X", gba.agb.gba_cpu.read_register(15));
				ImGui::Text("CPSR: %08X", gba.agb.gba_cpu.read_CPSR());

				if (mode != emulator::ArmMode::USR && mode != emulator::ArmMode::SYS) {
					ImGui::Text("SPSR: %08X", gba.agb.gba_cpu.read_SPSR());
				}

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
				ImGui::Text("Mode: %s", disassembler_t ? "THUMB" : "ARM");

				ImGui::EndTable();
			}

			ImGui::End();
		}
	}

	void initialize_disassembler() {
		disassembler_contents = (char*)calloc(CONTENTS_SIZE, sizeof(char));
	}
}
