#pragma once

#include "game_pak.h"

namespace emulator {
	struct AdvanceGamePak : public GamePak
	{
		AdvanceGamePak();
		AdvanceGamePak(const AdvanceGamePak&) = delete;
		AdvanceGamePak(AdvanceGamePak&&) = delete;
		AdvanceGamePak& operator=(const AdvanceGamePak&) = delete;
		AdvanceGamePak& operator=(AdvanceGamePak&&) = delete;
		~AdvanceGamePak();
	};
}
