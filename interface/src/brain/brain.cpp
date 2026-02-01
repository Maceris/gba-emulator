#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

#include "brain/brain.h"

#include "debugging/logger.h"
#include "gui/gui.h"
#include "memory/memory_util.h"
#include "rendering/render.h"
#include "rendering/render_state.h"

namespace brain {
	BrainData* g_brain_data = ALLOC BrainData();

	BrainData::BrainData()
		: command_queue{}
		, gba{}
	{}
	BrainData::~BrainData() = default;

	void process_commands() {
		while (!g_brain_data->command_queue.is_empty()) {
			Command command = g_brain_data->command_queue.remove();

#define GBA_GUI_COMMANDS_MAPPING(X) case Command::X: process_command_##X(); break;
#define GBA_GUI_COMMANDS_END_OF_LIST case Command::_count: LOG_ERROR("Provided an invalid command"); break;

			switch (command) {
				GBA_GUI_COMMANDS_LIST
			}

#undef GBA_GUI_COMMANDS_MAPPING
#undef GBA_GUI_COMMANDS_END_OF_LIST
		}
	}

	void run_application() {
		while (!render::g_render_state->should_close())
		{
			glfwPollEvents();
			gui::draw_ui();
			render::draw_frame();
			process_commands();
		}
	}

	void process_command_ControlsUp() {
		//TODO(ches) implement this
	}

	void process_command_ControlsDown() {
		//TODO(ches) implement this
	}

	void process_command_ControlsLeft() {
		//TODO(ches) implement this
	}

	void process_command_ControlsRight() {
		//TODO(ches) implement this
	}

	void process_command_ControlsMotionUp() {
		//TODO(ches) implement this
	}

	void process_command_ControlsMotionDown() {
		//TODO(ches) implement this
	}

	void process_command_ControlsMotionLeft() {
		//TODO(ches) implement this
	}

	void process_command_ControlsMotionRight() {
		//TODO(ches) implement this
	}

	void process_command_ControlsA() {
		//TODO(ches) implement this
	}

	void process_command_ControlsB() {
		//TODO(ches) implement this
	}

	void process_command_ControlsL() {
		//TODO(ches) implement this
	}

	void process_command_ControlsR() {
		//TODO(ches) implement this
	}

	void process_command_ControlsSelect() {
		//TODO(ches) implement this
	}

	void process_command_ControlsStart() {
		//TODO(ches) implement this
	}

	void process_command_ControlsSpeed() {
		//TODO(ches) implement this
	}

	void process_command_ControlsScreenCapture() {
		//TODO(ches) implement this
	}

	void process_command_FileOpenGameboyAdvance() {
		//TODO(ches) implement this
	}

	void process_command_FileOpenGameboy() {
		//TODO(ches) implement this
	}

	void process_command_FileRecent01() {
		//TODO(ches) implement this
	}

	void process_command_FileRecent02() {
		//TODO(ches) implement this
	}

	void process_command_FileRecent03() {
		//TODO(ches) implement this
	}

	void process_command_FileRecent04() {
		//TODO(ches) implement this
	}

	void process_command_FileRecent05() {
		//TODO(ches) implement this
	}

	void process_command_FileRecent06() {
		//TODO(ches) implement this
	}

	void process_command_FileRecent07() {
		//TODO(ches) implement this
	}

	void process_command_FileRecent08() {
		//TODO(ches) implement this
	}

	void process_command_FileRecent09() {
		//TODO(ches) implement this
	}

	void process_command_FileRecent10() {
		//TODO(ches) implement this
	}

	void process_command_FileSave() {
		//TODO(ches) implement this
	}

	void process_command_FileSaveGame01() {
		//TODO(ches) implement this
	}

	void process_command_FileSaveGame02() {
		//TODO(ches) implement this
	}

	void process_command_FileSaveGame03() {
		//TODO(ches) implement this
	}

	void process_command_FileSaveGame04() {
		//TODO(ches) implement this
	}

	void process_command_FileSaveGame05() {
		//TODO(ches) implement this
	}

	void process_command_FileSaveGame06() {
		//TODO(ches) implement this
	}

