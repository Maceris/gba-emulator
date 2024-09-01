#pragma once

#include "memory/memory_types.h"

enum class ARMInstructionType : uint8_t
{
	ADC,
	ADD,
	ADR,//Pseudo
	ADRL,//Pseudo
	AND,
	ASR,//Pseudo
	B,
	BIC,
	BL,
	BX,
	CDP,
	CMN,
	CMP,
	EOR,
	LDC,
	LDM,
	LDR,
	LSL,//Pseudo
	LSR,//Pseudo
	MCR,
	MLA,
	MOV,
	MRC,
	MRS,
	MSR,
	MUL,
	MVN,
	NOP,//Pseudo
	ORR,
	POP,//Pseudo
	PUSH,//Pseudo
	ROR,//Pseudo
	RRX,//Pseudo
	RSB,
	RSC,
	SBC,
	SMLAL,
	SMULL,
	STC,
	STM,
	STR,
	SUB,
	SWI,
	SWP,
	TEQ,
	TST,
	UMLAL,
	UMULL,
	UNIMPLEMENTED
};

enum class ThumbInstructionType
{
	ADD,
	AND,
	ASR,
	B,
	BL,
	BX,
	BEQ,
	BCC,
	BCS,
	BGE,
	BGT,
	BHI,
	BIC,
	BLE,
	BLS,
	BLT,
	BMI,
	BNE,
	BPL,
	BVC,
	BVS,
	EOR,
	CMN,
	CMP,
	LDMIA,
	LDR,
	LDRB,
	LDRH,
	LDRSB,
	LSL,
	LSR,
	MOV,
	MUL,
	MVN,
	NEG,
	OR,
	POP,
	PUSH,
	ROR,
	SBC,
	STMIA,
	STR,
	STRB,
	STRH,
	SUB,
	SWI,
	TST
};

namespace DecodeArm
{
	ARMInstructionType constexpr decode(ArmInstruction instruction);
	ARMInstructionType constexpr decode_conditional_instruction(ArmInstruction instruction);
	ARMInstructionType constexpr decode_data_processing_and_miscellaneous(ArmInstruction instruction);
	ARMInstructionType constexpr decode_data_processing_register(ArmInstruction instruction);
	/// <summary>
	/// Handles decoding of Data Processing instructions, except when 
	/// op1 is 1101x, given that we already know it's either a 
	/// Data Processing (register-shifted register) or 
	/// Data Processing (register) instruction.
	/// </summary>
	/// <param name="op">The 5 bits of op1.</param>
	/// <returns>The appropriate instruction.</returns>
	ARMInstructionType constexpr decode_data_processing_register_shared(const ArmInstruction op);
	ARMInstructionType constexpr decode_data_processing_register_shifted_register(ArmInstruction instruction);
	ARMInstructionType constexpr decode_miscellaneous(ArmInstruction instruction);
	ARMInstructionType constexpr decode_halfword_multiply_and_multiply_accumulate(ArmInstruction instruction);
	ARMInstructionType constexpr decode_multiply_and_multiply_accumulate(ArmInstruction instruction);
	ARMInstructionType constexpr decode_synchronization_primitives(ArmInstruction instruction);
	ARMInstructionType constexpr decode_extra_load_store(ArmInstruction instruction);
	ARMInstructionType constexpr decode_extra_load_store_unprivileged(ArmInstruction instruction);
	ARMInstructionType constexpr decode_data_processing_immediate(ArmInstruction instruction);
	ARMInstructionType constexpr decode_msr_and_hints(ArmInstruction instruction);

