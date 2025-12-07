#include "gui/gui.h"

#include <format>

#include "rendering/render_state.h"
#include "gui/key_binding.h"

namespace gui {
	const std::string TEXT_SAVE_TIME_MISSING = "----/--/-- --:--:--";
	constexpr bool SELECTED = true;
	constexpr bool NOT_SELECTED = false;
	constexpr bool ENABLED = true;
	constexpr bool DISABLED = false;
	constexpr const char* NO_SHORTCUT = nullptr;

	void draw_ui()
	{
		ImGui_ImplVulkan_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		draw_main_menu_bar();

		ImGui::ShowDemoWindow();

		ImGui::EndFrame();
	}

	void draw_main_menu_bar() {

		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				//TODO(ches) keybind
				if (ImGui::MenuItem("Open Gameboy Advance", NO_SHORTCUT, NOT_SELECTED, DISABLED))
				{
				}
				//TODO(ches) keybind
				if (ImGui::MenuItem("Open Gameboy", NO_SHORTCUT, NOT_SELECTED, DISABLED))
				{
				}

				if (ImGui::BeginMenu("Recent"))
				{
					for (int i = 1; i <= 10; i++) {
						//TODO(ches) keybinds
						if (ImGui::MenuItem(std::format("--- Ctrl+F{}", i, i).c_str(), NO_SHORTCUT, NOT_SELECTED, DISABLED))
						{
						}
					}
					ImGui::EndMenu();
				}
				ImGui::Separator();

				if (ImGui::BeginMenu("Save"))
				{
					if (ImGui::MenuItem("Oldest", NO_SHORTCUT, NOT_SELECTED, DISABLED))
					{
					}
					ImGui::Separator();

					for (int i = 1; i <= 10; i++) {
						//TODO(ches) keybinds

						if (ImGui::MenuItem(std::format("{} {} Shift+F{}", i,
							TEXT_SAVE_TIME_MISSING, i).c_str(), NO_SHORTCUT, NOT_SELECTED, DISABLED))
						{
						}
					}

					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("Load"))
				{
					if (ImGui::MenuItem("Most Recent", NO_SHORTCUT, NOT_SELECTED, DISABLED))
					{
					}

					ImGui::Separator();

					for (int i = 1; i <= 10; i++) {
						//TODO(ches) keybinds
						if (ImGui::MenuItem(std::format("{} {} F{}", i,
							TEXT_SAVE_TIME_MISSING, i).c_str(), NO_SHORTCUT, SELECTED, DISABLED))
						{
						}
					}
					ImGui::EndMenu();
				}
				ImGui::Separator();

				//TODO(ches) keybind
				if (ImGui::MenuItem("Pause", NO_SHORTCUT, NOT_SELECTED, DISABLED))
				{
				}
				//TODO(ches) keybind
				if (ImGui::MenuItem("Reset", NO_SHORTCUT, NOT_SELECTED, DISABLED))
				{
				}
				ImGui::Separator();
				
				if (ImGui::MenuItem("Close Game", NO_SHORTCUT, NOT_SELECTED, DISABLED))
				{
				}
				ImGui::Separator();

				if (ImGui::MenuItem("Screen Capture", NO_SHORTCUT, NOT_SELECTED, DISABLED))
				{
				}
				if (ImGui::MenuItem("ROM Information", NO_SHORTCUT, NOT_SELECTED, DISABLED))
				{
				}
				ImGui::Separator();

				ImGui::PushStyleColor(ImGuiCol_Text, RED);
				if (ImGui::MenuItem("Exit", NO_SHORTCUT, NOT_SELECTED, ENABLED))
				{
					render::g_render_state->close_requested = true;
				}
				ImGui::PopStyleColor();

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Options"))
			{
				if (ImGui::BeginMenu("Video"))
				{
					if (ImGui::MenuItem("VSync", NO_SHORTCUT, NOT_SELECTED, DISABLED))
					{
					}
					ImGui::Separator();
					if (ImGui::MenuItem("x1", NO_SHORTCUT, SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("x2", NO_SHORTCUT, NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("x3", NO_SHORTCUT, NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("x4", NO_SHORTCUT, NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("Full Screen...", NO_SHORTCUT, NOT_SELECTED, DISABLED))
					{
					}

					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("Frame Skip"))
				{
					if (ImGui::MenuItem("Automatic", NO_SHORTCUT, SELECTED, DISABLED))
					{
					}
					for (int i = 0; i <= 9; i++) {
						if (ImGui::MenuItem(std::format("{}", i).c_str(), NO_SHORTCUT, NOT_SELECTED, DISABLED))
						{
						}
					}
					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("Filter"))
				{
					if (ImGui::MenuItem("Normal", NO_SHORTCUT, SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("Bilinear", NO_SHORTCUT, NOT_SELECTED, DISABLED))
					{
					}
					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("Emulator"))
				{
					if (ImGui::MenuItem("Directories...", NO_SHORTCUT, NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("Pause When Inactive", NO_SHORTCUT, NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("Speed Up Toggle", NO_SHORTCUT, NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("Automatic IPS Patching", NO_SHORTCUT, NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("Real Time Clock", NO_SHORTCUT, NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("Rewind Interval...", NO_SHORTCUT, NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::BeginMenu("Show Speed"))
					{
						if (ImGui::MenuItem("None", NO_SHORTCUT, SELECTED, DISABLED))
						{
						}
						if (ImGui::MenuItem("Percentage", NO_SHORTCUT, NOT_SELECTED, DISABLED))
						{
						}
						if (ImGui::MenuItem("Detailed", NO_SHORTCUT, NOT_SELECTED, DISABLED))
						{
						}
						ImGui::Separator();

						if (ImGui::MenuItem("Transparent", NO_SHORTCUT, NOT_SELECTED, DISABLED))
						{
						}
						ImGui::EndMenu();
					}
					if (ImGui::BeginMenu("Save Type"))
					{
						if (ImGui::MenuItem("Automatic", NO_SHORTCUT, SELECTED, DISABLED))
						{
						}
						if (ImGui::MenuItem("EEPROM", NO_SHORTCUT, NOT_SELECTED, DISABLED))
						{
						}
						if (ImGui::MenuItem("SRAM", NO_SHORTCUT, NOT_SELECTED, DISABLED))
						{
						}
						if (ImGui::MenuItem("Flash", NO_SHORTCUT, NOT_SELECTED, DISABLED))
						{
						}
						if (ImGui::MenuItem("EEPROM+Sensor", NO_SHORTCUT, NOT_SELECTED, DISABLED))
						{
						}
						if (ImGui::MenuItem("None", NO_SHORTCUT, NOT_SELECTED, DISABLED))
						{
						}
						ImGui::Separator();

						if (ImGui::MenuItem("Flash 64K", NO_SHORTCUT, NOT_SELECTED, DISABLED))
						{
						}
						if (ImGui::MenuItem("Flash 128K", NO_SHORTCUT, SELECTED, DISABLED))
						{
						}
						ImGui::Separator();
						if (ImGui::MenuItem("Enhanced Detection", NO_SHORTCUT, NOT_SELECTED, DISABLED))
						{
						}
						ImGui::EndMenu();
					}
					ImGui::Separator();
					if (ImGui::MenuItem("Use BIOS File", NO_SHORTCUT, SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("Skip BIOS File", NO_SHORTCUT, NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("Select BIOS File...", NO_SHORTCUT, NOT_SELECTED, DISABLED))
					{
					}
					ImGui::Separator();
					if (ImGui::MenuItem("PNG Format", NO_SHORTCUT, SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("BMP Format", NO_SHORTCUT, NOT_SELECTED, DISABLED))
					{
					}

					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("Sound"))
				{
					if (ImGui::MenuItem("On", NO_SHORTCUT, SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("Mute", NO_SHORTCUT, NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("Off", NO_SHORTCUT, NOT_SELECTED, DISABLED))
					{
					}
					ImGui::Separator();
					if (ImGui::MenuItem("Echo", NO_SHORTCUT, NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("Low Pass Filter", NO_SHORTCUT, NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("Reverse Stereo", NO_SHORTCUT, NOT_SELECTED, DISABLED))
					{
					}
					ImGui::Separator();

					if (ImGui::MenuItem("Channel 1", NO_SHORTCUT, SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("Channel 2", NO_SHORTCUT, SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("Channel 3", NO_SHORTCUT, SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("Channel 4", NO_SHORTCUT, SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("Direct Sound A", NO_SHORTCUT, SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("Direct Sound B", NO_SHORTCUT, SELECTED, DISABLED))
					{
					}
					ImGui::Separator();
					if (ImGui::MenuItem("11 Khz", NO_SHORTCUT, NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("22 Khz", NO_SHORTCUT, SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("44 Khz", NO_SHORTCUT, NOT_SELECTED, DISABLED))
					{
					}
					ImGui::Separator();
					if (ImGui::BeginMenu("Volume"))
					{
						if (ImGui::MenuItem("0.25x", NO_SHORTCUT, NOT_SELECTED, DISABLED))
						{
						}
						if (ImGui::MenuItem("0.5x", NO_SHORTCUT, NOT_SELECTED, DISABLED))
						{
						}
						if (ImGui::MenuItem("1x", NO_SHORTCUT, SELECTED, DISABLED))
						{
						}
						if (ImGui::MenuItem("2x", NO_SHORTCUT, NOT_SELECTED, DISABLED))
						{
						}
						if (ImGui::MenuItem("3x", NO_SHORTCUT, NOT_SELECTED, DISABLED))
						{
						}
						if (ImGui::MenuItem("4x", NO_SHORTCUT, NOT_SELECTED, DISABLED))
						{
						}
						ImGui::EndMenu();
					}

					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("Gameboy"))
				{
					if (ImGui::MenuItem("Border", NO_SHORTCUT, NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("Border Automatic", NO_SHORTCUT, NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("Printer", NO_SHORTCUT, NOT_SELECTED, DISABLED))
					{
					}
					ImGui::Separator();
					if (ImGui::MenuItem("Automatic", NO_SHORTCUT, SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("GBA", NO_SHORTCUT, NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("GBC/CGB", NO_SHORTCUT, NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("SGB", NO_SHORTCUT, NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("SGB2", NO_SHORTCUT, NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("GB", NO_SHORTCUT, NOT_SELECTED, DISABLED))
					{
					}
					ImGui::Separator();

					if (ImGui::MenuItem("Real Colors", NO_SHORTCUT, SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("Gameboy Colors", NO_SHORTCUT, NOT_SELECTED, DISABLED))
					{
					}
					ImGui::Separator();

					if (ImGui::MenuItem("Colors...", NO_SHORTCUT, NOT_SELECTED, DISABLED))
					{
					}
					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("Joypad"))
				{
					if (ImGui::BeginMenu("Configure"))
					{
						if (ImGui::MenuItem("1...", NO_SHORTCUT, NOT_SELECTED, DISABLED))
						{
						}
						if (ImGui::MenuItem("2...", NO_SHORTCUT, NOT_SELECTED, DISABLED))
						{
						}
						if (ImGui::MenuItem("3...", NO_SHORTCUT, NOT_SELECTED, DISABLED))
						{
						}
						if (ImGui::MenuItem("4...", NO_SHORTCUT, NOT_SELECTED, DISABLED))
						{
						}
						ImGui::EndMenu();
					}
					if (ImGui::BeginMenu("Default Joypad"))
					{
						if (ImGui::MenuItem("1", NO_SHORTCUT, SELECTED, DISABLED))
						{
						}
						if (ImGui::MenuItem("2", NO_SHORTCUT, NOT_SELECTED, DISABLED))
						{
						}
						if (ImGui::MenuItem("3", NO_SHORTCUT, NOT_SELECTED, DISABLED))
						{
						}
						if (ImGui::MenuItem("4", NO_SHORTCUT, NOT_SELECTED, DISABLED))
						{
						}
						ImGui::EndMenu();
					}
					if (ImGui::MenuItem("Motion Controls...", NO_SHORTCUT, NOT_SELECTED, DISABLED))
					{
					}
					ImGui::Separator();

					if (ImGui::BeginMenu("Autofire"))
					{
						//TODO(ches) keybinds
						if (ImGui::MenuItem("A", NO_SHORTCUT, NOT_SELECTED, DISABLED))
						{
						}
						if (ImGui::MenuItem("B", NO_SHORTCUT, NOT_SELECTED, DISABLED))
						{
						}
						if (ImGui::MenuItem("L", NO_SHORTCUT, NOT_SELECTED, DISABLED))
						{
						}
						if (ImGui::MenuItem("R", NO_SHORTCUT, NOT_SELECTED, DISABLED))
						{
						}
						ImGui::EndMenu();
					}
					ImGui::EndMenu();
				}
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Cheats"))
			{
				//TODO(ches) keybind
				if (ImGui::MenuItem("Search For Cheats...", NO_SHORTCUT, NOT_SELECTED, DISABLED))
				{
				}
				if (ImGui::MenuItem("Cheat List...", NO_SHORTCUT, NOT_SELECTED, DISABLED))
				{
				}
				ImGui::Separator();
				if (ImGui::MenuItem("Automatically Save/Load Cheats", NO_SHORTCUT, NOT_SELECTED, DISABLED))
				{
				}
				if (ImGui::MenuItem("Disable Cheats", NO_SHORTCUT, NOT_SELECTED, DISABLED))
				{
				}
				if (ImGui::MenuItem("Load Cheat List...", NO_SHORTCUT, NOT_SELECTED, DISABLED))
				{
				}
				if (ImGui::MenuItem("Save Cheat List...", NO_SHORTCUT, NOT_SELECTED, DISABLED))
				{
				}
				 
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Tools"))
			{
				if (ImGui::MenuItem("Disassemble...", NO_SHORTCUT, NOT_SELECTED, DISABLED))
				{
				}
				if (ImGui::MenuItem("IO Viewer...", NO_SHORTCUT, NOT_SELECTED, DISABLED))
				{
				}
				if (ImGui::MenuItem("Map Viewer...", NO_SHORTCUT, NOT_SELECTED, DISABLED))
				{
				}
				if (ImGui::MenuItem("Memory Viewer...", NO_SHORTCUT, NOT_SELECTED, DISABLED))
				{
				}
				if (ImGui::MenuItem("OAM (Sprite) Viewer...", NO_SHORTCUT, NOT_SELECTED, DISABLED))
				{
				}
				if (ImGui::MenuItem("Palette Viewer...", NO_SHORTCUT, NOT_SELECTED, DISABLED))
				{
				}
				if (ImGui::MenuItem("Tile Viewer...", NO_SHORTCUT, NOT_SELECTED, DISABLED))
				{
				}
				ImGui::Separator();
				//TODO(ches) keybind
				if (ImGui::MenuItem("Next Frame", NO_SHORTCUT, NOT_SELECTED, DISABLED))
				{
				}
				if (ImGui::BeginMenu("Debugger"))
				{
					if (ImGui::MenuItem("Wait For Connection...", NO_SHORTCUT, NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("Load And Wait...", NO_SHORTCUT, NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("Break Into Debugger", NO_SHORTCUT, NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("Disconnect", NO_SHORTCUT, NOT_SELECTED, DISABLED))
					{
					}
					ImGui::EndMenu();
				}
				ImGui::Separator();

				if (ImGui::BeginMenu("Record"))
				{
					if (ImGui::MenuItem("Start Sound Recording...", NO_SHORTCUT, NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("Stop Sound Recording", NO_SHORTCUT, NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("Start AVI Recording...", NO_SHORTCUT, NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("Stop AVI Recording", NO_SHORTCUT, NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("Start Movie Recording...", NO_SHORTCUT, NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("Stop Movie Recording", NO_SHORTCUT, NOT_SELECTED, DISABLED))
					{
					}

					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("Play"))
				{
					if (ImGui::MenuItem("Start Playing Movie...", NO_SHORTCUT, NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("Stop Playing Movie", NO_SHORTCUT, NOT_SELECTED, DISABLED))
					{
					}

					ImGui::EndMenu();
				}
				ImGui::Separator();
				//TODO(ches) keybind
				if (ImGui::MenuItem("Rewind", NO_SHORTCUT, NOT_SELECTED, DISABLED))
				{
				}
				if (ImGui::MenuItem("Keybinds...", NO_SHORTCUT, NOT_SELECTED, DISABLED))
				{
				}

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Help"))
			{
				if (ImGui::MenuItem("Bug Report Details", NO_SHORTCUT, NOT_SELECTED, DISABLED))
				{
				}
				if (ImGui::MenuItem("MIT License (website)...", NO_SHORTCUT, NOT_SELECTED, DISABLED))
				{
				}
				ImGui::Separator();
				if (ImGui::MenuItem("About...", NO_SHORTCUT, NOT_SELECTED, DISABLED))
				{
				}
				
				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();
		}
	}
}