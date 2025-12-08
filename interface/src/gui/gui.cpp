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
				if (ImGui::MenuItem("Open Gameboy Advance", get_binding_text(Command::FileOpenGameboyAdvance), NOT_SELECTED, DISABLED))
				{
				}
				if (ImGui::MenuItem("Open Gameboy", get_binding_text(Command::FileOpenGameboy), NOT_SELECTED, DISABLED))
				{
				}

				if (ImGui::BeginMenu("Recent"))
				{
					if (ImGui::MenuItem("(empty slot 1)", get_binding_text(Command::FileRecent01), NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("(empty slot 2)", get_binding_text(Command::FileRecent02), NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("(empty slot 3)", get_binding_text(Command::FileRecent03), NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("(empty slot 4)", get_binding_text(Command::FileRecent04), NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("(empty slot 5)", get_binding_text(Command::FileRecent05), NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("(empty slot 6)", get_binding_text(Command::FileRecent06), NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("(empty slot 7)", get_binding_text(Command::FileRecent07), NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("(empty slot 8)", get_binding_text(Command::FileRecent08), NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("(empty slot 9)", get_binding_text(Command::FileRecent09), NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("(empty slot 10)", get_binding_text(Command::FileRecent10), NOT_SELECTED, DISABLED))
					{
					}

					ImGui::EndMenu();
				}
				ImGui::Separator();

				if (ImGui::BeginMenu("Save"))
				{
					if (ImGui::MenuItem("Oldest", get_binding_text(Command::FileSave), NOT_SELECTED, DISABLED))
					{
					}
					ImGui::Separator();

					if (ImGui::MenuItem(std::format("1 {}", TEXT_SAVE_TIME_MISSING).c_str(), get_binding_text(Command::FileSaveGame01), NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem(std::format("2 {}", TEXT_SAVE_TIME_MISSING).c_str(), get_binding_text(Command::FileSaveGame02), NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem(std::format("3 {}", TEXT_SAVE_TIME_MISSING).c_str(), get_binding_text(Command::FileSaveGame03), NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem(std::format("4 {}", TEXT_SAVE_TIME_MISSING).c_str(), get_binding_text(Command::FileSaveGame04), NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem(std::format("5 {}", TEXT_SAVE_TIME_MISSING).c_str(), get_binding_text(Command::FileSaveGame05), NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem(std::format("6 {}", TEXT_SAVE_TIME_MISSING).c_str(), get_binding_text(Command::FileSaveGame06), NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem(std::format("7 {}", TEXT_SAVE_TIME_MISSING).c_str(), get_binding_text(Command::FileSaveGame07), NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem(std::format("8 {}", TEXT_SAVE_TIME_MISSING).c_str(), get_binding_text(Command::FileSaveGame08), NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem(std::format("9 {}", TEXT_SAVE_TIME_MISSING).c_str(), get_binding_text(Command::FileSaveGame09), NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem(std::format("10 {}", TEXT_SAVE_TIME_MISSING).c_str(), get_binding_text(Command::FileSaveGame10), NOT_SELECTED, DISABLED))
					{
					}

					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("Load"))
				{
					if (ImGui::MenuItem("Most Recent", get_binding_text(Command::FileLoad), NOT_SELECTED, DISABLED))
					{
					}

					ImGui::Separator();
					if (ImGui::MenuItem(std::format("1 {}", TEXT_SAVE_TIME_MISSING).c_str(), get_binding_text(Command::FileLoadGame01), NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem(std::format("2 {}", TEXT_SAVE_TIME_MISSING).c_str(), get_binding_text(Command::FileLoadGame02), NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem(std::format("3 {}", TEXT_SAVE_TIME_MISSING).c_str(), get_binding_text(Command::FileLoadGame03), NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem(std::format("4 {}", TEXT_SAVE_TIME_MISSING).c_str(), get_binding_text(Command::FileLoadGame04), NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem(std::format("5 {}", TEXT_SAVE_TIME_MISSING).c_str(), get_binding_text(Command::FileLoadGame05), NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem(std::format("6 {}", TEXT_SAVE_TIME_MISSING).c_str(), get_binding_text(Command::FileLoadGame06), NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem(std::format("7 {}", TEXT_SAVE_TIME_MISSING).c_str(), get_binding_text(Command::FileLoadGame07), NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem(std::format("8 {}", TEXT_SAVE_TIME_MISSING).c_str(), get_binding_text(Command::FileLoadGame08), NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem(std::format("9 {}", TEXT_SAVE_TIME_MISSING).c_str(), get_binding_text(Command::FileLoadGame09), NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem(std::format("10 {}", TEXT_SAVE_TIME_MISSING).c_str(), get_binding_text(Command::FileLoadGame10), NOT_SELECTED, DISABLED))
					{
					}
					ImGui::EndMenu();
				}
				ImGui::Separator();

				if (ImGui::MenuItem("Pause", get_binding_text(Command::FilePause), NOT_SELECTED, DISABLED))
				{
				}
				if (ImGui::MenuItem("Reset", get_binding_text(Command::FileReset), NOT_SELECTED, DISABLED))
				{
				}
				ImGui::Separator();
				
				if (ImGui::MenuItem("Close Game", get_binding_text(Command::FileClose), NOT_SELECTED, DISABLED))
				{
				}
				ImGui::Separator();

				if (ImGui::MenuItem("Screen Capture", get_binding_text(Command::FileScreenCapture), NOT_SELECTED, DISABLED))
				{
				}
				if (ImGui::MenuItem("ROM Information", get_binding_text(Command::FileRomInformation), NOT_SELECTED, DISABLED))
				{
				}
				if (ImGui::MenuItem("Toggle Menu", get_binding_text(Command::FileToggleMenu), NOT_SELECTED, DISABLED))
				{
				}
				ImGui::Separator();

				ImGui::PushStyleColor(ImGuiCol_Text, RED);
				if (ImGui::MenuItem("Exit", get_binding_text(Command::FileExit), NOT_SELECTED, ENABLED))
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
					if (ImGui::MenuItem("VSync", get_binding_text(Command::OptionsVideoVSync), NOT_SELECTED, DISABLED))
					{
					}
					ImGui::Separator();
					if (ImGui::MenuItem("x1", get_binding_text(Command::OptionsVideoX1), SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("x2", get_binding_text(Command::OptionsVideoX2), NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("x3", get_binding_text(Command::OptionsVideoX3), NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("x4", get_binding_text(Command::OptionsVideoX4), NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("Full Screen...", get_binding_text(Command::OptionsVideoFullScreen), NOT_SELECTED, DISABLED))
					{
					}

					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("Frame Skip"))
				{
					if (ImGui::MenuItem("Automatic", get_binding_text(Command::OptionsFrameSkipAutomatic), SELECTED, DISABLED))
					{
					}

					if (ImGui::MenuItem("0", get_binding_text(Command::OptionsFrameSkip0), NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("1", get_binding_text(Command::OptionsFrameSkip1), NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("2", get_binding_text(Command::OptionsFrameSkip2), NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("3", get_binding_text(Command::OptionsFrameSkip3), NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("4", get_binding_text(Command::OptionsFrameSkip4), NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("5", get_binding_text(Command::OptionsFrameSkip5), NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("6", get_binding_text(Command::OptionsFrameSkip6), NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("7", get_binding_text(Command::OptionsFrameSkip7), NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("8", get_binding_text(Command::OptionsFrameSkip8), NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("9", get_binding_text(Command::OptionsFrameSkip9), NOT_SELECTED, DISABLED))
					{
					}

					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("Filter"))
				{
					if (ImGui::MenuItem("Normal", get_binding_text(Command::OptionsFilterNormal), SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("Bilinear", get_binding_text(Command::OptionsFilterBilinear), NOT_SELECTED, DISABLED))
					{
					}
					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("Emulator"))
				{
					if (ImGui::MenuItem("Directories...", get_binding_text(Command::OptionsEmulatorDirectories), NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("Pause When Inactive", get_binding_text(Command::OptionsEmulatorPauseWhenInactive), NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("Speed Up Toggle", get_binding_text(Command::OptionsEmulatorSpeedToggle), NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("Automatic IPS Patching", get_binding_text(Command::OptionsEmulatorAutomaticIPS), NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("Real Time Clock", get_binding_text(Command::OptionsEmulatorRealTimeClock), NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("Rewind Interval...", get_binding_text(Command::OptionsEmulatorRewindInterval), NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::BeginMenu("Show Speed"))
					{
						if (ImGui::MenuItem("None", get_binding_text(Command::OptionsEmulatorSpeedNone), SELECTED, DISABLED))
						{
						}
						if (ImGui::MenuItem("Percentage", get_binding_text(Command::OptionsEmulatorSpeedPercentage), NOT_SELECTED, DISABLED))
						{
						}
						if (ImGui::MenuItem("Detailed", get_binding_text(Command::OptionsEmulatorSpeedDetailed), NOT_SELECTED, DISABLED))
						{
						}
						ImGui::Separator();

						if (ImGui::MenuItem("Transparent", get_binding_text(Command::OptionsEmulatorSpeedTransparent), NOT_SELECTED, DISABLED))
						{
						}
						ImGui::EndMenu();
					}
					if (ImGui::BeginMenu("Save Type"))
					{
						if (ImGui::MenuItem("Automatic", get_binding_text(Command::OptionsEmulatorSaveAutomatic), SELECTED, DISABLED))
						{
						}
						if (ImGui::MenuItem("EEPROM", get_binding_text(Command::OptionsEmulatorSaveEEPROM), NOT_SELECTED, DISABLED))
						{
						}
						if (ImGui::MenuItem("SRAM", get_binding_text(Command::OptionsEmulatorSaveSRAM), NOT_SELECTED, DISABLED))
						{
						}
						if (ImGui::MenuItem("Flash", get_binding_text(Command::OptionsEmulatorSaveFlash), NOT_SELECTED, DISABLED))
						{
						}
						if (ImGui::MenuItem("EEPROM+Sensor", get_binding_text(Command::OptionsEmulatorSaveEEPROMAndSensor), NOT_SELECTED, DISABLED))
						{
						}
						if (ImGui::MenuItem("None", get_binding_text(Command::OptionsEmulatorSaveNone), NOT_SELECTED, DISABLED))
						{
						}
						ImGui::Separator();

						if (ImGui::MenuItem("Flash 64K", get_binding_text(Command::OptionsEmulatorSaveFlash64K), NOT_SELECTED, DISABLED))
						{
						}
						if (ImGui::MenuItem("Flash 128K", get_binding_text(Command::OptionsEmulatorSaveFlash128K), SELECTED, DISABLED))
						{
						}
						ImGui::Separator();
						if (ImGui::MenuItem("Enhanced Detection", get_binding_text(Command::OptionsEmulatorSaveEnhancedDetection), NOT_SELECTED, DISABLED))
						{
						}
						ImGui::EndMenu();
					}
					ImGui::Separator();
					if (ImGui::MenuItem("Use BIOS File", get_binding_text(Command::OptionsEmulatorUseBIOSFile), SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("Skip BIOS File", get_binding_text(Command::OptionsEmulatorSkipBIOSFile), NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("Select BIOS File...", get_binding_text(Command::OptionsEmulatorSelectBIOSFile), NOT_SELECTED, DISABLED))
					{
					}
					ImGui::Separator();
					if (ImGui::MenuItem("PNG Format", get_binding_text(Command::OptionsEmulatorPNGFormat), SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("BMP Format", get_binding_text(Command::OptionsEmulatorBMPFormat), NOT_SELECTED, DISABLED))
					{
					}

					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("Sound"))
				{
					if (ImGui::MenuItem("On", get_binding_text(Command::OptionsSoundOn), SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("Mute", get_binding_text(Command::OptionsSoundMute), NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("Off", get_binding_text(Command::OptionsSoundOff), NOT_SELECTED, DISABLED))
					{
					}
					ImGui::Separator();
					if (ImGui::MenuItem("Echo", get_binding_text(Command::OptionsSoundEcho), NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("Low Pass Filter", get_binding_text(Command::OptionsSoundLowPass), NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("Reverse Stereo", get_binding_text(Command::OptionsSoundReverseStereo), NOT_SELECTED, DISABLED))
					{
					}
					ImGui::Separator();

					if (ImGui::MenuItem("Channel 1", get_binding_text(Command::OptionsSoundChannel1), SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("Channel 2", get_binding_text(Command::OptionsSoundChannel2), SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("Channel 3", get_binding_text(Command::OptionsSoundChannel3), SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("Channel 4", get_binding_text(Command::OptionsSoundChannel4), SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("Direct Sound A", get_binding_text(Command::OptionsSoundDirectSoundA), SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("Direct Sound B", get_binding_text(Command::OptionsSoundDirectSoundB), SELECTED, DISABLED))
					{
					}
					ImGui::Separator();
					if (ImGui::MenuItem("11 Khz", get_binding_text(Command::OptionsSound11Khz), NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("22 Khz", get_binding_text(Command::OptionsSound22Khz), SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("44 Khz", get_binding_text(Command::OptionsSound44Khz), NOT_SELECTED, DISABLED))
					{
					}
					ImGui::Separator();
					if (ImGui::BeginMenu("Volume"))
					{
						if (ImGui::MenuItem("0.25x", get_binding_text(Command::OptionsSoundVolumeQuarter), NOT_SELECTED, DISABLED))
						{
						}
						if (ImGui::MenuItem("0.5x", get_binding_text(Command::OptionsSoundVolumeHalf), NOT_SELECTED, DISABLED))
						{
						}
						if (ImGui::MenuItem("1x", get_binding_text(Command::OptionsSoundVolume1x), SELECTED, DISABLED))
						{
						}
						if (ImGui::MenuItem("2x", get_binding_text(Command::OptionsSoundVolume2x), NOT_SELECTED, DISABLED))
						{
						}
						if (ImGui::MenuItem("3x", get_binding_text(Command::OptionsSoundVolume3x), NOT_SELECTED, DISABLED))
						{
						}
						if (ImGui::MenuItem("4x", get_binding_text(Command::OptionsSoundVolume4x), NOT_SELECTED, DISABLED))
						{
						}
						ImGui::EndMenu();
					}

					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("Gameboy"))
				{
					if (ImGui::MenuItem("Border", get_binding_text(Command::OptionsGameboyBorder), NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("Border Automatic", get_binding_text(Command::OptionsGameboyBorderAutomatic), NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("Printer", get_binding_text(Command::OptionsGameboyPrinter), NOT_SELECTED, DISABLED))
					{
					}
					ImGui::Separator();
					if (ImGui::MenuItem("Automatic", get_binding_text(Command::OptionsGameboyAutomatic), SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("GBA", get_binding_text(Command::OptionsGameboyGBA), NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("GBC/CGB", get_binding_text(Command::OptionsGameboyGBC), NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("SGB", get_binding_text(Command::OptionsGameboySGB), NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("SGB2", get_binding_text(Command::OptionsGameboySGB2), NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("GB", get_binding_text(Command::OptionsGameboyGB), NOT_SELECTED, DISABLED))
					{
					}
					ImGui::Separator();

					if (ImGui::MenuItem("Real Colors", get_binding_text(Command::OptionsGameboyRealColors), SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("Gameboy Colors", get_binding_text(Command::OptionsGameboyGameboyColors), NOT_SELECTED, DISABLED))
					{
					}
					ImGui::Separator();

					if (ImGui::MenuItem("Colors...", get_binding_text(Command::OptionsGameboyColors), NOT_SELECTED, DISABLED))
					{
					}
					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("Controls"))
				{
					if (ImGui::BeginMenu("Autofire"))
					{
						if (ImGui::MenuItem("A", get_binding_text(Command::OptionsControlsAutofireA), NOT_SELECTED, DISABLED))
						{
						}
						if (ImGui::MenuItem("B", get_binding_text(Command::OptionsControlsAutofireB), NOT_SELECTED, DISABLED))
						{
						}
						if (ImGui::MenuItem("L", get_binding_text(Command::OptionsControlsAutofireL), NOT_SELECTED, DISABLED))
						{
						}
						if (ImGui::MenuItem("R", get_binding_text(Command::OptionsControlsAutofireR), NOT_SELECTED, DISABLED))
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
				if (ImGui::MenuItem("Search For Cheats...", get_binding_text(Command::CheatsSearch), NOT_SELECTED, DISABLED))
				{
				}
				if (ImGui::MenuItem("Cheat List...", get_binding_text(Command::CheatsList), NOT_SELECTED, DISABLED))
				{
				}
				ImGui::Separator();
				if (ImGui::MenuItem("Automatically Save/Load Cheats", get_binding_text(Command::CheatsAutomaticallySaveAndLoad), NOT_SELECTED, DISABLED))
				{
				}
				if (ImGui::MenuItem("Disable Cheats", get_binding_text(Command::CheatsDisable), NOT_SELECTED, DISABLED))
				{
				}
				if (ImGui::MenuItem("Load Cheat List...", get_binding_text(Command::CheatsLoad), NOT_SELECTED, DISABLED))
				{
				}
				if (ImGui::MenuItem("Save Cheat List...", get_binding_text(Command::CheatsSave), NOT_SELECTED, DISABLED))
				{
				}
				 
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Tools"))
			{
				if (ImGui::MenuItem("Disassemble...", get_binding_text(Command::ToolsDisassemble), NOT_SELECTED, DISABLED))
				{
				}
				if (ImGui::MenuItem("IO Viewer...", get_binding_text(Command::ToolsIO), NOT_SELECTED, DISABLED))
				{
				}
				if (ImGui::MenuItem("Map Viewer...", get_binding_text(Command::ToolsMap), NOT_SELECTED, DISABLED))
				{
				}
				if (ImGui::MenuItem("Memory Viewer...", get_binding_text(Command::ToolsMemory), NOT_SELECTED, DISABLED))
				{
				}
				if (ImGui::MenuItem("OAM (Sprite) Viewer...", get_binding_text(Command::ToolsOAM), NOT_SELECTED, DISABLED))
				{
				}
				if (ImGui::MenuItem("Palette Viewer...", get_binding_text(Command::ToolsPalette), NOT_SELECTED, DISABLED))
				{
				}
				if (ImGui::MenuItem("Tile Viewer...", get_binding_text(Command::ToolsTile), NOT_SELECTED, DISABLED))
				{
				}
				ImGui::Separator();

				if (ImGui::MenuItem("Next Frame", get_binding_text(Command::ToolsNextFrame), NOT_SELECTED, DISABLED))
				{
				}
				if (ImGui::BeginMenu("Debugger"))
				{
					if (ImGui::MenuItem("Wait For Connection...", get_binding_text(Command::ToolsDebuggerWait), NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("Load And Wait...", get_binding_text(Command::ToolsDebuggerLoadAndWait), NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("Break Into Debugger", get_binding_text(Command::ToolsDebuggerBreak), NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("Disconnect", get_binding_text(Command::ToolsDebuggerDisconnect), NOT_SELECTED, DISABLED))
					{
					}
					ImGui::EndMenu();
				}
				ImGui::Separator();

				if (ImGui::BeginMenu("Record"))
				{
					if (ImGui::MenuItem("Start Sound Recording...", get_binding_text(Command::ToolsRecordSoundStart), NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("Stop Sound Recording", get_binding_text(Command::ToolsRecordSoundStop), NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("Start AVI Recording...", get_binding_text(Command::ToolsRecordAVIStart), NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("Stop AVI Recording", get_binding_text(Command::ToolsRecordAVIStop), NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("Start Movie Recording...", get_binding_text(Command::ToolsRecordMovieStart), NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("Stop Movie Recording", get_binding_text(Command::ToolsRecordMovieStop), NOT_SELECTED, DISABLED))
					{
					}

					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("Play"))
				{
					if (ImGui::MenuItem("Start Playing Movie...", get_binding_text(Command::ToolsPlayMovieStart), NOT_SELECTED, DISABLED))
					{
					}
					if (ImGui::MenuItem("Stop Playing Movie", get_binding_text(Command::ToolsPlayMovieStop), NOT_SELECTED, DISABLED))
					{
					}

					ImGui::EndMenu();
				}
				ImGui::Separator();

				if (ImGui::MenuItem("Rewind", get_binding_text(Command::ToolsRewind), NOT_SELECTED, DISABLED))
				{
				}
				if (ImGui::MenuItem("Keybinds...", get_binding_text(Command::ToolsKeybinds), NOT_SELECTED, DISABLED))
				{
				}

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Help"))
			{
				if (ImGui::MenuItem("Bug Report Details", get_binding_text(Command::HelpBugReport), NOT_SELECTED, DISABLED))
				{
				}
				if (ImGui::MenuItem("MIT License (website)...", get_binding_text(Command::HelpLicense), NOT_SELECTED, DISABLED))
				{
				}
				ImGui::Separator();
				if (ImGui::MenuItem("About...", get_binding_text(Command::HelpAbout), NOT_SELECTED, DISABLED))
				{
				}
				
				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();
		}
	}
}