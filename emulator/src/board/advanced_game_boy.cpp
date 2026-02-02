#include "board/advanced_game_boy.h"

namespace emulator {
	AdvancedGameBoy::AdvancedGameBoy()
		: gba_cpu{}
		, gbc_cpu{}
		, gba_bus{}
		, cartridge_switch{ false }
	{}

	AdvancedGameBoy::~AdvancedGameBoy() = default;
}