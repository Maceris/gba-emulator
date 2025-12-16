#pragma once

#include "memory/memory_types.h"

enum class ARMInstructionType : uint8_t
{
	/// <summary>
	/// Add with carry.
	/// </summary>
	ADC,
	/// <summary>
	/// Add.
	/// </summary>
	ADD,
	/// <summary>
	/// Load Address (short-range). Pseudo-instruction.
	/// </summary>
	ADR,
	/// <summary>
	/// Load Address (medium-range). Pseudo-instruction.
	/// </summary>
	ADRL,
	/// <summary>
	/// And.
	/// </summary>
	AND,
	/// <summary>
	/// Arithmetic Shift Right. Pseudo-instruction.
	/// </summary>
	ASR,
	/// <summary>
	/// Branch.
	/// </summary>
	B,
	/// <summary>
	/// Bit clear.
	/// </summary>
	BIC,
	/// <summary>
	/// Branch with link. Pseudo-instruction.
	/// </summary>
	BL,
	/// <summary>
	/// Branch and exchange.
	/// </summary>
	BX,
	/// <summary>
	/// Coprocessor data processing.
	/// </summary>
	CDP,
	/// <summary>
	/// Compare negative.
	/// </summary>
	CMN,
	/// <summary>
	/// Compare.
	/// </summary>
	CMP,
	/// <summary>
	/// Exclusive or.
	/// </summary>
	EOR,
	/// <summary>
	/// Load coprocessor from memory.
	/// </summary>
	LDC,
	/// <summary>
	/// Load multiple registers.
	/// </summary>
	LDM,
	/// <summary>
	/// Load multiple registers, exception return.
	/// </summary>
	LDM_EXCEPTION,
	/// <summary>
	/// Load multiple, decrement after.
	/// </summary>
	LDMDA,
	/// <summary>
	/// Load multiple, decrement before.
	/// </summary>
	LDMDB,
	/// <summary>
	/// Load multiple, increment after.
	/// </summary>
	LDMIA,
	/// <summary>
	/// Load multiple, increment before.
	/// </summary>
	LDMIB,
	/// <summary>
	/// Load register from memory.
	/// </summary>
	LDR,
	/// <summary>
	/// Load Register Byte.
	/// </summary>
	LDRB,
	/// <summary>
	/// Load Register Byte Unprivileged.
	/// </summary>
	LDRBT,
	/// <summary>
	/// Load Register Halfword.
	/// </summary>
	LDRH,
	/// <summary>
	/// Load Register Signed Byte.
	/// </summary>
	LDRSB,
	/// <summary>
	/// Load Register Signed Halfword.
	/// </summary>
	LDRSH,
	/// <summary>
	/// Load Register Unprivileged.
	/// </summary>
	LDRT,
	/// <summary>
	/// Logical Shift Left. Pseudo-instruction.
	/// </summary>
	LSL,
	/// <summary>
	/// Logical Shift Right. Pseudo-instruction.
	/// </summary>
	LSR,
	/// <summary>
	/// Move CPU register to coprocessor register.
	/// </summary>
	MCR,
	/// <summary>
	/// Multiply Accumulate.
	/// </summary>
	MLA,
	/// <summary>
	/// Move register or constant.
	/// </summary>
	MOV,
	/// <summary>
	/// Move from coprocessor register to CPU register.
	/// </summary>
	MRC,
	/// <summary>
	/// Move PSR status/flags to register.
	/// </summary>
	MRS,
	/// <summary>
	/// Move register to PSR status/flags.
	/// </summary>
	MSR,
	/// <summary>
	/// Multiply.
	/// </summary>
	MUL,
	/// <summary>
	/// Move negative register.
	/// </summary>
	MVN,
	/// <summary>
	/// No Operation. Pseudo-instruction.
	/// </summary>
	NOP,
	/// <summary>
	/// Or.
	/// </summary>
	ORR,
	/// <summary>
	/// Pop. Pseudo-instruction.
	/// </summary>
	POP,
	/// <summary>
	/// Push. Pseudo-instruction.
	/// </summary>
	PUSH,
	/// <summary>
	/// Rotate Right. Pseudo-instruction.
	/// </summary>
	ROR,
	/// <summary>
	/// Rotate Right with Extend. Pseudo-instruction.
	/// </summary>
	RRX,
	/// <summary>
	/// Reverse subtract.
	/// </summary>
	RSB,
	/// <summary>
	/// Reverse subtract with carry.
	/// </summary>
	RSC,
	/// <summary>
	/// Subtract with carry.
	/// </summary>
	SBC,
	/// <summary>
	/// Multiply signed accumulate long.
	/// </summary>
	SMLAL,
	/// <summary>
	/// Multiply signed long.
	/// </summary>
	SMULL,
	/// <summary>
	/// Store coprocessor register to memory.
	/// </summary>
	STC,
	/// <summary>
	/// Store multiple.
	/// </summary>
	STM,
	/// <summary>
	/// Store multiple, decrement after.
	/// </summary>
	STMDA,
	/// <summary>
	/// Store multiple, decrement before.
	/// </summary>
	STMDB,
	/// <summary>
	/// Store multiple, increment after.
	/// </summary>
	STMIA,
	/// <summary>
	/// Store multiple, increment before.
	/// </summary>
	STMIB,
	/// <summary>
	/// Store register to memory.
	/// </summary>
	STR,
	/// <summary>
	/// Store register byte.
	/// </summary>
	STRB,
	/// <summary>
	/// Store register byte unprivileged.
	/// </summary>
	STRBT,
	/// <summary>
	/// Store register halfword.
	/// </summary>
	STRH,
	/// <summary>
	/// Store register unprivileged.
	/// </summary>
	STRT,
	/// <summary>
	/// Subtract.
	/// </summary>
	SUB,
	/// <summary>
	/// Software interrupt.
	/// </summary>
	SWI,
	/// <summary>
	/// Swap register with memory.
	/// </summary>
	SWP,
	/// <summary>
	/// Test bitwise equality.
	/// </summary>
	TEQ,
	/// <summary>
	/// Test bits.
	/// </summary>
	TST,
	/// <summary>
	/// Permanently undefined.
	/// </summary>
	UDF,
	/// <summary>
	/// Multiply unsigned accumulate long.
	/// </summary>
	UMLAL,
	/// <summary>
	/// Multiply unsigned long.
	/// </summary>
	UMULL,
	UNIMPLEMENTED
};

