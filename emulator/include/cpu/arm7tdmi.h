#pragma once

#include "board/wire.h"
#include "memory/memory_types.h"

namespace emulator {

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

	/// <summary>
	/// Condition fields, named the same as the suffix used in instructions.
	/// These also happen to be in order, matching their cond value.
	/// </summary>
	enum class ARMCond : ArmInstruction {
		/// <summary>
		/// Equal.
		/// </summary>
		EQ,
		/// <summary>
		/// Not equal.
		/// </summary>
		NE,
		/// <summary>
		/// Unsigned higher, or same.
		/// </summary>
		CS,
		/// <summary>
		/// Unsigned lower.
		/// </summary>
		CC,
		/// <summary>
		/// Negative.
		/// </summary>
		MI,
		/// <summary>
		/// Positive, or zero.
		/// </summary>
		PL,
		/// <summary>
		/// Overflow
		/// </summary>
		VS,
		/// <summary>
		/// No overflow.
		/// </summary>
		VC,
		/// <summary>
		/// Unsigned higher.
		/// </summary>
		HI,
		/// <summary>
		/// Unsigned lower, or same.
		/// </summary>
		LS,
		/// <summary>
		/// Greater, or equal.
		/// </summary>
		GE,
		/// <summary>
		/// Less than.
		/// </summary>
		LT,
		/// <summary>
		/// Greater than.
		/// </summary>
		GT,
		/// <summary>
		/// Less than, or equal.
		/// </summary>
		LE,
		/// <summary>
		/// Always.
		/// </summary>
		AL,
	};

	/// <summary>
	/// Converts the 4-bit cond code to the appropriate conditional code.
	/// 0b1111u is only present for instructions that execute unconditionally,
	/// so we will return AL for that as well as the legitimate AL (0b1110u).
	/// </summary>
	/// <param name="cond">The 4 bits of the cond code.</param>
	/// <returns>The appropriate conditional code.</returns>
	ARMCond cond_to_enum(ArmInstruction cond);

	enum class ThumbInstructionType
	{
		/// <summary>
		/// Add, or address.
		/// </summary>
		ADD,
		/// <summary>
		/// Add with carry.
		/// </summary>
		ADC,
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
		/// Load signed halfword with register offset.
		/// </summary>
		LDRSH,
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
		/// No Operation.
		/// </summary>
		NOP,
		/// <summary>
		/// Or.
		/// </summary>
		ORR,
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
		/// Reverse subtract.
		/// </summary>
		RSB,
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
		bool constexpr is_32_bit(ThumbInstruction instruction);
		ThumbInstructionType constexpr decode_16(ThumbInstruction instruction);
		ThumbInstructionType constexpr decode_16_shift_add_sub_mov_cmp(ThumbInstruction instruction);
		ThumbInstructionType constexpr decode_16_data_processing(ThumbInstruction instruction);
		ThumbInstructionType constexpr decode_16_special_data_branch_exchange(ThumbInstruction instruction);
		ThumbInstructionType constexpr decode_16_load_store_single_data(ThumbInstruction instruction);
		ThumbInstructionType constexpr decode_16_misc(ThumbInstruction instruction);
		ThumbInstructionType constexpr decode_16_conditional_branch_supervisor(ThumbInstruction instruction);
		ThumbInstructionType constexpr decode_32(ThumbInstruction first_instruction, ThumbInstruction second_instruction);
		ThumbInstructionType constexpr decode_32_load_store_multiple(ThumbInstruction first_instruction);
		ThumbInstructionType constexpr decode_32_data_processing_shifted_register(ThumbInstruction first_instruction, ThumbInstruction second_instruction);
		ThumbInstructionType constexpr decode_32_load_single(ThumbInstruction first_instruction, ThumbInstruction second_instruction);
		ThumbInstructionType constexpr decode_32_load_byte_memory_hints(ThumbInstruction first_instruction, ThumbInstruction second_instruction);
		ThumbInstructionType constexpr decode_32_load_halfword_memory_hints(ThumbInstruction first_instruction, ThumbInstruction second_instruction);
		ThumbInstructionType constexpr decode_32_load_word(ThumbInstruction first_instruction, ThumbInstruction second_instruction);
		ThumbInstructionType constexpr decode_32_data_processing_register(ThumbInstruction first_instruction, ThumbInstruction second_instruction);
		ThumbInstructionType constexpr decode_32_multiply_multiply_accumulate_absolute_difference(ThumbInstruction first_instruction, ThumbInstruction second_instruction);
	}