	ARMInstructionType constexpr decode_load_store_word_and_unsigned_byte(ArmInstruction instruction);
	ARMInstructionType constexpr decode_media_instructions(ArmInstruction instruction);
	ARMInstructionType constexpr decode_branch_branch_with_link_and_block_data_transfer(ArmInstruction instruction);
	ARMInstructionType constexpr decode_coprocessor_and_supervisor_call(ArmInstruction instruction);
	ARMInstructionType constexpr decode_unconditional_instruction(ArmInstruction instruction);
}

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
	void arm_adc(ArmInstruction instruction);
	/// <summary>
	/// Add.
	/// </summary>
	void arm_add(ArmInstruction instruction);
	/// <summary>
	/// Load Address (short-range).
	/// </summary>
	void arm_adr(ArmInstruction instruction);
	/// <summary>
	/// Load Address (medium-range).
	/// </summary>
	void arm_adrl(ArmInstruction instruction);
	/// <summary>
	/// And.
	/// </summary>
	void arm_and(ArmInstruction instruction);
	/// <summary>
	/// Arithmetic Shift Right.
	/// </summary>
	void arm_asr(ArmInstruction instruction);
	/// <summary>
	/// Branch.
	/// </summary>
	void arm_b(ArmInstruction instruction);
	/// <summary>
	/// Bit clear.
	/// </summary>
	void arm_bic(ArmInstruction instruction);
	/// <summary>
	/// Branch with link;
	/// </summary>
	void arm_bl(ArmInstruction instruction);
	/// <summary>
	/// Branch and exchange.
	/// </summary>
	void arm_bx(ArmInstruction instruction);
	/// <summary>
	/// Coprocessor data processing.
	/// </summary>
	void arm_cdp(ArmInstruction instruction);
	/// <summary>
	/// Compare negative.
	/// </summary>
	void arm_cmn(ArmInstruction instruction);
	/// <summary>
	/// Compare.
	/// </summary>
	void arm_cmp(ArmInstruction instruction);
	/// <summary>
	/// Exclusive or.
	/// </summary>
	void arm_eor(ArmInstruction instruction);
	/// <summary>
	/// Load coprocessor from memory.
	/// </summary>
	void arm_ldc(ArmInstruction instruction);
	/// <summary>
	/// Load multiple registers.
	/// </summary>
	void arm_ldm(ArmInstruction instruction);
	/// <summary>
	/// Load register from memory.
	/// </summary>
	void arm_ldr(ArmInstruction instruction);
	/// <summary>
	/// Logical Shift Left.
	/// </summary>
	void arm_lsl(ArmInstruction instruction);
	/// <summary>
	/// Logical Shift Right.
	/// </summary>
	void arm_lsr(ArmInstruction instruction);
	/// <summary>
	/// Move CPU register to coprocessor register.
	/// </summary>
	void arm_mcr(ArmInstruction instruction);
	/// <summary>
	/// Multiply Accumulate.
	/// </summary>
	void arm_mla(ArmInstruction instruction);
	/// <summary>
	/// Move register or constant.
	/// </summary>
	void arm_mov(ArmInstruction instruction);
	/// <summary>
	/// Move from coprocessor register to CPU register.
	/// </summary>
	void arm_mrc(ArmInstruction instruction);
	/// <summary>
	/// Move PSR status/flags to register.
	/// </summary>
	void arm_mrs(ArmInstruction instruction);
	/// <summary>
	/// Move register to PSR status/flags.
	/// </summary>
	void arm_msr(ArmInstruction instruction);
	/// <summary>
	/// Multiply.
	/// </summary>
	void arm_mul(ArmInstruction instruction);
	/// <summary>
	/// Move negative register.
	/// </summary>
	void arm_mvn(ArmInstruction instruction);
	/// <summary>
	/// No Operation.
	/// </summary>
	void arm_nop(ArmInstruction instruction);
	/// <summary>
	/// Or.
	/// </summary>
	void arm_orr(ArmInstruction instruction);
	/// <summary>
	/// Pop.
	/// </summary>
	void arm_pop(ArmInstruction instruction);
	/// <summary>
	/// Push.
	/// </summary>
	void arm_push(ArmInstruction instruction);
	/// <summary>
	/// Rotate Right.
	/// </summary>
	void arm_ror(ArmInstruction instruction);
	/// <summary>
	/// Rotate Right with Extend.
	/// </summary>
	void arm_rrx(ArmInstruction instruction);
	/// <summary>
	/// Reverse subtract.
	/// </summary>
	void arm_rsb(ArmInstruction instruction);
	/// <summary>
	/// Reverse subtract with carry.
	/// </summary>
	void arm_rsc(ArmInstruction instruction);
	/// <summary>
	/// Subtract with carry.
	/// </summary>
	void arm_sbc(ArmInstruction instruction);
	/// <summary>
	/// Multiply signed accumulate long.
	/// </summary>
	void arm_smlal(ArmInstruction instruction);
	/// <summary>
	/// Multiply signed long.
	/// </summary>
	void arm_smull(ArmInstruction instruction);
	/// <summary>
	/// Store coprocessor register to memory.
	/// </summary>
	void arm_stc(ArmInstruction instruction);
	/// <summary>
	/// Store multiple.
	/// </summary>
	void arm_stm(ArmInstruction instruction);
	/// <summary>
	/// Store register to memory.
	/// </summary>
	void arm_str(ArmInstruction instruction);
	/// <summary>
	/// Subtract.
	/// </summary>
	void arm_sub(ArmInstruction instruction);
	/// <summary>
	/// Software interrupt.
	/// </summary>
	void arm_swi(ArmInstruction instruction);
	/// <summary>
	/// Swap register with memory.
	/// </summary>
	void arm_swp(ArmInstruction instruction);
	/// <summary>
	/// Test bitwise equality.
	/// </summary>
	void arm_teq(ArmInstruction instruction);
	/// <summary>
	/// Test bits.
	/// </summary>
	void arm_tst(ArmInstruction instruction);
	/// <summary>
	/// Multiply unsigned accumulate long.
	/// </summary>
	void arm_umlal(ArmInstruction instruction);
	/// <summary>
	/// Multiply unsigned long
	/// </summary>
	void arm_umull(ArmInstruction instruction);