enum class ThumbInstructionType
{
	/// <summary>
	/// Add, or address.
	/// </summary>
	ADD,
	/// <summary>
	/// And.
	/// </summary>
	AND,
	/// <summary>
	/// Arithmetic shift right.
	/// </summary>
	ASR,
	/// <summary>
	/// Unconditional branch.
	/// </summary>
	B,
	/// <summary>
	/// Long branch with link.
	/// </summary>
	BL,
	/// <summary>
	/// Operational state change, to either an address held in Lo or Hi 
	/// register.
	/// </summary>
	BX,
	/// <summary>
	/// Branch if equal (if Z set).
	/// </summary>
	BEQ,
	/// <summary>
	/// Branch if carry is clear (if C clear).
	/// </summary>
	BCC,
	/// <summary>
	/// Branch if carry set (if C set).
	/// </summary>
	BCS,
	/// <summary>
	/// Branch if greater than or equal to 
	/// (if (N set and V set) or (N clear and V clear)).
	/// </summary>
	BGE,
	/// <summary>
	/// Branch if greater than (signed), 
	/// (if Z clear and ((N or V set) or (N or V clear))).
	/// </summary>
	BGT,
	/// <summary>
	/// Branch if greater than (unsigned), (if C set and Z clear).
	/// </summary>
	BHI,
	/// <summary>
	/// Bit clear.
	/// </summary>
	BIC,
	/// <summary>
	/// Branch if less than or equal to (signed), 
	/// (if Z set or ((N set and V clear) or (N clear and V set))).
	/// </summary>
	BLE,
	/// <summary>
	/// Branch if less than or equal to (unsigned), 
	/// (if C is clear and Z is set).
	/// </summary>
	BLS,
	/// <summary>
	/// Branch if less than (if (N set and V clear) or (N clear and V set)).
	/// </summary>
	BLT,
	/// <summary>
	/// Branch if minus (if N set).
	/// </summary>
	BMI,
	/// <summary>
	/// Branch if not equal (if Z clear).
	/// </summary>
	BNE,
	/// <summary>
	/// Branch if plus (if N clear).
	/// </summary>
	BPL,
	/// <summary>
	/// Branch if overflow clear (if V clear).
	/// </summary>
	BVC,
	/// <summary>
	/// Branch if overflow set (if V set).
	/// </summary>
	BVS,
	/// <summary>
	/// Exclusive or.
	/// </summary>
	EOR,
	/// <summary>
	/// Compare negative.
	/// </summary>
	CMN,
	/// <summary>
	/// Compare immediate, high to low, low to high, or high to high.
	/// </summary>
	CMP,
	/// <summary>
	/// Load multiple.
	/// </summary>
	LDMIA,
	/// <summary>
	/// Load word with immediate offset, register offset, PC-relative,
	/// or SP relative.
	/// </summary>
	LDR,
	/// <summary>
	/// Load byte with immediate offset or register offset.
	/// </summary>
	LDRB,
	/// <summary>
	/// Load halfword with immediate offset or register offset.
	/// </summary>
	LDRH,
	/// <summary>
	/// Load signed byte with register offset.
	/// </summary>
	LDRSB,
	/// <summary>
	/// Logical shift left.
	/// </summary>
	LSL,
	/// <summary>
	/// Logical shift right.
	/// </summary>
	LSR,
	/// <summary>
	/// Move immediate, high to low, low to high, or high to high.
	/// </summary>
	MOV,
	/// <summary>
	/// Multiply.
	/// </summary>
	MUL,
	/// <summary>
	/// Move not.
	/// </summary>
	MVN,
	/// <summary>
	/// Negate.
	/// </summary>
	NEG,
	/// <summary>
	/// Or.
	/// </summary>
	OR,
	/// <summary>
	/// Pop registers from stack, or pop registers and PC from stack.
	/// </summary>
	POP,
	/// <summary>
	/// Push registers onto stack, or LR and registers onto stack.
	/// </summary>
	PUSH,
	/// <summary>
	/// Rotate right.
	/// </summary>
	ROR,
	/// <summary>
	/// Subtract with carry.
	/// </summary>
	SBC,
	/// <summary>
	/// Store multiple.
	/// </summary>
	STMIA,
	/// <summary>
	/// Store word with immediate offset, register offset, or SP-relative.
	/// </summary>
	STR,
	/// <summary>
	/// Store byte with immediate offset or register offset.
	/// </summary>
	STRB,
	/// <summary>
	/// Store halfword with immediate offset or register offset.
	/// </summary>
	STRH,
	/// <summary>
	/// Subtract.
	/// </summary>
	SUB,
	/// <summary>
	/// Software interrupt.
	/// </summary>
	SWI,
	/// <summary>
	/// Test bits.
	/// </summary>
	TST,
	UNIMPLEMENTED
};

