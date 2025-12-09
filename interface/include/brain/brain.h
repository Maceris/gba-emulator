#pragma once

#include "command_queue.h"

namespace brain {

	struct BrainData {
		BrainData();
		BrainData(const BrainData&) = delete;
		BrainData(BrainData&&) = delete;
		~BrainData();
		BrainData& operator=(const BrainData&) = delete;
		BrainData& operator=(BrainData&&) = delete;
		
		CommandQueue command_queue;
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