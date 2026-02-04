#pragma once

#include "board/advanced_game_boy.h"
#include "cartridge/game_pak.h"

namespace emulator {

	struct GBA {
		AdvancedGameBoy agb;
		GamePak game_pak;

		bool powered_on;

		GBA();
		GBA(const GBA&) = delete;
		GBA(GBA&&) = delete;
		GBA& operator=(const GBA&) = delete;
		GBA& operator=(GBA&&) = delete;
		~GBA();

		/// <summary>
		/// Execute one clock cycle of stuff for the GBA.
		/// </summary>
		void pulse_clock();
	};
}