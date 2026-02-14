#include "gui/disassembler.h"

#include <cstdlib>
#include <cstdint>

#include "imgui.h"

#include "debugging/logger.h"
#include "brain/brain.h"
#include "gui/gui.h"
#include "memory/memory_util.h"

namespace gui {

	static constexpr const char* MODE_AUTOMATIC_TEXT = "Automatic";
	static constexpr const int MODE_AUTOMATIC_VALUE = 0;
	static constexpr const char* MODE_ARM_TEXT = "ARM";
	static constexpr const int MODE_ARM_VALUE = 1;
	static constexpr const char* MODE_THUMB_TEXT = "THUMB";
	static constexpr const int MODE_THUMB_VALUE = 2;


	static int disassembler_mode_selection = 0;
	static bool disassembler_mode_is_thumb = false;
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

	static void draw_arm_disassembler() {
		const emulator::GBA& gba = brain::g_brain_data->gba;

		if (ImGui::BeginTable("DisassemblerLayout", 2, ImGuiTableFlags_None)) {
			// Variable setup
			const emulator::ArmMode execution_mode = gba.agb.gba_cpu.get_flag_mode();

			disassembler_n = gba.agb.gba_cpu.get_flag_N();
			disassembler_z = gba.agb.gba_cpu.get_flag_Z();
			disassembler_c = gba.agb.gba_cpu.get_flag_C();
			disassembler_v = gba.agb.gba_cpu.get_flag_V();
			disassembler_i = gba.agb.gba_cpu.get_flag_I();
			disassembler_f = gba.agb.gba_cpu.get_flag_F();
			disassembler_t = gba.agb.gba_cpu.get_flag_T();

			if (disassembler_mode_selection == MODE_AUTOMATIC_VALUE) {
				disassembler_mode_is_thumb = disassembler_t;
			}
			else if (disassembler_mode_selection == MODE_ARM_VALUE) {
				disassembler_mode_is_thumb = false;
			}
			else if (disassembler_mode_selection == MODE_THUMB_VALUE) {
				disassembler_mode_is_thumb = true;
			}
			else {
				LOG_FATAL("Internal error: Invalid mode selection");
			}

			const char* mode_name = "";
			switch (execution_mode) {
			case emulator::ArmMode::USR:
				mode_name = "USR (User)";
				break;
			case emulator::ArmMode::FIQ:
				mode_name = "FIQ (Fast Interrupt)";
				break;
			case emulator::ArmMode::IRQ:
				mode_name = "IRQ (Interrupt)";
				break;
			case emulator::ArmMode::SVC:
				mode_name = "SVC (Supervisor)";
				break;
			case emulator::ArmMode::ABT:
				mode_name = "ABT (Abort)";
				break;
			case emulator::ArmMode::UND:
				mode_name = "UND (Undefined)";
				break;
			case emulator::ArmMode::SYS:
				mode_name = "SYS (System)";
				break;
			}

			// Contents
			ImGui::TableNextColumn();
			if (ImGui::RadioButton(MODE_AUTOMATIC_TEXT, 
				&disassembler_mode_selection, MODE_AUTOMATIC_VALUE)) {}
			ImGui::SameLine();
			if (ImGui::RadioButton(MODE_ARM_TEXT, 
				&disassembler_mode_selection, MODE_ARM_VALUE)) {}
			ImGui::SameLine();
			if (ImGui::RadioButton(MODE_THUMB_TEXT, 
				&disassembler_mode_selection, MODE_THUMB_VALUE)) {}

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

			if (disassembler_mode_is_thumb) {
				// Thumb mode
				ImGui::Text("R0: %08X", gba.agb.gba_cpu.read_register(0));
				ImGui::Text("R1: %08X", gba.agb.gba_cpu.read_register(1));
				ImGui::Text("R2: %08X", gba.agb.gba_cpu.read_register(2));
				ImGui::Text("R3: %08X", gba.agb.gba_cpu.read_register(3));
				ImGui::Text("R4: %08X", gba.agb.gba_cpu.read_register(4));
				ImGui::Text("R5: %08X", gba.agb.gba_cpu.read_register(5));
				ImGui::Text("R6: %08X", gba.agb.gba_cpu.read_register(6));
				ImGui::Text("R7: %08X", gba.agb.gba_cpu.read_register(7));
				ImGui::Text("SP: %08X", gba.agb.gba_cpu.read_register(13));
				ImGui::Text("LR: %08X", gba.agb.gba_cpu.read_register(14));
				ImGui::Text("PC: %08X", gba.agb.gba_cpu.read_register(15));
			}
			else {
				// ARM mode
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
			}
			
			ImGui::Text("CPSR: %08X", gba.agb.gba_cpu.read_CPSR());

			if (execution_mode != emulator::ArmMode::USR 
				&& execution_mode != emulator::ArmMode::SYS) {
				ImGui::Text("SPSR: %08X", gba.agb.gba_cpu.read_SPSR());
			}
			else {
				ImGui::Text("SPSR: N/A");
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

			
			ImGui::Text("Mode: %s", mode_name);

			ImGui::EndTable();
		}
	}

	static void draw_sm83_disassembler() {
		//TODO(ches) do the GUI for this
	}

	void draw_window_disassembler() {
		ImGui::SetNextWindowPos(ImVec2(10, 30), ImGuiCond_Once);
		ImGui::SetNextWindowSize(ImVec2(500, 500), ImGuiCond_Once);

		if (ImGui::Begin("Disassembler", &g_gui_state.show_window_disassembler)) {
			const emulator::GBA& gba = brain::g_brain_data->gba;
			if (brain::g_brain_data->game_loaded) {
				if (gba.agb.cartridge_switch) {
					draw_sm83_disassembler();
				}
				else {
					draw_arm_disassembler();
				}
			}
			else {
				ImGui::Text("No game loaded, CPU offline");
			}

			ImGui::End();
		}
	}

	void initialize_disassembler() {
		disassembler_contents = (char*)calloc(CONTENTS_SIZE, sizeof(char));
	}
}