	enum class ArmMode {
		/// <summary>
		/// User.
		/// </summary>
		USR,
		/// <summary>
		/// Fast Interrupt.
		/// </summary>
		FIQ,
		/// <summary>
		/// Interrupt.
		/// </summary>
		IRQ,
		/// <summary>
		/// Supervisor.
		/// </summary>
		SVC,
		/// <summary>
		/// Abort.
		/// </summary>
		ABT,
		/// <summary>
		/// Undefined.
		/// </summary>
		UND,
		/// <summary>
		/// System.
		/// </summary>
		SYS,
	};

	/// <summary>
	/// A 16.78 MHz ARM7TDMI RISC processor, featuring 16-bit Thumb, JTAG Debug,
	/// fast multiplier, and enhanced ICE.
	/// 
	/// While called ARM7, it's an implementation of the ARMv4T architecture.
	/// </summary>
	struct ARM7TDMI
	{
#pragma region Registers
		// System (sys)/User (usr) Registers

		/// <summary>
		/// General purpose register. Available in both ARM and THUMB state.
		/// </summary>
		Register R0;
		/// <summary>
		/// General purpose register. Available in both ARM and THUMB state.
		/// </summary>
		Register R1;
		/// <summary>
		/// General purpose register. Available in both ARM and THUMB state.
		/// </summary>
		Register R2;
		/// <summary>
		/// General purpose register. Available in both ARM and THUMB state.
		/// </summary>
		Register R3;
		/// <summary>
		/// General purpose register. Available in both ARM and THUMB state.
		/// </summary>
		Register R4;
		/// <summary>
		/// General purpose register. Available in both ARM and THUMB state.
		/// </summary>
		Register R5;
		/// <summary>
		/// General purpose register. Available in both ARM and THUMB state.
		/// </summary>
		Register R6;
		/// <summary>
		/// General purpose register. Available in both ARM and THUMB state.
		/// </summary>
		Register R7;

		/// <summary>
		/// General purpose register. Only available in ARM state.
		/// </summary>
		Register R8;
		/// <summary>
		/// General purpose register. Only available in ARM state.
		/// </summary>
		Register R9;
		/// <summary>
		/// General purpose register. Only available in ARM state.
		/// </summary>
		Register R10;
		/// <summary>
		/// General purpose register. Only available in ARM state.
		/// </summary>
		Register R11;
		/// <summary>
		/// General purpose register. Only available in ARM state.
		/// </summary>
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
		/// respective exception mode.
		/// <para/>
		/// 
		/// |--------------------------------------------|<para/>
		/// |31|30|29|28|27 --- 8| 7| 6| 5| 4| 3| 2| 1| 0|<para/>
		/// |--+--+--+--+--------+--+--+--+--+--+--+--+--|<para/>
		/// | N| Z| C| V|Reserved| I| F| T|M4|M3|M2|M1|M0|<para/>
		/// |--------------------------------------------|<para/>
		/// N = Negative or less than
		/// Z = Zero
		/// C = Carry or borrow or extend
		/// V = Overflow
		/// I - IRQ disable
		/// F = FIQ disable
		/// T = State bit
		/// M4-M0 = Mode bits
		/// </summary>
		Register CPSR;

		// Fast Interrupt (fiq) Registers

		/// <summary>
		/// Banked version of a general purpose register for FIQ mode.
		/// Only available in ARM state.
		/// </summary>
		Register R8_fiq;
		/// <summary>
		/// Banked version of a general purpose register for FIQ mode.
		/// Only available in ARM state.
		/// </summary>
		Register R9_fiq;
		/// <summary>
		/// Banked version of a general purpose register for FIQ mode.
		/// Only available in ARM state.
		/// </summary>
		Register R10_fiq;
		/// <summary>
		/// Banked version of a general purpose register for FIQ mode.
		/// Only available in ARM state.
		/// </summary>
		Register R11_fiq;
		/// <summary>
		/// Banked version of a general purpose register for FIQ mode.
		/// Only available in ARM state.
		/// </summary>
		Register R12_fiq;
		/// <summary>
		/// Banked version for FIQ mode, used as the Stack Pointer (SP)
		/// in THUMB state, the ARM state may or may not use this as
		/// a stack pointer.
		/// </summary>
		Register R13_fiq;
		/// <summary>
		/// Banked version of the Link Register (LR) for FIQ mode. 
		/// When calling a sub-routine using a BL instruction, 
		/// the return address is saved here. ARM state may use this as a
		/// general register.
		/// </summary>
		Register R14_fiq;
		/// <summary>
		/// Banked version of the Saved Program Status Register for FIQ mode. 
		/// Contains condition code flags, and mode bits saved as a result of
		/// the exception that caused entry to the current mode.
		/// </summary>
		Register SPSR_fiq;