	void process_command_FileSaveGame07() {
		//TODO(ches) implement this
	}

	void process_command_FileSaveGame08() {
		//TODO(ches) implement this
	}

	void process_command_FileSaveGame09() {
		//TODO(ches) implement this
	}

	void process_command_FileSaveGame10() {
		//TODO(ches) implement this
	}

	void process_command_FileLoad() {
		//TODO(ches) implement this
	}

	void process_command_FileLoadGame01() {
		//TODO(ches) implement this
	}

	void process_command_FileLoadGame02() {
		//TODO(ches) implement this
	}

	void process_command_FileLoadGame03() {
		//TODO(ches) implement this
	}

	void process_command_FileLoadGame04() {
		//TODO(ches) implement this
	}

	void process_command_FileLoadGame05() {
		//TODO(ches) implement this
	}

	void process_command_FileLoadGame06() {
		//TODO(ches) implement this
	}

	void process_command_FileLoadGame07() {
		//TODO(ches) implement this
	}

	void process_command_FileLoadGame08() {
		//TODO(ches) implement this
	}

	void process_command_FileLoadGame09() {
		//TODO(ches) implement this
	}

	void process_command_FileLoadGame10() {
		//TODO(ches) implement this
	}

	void process_command_FilePause() {
		//TODO(ches) implement this
	}

	void process_command_FileReset() {
		//TODO(ches) implement this
	}

	void process_command_FileScreenCapture() {
		//TODO(ches) implement this
	}

	void process_command_FileRomInformation() {
		//TODO(ches) implement this
	}

	void process_command_FileToggleMenu() {
		//TODO(ches) implement this
	}

	void process_command_FileClose() {
		//TODO(ches) implement this
	}

	void process_command_FileExit() {
		render::g_render_state->close_requested = true;
	}

	void process_command_OptionsVideoVSync() {
		//TODO(ches) implement this
	}

	void process_command_OptionsVideoX1() {
		//TODO(ches) implement this
	}

	void process_command_OptionsVideoX2() {
		//TODO(ches) implement this
	}

	void process_command_OptionsVideoX3() {
		//TODO(ches) implement this
	}

	void process_command_OptionsVideoX4() {
		//TODO(ches) implement this
	}

	void process_command_OptionsVideoFullScreen() {
		//TODO(ches) implement this
	}

	void process_command_OptionsFrameSkipAutomatic() {
		//TODO(ches) implement this
	}

	void process_command_OptionsFrameSkip0() {
		//TODO(ches) implement this
	}

	void process_command_OptionsFrameSkip1() {
		//TODO(ches) implement this
	}

	void process_command_OptionsFrameSkip2() {
		//TODO(ches) implement this
	}

	void process_command_OptionsFrameSkip3() {
		//TODO(ches) implement this
	}

	void process_command_OptionsFrameSkip4() {
		//TODO(ches) implement this
	}

	void process_command_OptionsFrameSkip5() {
		//TODO(ches) implement this
	}

	void process_command_OptionsFrameSkip6() {
		//TODO(ches) implement this
	}

	void process_command_OptionsFrameSkip7() {
		//TODO(ches) implement this
	}

	void process_command_OptionsFrameSkip8() {
		//TODO(ches) implement this
	}

	void process_command_OptionsFrameSkip9() {
		//TODO(ches) implement this
	}

	void process_command_OptionsFilterNormal() {
		//TODO(ches) implement this
	}

	void process_command_OptionsFilterBilinear() {
		//TODO(ches) implement this
	}

	void process_command_OptionsEmulatorDirectories() {
		//TODO(ches) implement this
	}

	void process_command_OptionsEmulatorPauseWhenInactive() {
		//TODO(ches) implement this
	}

	void process_command_OptionsEmulatorSpeedToggle() {
		//TODO(ches) implement this
	}

	void process_command_OptionsEmulatorAutomaticIPS() {
		//TODO(ches) implement this
	}

	void process_command_OptionsEmulatorRealTimeClock() {
		//TODO(ches) implement this
	}

	void process_command_OptionsEmulatorRewindInterval() {
		//TODO(ches) implement this
	}

