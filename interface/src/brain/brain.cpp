#include "brain/brain.h"

#include "memory/memory_util.h"

namespace brain {
	BrainData* g_brain_data = ALLOC BrainData();

	BrainData::BrainData()
		: command_queue{}
	{}
	BrainData::~BrainData() = default;

}