		// Supervisor (svc) Registers

		/// <summary>
		/// Banked version for SVC mode, used as the Stack Pointer (SP)
		/// in THUMB state, the ARM state may or may not use this as
		/// a stack pointer.
		/// </summary>
		Register R13_svc;
		/// <summary>
		/// Banked version of the Link Register (LR) for SVC mode. 
		/// When calling a sub-routine using a BL instruction, 
		/// the return address is saved here. ARM state may use this as a
		/// general register.
		/// </summary>
		Register R14_svc;
		/// <summary>
		/// Banked version of the Saved Program Status Register for SVC mode. 
		/// Contains condition code flags, and mode bits saved as a result of
		/// the exception that caused entry to the current mode.
		/// </summary>
		Register SPSR_svc;

		// Abort (abt) Registers

		/// <summary>
		/// Banked version for ABT mode, used as the Stack Pointer (SP)
		/// in THUMB state, the ARM state may or may not use this as
		/// a stack pointer.
		/// </summary>
		Register R13_abt;
		/// <summary>
		/// Banked version of the Link Register (LR) for ABT mode. 
		/// When calling a sub-routine using a BL instruction, 
		/// the return address is saved here. ARM state may use this as a
		/// general register.
		/// </summary>
		Register R14_abt;
		/// <summary>
		/// Banked version of the Saved Program Status Register for ABT mode. 
		/// Contains condition code flags, and mode bits saved as a result of
		/// the exception that caused entry to the current mode.
		/// </summary>
		Register SPSR_abt;

		// Interrupt (irq) Registers

		/// <summary>
		/// Banked version for IRQ mode, used as the Stack Pointer (SP)
		/// in THUMB state, the ARM state may or may not use this as
		/// a stack pointer.
		/// </summary>
		Register R13_irq;
		/// <summary>
		/// Banked version of the Link Register (LR) for IRQ mode. 
		/// When calling a sub-routine using a BL instruction, 
		/// the return address is saved here. ARM state may use this as a
		/// general register.
		/// </summary>
		Register R14_irq;
		/// <summary>
		/// Banked version of the Saved Program Status Register for IRQ mode. 
		/// Contains condition code flags, and mode bits saved as a result of
		/// the exception that caused entry to the current mode.
		/// </summary>
		Register SPSR_irq;

		// Undefined (und) Registers

		/// <summary>
		/// Banked version for UND mode, used as the Stack Pointer (SP)
		/// in THUMB state, the ARM state may or may not use this as
		/// a stack pointer.
		/// </summary>
		Register R13_und;
		/// <summary>
		/// Banked version of the Link Register (LR) for UND mode. 
		/// When calling a sub-routine using a BL instruction, 
		/// the return address is saved here. ARM state may use this as a
		/// general register.
		/// </summary>
		Register R14_und;
		/// <summary>
		/// Banked version of the Saved Program Status Register for UND mode. 
		/// Contains condition code flags, and mode bits saved as a result of
		/// the exception that caused entry to the current mode.
		/// </summary>
		Register SPSR_und;
#pragma endregion

#pragma region External interface
	
		// Clock
		WIRE_INCOMING Wire1 CLK;
		WIRE_INCOMING Wire1 CLKEN;

		// Interrupts
		WIRE_INCOMING Wire1 nIRQ;
		WIRE_INCOMING Wire1 nFIQ;
		WIRE_INCOMING Wire1 nRESET;

		// Bus control
		WIRE_INCOMING Wire1 CFGBIGEND;

		// Arbitration
		WIRE_OUTGOING Wire1 DMORE;
		WIRE_OUTGOING Wire1 LOCK;

