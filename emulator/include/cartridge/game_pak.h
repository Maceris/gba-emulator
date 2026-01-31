#pragma once

namespace emulator {
	struct GamePak
	{
		GamePak();
		GamePak(const GamePak&) = delete;
		GamePak(GamePak&&) = delete;
		GamePak& operator=(const GamePak&) = delete;
		GamePak& operator=(GamePak&&) = delete;
		~GamePak();

		// SRAM
		// Mask ROM Program
		// Optional Mapper
		// Battery
	};
}
