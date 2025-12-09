#include "gui/gui.h"

#include <format>

#include "brain/brain.h"
#include "rendering/render_state.h"
#include "gui/key_binding.h"
#include "gui/settings.h"

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
					brain::g_brain_data->command_queue.add(Command::FileOpenGameboyAdvance);
				}
				if (ImGui::MenuItem("Open Gameboy", get_binding_text(Command::FileOpenGameboy), NOT_SELECTED, DISABLED))
				{
					brain::g_brain_data->command_queue.add(Command::FileOpenGameboy);
				}

				if (ImGui::BeginMenu("Recent"))
				{
					if (ImGui::MenuItem("(empty slot 1)", get_binding_text(Command::FileRecent01), NOT_SELECTED, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::FileRecent01);
					}
					if (ImGui::MenuItem("(empty slot 2)", get_binding_text(Command::FileRecent02), NOT_SELECTED, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::FileRecent02);
					}
					if (ImGui::MenuItem("(empty slot 3)", get_binding_text(Command::FileRecent03), NOT_SELECTED, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::FileRecent03);
					}
					if (ImGui::MenuItem("(empty slot 4)", get_binding_text(Command::FileRecent04), NOT_SELECTED, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::FileRecent04);
					}
					if (ImGui::MenuItem("(empty slot 5)", get_binding_text(Command::FileRecent05), NOT_SELECTED, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::FileRecent05);
					}
					if (ImGui::MenuItem("(empty slot 6)", get_binding_text(Command::FileRecent06), NOT_SELECTED, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::FileRecent06);
					}
					if (ImGui::MenuItem("(empty slot 7)", get_binding_text(Command::FileRecent07), NOT_SELECTED, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::FileRecent07);
					}
					if (ImGui::MenuItem("(empty slot 8)", get_binding_text(Command::FileRecent08), NOT_SELECTED, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::FileRecent08);
					}
					if (ImGui::MenuItem("(empty slot 9)", get_binding_text(Command::FileRecent09), NOT_SELECTED, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::FileRecent09);
					}
					if (ImGui::MenuItem("(empty slot 10)", get_binding_text(Command::FileRecent10), NOT_SELECTED, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::FileRecent10);
					}

					ImGui::EndMenu();
				}
				ImGui::Separator();

				if (ImGui::BeginMenu("Save"))
				{
					if (ImGui::MenuItem("Oldest", get_binding_text(Command::FileSave), NOT_SELECTED, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::FileSave);
					}
					ImGui::Separator();

					if (ImGui::MenuItem(std::format("1 {}", TEXT_SAVE_TIME_MISSING).c_str(), get_binding_text(Command::FileSaveGame01), NOT_SELECTED, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::FileSaveGame01);
					}
					if (ImGui::MenuItem(std::format("2 {}", TEXT_SAVE_TIME_MISSING).c_str(), get_binding_text(Command::FileSaveGame02), NOT_SELECTED, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::FileSaveGame02);
					}
					if (ImGui::MenuItem(std::format("3 {}", TEXT_SAVE_TIME_MISSING).c_str(), get_binding_text(Command::FileSaveGame03), NOT_SELECTED, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::FileSaveGame03);
					}
					if (ImGui::MenuItem(std::format("4 {}", TEXT_SAVE_TIME_MISSING).c_str(), get_binding_text(Command::FileSaveGame04), NOT_SELECTED, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::FileSaveGame04);
					}
					if (ImGui::MenuItem(std::format("5 {}", TEXT_SAVE_TIME_MISSING).c_str(), get_binding_text(Command::FileSaveGame05), NOT_SELECTED, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::FileSaveGame05);
					}
					if (ImGui::MenuItem(std::format("6 {}", TEXT_SAVE_TIME_MISSING).c_str(), get_binding_text(Command::FileSaveGame06), NOT_SELECTED, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::FileSaveGame06);
					}
					if (ImGui::MenuItem(std::format("7 {}", TEXT_SAVE_TIME_MISSING).c_str(), get_binding_text(Command::FileSaveGame07), NOT_SELECTED, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::FileSaveGame07);
					}
					if (ImGui::MenuItem(std::format("8 {}", TEXT_SAVE_TIME_MISSING).c_str(), get_binding_text(Command::FileSaveGame08), NOT_SELECTED, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::FileSaveGame08);
					}
					if (ImGui::MenuItem(std::format("9 {}", TEXT_SAVE_TIME_MISSING).c_str(), get_binding_text(Command::FileSaveGame09), NOT_SELECTED, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::FileSaveGame09);
					}
					if (ImGui::MenuItem(std::format("10 {}", TEXT_SAVE_TIME_MISSING).c_str(), get_binding_text(Command::FileSaveGame10), NOT_SELECTED, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::FileSaveGame10);
					}

					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("Load"))
				{
					if (ImGui::MenuItem("Most Recent", get_binding_text(Command::FileLoad), NOT_SELECTED, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::FileLoad);
					}

					ImGui::Separator();
					if (ImGui::MenuItem(std::format("1 {}", TEXT_SAVE_TIME_MISSING).c_str(), get_binding_text(Command::FileLoadGame01), NOT_SELECTED, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::FileLoadGame01);
					}
					if (ImGui::MenuItem(std::format("2 {}", TEXT_SAVE_TIME_MISSING).c_str(), get_binding_text(Command::FileLoadGame02), NOT_SELECTED, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::FileLoadGame02);
					}
					if (ImGui::MenuItem(std::format("3 {}", TEXT_SAVE_TIME_MISSING).c_str(), get_binding_text(Command::FileLoadGame03), NOT_SELECTED, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::FileLoadGame03);
					}
					if (ImGui::MenuItem(std::format("4 {}", TEXT_SAVE_TIME_MISSING).c_str(), get_binding_text(Command::FileLoadGame04), NOT_SELECTED, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::FileLoadGame04);
					}
					if (ImGui::MenuItem(std::format("5 {}", TEXT_SAVE_TIME_MISSING).c_str(), get_binding_text(Command::FileLoadGame05), NOT_SELECTED, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::FileLoadGame05);
					}
					if (ImGui::MenuItem(std::format("6 {}", TEXT_SAVE_TIME_MISSING).c_str(), get_binding_text(Command::FileLoadGame06), NOT_SELECTED, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::FileLoadGame06);
					}
					if (ImGui::MenuItem(std::format("7 {}", TEXT_SAVE_TIME_MISSING).c_str(), get_binding_text(Command::FileLoadGame07), NOT_SELECTED, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::FileLoadGame07);
					}
					if (ImGui::MenuItem(std::format("8 {}", TEXT_SAVE_TIME_MISSING).c_str(), get_binding_text(Command::FileLoadGame08), NOT_SELECTED, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::FileLoadGame08);
					}
					if (ImGui::MenuItem(std::format("9 {}", TEXT_SAVE_TIME_MISSING).c_str(), get_binding_text(Command::FileLoadGame09), NOT_SELECTED, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::FileLoadGame09);
					}
					if (ImGui::MenuItem(std::format("10 {}", TEXT_SAVE_TIME_MISSING).c_str(), get_binding_text(Command::FileLoadGame10), NOT_SELECTED, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::FileLoadGame10);
					}
					ImGui::EndMenu();
				}
				ImGui::Separator();

				if (ImGui::MenuItem("Pause", get_binding_text(Command::FilePause), NOT_SELECTED, DISABLED))
				{
					brain::g_brain_data->command_queue.add(Command::FilePause);
				}
				if (ImGui::MenuItem("Reset", get_binding_text(Command::FileReset), NOT_SELECTED, DISABLED))
				{
					brain::g_brain_data->command_queue.add(Command::FileReset);
				}
				ImGui::Separator();
				
				if (ImGui::MenuItem("Close Game", get_binding_text(Command::FileClose), NOT_SELECTED, DISABLED))
				{
					brain::g_brain_data->command_queue.add(Command::FileClose);
				}
				ImGui::Separator();

				if (ImGui::MenuItem("Screen Capture", get_binding_text(Command::FileScreenCapture), NOT_SELECTED, DISABLED))
				{
					brain::g_brain_data->command_queue.add(Command::FileScreenCapture);
				}
				if (ImGui::MenuItem("ROM Information", get_binding_text(Command::FileRomInformation), NOT_SELECTED, DISABLED))
				{
					brain::g_brain_data->command_queue.add(Command::FileScreenCapture);
				}
				if (ImGui::MenuItem("Toggle Menu", get_binding_text(Command::FileToggleMenu), NOT_SELECTED, 
					Settings::Options::Video::Size::FULL_SCREEN == g_settings.options.video.size))
				{
					brain::g_brain_data->command_queue.add(Command::FileToggleMenu);
				}
				ImGui::Separator();

				ImGui::PushStyleColor(ImGuiCol_Text, RED);
				if (ImGui::MenuItem("Exit", get_binding_text(Command::FileExit), NOT_SELECTED, ENABLED))
				{
					brain::g_brain_data->command_queue.add(Command::FileExit);
					//TODO(ches) do this in the command handing
					render::g_render_state->close_requested = true;
				}
				ImGui::PopStyleColor();

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Options"))
			{
				if (ImGui::BeginMenu("Video"))
				{
					if (ImGui::MenuItem("VSync", get_binding_text(Command::OptionsVideoVSync), 
						g_settings.options.video.vsync, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::OptionsVideoVSync);
					}
					ImGui::Separator();
					if (ImGui::MenuItem("x1", get_binding_text(Command::OptionsVideoX1), 
						Settings::Options::Video::Size::X1 == g_settings.options.video.size, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::OptionsVideoX1);
					}
					if (ImGui::MenuItem("x2", get_binding_text(Command::OptionsVideoX2),
						Settings::Options::Video::Size::X2 == g_settings.options.video.size, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::OptionsVideoX2);
					}
					if (ImGui::MenuItem("x3", get_binding_text(Command::OptionsVideoX3), 
						Settings::Options::Video::Size::X3 == g_settings.options.video.size, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::OptionsVideoX3);
					}
					if (ImGui::MenuItem("x4", get_binding_text(Command::OptionsVideoX4), 
						Settings::Options::Video::Size::X4 == g_settings.options.video.size, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::OptionsVideoX4);
					}
					if (ImGui::MenuItem("Full Screen...", get_binding_text(Command::OptionsVideoFullScreen), 
						Settings::Options::Video::Size::FULL_SCREEN == g_settings.options.video.size, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::OptionsVideoFullScreen);
					}

					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("Frame Skip"))
				{
					if (ImGui::MenuItem("Automatic", get_binding_text(Command::OptionsFrameSkipAutomatic), 
						Settings::Options::FrameSkip::AUTOMATIC == g_settings.options.frame_skip, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::OptionsFrameSkipAutomatic);
					}

					if (ImGui::MenuItem("0", get_binding_text(Command::OptionsFrameSkip0), Settings::Options::FrameSkip::X0 == g_settings.options.frame_skip, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::OptionsFrameSkip0);
					}
					if (ImGui::MenuItem("1", get_binding_text(Command::OptionsFrameSkip1), Settings::Options::FrameSkip::X1 == g_settings.options.frame_skip, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::OptionsFrameSkip1);
					}
					if (ImGui::MenuItem("2", get_binding_text(Command::OptionsFrameSkip2), Settings::Options::FrameSkip::X2 == g_settings.options.frame_skip, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::OptionsFrameSkip2);
					}
					if (ImGui::MenuItem("3", get_binding_text(Command::OptionsFrameSkip3), Settings::Options::FrameSkip::X3 == g_settings.options.frame_skip, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::OptionsFrameSkip3);
					}
					if (ImGui::MenuItem("4", get_binding_text(Command::OptionsFrameSkip4), Settings::Options::FrameSkip::X4 == g_settings.options.frame_skip, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::OptionsFrameSkip4);
					}
					if (ImGui::MenuItem("5", get_binding_text(Command::OptionsFrameSkip5), Settings::Options::FrameSkip::X5 == g_settings.options.frame_skip, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::OptionsFrameSkip5);
					}
					if (ImGui::MenuItem("6", get_binding_text(Command::OptionsFrameSkip6), Settings::Options::FrameSkip::X6 == g_settings.options.frame_skip, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::OptionsFrameSkip6);
					}
					if (ImGui::MenuItem("7", get_binding_text(Command::OptionsFrameSkip7), Settings::Options::FrameSkip::X7 == g_settings.options.frame_skip, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::OptionsFrameSkip7);
					}
					if (ImGui::MenuItem("8", get_binding_text(Command::OptionsFrameSkip8), Settings::Options::FrameSkip::X8 == g_settings.options.frame_skip, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::OptionsFrameSkip8);
					}
					if (ImGui::MenuItem("9", get_binding_text(Command::OptionsFrameSkip9), Settings::Options::FrameSkip::X9 == g_settings.options.frame_skip, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::OptionsFrameSkip9);
					}

					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("Filter"))
				{
					if (ImGui::MenuItem("Normal", get_binding_text(Command::OptionsFilterNormal), 
						Settings::Options::Filter::NORMAL == g_settings.options.filter, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::OptionsFilterNormal);
					}
					if (ImGui::MenuItem("Bilinear", get_binding_text(Command::OptionsFilterBilinear), 
						Settings::Options::Filter::BILINEAR == g_settings.options.filter, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::OptionsFilterBilinear);
					}
					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("Emulator"))
				{
					if (ImGui::MenuItem("Directories...", get_binding_text(Command::OptionsEmulatorDirectories), NOT_SELECTED, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::OptionsEmulatorDirectories);
					}
					if (ImGui::MenuItem("Pause When Inactive", get_binding_text(Command::OptionsEmulatorPauseWhenInactive),
						g_settings.options.emulator.pause_when_inactive, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::OptionsEmulatorPauseWhenInactive);
					}
					if (ImGui::MenuItem("Speed Up Toggle", get_binding_text(Command::OptionsEmulatorSpeedToggle), 
						g_settings.options.emulator.speed_up_toggle, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::OptionsEmulatorSpeedToggle);
					}
					if (ImGui::MenuItem("Automatic IPS Patching", get_binding_text(Command::OptionsEmulatorAutomaticIPS),
						g_settings.options.emulator.automatic_ips_patching, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::OptionsEmulatorAutomaticIPS);
					}
					if (ImGui::MenuItem("Real Time Clock", get_binding_text(Command::OptionsEmulatorRealTimeClock),
						g_settings.options.emulator.real_time_clock, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::OptionsEmulatorRealTimeClock);
					}
					if (ImGui::MenuItem("Rewind Interval...", get_binding_text(Command::OptionsEmulatorRewindInterval), NOT_SELECTED, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::OptionsEmulatorRewindInterval);
					}
					if (ImGui::BeginMenu("Show Speed"))
					{
						if (ImGui::MenuItem("None", get_binding_text(Command::OptionsEmulatorSpeedNone), 
							Settings::Options::Emulator::ShowSpeed::NONE == g_settings.options.emulator.show_speed, DISABLED))
						{
							brain::g_brain_data->command_queue.add(Command::OptionsEmulatorSpeedNone);
						}
						if (ImGui::MenuItem("Percentage", get_binding_text(Command::OptionsEmulatorSpeedPercentage),
							Settings::Options::Emulator::ShowSpeed::PERCENTAGE == g_settings.options.emulator.show_speed, DISABLED))
						{
							brain::g_brain_data->command_queue.add(Command::OptionsEmulatorSpeedPercentage);
						}
						if (ImGui::MenuItem("Detailed", get_binding_text(Command::OptionsEmulatorSpeedDetailed),
							Settings::Options::Emulator::ShowSpeed::DETAILED == g_settings.options.emulator.show_speed, DISABLED))
						{
							brain::g_brain_data->command_queue.add(Command::OptionsEmulatorSpeedDetailed);
						}
						ImGui::Separator();

						if (ImGui::MenuItem("Transparent", get_binding_text(Command::OptionsEmulatorSpeedTransparent), 
							g_settings.options.emulator.speed_transparent, DISABLED))
						{
							brain::g_brain_data->command_queue.add(Command::OptionsEmulatorSpeedTransparent);
						}
						ImGui::EndMenu();
					}
					if (ImGui::BeginMenu("Save Type"))
					{
						if (ImGui::MenuItem("Automatic", get_binding_text(Command::OptionsEmulatorSaveAutomatic),
							Settings::Options::Emulator::SaveType::AUTOMATIC == g_settings.options.emulator.save_type, DISABLED))
						{
							brain::g_brain_data->command_queue.add(Command::OptionsEmulatorSaveAutomatic);
						}
						if (ImGui::MenuItem("EEPROM", get_binding_text(Command::OptionsEmulatorSaveEEPROM),
							Settings::Options::Emulator::SaveType::EEPROM == g_settings.options.emulator.save_type, DISABLED))
						{
							brain::g_brain_data->command_queue.add(Command::OptionsEmulatorSaveEEPROM);
						}
						if (ImGui::MenuItem("SRAM", get_binding_text(Command::OptionsEmulatorSaveSRAM),
							Settings::Options::Emulator::SaveType::SRAM == g_settings.options.emulator.save_type, DISABLED))
						{
							brain::g_brain_data->command_queue.add(Command::OptionsEmulatorSaveSRAM);
						}
						if (ImGui::MenuItem("Flash", get_binding_text(Command::OptionsEmulatorSaveFlash),
							Settings::Options::Emulator::SaveType::FLASH == g_settings.options.emulator.save_type, DISABLED))
						{
							brain::g_brain_data->command_queue.add(Command::OptionsEmulatorSaveFlash);
						}
						if (ImGui::MenuItem("EEPROM+Sensor", get_binding_text(Command::OptionsEmulatorSaveEEPROMAndSensor),
							Settings::Options::Emulator::SaveType::EEPROM_AND_SENSOR == g_settings.options.emulator.save_type, DISABLED))
						{
							brain::g_brain_data->command_queue.add(Command::OptionsEmulatorSaveEEPROMAndSensor);
						}
						if (ImGui::MenuItem("None", get_binding_text(Command::OptionsEmulatorSaveNone),
							Settings::Options::Emulator::SaveType::NONE == g_settings.options.emulator.save_type, DISABLED))
						{
							brain::g_brain_data->command_queue.add(Command::OptionsEmulatorSaveNone);
						}
						ImGui::Separator();

						if (ImGui::MenuItem("Flash 32K", get_binding_text(Command::OptionsEmulatorSaveFlash32K),
							Settings::Options::Emulator::SaveSize::FLASH_32K == g_settings.options.emulator.save_size, DISABLED))
						{
							brain::g_brain_data->command_queue.add(Command::OptionsEmulatorSaveFlash32K);
						}
						if (ImGui::MenuItem("Flash 64K", get_binding_text(Command::OptionsEmulatorSaveFlash64K), 
							Settings::Options::Emulator::SaveSize::FLASH_64K == g_settings.options.emulator.save_size, DISABLED))
						{
							brain::g_brain_data->command_queue.add(Command::OptionsEmulatorSaveFlash64K);
						}
						if (ImGui::MenuItem("Flash 128K", get_binding_text(Command::OptionsEmulatorSaveFlash128K),
							Settings::Options::Emulator::SaveSize::FLASH_128K == g_settings.options.emulator.save_size, DISABLED))
						{
							brain::g_brain_data->command_queue.add(Command::OptionsEmulatorSaveFlash128K);
						}
						if (ImGui::MenuItem("Enhanced Detection", get_binding_text(Command::OptionsEmulatorSaveAutomaticSizeDetection),
							g_settings.options.emulator.save_automatic_size_detection, DISABLED))
						{
							brain::g_brain_data->command_queue.add(Command::OptionsEmulatorSaveAutomaticSizeDetection);
						}
						ImGui::EndMenu();
					}
					ImGui::Separator();
					if (ImGui::MenuItem("Use BIOS File", get_binding_text(Command::OptionsEmulatorUseBIOSFile), 
						g_settings.options.emulator.use_bios_file, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::OptionsEmulatorUseBIOSFile);
					}
					if (ImGui::MenuItem("Skip BIOS File", get_binding_text(Command::OptionsEmulatorSkipBIOSFile),
						g_settings.options.emulator.skip_bios_file, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::OptionsEmulatorSkipBIOSFile);
					}
					if (ImGui::MenuItem("Select BIOS File...", get_binding_text(Command::OptionsEmulatorSelectBIOSFile), NOT_SELECTED, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::OptionsEmulatorSelectBIOSFile);
					}
					ImGui::Separator();
					if (ImGui::MenuItem("PNG Format", get_binding_text(Command::OptionsEmulatorPNGFormat), 
						Settings::Options::Emulator::Format::PNG == g_settings.options.emulator.format, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::OptionsEmulatorPNGFormat);
					}
					if (ImGui::MenuItem("BMP Format", get_binding_text(Command::OptionsEmulatorBMPFormat),
						Settings::Options::Emulator::Format::BMP == g_settings.options.emulator.format, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::OptionsEmulatorBMPFormat);
					}

					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("Sound"))
				{
					if (ImGui::MenuItem("On", get_binding_text(Command::OptionsSoundOn),
						Settings::Options::Sound::Status::ON == g_settings.options.sound.sound_status, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::OptionsSoundOn);
					}
					if (ImGui::MenuItem("Mute", get_binding_text(Command::OptionsSoundMute),
						Settings::Options::Sound::Status::MUTE == g_settings.options.sound.sound_status, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::OptionsSoundMute);
					}
					if (ImGui::MenuItem("Off", get_binding_text(Command::OptionsSoundOff),
						Settings::Options::Sound::Status::OFF == g_settings.options.sound.sound_status, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::OptionsSoundOff);
					}
					ImGui::Separator();
					if (ImGui::MenuItem("Echo", get_binding_text(Command::OptionsSoundEcho), 
						g_settings.options.sound.echo, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::OptionsSoundEcho);
					}
					if (ImGui::MenuItem("Low Pass Filter", get_binding_text(Command::OptionsSoundLowPass),
						g_settings.options.sound.low_pass_filter, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::OptionsSoundLowPass);
					}
					if (ImGui::MenuItem("Reverse Stereo", get_binding_text(Command::OptionsSoundReverseStereo),
						g_settings.options.sound.reverse_stereo, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::OptionsSoundReverseStereo);
					}
					ImGui::Separator();

					if (ImGui::MenuItem("Channel 1", get_binding_text(Command::OptionsSoundChannel1),
						g_settings.options.sound.channel_1, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::OptionsSoundChannel1);
					}
					if (ImGui::MenuItem("Channel 2", get_binding_text(Command::OptionsSoundChannel2),
						g_settings.options.sound.channel_2, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::OptionsSoundChannel2);
					}
					if (ImGui::MenuItem("Channel 3", get_binding_text(Command::OptionsSoundChannel3),
						g_settings.options.sound.channel_3, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::OptionsSoundChannel3);
					}
					if (ImGui::MenuItem("Channel 4", get_binding_text(Command::OptionsSoundChannel4),
						g_settings.options.sound.channel_4, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::OptionsSoundChannel4);
					}
					if (ImGui::MenuItem("Direct Sound A", get_binding_text(Command::OptionsSoundDirectSoundA),
						g_settings.options.sound.direct_sound_a, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::OptionsSoundDirectSoundA);
					}
					if (ImGui::MenuItem("Direct Sound B", get_binding_text(Command::OptionsSoundDirectSoundB),
						g_settings.options.sound.direct_sound_b, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::OptionsSoundDirectSoundB);
					}
					ImGui::Separator();
					if (ImGui::MenuItem("11 Khz", get_binding_text(Command::OptionsSound11Khz),
						Settings::Options::Sound::Frequency::KHZ_11 == g_settings.options.sound.frequency, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::OptionsSound11Khz);
					}
					if (ImGui::MenuItem("22 Khz", get_binding_text(Command::OptionsSound22Khz),
						Settings::Options::Sound::Frequency::KHZ_22 == g_settings.options.sound.frequency, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::OptionsSound22Khz);
					}
					if (ImGui::MenuItem("44 Khz", get_binding_text(Command::OptionsSound44Khz),
						Settings::Options::Sound::Frequency::KHZ_44 == g_settings.options.sound.frequency, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::OptionsSound44Khz);
					}
					ImGui::Separator();
					if (ImGui::BeginMenu("Volume"))
					{
						if (ImGui::MenuItem("0.25x", get_binding_text(Command::OptionsSoundVolumeQuarter),
							Settings::Options::Sound::Volume::QUARTER == g_settings.options.sound.volume, DISABLED))
						{
							brain::g_brain_data->command_queue.add(Command::OptionsSoundVolumeQuarter);
						}
						if (ImGui::MenuItem("0.5x", get_binding_text(Command::OptionsSoundVolumeHalf),
							Settings::Options::Sound::Volume::HALF == g_settings.options.sound.volume, DISABLED))
						{
							brain::g_brain_data->command_queue.add(Command::OptionsSoundVolumeHalf);
						}
						if (ImGui::MenuItem("1x", get_binding_text(Command::OptionsSoundVolume1x),
							Settings::Options::Sound::Volume::X1 == g_settings.options.sound.volume, DISABLED))
						{
							brain::g_brain_data->command_queue.add(Command::OptionsSoundVolume1x);
						}
						if (ImGui::MenuItem("2x", get_binding_text(Command::OptionsSoundVolume2x),
							Settings::Options::Sound::Volume::X2 == g_settings.options.sound.volume, DISABLED))
						{
							brain::g_brain_data->command_queue.add(Command::OptionsSoundVolume2x);
						}
						if (ImGui::MenuItem("3x", get_binding_text(Command::OptionsSoundVolume3x),
							Settings::Options::Sound::Volume::X3 == g_settings.options.sound.volume, DISABLED))
						{
							brain::g_brain_data->command_queue.add(Command::OptionsSoundVolume3x);
						}
						if (ImGui::MenuItem("4x", get_binding_text(Command::OptionsSoundVolume4x),
							Settings::Options::Sound::Volume::X4 == g_settings.options.sound.volume, DISABLED))
						{
							brain::g_brain_data->command_queue.add(Command::OptionsSoundVolume4x);
						}
						ImGui::EndMenu();
					}

					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("Gameboy"))
				{
					if (ImGui::MenuItem("Border", get_binding_text(Command::OptionsGameboyBorder),
						g_settings.options.gameboy.border, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::OptionsGameboyBorder);
					}
					if (ImGui::MenuItem("Border Automatic", get_binding_text(Command::OptionsGameboyBorderAutomatic),
						g_settings.options.gameboy.border_automatic, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::OptionsGameboyBorderAutomatic);
					}
					if (ImGui::MenuItem("Printer", get_binding_text(Command::OptionsGameboyPrinter),
						g_settings.options.gameboy.printer, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::OptionsGameboyPrinter);
					}
					ImGui::Separator();
					if (ImGui::MenuItem("Automatic", get_binding_text(Command::OptionsGameboyAutomatic),
						Settings::Options::Gameboy::Type::AUTOMATIC == g_settings.options.gameboy.type, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::OptionsGameboyAutomatic);
					}
					if (ImGui::MenuItem("GBA", get_binding_text(Command::OptionsGameboyGBA),
						Settings::Options::Gameboy::Type::GBA == g_settings.options.gameboy.type, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::OptionsGameboyGBA);
					}
					if (ImGui::MenuItem("GBC/CGB", get_binding_text(Command::OptionsGameboyGBC),
						Settings::Options::Gameboy::Type::GBC == g_settings.options.gameboy.type, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::OptionsGameboyGBC);
					}
					if (ImGui::MenuItem("SGB", get_binding_text(Command::OptionsGameboySGB),
						Settings::Options::Gameboy::Type::SGB == g_settings.options.gameboy.type, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::OptionsGameboySGB);
					}
					if (ImGui::MenuItem("SGB2", get_binding_text(Command::OptionsGameboySGB2),
						Settings::Options::Gameboy::Type::SGB2 == g_settings.options.gameboy.type, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::OptionsGameboySGB2);
					}
					if (ImGui::MenuItem("GB", get_binding_text(Command::OptionsGameboyGB),
						Settings::Options::Gameboy::Type::GB == g_settings.options.gameboy.type, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::OptionsGameboyGB);
					}
					ImGui::Separator();

					if (ImGui::MenuItem("Real Colors", get_binding_text(Command::OptionsGameboyRealColors),
						Settings::Options::Gameboy::Colors::REAL == g_settings.options.gameboy.colors, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::OptionsGameboyRealColors);
					}
					if (ImGui::MenuItem("Gameboy Colors", get_binding_text(Command::OptionsGameboyGameboyColors),
						Settings::Options::Gameboy::Colors::GAMEBOY == g_settings.options.gameboy.colors, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::OptionsGameboyGameboyColors);
					}
					ImGui::Separator();

					if (ImGui::MenuItem("Colors...", get_binding_text(Command::OptionsGameboyColors), NOT_SELECTED, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::OptionsGameboyColors);
					}
					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("Controls"))
				{
					if (ImGui::BeginMenu("Autofire"))
					{
						if (ImGui::MenuItem("A", get_binding_text(Command::OptionsControlsAutofireA),
							g_settings.controls.autofire.a, DISABLED))
						{
							brain::g_brain_data->command_queue.add(Command::OptionsControlsAutofireA);
						}
						if (ImGui::MenuItem("B", get_binding_text(Command::OptionsControlsAutofireB),
							g_settings.controls.autofire.b, DISABLED))
						{
							brain::g_brain_data->command_queue.add(Command::OptionsControlsAutofireB);
						}
						if (ImGui::MenuItem("L", get_binding_text(Command::OptionsControlsAutofireL),
							g_settings.controls.autofire.l, DISABLED))
						{
							brain::g_brain_data->command_queue.add(Command::OptionsControlsAutofireL);
						}
						if (ImGui::MenuItem("R", get_binding_text(Command::OptionsControlsAutofireR),
							g_settings.controls.autofire.r, DISABLED))
						{
							brain::g_brain_data->command_queue.add(Command::OptionsControlsAutofireR);
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
					brain::g_brain_data->command_queue.add(Command::CheatsSearch);
				}
				if (ImGui::MenuItem("Cheat List...", get_binding_text(Command::CheatsList), NOT_SELECTED, DISABLED))
				{
					brain::g_brain_data->command_queue.add(Command::CheatsList);
				}
				ImGui::Separator();
				if (ImGui::MenuItem("Automatically Save/Load Cheats", get_binding_text(Command::CheatsAutomaticallySaveAndLoad),
					g_settings.cheats.autoload_cheats, DISABLED))
				{
					brain::g_brain_data->command_queue.add(Command::CheatsAutomaticallySaveAndLoad);
				}
				if (ImGui::MenuItem("Disable Cheats", get_binding_text(Command::CheatsDisable),
					g_settings.cheats.disable_cheats, DISABLED))
				{
					brain::g_brain_data->command_queue.add(Command::CheatsDisable);
				}
				if (ImGui::MenuItem("Load Cheat List...", get_binding_text(Command::CheatsLoad), NOT_SELECTED, DISABLED))
				{
					brain::g_brain_data->command_queue.add(Command::CheatsLoad);
				}
				if (ImGui::MenuItem("Save Cheat List...", get_binding_text(Command::CheatsSave), NOT_SELECTED, DISABLED))
				{
					brain::g_brain_data->command_queue.add(Command::CheatsSave);
				}
				 
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Tools"))
			{
				if (ImGui::MenuItem("Disassemble...", get_binding_text(Command::ToolsDisassemble), NOT_SELECTED, DISABLED))
				{
					brain::g_brain_data->command_queue.add(Command::ToolsDisassemble);
				}
				if (ImGui::MenuItem("IO Viewer...", get_binding_text(Command::ToolsIO), NOT_SELECTED, DISABLED))
				{
					brain::g_brain_data->command_queue.add(Command::ToolsIO);
				}
				if (ImGui::MenuItem("Map Viewer...", get_binding_text(Command::ToolsMap), NOT_SELECTED, DISABLED))
				{
					brain::g_brain_data->command_queue.add(Command::ToolsMap);
				}
				if (ImGui::MenuItem("Memory Viewer...", get_binding_text(Command::ToolsMemory), NOT_SELECTED, DISABLED))
				{
					brain::g_brain_data->command_queue.add(Command::ToolsMemory);
				}
				if (ImGui::MenuItem("OAM (Sprite) Viewer...", get_binding_text(Command::ToolsOAM), NOT_SELECTED, DISABLED))
				{
					brain::g_brain_data->command_queue.add(Command::ToolsOAM);
				}
				if (ImGui::MenuItem("Palette Viewer...", get_binding_text(Command::ToolsPalette), NOT_SELECTED, DISABLED))
				{
					brain::g_brain_data->command_queue.add(Command::ToolsPalette);
				}
				if (ImGui::MenuItem("Tile Viewer...", get_binding_text(Command::ToolsTile), NOT_SELECTED, DISABLED))
				{
					brain::g_brain_data->command_queue.add(Command::ToolsTile);
				}
				ImGui::Separator();

				if (ImGui::MenuItem("Next Frame", get_binding_text(Command::ToolsNextFrame), NOT_SELECTED, DISABLED))
				{
					brain::g_brain_data->command_queue.add(Command::ToolsNextFrame);
				}
				if (ImGui::BeginMenu("Debugger"))
				{
					if (ImGui::MenuItem("Wait For Connection...", get_binding_text(Command::ToolsDebuggerWait), NOT_SELECTED, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::ToolsDebuggerWait);
					}
					if (ImGui::MenuItem("Load And Wait...", get_binding_text(Command::ToolsDebuggerLoadAndWait), NOT_SELECTED, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::ToolsDebuggerLoadAndWait);
					}
					if (ImGui::MenuItem("Break Into Debugger", get_binding_text(Command::ToolsDebuggerBreak), NOT_SELECTED, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::ToolsDebuggerBreak);
					}
					if (ImGui::MenuItem("Disconnect", get_binding_text(Command::ToolsDebuggerDisconnect), NOT_SELECTED, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::ToolsDebuggerDisconnect);
					}
					ImGui::EndMenu();
				}
				ImGui::Separator();

				if (ImGui::BeginMenu("Record"))
				{
					if (ImGui::MenuItem("Start Sound Recording...", get_binding_text(Command::ToolsRecordSoundStart), NOT_SELECTED, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::ToolsRecordSoundStart);
					}
					if (ImGui::MenuItem("Stop Sound Recording", get_binding_text(Command::ToolsRecordSoundStop), NOT_SELECTED, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::ToolsRecordSoundStop);
					}
					if (ImGui::MenuItem("Start AVI Recording...", get_binding_text(Command::ToolsRecordAVIStart), NOT_SELECTED, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::ToolsRecordAVIStart);
					}
					if (ImGui::MenuItem("Stop AVI Recording", get_binding_text(Command::ToolsRecordAVIStop), NOT_SELECTED, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::ToolsRecordAVIStop);
					}
					if (ImGui::MenuItem("Start Movie Recording...", get_binding_text(Command::ToolsRecordMovieStart), NOT_SELECTED, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::ToolsRecordMovieStart);
					}
					if (ImGui::MenuItem("Stop Movie Recording", get_binding_text(Command::ToolsRecordMovieStop), NOT_SELECTED, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::ToolsRecordMovieStop);
					}

					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("Play"))
				{
					if (ImGui::MenuItem("Start Playing Movie...", get_binding_text(Command::ToolsPlayMovieStart), NOT_SELECTED, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::ToolsPlayMovieStart);
					}
					if (ImGui::MenuItem("Stop Playing Movie", get_binding_text(Command::ToolsPlayMovieStop), NOT_SELECTED, DISABLED))
					{
						brain::g_brain_data->command_queue.add(Command::ToolsPlayMovieStop);
					}

					ImGui::EndMenu();
				}
				ImGui::Separator();

				if (ImGui::MenuItem("Rewind", get_binding_text(Command::ToolsRewind), NOT_SELECTED, DISABLED))
				{
					brain::g_brain_data->command_queue.add(Command::ToolsRewind);
				}
				if (ImGui::MenuItem("Keybinds...", get_binding_text(Command::ToolsKeybinds), NOT_SELECTED, DISABLED))
				{
					brain::g_brain_data->command_queue.add(Command::ToolsKeybinds);
				}

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Help"))
			{
				if (ImGui::MenuItem("Bug Report Details", get_binding_text(Command::HelpBugReport), NOT_SELECTED, DISABLED))
				{
					brain::g_brain_data->command_queue.add(Command::HelpBugReport);
				}
				if (ImGui::MenuItem("MIT License (website)...", get_binding_text(Command::HelpLicense), NOT_SELECTED, DISABLED))
				{
					brain::g_brain_data->command_queue.add(Command::HelpLicense);
				}
				ImGui::Separator();
				if (ImGui::MenuItem("About...", get_binding_text(Command::HelpAbout), NOT_SELECTED, DISABLED))
				{
					brain::g_brain_data->command_queue.add(Command::HelpAbout);
				}
				
				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();
		}
	}
}