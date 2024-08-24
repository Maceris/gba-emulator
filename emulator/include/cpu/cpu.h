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

#pragma region ARM Instructions
	/// <summary>
	/// Add with carry.
	/// </summary>
	void arm_adc();
	/// <summary>
	/// Add.
	/// </summary>
	void arm_add();
	/// <summary>
	/// And.
	/// </summary>
	void arm_and();
	/// <summary>
	/// Branch.
	/// </summary>
	void arm_b();
	/// <summary>
	/// Bit clear.
	/// </summary>
	void arm_bic();
	/// <summary>
	/// Branch with link;
	/// </summary>
	void arm_bl();
	/// <summary>
	/// Branch and exchange.
	/// </summary>
	void arm_bx();
	/// <summary>
	/// Coprocessor data processing.
	/// </summary>
	void arm_cdp();
	/// <summary>
	/// Compare negative.
	/// </summary>
	void arm_cmn();
	/// <summary>
	/// Compare.
	/// </summary>
	void arm_cmp();
	/// <summary>
	/// Exclusive or.
	/// </summary>
	void arm_eor();
	/// <summary>
	/// Load coprocessor from memory.
	/// </summary>
	void arm_ldc();
	/// <summary>
	/// Load multiple registers.
	/// </summary>
	void arm_ldm();
	/// <summary>
	/// Load register from memory.
	/// </summary>
	void arm_ldr();
	/// <summary>
	/// Move CPU register to coprocessor register.
	/// </summary>
	void arm_mcr();
	/// <summary>
	/// Multiply Accumulate.
	/// </summary>
	void arm_mla();
	/// <summary>
	/// Move register or constant.
	/// </summary>
	void arm_mov();
	/// <summary>
	/// Move from coprocessor register to CPU register.
	/// </summary>
	void arm_mrc();
	/// <summary>
	/// Move PSR status/flags to register.
	/// </summary>
	void arm_mrs();
	/// <summary>
	/// Move register to PSR status/flags.
	/// </summary>
	void arm_msr();
	/// <summary>
	/// Multiply.
	/// </summary>
	void arm_mul();
	/// <summary>
	/// Move negative register.
	/// </summary>
	void arm_mvn();
	/// <summary>
	/// Or.
	/// </summary>
	void arm_orr();
	/// <summary>
	/// Reverse subtract.
	/// </summary>
	void arm_rsb();
	/// <summary>
	/// Reverse subtract with carry.
	/// </summary>
	void arm_rsc();
	/// <summary>
	/// Subtract with carry.
	/// </summary>
	void arm_sbc();
	/// <summary>
	/// Multiply signed accumulate long.
	/// </summary>
	void arm_smlal();
	/// <summary>
	/// Multiply signed long.
	/// </summary>
	void arm_smull();
	/// <summary>
	/// Store coprocessor register to memory.
	/// </summary>
	void arm_stc();
	/// <summary>
	/// Store multiple.
	/// </summary>
	void arm_stm();
	/// <summary>
	/// Store register to memory.
	/// </summary>
	void arm_str();
	/// <summary>
	/// Subtract.
	/// </summary>
	void arm_sub();
	/// <summary>
	/// Software interrupt.
	/// </summary>
	void arm_swi();
	/// <summary>
	/// Swap register with memory.
	/// </summary>
	void arm_swp();
	/// <summary>
	/// Test bitwise equality.
	/// </summary>
	void arm_teq();
	/// <summary>
	/// Test bits.
	/// </summary>
	void arm_tst();
	/// <summary>
	/// Multiply unsigned accumulate long.
	/// </summary>
	void arm_umlal();
	/// <summary>
	/// Multiply unsigned long
	/// </summary>
	void arm_umull();
#pragma endregion