#pragma endregion

#pragma region Thumb Instructions
	/// <summary>
	/// Add, or address.
	/// </summary>
	void thumb_add(ThumbInstruction instruction);
	/// <summary>
	/// And.
	/// </summary>
	void thumb_and(ThumbInstruction instruction);
	/// <summary>
	/// Arithmetic shift right.
	/// </summary>
	void thumb_asr(ThumbInstruction instruction);
	/// <summary>
	/// Unconditional branch.
	/// </summary>
	void thumb_b(ThumbInstruction instruction);
	/// <summary>
	/// Long branch with link.
	/// </summary>
	void thumb_bl(ThumbInstruction instruction);
	/// <summary>
	/// Operational state change, to either an address held in Lo or Hi 
	/// register.
	/// </summary>
	void thumb_bx(ThumbInstruction instruction);
	/// <summary>
	/// Branch if equal (if Z set).
	/// </summary>
	void thumb_beq(ThumbInstruction instruction);
	/// <summary>
	/// Branch if carry is clear (if C clear).
	/// </summary>
	void thumb_bcc(ThumbInstruction instruction);
	/// <summary>
	/// Branch if carry set (if C set).
	/// </summary>
	void thumb_bcs(ThumbInstruction instruction);
	/// <summary>
	/// Branch if greater than or equal to 
	/// (if (N set and V set) or (N clear and V clear)).
	/// </summary>
	void thumb_bge(ThumbInstruction instruction);
	/// <summary>
	/// Branch if greater than (signed), 
	/// (if Z clear and ((N or V set) or (N or V clear))).
	/// </summary>
	void thumb_bgt(ThumbInstruction instruction);
	/// <summary>
	/// Branch if greater than (unsigned), (if C set and Z clear).
	/// </summary>
	void thumb_bhi(ThumbInstruction instruction);
	/// <summary>
	/// Bit clear.
	/// </summary>
	void thumb_bic(ThumbInstruction instruction);
	/// <summary>
	/// Branch if less than or equal to (signed), 
	/// (if Z set or ((N set and V clear) or (N clear and V set))).
	/// </summary>
	void thumb_ble(ThumbInstruction instruction);
	/// <summary>
	/// Branch if less than or equal to (unsigned), 
	/// (if C is clear and Z is set).
	/// </summary>
	void thumb_bls(ThumbInstruction instruction);
	/// <summary>
	/// Branch if less than (if (N set and V clear) or (N clear and V set)).
	/// </summary>
	void thumb_blt(ThumbInstruction instruction);
	/// <summary>
	/// Branch if minus (if N set).
	/// </summary>
	void thumb_bmi(ThumbInstruction instruction);
	/// <summary>
	/// Branch if not equal (if Z clear).
	/// </summary>
	void thumb_bne(ThumbInstruction instruction);
	/// <summary>
	/// Branch if plus (if N clear).
	/// </summary>
	void thumb_bpl(ThumbInstruction instruction);
	/// <summary>
	/// Branch if overflow clear (if V clear).
	/// </summary>
	void thumb_bvc(ThumbInstruction instruction);
	/// <summary>
	/// Branch if overflow set (if V set).
	/// </summary>
	void thumb_bvs(ThumbInstruction instruction);
	/// <summary>
	/// Exclusive or.
	/// </summary>
	void thumb_eor(ThumbInstruction instruction);
	/// <summary>
	/// Compare negative.
	/// </summary>
	void thumb_cmn(ThumbInstruction instruction);
	/// <summary>
	/// Compare immediate, high to low, low to high, or high to high.
	/// </summary>
	void thumb_cmp(ThumbInstruction instruction);
	/// <summary>
	/// Load multiple.
	/// </summary>
	void thumb_ldmia(ThumbInstruction instruction);
	/// <summary>
	/// Load word with immediate offset, register offset, PC-relative,
	/// or SP relative.
	/// </summary>
	void thumb_ldr(ThumbInstruction instruction);
	/// <summary>
	/// Load byte with immediate offset or register offset.
	/// </summary>
	void thumb_ldrb(ThumbInstruction instruction);
	/// <summary>
	/// Load halfword with immediate offset or register offset.
	/// </summary>
	void thumb_ldrh(ThumbInstruction instruction);
	/// <summary>
	/// Load signed byte with register offset.
	/// </summary>
	void thumb_ldrsb(ThumbInstruction instruction);
	/// <summary>
	/// Logical shift left.
	/// </summary>
	void thumb_lsl(ThumbInstruction instruction);
	/// <summary>
	/// Logical shift right.
	/// </summary>
	void thumb_lsr(ThumbInstruction instruction);
	/// <summary>
	/// Move immediate, high to low, low to high, or high to high.
	/// </summary>
	void thumb_mov(ThumbInstruction instruction);
	/// <summary>
	/// Multiply.
	/// </summary>
	void thumb_mul(ThumbInstruction instruction);
	/// <summary>
	/// Move not.
	/// </summary>
	void thumb_mvn(ThumbInstruction instruction);
	/// <summary>
	/// Negate.
	/// </summary>
	void thumb_neg(ThumbInstruction instruction);
	/// <summary>
	/// Or.
	/// </summary>
	void thumb_or(ThumbInstruction instruction);
	/// <summary>
	/// Pop registers from stack, or pop registers and PC from stack.
	/// </summary>
	void thumb_pop(ThumbInstruction instruction);
	/// <summary>
	/// Push registers onto stack, or LR and registers onto stack.
	/// </summary>
	void thumb_push(ThumbInstruction instruction);
	/// <summary>
	/// Rotate right.
	/// </summary>
	void thumb_ror(ThumbInstruction instruction);
	/// <summary>
	/// Subtract with carry.
	/// </summary>
	void thumb_sbc(ThumbInstruction instruction);
	/// <summary>
	/// Store multiple.
	/// </summary>
	void thumb_stmia(ThumbInstruction instruction);
	/// <summary>
	/// Store word with immediate offset, register offset, or SP-relative.
	/// </summary>
	void thumb_str(ThumbInstruction instruction);
	/// <summary>
	/// Store byte with immediate offset or register offset.
	/// </summary>
	void thumb_strb(ThumbInstruction instruction);
	/// <summary>
	/// Store halfword with immediate offset or register offset.
	/// </summary>
	void thumb_strh(ThumbInstruction instruction);
	/// <summary>
	/// Subtract.
	/// </summary>
	void thumb_sub(ThumbInstruction instruction);
	/// <summary>
	/// Software interrupt.
	/// </summary>
	void thumb_swi(ThumbInstruction instruction);
	/// <summary>
	/// Test bits.
	/// </summary>
	void thumb_tst(ThumbInstruction instruction);

