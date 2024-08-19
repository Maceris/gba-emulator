#pragma once

#include <cstdint>

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

/// <summary>
/// A 16.78 MHz ARM7TDMI RISC processor, featuring 16-bit Thumb, JTAG Debug,
/// fast multiplier, and enhanced ICE.
/// </summary>
struct ARM7TDMI
{
#pragma region Registers
	// System/User Registers
	Register R0;
	Register R1;
	Register R2;
	Register R3;
	Register R4;
	Register R5;
	Register R6;
	Register R7;
	Register R8;
	Register R9;
	Register R10;
	Register R11;
	Register R12;
	/// <summary>
	/// Stack Pointer (SP) in THUMB state. ARM state may or may not use this as
	/// a stack pointer.
	/// </summary>
	Register R13;
	/// <summary>
	/// Link Register (LR). When calling a sub-routine using a BL instruction, 
	/// the return address is saved here. ARM state may use this as a
	/// general register.
	/// </summary>
	Register R14;
	/// <summary>
	/// Program Counter (PC). When reading, usually returns a value of PC+n,
	/// where n depends on the instruction and on CPU state (ARM/THUMB),
	/// because of pipelining. 
	/// </summary>
	Register R15;
	/// <summary>
	/// Current Program Status Register.
	/// Stores current condition codes (flags) and CPU control bits. 
	/// When exceptions are raised, the old CPSR is saved in the SPSR of the 
	/// respective exceptoin mode.
	/// </summary>
	Register CPSR;

	// FIQ Registers
	Register R8_fiq;
	Register R9_fiq;
	Register R10_fiq;
	Register R11_fiq;
	Register R12_fiq;
	Register R13_fiq;
	Register R14_fiq;
	Register SPSR_fiq;

	// Supervisor Registers
	Register R13_svc;
	Register R14_svc;
	Register SPSR_svc;

	// Abort Registers
	Register R13_abt;
	Register R14_abt;
	Register SPSR_abt;

	// IRQ Registers
	Register R13_irq;
	Register R14_irq;
	Register SPSR_irq;

	// Undefined Registers
	Register R13_und;
	Register R14_und;
	Register SPSR_und;
#pragma endregion

};

/// <summary>
/// A Sharp SM83 (LR35902) CPU running at either 4.194304 MHz or
/// 8.388608 MHz for backward compatibilty with Game Boy and Game Boy color
/// games.
/// 
/// A hybrid between the Intel 8080 and the Zilog Z80 processors.
/// </summary>
struct SM83
{

};