#pragma region Thumb Instructions
	/// <summary>
	/// Add, or address.
	/// </summary>
	void thumb_add();
	/// <summary>
	/// And.
	/// </summary>
	void thumb_and();
	/// <summary>
	/// Arithmetic shift right.
	/// </summary>
	void thumb_asr();
	/// <summary>
	/// Unconditional branch.
	/// </summary>
	void thumb_b();
	/// <summary>
	/// Long branch with link.
	/// </summary>
	void thumb_bl();
	/// <summary>
	/// Operational state change, to either an address held in Lo or Hi 
	/// register.
	/// </summary>
	void thumb_bx();
	/// <summary>
	/// Branch if equal (if Z set).
	/// </summary>
	void thumb_beq();
	/// <summary>
	/// Branch if carry is clear (if C clear).
	/// </summary>
	void thumb_bcc();
	/// <summary>
	/// Branch if carry set (if C set).
	/// </summary>
	void thumb_bcs();
	/// <summary>
	/// Branch if greater than or equal to 
	/// (if (N set and V set) or (N clear and V clear)).
	/// </summary>
	void thumb_bge();
	/// <summary>
	/// Branch if greater than (signed), 
	/// (if Z clear and ((N or V set) or (N or V clear))).
	/// </summary>
	void thumb_bgt();
	/// <summary>
	/// Branch if greater than (unsigned), (if C set and Z clear).
	/// </summary>
	void thumb_bhi();
	/// <summary>
	/// Bit clear.
	/// </summary>
	void thumb_bic();
	/// <summary>
	/// Branch if less than or equal to (signed), 
	/// (if Z set or ((N set and V clear) or (N clear and V set))).
	/// </summary>
	void thumb_ble();
	/// <summary>
	/// Branch if less than or equal to (unsigned), 
	/// (if C is clear and Z is set).
	/// </summary>
	void thumb_bls();
	/// <summary>
	/// Branch if less than (if (N set and V clear) or (N clear and V set)).
	/// </summary>
	void thumb_blt();
	/// <summary>
	/// Branch if minus (if N set).
	/// </summary>
	void thumb_bmi();
	/// <summary>
	/// Branch if not equal (if Z clear).
	/// </summary>
	void thumb_bne();
	/// <summary>
	/// Branch if plus (if N clear).
	/// </summary>
	void thumb_bpl();
	/// <summary>
	/// Branch if overflow clear (if V clear).
	/// </summary>
	void thumb_bvc();
	/// <summary>
	/// Branch if overflow set (if V set).
	/// </summary>
	void thumb_bvs();
	/// <summary>
	/// Exclusive or.
	/// </summary>
	void thumb_eor();
	/// <summary>
	/// Compare negative.
	/// </summary>
	void thumb_cmn();
	/// <summary>
	/// Compare immediate, high to low, low to high, or high to high.
	/// </summary>
	void thumb_cmp();
	/// <summary>
	/// Load multiple.
	/// </summary>
	void thumb_ldmia();
	/// <summary>
	/// Load word with immediate offset, register offset, PC-relative,
	/// or SP relative.
	/// </summary>
	void thumb_ldr();
	/// <summary>
	/// Load byte with immediate offset or register offset.
	/// </summary>
	void thumb_ldrb();
	/// <summary>
	/// Load halfword with immediate offset or register offset.
	/// </summary>
	void thumb_ldrh();
	/// <summary>
	/// Load signed byte with register offset.
	/// </summary>
	void thumb_ldrsb();
	/// <summary>
	/// Logical shift left.
	/// </summary>
	void thumb_lsl();
	/// <summary>
	/// Logical shift right.
	/// </summary>
	void thumb_lsr();
	/// <summary>
	/// Move immediate, high to low, low to high, or high to high.
	/// </summary>
	void thumb_mov();
	/// <summary>
	/// Multiply.
	/// </summary>
	void thumb_mul();
	/// <summary>
	/// Move not.
	/// </summary>
	void thumb_mvn();
	/// <summary>
	/// Negate.
	/// </summary>
	void thumb_neg();
	/// <summary>
	/// Or.
	/// </summary>
	void thumb_or();
	/// <summary>
	/// Pop registers from stack, or pop registers and PC from stack.
	/// </summary>
	void thumb_pop();
	/// <summary>
	/// Push registers onto stack, or LR and registers onto stack.
	/// </summary>
	void thumb_push();
	/// <summary>
	/// Rotate right.
	/// </summary>
	void thumb_ror();
	/// <summary>
	/// Subtract with carry.
	/// </summary>
	void thumb_sbc();
	/// <summary>
	/// Store multiple.
	/// </summary>
	void thumb_stmia();
	/// <summary>
	/// Store word with immediate offset, register offset, or SP-relative.
	/// </summary>
	void thumb_str();
	/// <summary>
	/// Store byte with immediate offset or register offset.
	/// </summary>
	void thumb_strb();
	/// <summary>
	/// Store halfword with immediate offset or register offset.
	/// </summary>
	void thumb_strh();
	/// <summary>
	/// Subtract.
	/// </summary>
	void thumb_sub();
	/// <summary>
	/// Software interrupt.
	/// </summary>
	void thumb_swi();
	/// <summary>
	/// Test bits.
	/// </summary>
	void thumb_tst();

#pragma endregion

	void fetch();
	void decode();
	void execute();
	
private:
#pragma region ARM Decoding
	void decode_arm();
	void decode_thumb();

	void is_arm_data_processing_or_psr_transfer();
	void is_arm_multiply();
	void is_arm_multiply_long();
	void is_arm_single_data_swap();
	void is_arm_branch_exchange();
	void is_arm_halfword_data_transfer_register_offset();
	void is_arm_halfword_data_transfer_immediate_offset();
	void is_arm_single_data_transfer();
	void is_arm_undefined();
	void is_arm_block_data_transfer();
	void is_arm_branch();
	void is_arm_coprocessor_data_transfer();
	void is_arm_coprocessor_data_operation();
	void is_arm_coprocessor_register_transfer();
	void is_arm_software_interrupt();

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
	void asm_adc();
	void asm_add();
	void asm_and();
	void asm_bit();
	void asm_call();
	void asm_ccf();
	void asm_cp();
	void asm_cpl();
	void asm_daa();
	void asm_dec();
	void asm_di();
	void asm_ei();
	void asm_halt();
	void asm_inc();
	void asm_jp();
	void asm_jr();
	void asm_ld();
	void asm_ldh();
	void asm_nop();
	void asm_or();
	void asm_pop();
	void asm_push();
	void asm_res();
	void asm_ret();
	void asm_reti();
	void asm_rl();
	void asm_rla();
	void asm_rlc();
	void asm_rlca();
	void asm_rr();
	void asm_rra();
	void asm_rrc();
	void asm_rst();
	void asm_sbc();
	void asm_scf();
	void asm_set();
	void asm_sla();
	void asm_sra();
	void asm_srl();
	void asm_stop();
	void asm_sub();
	void asm_swap();
	void asm_xor();
};
