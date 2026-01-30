#pragma once

#include "board/advanced_game_boy.h"
#include "cartridge/game_pak.h"

namespace emulator {

	struct GBA {
		AdvancedGameBoy agb;
		GamePak game_pak;
	};
}