	void process_command_OptionsEmulatorSpeedNone() {
		//TODO(ches) implement this
	}

	void process_command_OptionsEmulatorSpeedPercentage() {
		//TODO(ches) implement this
	}

	void process_command_OptionsEmulatorSpeedDetailed() {
		//TODO(ches) implement this
	}

	void process_command_OptionsEmulatorSpeedTransparent() {
		//TODO(ches) implement this
	}

	void process_command_OptionsEmulatorSaveAutomatic() {
		//TODO(ches) implement this
	}

	void process_command_OptionsEmulatorSaveEEPROM() {
		//TODO(ches) implement this
	}

	void process_command_OptionsEmulatorSaveSRAM() {
		//TODO(ches) implement this
	}

	void process_command_OptionsEmulatorSaveFlash() {
		//TODO(ches) implement this
	}

	void process_command_OptionsEmulatorSaveEEPROMAndSensor() {
		//TODO(ches) implement this
	}

	void process_command_OptionsEmulatorSaveNone() {
		//TODO(ches) implement this
	}

	void process_command_OptionsEmulatorSaveFlash32K() {
		//TODO(ches) implement this
	}

	void process_command_OptionsEmulatorSaveFlash64K() {
		//TODO(ches) implement this
	}

	void process_command_OptionsEmulatorSaveFlash128K() {
		//TODO(ches) implement this
	}

	void process_command_OptionsEmulatorSaveAutomaticSizeDetection() {
		//TODO(ches) implement this
	}

	void process_command_OptionsEmulatorUseBIOSFile() {
		//TODO(ches) implement this
	}

	void process_command_OptionsEmulatorSkipBIOSFile() {
		//TODO(ches) implement this
	}

	void process_command_OptionsEmulatorSelectBIOSFile() {
		//TODO(ches) implement this
	}

	void process_command_OptionsEmulatorPNGFormat() {
		//TODO(ches) implement this
	}

	void process_command_OptionsEmulatorBMPFormat() {
		//TODO(ches) implement this
	}

	void process_command_OptionsSoundOn() {
		//TODO(ches) implement this
	}

	void process_command_OptionsSoundMute() {
		//TODO(ches) implement this
	}

	void process_command_OptionsSoundOff() {
		//TODO(ches) implement this
	}

	void process_command_OptionsSoundEcho() {
		//TODO(ches) implement this
	}

	void process_command_OptionsSoundLowPass() {
		//TODO(ches) implement this
	}

	void process_command_OptionsSoundReverseStereo() {
		//TODO(ches) implement this
	}

	void process_command_OptionsSoundChannel1() {
		//TODO(ches) implement this
	}

	void process_command_OptionsSoundChannel2() {
		//TODO(ches) implement this
	}

	void process_command_OptionsSoundChannel3() {
		//TODO(ches) implement this
	}

	void process_command_OptionsSoundChannel4() {
		//TODO(ches) implement this
	}

	void process_command_OptionsSoundDirectSoundA() {
		//TODO(ches) implement this
	}

	void process_command_OptionsSoundDirectSoundB() {
		//TODO(ches) implement this
	}

	void process_command_OptionsSound11Khz() {
		//TODO(ches) implement this
	}

	void process_command_OptionsSound22Khz() {
		//TODO(ches) implement this
	}

	void process_command_OptionsSound44Khz() {
		//TODO(ches) implement this
	}

	void process_command_OptionsSoundVolumeQuarter() {
		//TODO(ches) implement this
	}

	void process_command_OptionsSoundVolumeHalf() {
		//TODO(ches) implement this
	}

	void process_command_OptionsSoundVolume1x() {
		//TODO(ches) implement this
	}

	void process_command_OptionsSoundVolume2x() {
		//TODO(ches) implement this
	}

	void process_command_OptionsSoundVolume3x() {
		//TODO(ches) implement this
	}

	void process_command_OptionsSoundVolume4x() {
		//TODO(ches) implement this
	}

	void process_command_OptionsGameboyBorder() {
		//TODO(ches) implement this
	}

	void process_command_OptionsGameboyBorderAutomatic() {
		//TODO(ches) implement this
	}