namespace DecodeArm
{
	ARMInstructionType constexpr decode(ArmInstruction instruction);
	ARMInstructionType constexpr decode_conditional_instruction(ArmInstruction instruction);
	ARMInstructionType constexpr decode_data_processing_and_miscellaneous(ArmInstruction instruction);
	ARMInstructionType constexpr decode_data_processing_immediate(ArmInstruction instruction);
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
	ARMInstructionType constexpr decode_multiply_and_multiply_accumulate(ArmInstruction instruction);
	ARMInstructionType constexpr decode_synchronization_primitives(ArmInstruction instruction);
	ARMInstructionType constexpr decode_extra_load_store(ArmInstruction instruction);
	ARMInstructionType constexpr decode_msr_and_hints(ArmInstruction instruction);

	/// <summary>
	/// Decode load/store word and unsigned byte instructions, given the 
	/// below information.
	/// 
	/// 31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 10  9  8  7  6  5  4  3  2  1  0
	/// ____cond___  0  1  A _____op1______ ____Rn_____                                B
	/// 
	/// Either bits A or B may be 1, but not both.
	/// 
	/// </summary>
	/// <param name="instruction">The instruction to decode.</param>
	/// <returns>The appropriate instruction.</returns>
	ARMInstructionType constexpr decode_load_store_word_and_unsigned_byte(ArmInstruction instruction);
	ARMInstructionType constexpr decode_media_instructions(ArmInstruction instruction);

