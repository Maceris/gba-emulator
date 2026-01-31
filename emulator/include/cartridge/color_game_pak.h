#pragma once

#include "game_pak.h"

namespace emulator {
	struct ColorGamePak : public GamePak
	{
		ColorGamePak();
		ColorGamePak(const ColorGamePak&) = delete;
		ColorGamePak(ColorGamePak&&) = delete;
		ColorGamePak& operator=(const ColorGamePak&) = delete;
		ColorGamePak& operator=(ColorGamePak&&) = delete;
		~ColorGamePak();
	};
}