		// Debug
		WIRE_OUTGOING Wire1 DBGINSTRVALID;
		WIRE_INCOMING Wire1 DBGRQ;
		WIRE_INCOMING Wire1 DBGBREAK;
		WIRE_OUTGOING Wire1 DBGACK;
		WIRE_OUTGOING Wire1 DBGnEXEC;
		WIRE_INCOMING Wire1 DBGEXT0;
		WIRE_INCOMING Wire1 DBGEXT1;
		WIRE_INCOMING Wire1 DBGGEN;
		WIRE_OUTGOING Wire1 DBGRNG0;
		WIRE_OUTGOING Wire1 DBGRNG1;
		WIRE_OUTGOING Wire1 DBGCOMMRX;
		WIRE_OUTGOING Wire1 DBGCOMMTX;

		// Synchronized EmbeddedICE-RT scan debug access port
		WIRE_INCOMING Wire1 DBGTCKEN;
		WIRE_INCOMING Wire1 DBGTMS;
		WIRE_INCOMING Wire1 DBGTDI;
		WIRE_INCOMING Wire1 DBGnTRST;
		WIRE_OUTGOING Wire1 DBGTDO;
		WIRE_OUTGOING Wire1 DBGnTDOEN;

		// Memory interface
		WIRE_INCOMING Wire1 ABORT;
		WIRE_OUTGOING Wire1 WRITE;
		WIRE_OUTGOING Wire32 ADDR;
		WIRE_OUTGOING Wire32 WDATA;
		WIRE_INCOMING Wire32 RDATA;
		WIRE_OUTGOING Wire2 SIZE;
		WIRE_OUTGOING Wire2 PROT;
		WIRE_OUTGOING Wire2 TRANS;

		// Memory management interface
		WIRE_OUTGOING Wire1 CPnTRANS;
		WIRE_OUTGOING Wire1 CPnOPC;

		// Coprocessor interface
		WIRE_OUTGOING Wire1 CPnMREQ;
		WIRE_OUTGOING Wire1 CPSEQ;
		WIRE_OUTGOING Wire1 CPTBIT;
		WIRE_OUTGOING Wire1 CPnl;
		WIRE_INCOMING Wire1 CPA;
		WIRE_INCOMING Wire1 CPB;

#pragma endregion

#pragma region Internal wires

		/// <summary>
		/// Connects from the register bank to the 32x8 multiplier and 32-bit ALU.
		/// </summary>
		WIRE_INTERNAL Wire32 bus_A;

		/// <summary>
		/// Connects from the register bank, barrel shifter, instruction pipeline,
		/// read sata register, thumb instruction decoder, and 32x8 multiplier
		/// to the write data register, and 32x8 multiplier.
		/// </summary>
		WIRE_INTERNAL Wire32 bus_B;

		/// <summary>
		/// Connects from the 32-bit ALU to the register bank, and address 
		/// register.
		/// </summary>
		WIRE_INTERNAL Wire32 bus_ALU;

		/// <summary>
		/// Connects from the address incrementer to the address register, and
		/// the register bank.
		/// </summary>
		WIRE_INTERNAL Wire32 bus_incrementer;

		/// <summary>
		/// Connects from the register bank to the address register.
		/// </summary>
		WIRE_INTERNAL Wire32 bus_PC;
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
		/// Add with carry.
		/// </summary>
		void thumb_adc(ThumbInstruction instruction);
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
		/// Load signed halfword with register offset.
		/// </summary>
		void thumb_ldrsh(ThumbInstruction instruction);
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
		/// No operation.
		/// </summary>
		void thumb_nop(ThumbInstruction instruction);
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
		/// Reverse subtract.
		/// </summary>
		void thumb_rsb(ThumbInstruction instruction);
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

		ARM7TDMI();
		ARM7TDMI(const ARM7TDMI&) = delete;
		ARM7TDMI(ARM7TDMI&&) = delete;
		ARM7TDMI& operator=(const ARM7TDMI&) = delete;
		ARM7TDMI& operator=(ARM7TDMI&&) = delete;
		~ARM7TDMI();

		void pulse_clock();

		void fetch();
		void decode();
		void execute();

#pragma region Get register functions
		/// <summary>
		/// Fetch the CPSR condition code flag for sign. false = not signed,
		/// true = signed (negative or less than).
		/// </summary>
		/// <returns>The flag value.</returns>
		bool get_flag_N() const;

		/// <summary>
		/// Fetch the CPSR condition code flag for zero. false = not zero, 
		/// true = zero.
		/// </summary>
		/// <returns>The flag value.</returns>
		bool get_flag_Z() const;

