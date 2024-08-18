#pragma once

#include "cpu/cpu.h"

struct AdvancedGameBoy
{
	ARM7TDMI gba_cpu;
	SM83 gbc_cpu;
	// 32 KB WRAM
	// 96 KB VRAM
	// PPU
	// Key Controller
	// DMA
	// 2 KB CGB ROM
	// 16 KB AGB ROM
	// Sound Generator
	// Prefetch Buffer
	// Bus?

	// 16-bit line to 256KB WRAM
	// 8/32-bit line to  6-pin serial subconnector
	// 16 bit line to game pak / shape detector switch
};
