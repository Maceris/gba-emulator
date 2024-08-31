#pragma once

#include "cpu/cpu_constants.h"

enum class CPUMode
{
	/// <summary>
	/// ARM7TDMI 32bit RISC CPU, 16.78MHz, 32bit opcodes (GBA)
	/// </summary>
	ARM,
	/// <summary>
	/// ARM7TDMI 32bit RISC CPU, 16.78MHz, 16bit opcodes (GBA)
	/// </summary>
	THUMB,
	/// <summary>
	/// Z80/8080-style 8bit CPU, 4.2MHz or 8.4MHz  (CGB compatibility)
	/// </summary>
	CGB,
	/// <summary>
	/// Z80/8080-style 8bit CPU, 4.2MHz (monochrome gameboy compatibility)
	/// </summary>
	DMG
};

#include "cpu/arm7tdmi.h"
#include "cpu/sm83.h"