		/// <summary>
		/// Fetch the CPSR condition code flag for carry or borrow or extend.
		/// false = Borrow/No Carry, true = Carry/No Borrow.
		/// </summary>
		/// <returns>The flag value.</returns>
		bool get_flag_C() const;

		/// <summary>
		/// Fetch the CPSR condition code flag for overflow.
		/// false = no overflow, true = overflow.
		/// </summary>
		/// <returns>The flag value.</returns>
		bool get_flag_V() const;

		/// <summary>
		/// Fetch the CPSR control bit for IRQ disable.
		/// false = enable, true = disable.
		/// </summary>
		/// <returns>The flag value.</returns>
		bool get_flag_I() const;

		/// <summary>
		/// Fetch the CPSR control bit for FIQ disable.
		/// false = enable, true = disable.
		/// </summary>
		/// <returns>The flag value.</returns>
		bool get_flag_F() const;

		/// <summary>
		/// Fetch the CPSR control bit for state.
		/// false = ARM, true = THUMB.
		/// </summary>
		/// <returns>The flag value.</returns>
		bool get_flag_T() const;

		/// <summary>
		/// Fetch the ARM mode associated with the current mode bits.
		/// </summary>
		/// <returns>The current ARM mode.</returns>
		ArmMode get_flag_mode() const;

		/// <summary>
		/// Read a numbered register (R0-R15), accounting for the current
		/// processor mode.
		/// </summary>
		/// <param name="register_id">The number of the register.</param>
		/// <returns>The register value.</returns>
		Word read_register(Word register_id) const;

		/// <summary>
		/// Read the CPSR register.
		/// </summary>
		Word read_CPSR() const;

		/// <summary>
		/// Read the banked SPSR register, for the current mode. Must be in
		/// a mode that actually has that register.
		/// </summary>
		/// <returns>The register value.</returns>
		Word read_SPSR() const;
#pragma endregion

	private:
#pragma region ARM Decoding
		ARMInstructionType decode_arm(ArmInstruction instruction);
		ThumbInstructionType decode_thumb(ThumbInstruction instruction, 
			ThumbInstruction next_instruction);
#pragma endregion

#pragma region Set register functions
		/// <summary>
		/// Set the CPSR condition code flag for sign. false = not signed,
		/// true = signed (negative or less than).
		/// </summary>
		/// <param name="flag">The value to set.</param>
		void set_flag_N(bool flag);

		/// <summary>
		/// Set the CPSR condition code flag for zero. false = not zero, 
		/// true = zero.
		/// </summary>
		/// <param name="flag">The value to set.</param>
		void set_flag_Z(bool flag);

		/// <summary>
		/// Set the CPSR condition code flag for carry or borrow or extend.
		/// false = Borrow/No Carry, true = Carry/No Borrow.
		/// </summary>
		/// <param name="flag">The value to set.</param>
		void set_flag_C(bool flag);

		/// <summary>
		/// Set the CPSR condition code flag for overflow. false = no overflow,
		/// true = overflow.
		/// </summary>
		/// <param name="flag">The value to set.</param>
		void set_flag_V(bool flag);

		/// <summary>
		/// Set the CPSR control bit for IRQ disable.
		/// false = enable, true = disable.
		/// </summary>
		/// <param name="flag">The value to set.</param>
		void set_flag_I(bool flag);

		/// <summary>
		/// Set the CPSR control bit for FIQ disable.
		/// false = enable, true = disable.
		/// </summary>
		/// <param name="flag">The value to set.</param>
		void set_flag_F(bool flag);

		/// <summary>
		/// Set the CPSR control bit for state.
		/// false = ARM, true = THUMB.
		/// Should not be changed manually, only by the BX instruction.
		/// </summary>
		/// <param name="flag">The value to set.</param>
		void set_flag_T(bool flag);

		/// <summary>
		/// Set the CPSR mode bits.
		/// </summary>
		/// <param name="mode">The ARM mode we want to set bits for.</param>
		void set_flag_mode(ArmMode mode);

		/// <summary>
		/// Write to a numbered register (R0-R15), accounting for the current
		/// processor mode.
		/// </summary>
		/// <param name="register_id">The number of the register.</param>
		/// <param name="value">The value to write to the register.</param>
		void write_register(Word register_id, Word value);
#pragma endregion

		void reset();

	};

}