#pragma endregion

	void fetch();
	void decode();
	void execute();

private:
#pragma region ARM Decoding
	ARMInstructionType decode_arm(ArmInstruction instruction);
	ThumbInstructionType decode_thumb(ThumbInstruction instruction);

	bool constexpr is_arm_block_data_transfer(ArmInstruction instruction);
	bool constexpr is_arm_branch(ArmInstruction instruction);
	bool constexpr is_arm_branch_exchange(ArmInstruction instruction);
	bool constexpr is_arm_coprocessor_data_transfer(ArmInstruction instruction);
	bool constexpr is_arm_coprocessor_data_operation(ArmInstruction instruction);
	bool constexpr is_arm_coprocessor_register_transfer(ArmInstruction instruction);
	bool constexpr is_arm_data_processing(ArmInstruction instruction);
	bool constexpr is_arm_halfword_data_transfer_immediate_offset(ArmInstruction instruction);
	bool constexpr is_arm_halfword_data_transfer_register_offset(ArmInstruction instruction);
	bool constexpr is_arm_multiply(ArmInstruction instruction);
	bool constexpr is_arm_psr_transfer_mrs(ArmInstruction instruction);
	bool constexpr is_arm_psr_transfer_msr(ArmInstruction instruction);
	bool constexpr is_arm_single_data_swap(ArmInstruction instruction);
	bool constexpr is_arm_single_data_transfer(ArmInstruction instruction);
	bool constexpr is_arm_software_interrupt(ArmInstruction instruction);
	bool constexpr is_arm_undefined(ArmInstruction instruction);

#pragma endregion

};