	ARMInstructionType constexpr decode_branch_branch_with_link_and_block_data_transfer(ArmInstruction instruction);
	ARMInstructionType constexpr decode_coprocessor_and_supervisor_call(ArmInstruction instruction);
	ARMInstructionType constexpr decode_unconditional_instruction(ArmInstruction instruction);
}

namespace DecodeThumb {
	ThumbInstructionType constexpr decode(ThumbInstruction instruction);
	ThumbInstructionType constexpr decode_16(ThumbInstruction instruction);
	ThumbInstructionType constexpr decode_32(ThumbInstruction instruction);
}

/// <summary>
/// A 16.78 MHz ARM7TDMI RISC processor, featuring 16-bit Thumb, JTAG Debug,
/// fast multiplier, and enhanced ICE.
/// 
/// While called ARM7, it's an implementation of the ARMv4T architecture.
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
	/// Branch with link.
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
	/// Load multiple registers, exception return.
	/// </summary>
	void arm_ldm_exception(ArmInstruction instruction);
	/// <summary>
	/// Load multiple, decrement after.
	/// </summary>
	void arm_ldmda(ArmInstruction instruction);
	/// <summary>
	/// Load multiple, decrement before.
	/// </summary>
	void arm_ldmdb(ArmInstruction instruction);
	/// <summary>
	/// Load multiple, increment after.
	/// </summary>
	void arm_ldmia(ArmInstruction instruction);
	/// <summary>
	/// Load multiple, increment before.
	/// </summary>
	void arm_ldmib(ArmInstruction instruction);
	/// <summary>
	/// Load register from memory.
	/// </summary>
	void arm_ldr(ArmInstruction instruction);
	/// <summary>
	/// Load register byte.
	/// </summary>
	void arm_ldrb(ArmInstruction instruction);
	/// <summary>
	/// Load register byte unprivileged.
	/// </summary>
	void arm_ldrbt(ArmInstruction instruction);
	/// <summary>
	/// Load register halfword.
	/// </summary>
	void arm_ldrh(ArmInstruction instruction);
	/// <summary>
	/// Load register signed byte.
	/// </summary>
	void arm_ldrsb(ArmInstruction instruction);
	/// <summary>
	/// Load register signed halfword.
	/// </summary>
	void arm_ldrsh(ArmInstruction instruction);
	/// <summary>
	/// Load register unprivileged.
	/// </summary>
	void arm_ldrt(ArmInstruction instruction);
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
	/// Store multiple, decrement after.
	/// </summary>
	void arm_stmda(ArmInstruction instruction);
	/// <summary>
	/// Store multiple, decrement before.
	/// </summary>
	void arm_stmdb(ArmInstruction instruction);
	/// <summary>
	/// Store multiple, increment after.
	/// </summary>
	void arm_stmia(ArmInstruction instruction);
	/// <summary>
	/// Store multiple, increment before.
	/// </summary>
	void arm_stmib(ArmInstruction instruction);
	/// <summary>
	/// Store register to memory.
	/// </summary>
	void arm_str(ArmInstruction instruction);
	/// <summary>
	/// Store register byte.
	/// </summary>
	void arm_strb(ArmInstruction instruction);
	/// <summary>
	/// Store register byte unprivileged.
	/// </summary>
	void arm_strbt(ArmInstruction instruction);
	/// <summary>
	/// Store register dual.
	/// </summary>
	void arm_strd(ArmInstruction instruction);
	/// <summary>
	/// Store register halfword.
	/// </summary>
	void arm_strh(ArmInstruction instruction);
	/// <summary>
	/// Store register unprivileged.
	/// </summary>
	void arm_strt(ArmInstruction instruction);
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
	/// Permanently undefined.
	/// </summary>
	void arm_udf(ArmInstruction instruction);
	/// <summary>
	/// Multiply unsigned accumulate long.
	/// </summary>
	void arm_umlal(ArmInstruction instruction);
	/// <summary>
	/// Multiply unsigned long.
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
#pragma endregion

};