	void process_command_OptionsGameboyPrinter() {
		//TODO(ches) implement this
	}

	void process_command_OptionsGameboyAutomatic() {
		//TODO(ches) implement this
	}

	void process_command_OptionsGameboyGBA() {
		//TODO(ches) implement this
	}

	void process_command_OptionsGameboyGBC() {
		//TODO(ches) implement this
	}

	void process_command_OptionsGameboySGB() {
		//TODO(ches) implement this
	}

	void process_command_OptionsGameboySGB2() {
		//TODO(ches) implement this
	}

	void process_command_OptionsGameboyGB() {
		//TODO(ches) implement this
	}

	void process_command_OptionsGameboyRealColors() {
		//TODO(ches) implement this
	}

	void process_command_OptionsGameboyGameboyColors() {
		//TODO(ches) implement this
	}

	void process_command_OptionsGameboyColors() {
		//TODO(ches) implement this
	}

	void process_command_OptionsControlsAutofireA() {
		//TODO(ches) implement this
	}

	void process_command_OptionsControlsAutofireB() {
		//TODO(ches) implement this
	}

	void process_command_OptionsControlsAutofireL() {
		//TODO(ches) implement this
	}

	void process_command_OptionsControlsAutofireR() {
		//TODO(ches) implement this
	}

	void process_command_CheatsSearch() {
		//TODO(ches) implement this
	}

	void process_command_CheatsList() {
		//TODO(ches) implement this
	}

	void process_command_CheatsAutomaticallySaveAndLoad() {
		//TODO(ches) implement this
	}

	void process_command_CheatsDisable() {
		//TODO(ches) implement this
	}

	void process_command_CheatsLoad() {
		//TODO(ches) implement this
	}

	void process_command_CheatsSave() {
		//TODO(ches) implement this
	}

	void process_command_ToolsDisassemble() {
		gui::g_gui_state.show_window_disassembler = 
			!gui::g_gui_state.show_window_disassembler;
	}

	void process_command_ToolsIO() {
		//TODO(ches) implement this
	}

	void process_command_ToolsMap() {
		//TODO(ches) implement this
	}

	void process_command_ToolsMemory() {
		//TODO(ches) implement this
	}

	void process_command_ToolsOAM() {
		//TODO(ches) implement this
	}

	void process_command_ToolsPalette() {
		//TODO(ches) implement this
	}

	void process_command_ToolsTile() {
		//TODO(ches) implement this
	}

	void process_command_ToolsNextFrame() {
		//TODO(ches) implement this
	}

	void process_command_ToolsDebuggerWait() {
		//TODO(ches) implement this
	}

	void process_command_ToolsDebuggerLoadAndWait() {
		//TODO(ches) implement this
	}

	void process_command_ToolsDebuggerBreak() {
		//TODO(ches) implement this
	}

	void process_command_ToolsDebuggerDisconnect() {
		//TODO(ches) implement this
	}

	void process_command_ToolsRecordSoundStart() {
		//TODO(ches) implement this
	}

	void process_command_ToolsRecordSoundStop() {
		//TODO(ches) implement this
	}

	void process_command_ToolsRecordAVIStart() {
		//TODO(ches) implement this
	}

	void process_command_ToolsRecordAVIStop() {
		//TODO(ches) implement this
	}

	void process_command_ToolsRecordMovieStart() {
		//TODO(ches) implement this
	}

	void process_command_ToolsRecordMovieStop() {
		//TODO(ches) implement this
	}

	void process_command_ToolsPlayMovieStart() {
		//TODO(ches) implement this
	}

	void process_command_ToolsPlayMovieStop() {
		//TODO(ches) implement this
	}

	void process_command_ToolsRewind() {
		//TODO(ches) implement this
	}

	void process_command_ToolsKeybinds() {
		//TODO(ches) implement this
	}

	void process_command_HelpBugReport() {
		//TODO(ches) implement this
	}

	void process_command_HelpLicense() {
		//TODO(ches) implement this
	}

	void process_command_HelpAbout() {
		//TODO(ches) implement this
	}

}