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
}