#pragma once

#include <chrono>

#include "brain/command_queue.h"
#include "board/gba.h"

namespace brain {

	using Instant = std::chrono::steady_clock::time_point;

	struct BrainData {
		BrainData();
		BrainData(const BrainData&) = delete;
		BrainData(BrainData&&) = delete;
		~BrainData();
		BrainData& operator=(const BrainData&) = delete;
		BrainData& operator=(BrainData&&) = delete;
		
		CommandQueue command_queue;
		emulator::GBA gba;
		Instant last_frame;
		bool paused;
		bool game_loaded;
	};

	extern BrainData* g_brain_data;

	/// <summary>
	/// Process any commands in the queue.
	/// </summary>
	void process_commands();

	/// <summary>
	/// Run the application until it requests to be closed.
	/// </summary>
	void run_application();

#define GBA_GUI_COMMANDS_MAPPING(X) void process_command_##X();
#define GBA_GUI_COMMANDS_END_OF_LIST

	GBA_GUI_COMMANDS_LIST

#undef GBA_GUI_COMMANDS_MAPPING
#undef GBA_GUI_COMMANDS_END_OF_LIST

}