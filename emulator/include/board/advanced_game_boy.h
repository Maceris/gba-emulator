#pragma once

#include "board/bus.h"
#include "cpu/cpu.h"

/// <summary>
/// A System on a Chip containing various components.
/// </summary>
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
	ARM7TDMI_Bus gba_bus;

	// 16-bit line to 256KB WRAM
	// 8/32-bit line to  6-pin serial subconnector
	// 16 bit line to game pak / shape detector switch
};
