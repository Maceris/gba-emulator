#include "board/gba.h"

namespace emulator {
	GBA::GBA()
		: agb{}
		, game_pak{}
		, powered_on{ false }
	{}
	GBA::~GBA() = default;

	void GBA::pulse_clock() {
		if (!powered_on) {
			return;
		}
		agb.pulse_clock();
	}
}