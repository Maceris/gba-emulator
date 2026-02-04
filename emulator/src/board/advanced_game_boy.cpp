#include "board/advanced_game_boy.h"

namespace emulator {
	AdvancedGameBoy::AdvancedGameBoy()
		: gba_cpu{}
		, gbc_cpu{}
		, gba_bus{}
		, cartridge_switch{ false }
	{}

	AdvancedGameBoy::~AdvancedGameBoy() = default;

	void AdvancedGameBoy::pulse_clock() {
		if (cartridge_switch) {
			gbc_cpu.pulse_clock();
		}
		else {
			gba_cpu.pulse_clock();
		}
	}
}