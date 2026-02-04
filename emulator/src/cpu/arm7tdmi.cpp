#include "cpu/arm7tdmi.h"

#include "cpu/cpu_constants.h"
#include "debugging/logger.h"

namespace emulator {

	ARMCond cond_to_enum(ArmInstruction cond) {
		LOG_ASSERT(cond <= 15);

		// 0000 = EQ
		// 0001 = NE
		// 0010 = CS
		// 0011 = CC
		// 0100 = MI
		// 0101 = PL
		// 0110 = VS
		// 0111 = VC
		// 1000 = HI
		// 1001 = LS
		// 1010 = GE
		// 1011 = LT
		// 1100 = GT
		// 1101 = LE
		// 1110 = AL
		if (cond == 0b1111u) {
			return ARMCond::AL;
		}
		return static_cast<ARMCond>(cond);
	}

#pragma region ARM7TDMI ARM Instructions
	void ARM7TDMI::arm_adc(ArmInstruction instruction)
	{
		const ArmInstruction cond = (instruction >> 28) & 0b1111u;
		// First operand register, PC can be used
		const ArmInstruction rn = (instruction >> 16) & 0b1111u;
		// Destination register
		const ArmInstruction rd = (instruction >> 12) & 0b1111u;

		// S, Whether we should update the flags
		const bool update_flags = ((instruction >> 20) & 0b1u) == 0b1u;
		const bool is_immediate = ((instruction >> 25) & 0b1u) == 0b1u;
		const bool is_register_shifted = ((instruction >> 4) & 0b1u) == 0b1u;

		// TODO(ches) handle Rd being the PC, might be a branch or SUBS

		// TODO(ches) finish the decoding and processing
		if (is_immediate) {
			// ADC (immediate)
			const ArmInstruction imm12 = instruction & 0b1111'1111'1111u;

		}
		else if (is_register_shifted) {
			// ADC (register-shifted register)
			const ArmInstruction rs = (instruction >> 7) & 0b1111u;
			const ArmInstruction rm = instruction & 0b1111u;

		}
		else {
			// ADC (register)
			const ArmInstruction imm5 = (instruction >> 7) & 0b1'1111u;
			const ArmInstruction type = (instruction >> 5) & 0b11u;
			const ArmInstruction rm = instruction & 0b1111u;

			if (type == 0b00u) {
				// LSL
			}
			else if (type == 0b01u) {
				// LSR
			}
			else if (type == 0b10u) {
				// ASR
			}
			else /* if (type == 0b11u) */ {
				// ROR
			}

		}

	}

	void ARM7TDMI::arm_add(ArmInstruction instruction)
	{}

	void ARM7TDMI::arm_adr(ArmInstruction instruction)
	{}

	void ARM7TDMI::arm_adrl(ArmInstruction instruction)
	{}

	void ARM7TDMI::arm_and(ArmInstruction instruction)
	{}

	void ARM7TDMI::arm_asr(ArmInstruction instruction)
	{}

	void ARM7TDMI::arm_b(ArmInstruction instruction)
	{}

	void ARM7TDMI::arm_bic(ArmInstruction instruction)
	{}

	void ARM7TDMI::arm_bl(ArmInstruction instruction)
	{}

	void ARM7TDMI::arm_bx(ArmInstruction instruction)
	{}

	void ARM7TDMI::arm_cdp(ArmInstruction instruction)
	{}

	void ARM7TDMI::arm_cmn(ArmInstruction instruction)
	{}

	void ARM7TDMI::arm_cmp(ArmInstruction instruction)
	{}

	void ARM7TDMI::arm_eor(ArmInstruction instruction)
	{}

	void ARM7TDMI::arm_ldc(ArmInstruction instruction)
	{}

	void ARM7TDMI::arm_ldm(ArmInstruction instruction)
	{}

	void ARM7TDMI::arm_ldm_exception(ArmInstruction instruction)
	{}

	void ARM7TDMI::arm_ldmda(ArmInstruction instruction)
	{}

	void ARM7TDMI::arm_ldmdb(ArmInstruction instruction)
	{}

	void ARM7TDMI::arm_ldmia(ArmInstruction instruction)
	{}

	void ARM7TDMI::arm_ldmib(ArmInstruction instruction)
	{}

	void ARM7TDMI::arm_ldr(ArmInstruction instruction)
	{}

	void ARM7TDMI::arm_ldrb(ArmInstruction instruction)
	{}

	void ARM7TDMI::arm_ldrbt(ArmInstruction instruction)
	{}

	void ARM7TDMI::arm_ldrh(ArmInstruction instruction)
	{}

	void ARM7TDMI::arm_ldrsb(ArmInstruction instruction)
	{}

	void ARM7TDMI::arm_ldrsh(ArmInstruction instruction)
	{}

	void ARM7TDMI::arm_ldrt(ArmInstruction instruction)
	{}

	void ARM7TDMI::arm_lsl(ArmInstruction instruction)
	{}

	void ARM7TDMI::arm_lsr(ArmInstruction instruction)
	{}

	void ARM7TDMI::arm_mcr(ArmInstruction instruction)
	{}

	void ARM7TDMI::arm_mla(ArmInstruction instruction)
	{}

	void ARM7TDMI::arm_mov(ArmInstruction instruction)
	{}

	void ARM7TDMI::arm_mrc(ArmInstruction instruction)
	{}

	void ARM7TDMI::arm_mrs(ArmInstruction instruction)
	{}

	void ARM7TDMI::arm_msr(ArmInstruction instruction)
	{}

	void ARM7TDMI::arm_mul(ArmInstruction instruction)
	{}

	void ARM7TDMI::arm_mvn(ArmInstruction instruction)
	{}

	void ARM7TDMI::arm_nop(ArmInstruction instruction)
	{}

	void ARM7TDMI::arm_orr(ArmInstruction instruction)
	{}

	void ARM7TDMI::arm_pop(ArmInstruction instruction)
	{}

	void ARM7TDMI::arm_push(ArmInstruction instruction)
	{}

	void ARM7TDMI::arm_ror(ArmInstruction instruction)
	{}

	void ARM7TDMI::arm_rrx(ArmInstruction instruction)
	{}

	void ARM7TDMI::arm_rsb(ArmInstruction instruction)
	{}

	void ARM7TDMI::arm_rsc(ArmInstruction instruction)
	{}

	void ARM7TDMI::arm_sbc(ArmInstruction instruction)
	{}

	void ARM7TDMI::arm_smlal(ArmInstruction instruction)
	{}

	void ARM7TDMI::arm_smull(ArmInstruction instruction)
	{}

	void ARM7TDMI::arm_stc(ArmInstruction instruction)
	{}

	void ARM7TDMI::arm_stm(ArmInstruction instruction)
	{}

	void ARM7TDMI::arm_stmda(ArmInstruction instruction)
	{}

	void ARM7TDMI::arm_stmdb(ArmInstruction instruction)
	{}

	void ARM7TDMI::arm_stmia(ArmInstruction instruction)
	{}

	void ARM7TDMI::arm_stmib(ArmInstruction instruction)
	{}

	void ARM7TDMI::arm_str(ArmInstruction instruction)
	{}

	void ARM7TDMI::arm_strb(ArmInstruction instruction)
	{}

	void ARM7TDMI::arm_strbt(ArmInstruction instruction)
	{}

	void ARM7TDMI::arm_strd(ArmInstruction instruction)
	{}

	void ARM7TDMI::arm_strh(ArmInstruction instruction)
	{}

	void ARM7TDMI::arm_strt(ArmInstruction instruction)
	{}

	void ARM7TDMI::arm_sub(ArmInstruction instruction)
	{}

	void ARM7TDMI::arm_swi(ArmInstruction instruction)
	{}

	void ARM7TDMI::arm_swp(ArmInstruction instruction)
	{}

	void ARM7TDMI::arm_teq(ArmInstruction instruction)
	{}

	void ARM7TDMI::arm_tst(ArmInstruction instruction)
	{}

	void ARM7TDMI::arm_udf(ArmInstruction instruction)
	{}

	void ARM7TDMI::arm_umlal(ArmInstruction instruction)
	{}

	void ARM7TDMI::arm_umull(ArmInstruction instruction)
	{}

#pragma endregion

#pragma region ARM7TDMI Thumb Instructions
	void ARM7TDMI::thumb_add(ThumbInstruction instruction)
	{}

	void ARM7TDMI::thumb_adc(ThumbInstruction instruction)
	{}

	void ARM7TDMI::thumb_and(ThumbInstruction instruction)
	{}

	void ARM7TDMI::thumb_asr(ThumbInstruction instruction)
	{}

	void ARM7TDMI::thumb_b(ThumbInstruction instruction)
	{}

	void ARM7TDMI::thumb_bl(ThumbInstruction instruction)
	{}

	void ARM7TDMI::thumb_bx(ThumbInstruction instruction)
	{}

	void ARM7TDMI::thumb_beq(ThumbInstruction instruction)
	{}

	void ARM7TDMI::thumb_bcc(ThumbInstruction instruction)
	{}

	void ARM7TDMI::thumb_bcs(ThumbInstruction instruction)
	{}

	void ARM7TDMI::thumb_bge(ThumbInstruction instruction)
	{}

	void ARM7TDMI::thumb_bgt(ThumbInstruction instruction)
	{}

	void ARM7TDMI::thumb_bhi(ThumbInstruction instruction)
	{}

	void ARM7TDMI::thumb_bic(ThumbInstruction instruction)
	{}

	void ARM7TDMI::thumb_ble(ThumbInstruction instruction)
	{}

	void ARM7TDMI::thumb_bls(ThumbInstruction instruction)
	{}

	void ARM7TDMI::thumb_blt(ThumbInstruction instruction)
	{}

	void ARM7TDMI::thumb_bmi(ThumbInstruction instruction)
	{}

	void ARM7TDMI::thumb_bne(ThumbInstruction instruction)
	{}

	void ARM7TDMI::thumb_bpl(ThumbInstruction instruction)
	{}

	void ARM7TDMI::thumb_bvc(ThumbInstruction instruction)
	{}

	void ARM7TDMI::thumb_bvs(ThumbInstruction instruction)
	{}

	void ARM7TDMI::thumb_eor(ThumbInstruction instruction)
	{}

	void ARM7TDMI::thumb_cmn(ThumbInstruction instruction)
	{}

	void ARM7TDMI::thumb_cmp(ThumbInstruction instruction)
	{}

	void ARM7TDMI::thumb_ldmia(ThumbInstruction instruction)
	{}

	void ARM7TDMI::thumb_ldr(ThumbInstruction instruction)
	{}

	void ARM7TDMI::thumb_ldrb(ThumbInstruction instruction)
	{}

	void ARM7TDMI::thumb_ldrh(ThumbInstruction instruction)
	{}

	void ARM7TDMI::thumb_ldrsb(ThumbInstruction instruction)
	{}

	void ARM7TDMI::thumb_ldrsh(ThumbInstruction instruction)
	{}

	void ARM7TDMI::thumb_lsl(ThumbInstruction instruction)
	{}

	void ARM7TDMI::thumb_lsr(ThumbInstruction instruction)
	{}

	void ARM7TDMI::thumb_mov(ThumbInstruction instruction)
	{}

	void ARM7TDMI::thumb_mul(ThumbInstruction instruction)
	{}

	void ARM7TDMI::thumb_mvn(ThumbInstruction instruction)
	{}

	void ARM7TDMI::thumb_neg(ThumbInstruction instruction)
	{}

	void ARM7TDMI::thumb_nop(ThumbInstruction instruction)
	{
		//NOTE(ches) this one is easy.
	}

	void ARM7TDMI::thumb_or(ThumbInstruction instruction)
	{}

	void ARM7TDMI::thumb_pop(ThumbInstruction instruction)
	{}

	void ARM7TDMI::thumb_push(ThumbInstruction instruction)
	{}

	void ARM7TDMI::thumb_ror(ThumbInstruction instruction)
	{}

	void ARM7TDMI::thumb_rsb(ThumbInstruction instruction)
	{
		// TODO(ches) confirm GBA supports this, can't find in ARM7TDMI-S docs
	}

	void ARM7TDMI::thumb_sbc(ThumbInstruction instruction)
	{}

	void ARM7TDMI::thumb_stmia(ThumbInstruction instruction)
	{}

	void ARM7TDMI::thumb_str(ThumbInstruction instruction)
	{}

	void ARM7TDMI::thumb_strb(ThumbInstruction instruction)
	{}

	void ARM7TDMI::thumb_strh(ThumbInstruction instruction)
	{}

	void ARM7TDMI::thumb_sub(ThumbInstruction instruction)
	{}

	void ARM7TDMI::thumb_swi(ThumbInstruction instruction)
	{}

	void ARM7TDMI::thumb_tst(ThumbInstruction instruction)
	{}

#pragma endregion

	ARM7TDMI::ARM7TDMI()
		: R0{ 0 }
		, R1{ 0 }
		, R2{ 0 }
		, R3{ 0 }
		, R4{ 0 }
		, R5{ 0 }
		, R6{ 0 }
		, R7{ 0 }
		, R8{ 0 }
		, R9{ 0 }
		, R10{ 0 }
		, R11{ 0 }
		, R12{ 0 }
		, R13{ 0 }
		, R14{ 0 }
		, R15{ 0 }
		, CPSR{ 0 }
		, R8_fiq{ 0 }
		, R9_fiq{ 0 }
		, R10_fiq{ 0 }
		, R11_fiq{ 0 }
		, R12_fiq{ 0 }
		, R13_fiq{ 0 }
		, R14_fiq{ 0 }
		, SPSR_fiq{ 0 }
		, R13_svc{ 0 }
		, R14_svc{ 0 }
		, SPSR_svc{ 0 }
		, R13_abt{ 0 }
		, R14_abt{ 0 }
		, SPSR_abt{ 0 }
		, R13_irq{ 0 }
		, R14_irq{ 0 }
		, SPSR_irq{ 0 }
		, R13_und{ 0 }
		, R14_und{ 0 }
		, SPSR_und{ 0 }
		, CLK{ 0 }
		, CLKEN{ 0 }
		, nIRQ{ 0 }
		, nFIQ{ 0 }
		, nRESET{ 0 }
		, CFGBIGEND{ 0 }
		, DMORE{ 0 }
		, LOCK{ 0 }
		, DBGINSTRVALID{ 0 }
		, DBGRQ{ 0 }
		, DBGBREAK{ 0 }
		, DBGACK{ 0 }
		, DBGnEXEC{ 0 }
		, DBGEXT0{ 0 }
		, DBGEXT1{ 0 }
		, DBGGEN{ 0 }
		, DBGRNG0{ 0 }
		, DBGRNG1{ 0 }
		, DBGCOMMRX{ 0 }
		, DBGCOMMTX{ 0 }
		, DBGTCKEN{ 0 }
		, DBGTMS{ 0 }
		, DBGTDI{ 0 }
		, DBGnTRST{ 0 }
		, DBGTDO{ 0 }
		, DBGnTDOEN{ 0 }
		, ABORT{ 0 }
		, WRITE{ 0 }
		, ADDR{ 0 }
		, WDATA{ 0 }
		, RDATA{ 0 }
		, SIZE{ 0 }
		, PROT{ 0 }
		, TRANS{ 0 }
		, CPnTRANS{ 0 }
		, CPnOPC{ 0 }
		, CPnMREQ{ 0 }
		, CPSEQ{ 0 }
		, CPTBIT{ 0 }
		, CPnl{ 0 }
		, CPA{ 0 }
		, CPB{ 0 }
	{
		reset();
	}
	ARM7TDMI::~ARM7TDMI() = default;

	void ARM7TDMI::pulse_clock() {

	}

	void ARM7TDMI::fetch()
	{}

	void ARM7TDMI::decode()
	{}

	void ARM7TDMI::execute()
	{}

#pragma region Get register functions
	bool ARM7TDMI::get_flag_N() const {
		return (CPSR & SIGN_FLAG_BITS) != 0;
	}

	bool ARM7TDMI::get_flag_Z() const {
		return (CPSR & ZERO_FLAG_BITS) != 0;
	}

	bool ARM7TDMI::get_flag_C() const {
		return (CPSR & CARRY_FLAG_BITS) != 0;
	}

	bool ARM7TDMI::get_flag_V() const {
		return (CPSR & OVERFLOW_FLAG_BITS) != 0;
	}

	bool ARM7TDMI::get_flag_I() const {
		return (CPSR & IRQ_DISABLE_FLAG_BITS) != 0;
	}

	bool ARM7TDMI::get_flag_F() const {
		return (CPSR & FIQ_DISABLE_FLAG_BITS) != 0;
	}

	bool ARM7TDMI::get_flag_T() const {
		return (CPSR & STATE_FLAG_BITS) != 0;
	}

	ArmMode ARM7TDMI::get_flag_mode() const {
		const Word mode_bits = CPSR & MODE_FLAG_BITS;

		switch (mode_bits) {
		case MODE_USER:
			return ArmMode::USR;
		case MODE_FIQ:
			return ArmMode::FIQ;
		case MODE_IRQ:
			return ArmMode::IRQ;
		case MODE_SUPERVISOR:
			return ArmMode::SVC;
		case MODE_ABORT:
			return ArmMode::ABT;
		case MODE_UNDEFINED:
			return ArmMode::UND;
		case MODE_SYSTEM:
			return ArmMode::SYS;
		default:
			LOG_FATAL("Invalid processor mode");
		}
	}

	Word ARM7TDMI::read_register(Word register_id) const {
		const ArmMode mode = get_flag_mode();

		switch (register_id) {
			//These share registers for every mode
		case 0: return R0;
		case 1: return R1;
		case 2: return R2;
		case 3: return R3;
		case 4: return R4;
		case 5: return R5;
		case 6: return R6;
		case 7: return R7;
		case 15: return R15;

			// These are partially banked
		case 8:
			if (mode != ArmMode::FIQ) {
				return R8;
			}
			else [[unlikely]] {
				return R8_fiq;
			}
		case 9:
			if (mode != ArmMode::FIQ) {
				return R9;
			}
			else [[unlikely]] {
				return R9_fiq;
			}
		case 10:
			if (mode != ArmMode::FIQ) {
				return R10;
			}
			else [[unlikely]] {
				return R10_fiq;
			}
		case 11:
			if (mode != ArmMode::FIQ) {
				return R11;
			}
			else [[unlikely]] {
				return R11_fiq;
			}
		case 12:
			if (mode != ArmMode::FIQ) {
				return R12;
			}
			else [[unlikely]] {
				return R12_fiq;
			}

			//These are banked
		case 13:
			switch (mode) {
			case ArmMode::SYS:
			case ArmMode::USR: return R13;
			case ArmMode::FIQ: return R13_fiq;
			case ArmMode::IRQ: return R13_irq;
			case ArmMode::SVC: return R13_svc;
			case ArmMode::ABT: return R13_abt;
			case ArmMode::UND: return R13_und;
			}
			break;
		case 14:
			switch (mode) {
			case ArmMode::SYS:
			case ArmMode::USR: return R14;
			case ArmMode::FIQ: return R14_fiq;
			case ArmMode::IRQ: return R14_irq;
			case ArmMode::SVC: return R14_svc;
			case ArmMode::ABT: return R14_abt;
			case ArmMode::UND: return R14_und;
			}
			break;
		default:
			LOG_FATAL("Unknown register ID");
		}
		LOG_FATAL("Failed to find a register");
	}

	Word ARM7TDMI::read_CPSR() const {
		return CPSR;
	}

	Word ARM7TDMI::read_SPSR() const {
		const ArmMode mode = get_flag_mode();

		switch (mode) {
			switch (mode) {
			case ArmMode::SYS:
			case ArmMode::USR:
				LOG_FATAL("System and User Modes don't ahve SPSR.");
				break;
			case ArmMode::FIQ:
				return SPSR_fiq;
			case ArmMode::IRQ:
				return SPSR_irq;
			case ArmMode::SVC:
				return SPSR_svc;
			case ArmMode::ABT:
				return SPSR_abt;
			case ArmMode::UND:
				return SPSR_und;
			}
		}
	}

#pragma endregion

#pragma region ARM Decoding

	// https://developer.arm.com/documentation/ddi0406/cb/Application-Level-Architecture/ARM-Instruction-Set-Encoding?lang=en
	namespace DecodeArm
	{
		ARMInstructionType constexpr decode(ArmInstruction instruction)
		{
			const ArmInstruction CONDITIONAL_MASK = 0b1111'0000'0000'0000'0000'0000'0000'0000u;
			const ArmInstruction UNCONDITIONAL_FORMAT = 0b1111'0000'0000'0000'0000'0000'0000'0000u;

			const ArmInstruction conditional = instruction & CONDITIONAL_MASK;

			if (conditional != UNCONDITIONAL_FORMAT)
			{
				return decode_conditional_instruction(instruction);
			}
			return decode_unconditional_instruction(instruction);
		}

		ARMInstructionType constexpr decode_conditional_instruction(ArmInstruction instruction)
		{
			const ArmInstruction op1 = (instruction >> 26) & 0b111u;

			if ((op1 & 0b110u) == 0b000u)
			{
				return decode_data_processing_and_miscellaneous(instruction);
			}
			if (op1 == 0b010u)
			{
				return decode_load_store_word_and_unsigned_byte(instruction);
			}
			if (op1 == 0b011u)
			{
				const ArmInstruction b = (instruction >> 4) & 0b1u;
				if (b == 1)
				{
					return decode_media_instructions(instruction);
				}
				return decode_load_store_word_and_unsigned_byte(instruction);
			}
			if ((op1 & 0b110u) == 0b100u)
			{
				return decode_branch_branch_with_link_and_block_data_transfer(instruction);
			}
			if ((op1 & 0b110u) == 0b110u)
			{
				return decode_coprocessor_and_supervisor_call(instruction);
			}
			return ARMInstructionType::UNIMPLEMENTED;
		}

		ARMInstructionType constexpr decode_data_processing_and_miscellaneous(ArmInstruction instruction)
		{
			const ArmInstruction OP_MASK = 0b0000'0010'0000'0000'0000'0000'0000'0000u;
			const ArmInstruction OP1_MASK = 0b0000'0001'1111'0000'0000'0000'0000'0000u;
			const ArmInstruction OP2_MASK = 0b0000'0000'0000'0000'0000'0000'1111'0000u;

			const ArmInstruction op = (instruction & OP_MASK) >> 25;
			const ArmInstruction op1 = (instruction & OP1_MASK) >> 20;

			if (op == 0)
			{
				const ArmInstruction op2 = (instruction & OP2_MASK) >> 4;

				if ((op1 & 0b11001u) != 0b10000u && (op2 & 0x0001) == 0x0000)
				{
					return decode_data_processing_register(instruction);
				}
				if ((op1 & 0b11001u) != 0b10000u && (op2 & 0x1001) == 0x0001)
				{
					return decode_data_processing_register_shifted_register(instruction);
				}
				if ((op1 & 0b11001u) == 0b10000u && (op2 & 0x1000) == 0x0000)
				{
					return decode_miscellaneous(instruction);
				}
				if ((op1 & 0b11001u) == 0b10000u && (op2 & 0x1001) == 0x1000)
				{
					// Halfword multiply and multiply accumulate are only on
					// ARMv5TE and above
					return ARMInstructionType::UNIMPLEMENTED;
				}
				if ((op1 & 0b10000u) == 0b00000u && op2 == 0x1001)
				{
					return decode_multiply_and_multiply_accumulate(instruction);
				}
				if ((op1 & 0b10000u) == 0b10000u && op2 == 0x1001)
				{
					return decode_synchronization_primitives(instruction);
				}
				if ((op1 & 0b10010u) != 0b00010u && op2 == 0x1011)
				{
					return decode_extra_load_store(instruction);
				}
				if ((op1 & 0b10010u) != 0b00010u && (op2 & 0x1101) == 0x1101)
				{
					return decode_extra_load_store(instruction);
				}
				if ((op1 & 0b10010u) == 0b00010u && op2 == 0x1011)
				{
					// Unprivileged load/store instructions are all v6T2 and above
					return ARMInstructionType::UNIMPLEMENTED;
				}
				if ((op1 & 0b10010u) == 0b00010u && (op2 & 0x1101) == 0x1101)
				{
					return decode_extra_load_store(instruction);
				}
			}
			else
			{
				if ((op1 & 0b11001u) != 0b10000u)
				{
					return decode_data_processing_immediate(instruction);
				}
				if (op1 == 0b10000u)
				{
					// v6T2 instruction, 16-bit immediate load, MOV (immediate)
					return ARMInstructionType::UNIMPLEMENTED;
				}
				if (op1 == 0b10100u)
				{
					// High halfword 16-bit immediate load, MOVT
					return ARMInstructionType::UNIMPLEMENTED;
				}
				if ((op1 & 0b11011u) != 0b10010u)
				{
					return decode_msr_and_hints(instruction);
				}
			}

			return ARMInstructionType::UNIMPLEMENTED;
		}

		ARMInstructionType constexpr decode_data_processing_immediate(ArmInstruction instruction)
		{
			const ArmInstruction op = (instruction >> 20) & 0b11111u;
			const ArmInstruction rn = (instruction >> 16) & 0b1111u;

			const ArmInstruction op_first_4 = (instruction >> 20) & 0b11110u;

			if ((op_first_4 == 0b00010u || op_first_4 == 0b01000u) && rn == 0b1111u)
			{
				return ARMInstructionType::ADR;
			}
			if ((op & 0b11001u) == 0b10000u)
			{
				return decode_data_processing_and_miscellaneous(instruction);
			}
			if (op_first_4 == 0b11010u)
			{
				return ARMInstructionType::MOV;
			}

			return decode_data_processing_register_shared(instruction);
		}

		ARMInstructionType constexpr decode_data_processing_register(ArmInstruction instruction)
		{
			const ArmInstruction op = (instruction >> 20) & 0b11111u;

			if ((op & 0b11110u) != 0b11010u)
			{
				return decode_data_processing_register_shared(instruction);
			}
		
			const ArmInstruction op2 = (instruction >> 5) & 0b11u;
			const ArmInstruction imm5 = (instruction >> 7) & 0b11111u;

			if (op2 == 0b00u && imm5 == 0b00000u)
			{
				return ARMInstructionType::MOV;
			}
			if (op2 == 0b00u && imm5 != 0b00000u)
			{
				return ARMInstructionType::LSL;
			}
			if (op2 == 0b01u)
			{
				return ARMInstructionType::LSR;
			}
			if (op2 == 0b10u)
			{
				return ARMInstructionType::ASR;
			}
			if (op2 == 0b11u && imm5 == 0b00000u)
			{
				return ARMInstructionType::RRX;
			}
			if (op2 == 0b11u && imm5 != 0b00000u)
			{
				return ARMInstructionType::ROR;
			}

			return ARMInstructionType::UNIMPLEMENTED;
		}

		ARMInstructionType constexpr decode_data_processing_register_shared(const ArmInstruction op)
		{
			if ((op & 0b11110u) == 0b00000u)
			{
				return ARMInstructionType::AND;
			}
			if ((op & 0b11110u) == 0b00010u)
			{
				return ARMInstructionType::EOR;
			}
			if ((op & 0b11110u) == 0b00100u)
			{
				return ARMInstructionType::SUB;
			}
			if ((op & 0b11110u) == 0b00110u)
			{
				return ARMInstructionType::RSB;
			}
			if ((op & 0b11110u) == 0b01000u)
			{
				return ARMInstructionType::ADD;
			}
			if ((op & 0b11110u) == 0b01010u)
			{
				return ARMInstructionType::ADC;
			}
			if ((op & 0b11110u) == 0b01100u)
			{
				return ARMInstructionType::SBC;
			}
			if ((op & 0b11110u) == 0b01110u)
			{
				return ARMInstructionType::RSC;
			}
			if ((op & 0b11001u) == 0b10000u)
			{
				// Shouldn't be able to arrive here
				return ARMInstructionType::UNIMPLEMENTED;
			}
			if (op == 0b10001u)
			{
				return ARMInstructionType::TST;
			}
			if (op == 0b10011u)
			{
				return ARMInstructionType::TEQ;
			}
			if (op == 0b10101u)
			{
				return ARMInstructionType::CMP;
			}
			if (op == 0b10111u)
			{
				return ARMInstructionType::CMN;
			}
			if ((op & 0b11110u) == 0b11000u)
			{
				return ARMInstructionType::ORR;
			}
			if ((op & 0b11110u) == 0b11100u)
			{
				return ARMInstructionType::BIC;
			}
			if ((op & 0b11110u) == 0b11110u)
			{
				return ARMInstructionType::MVN;
			}
			return ARMInstructionType::UNIMPLEMENTED;
		}

		ARMInstructionType constexpr decode_data_processing_register_shifted_register(ArmInstruction instruction)
		{
			const ArmInstruction OP_MASK = 0b0000'0001'1111'0000'0000'0000'0000'0000u;

			const ArmInstruction op = (instruction & OP_MASK) >> 20;

			if ((op & 0b11110u) != 0b11010u)
			{
				return decode_data_processing_register_shared(instruction);
			}
		
			const ArmInstruction op2 = (instruction >> 5) & 0b11u;

			if (op2 == 0b00u)
			{
				return ARMInstructionType::LSL;
			}
			if (op2 == 0b01u)
			{
				return ARMInstructionType::LSR;
			}
			if (op2 == 0b10u)
			{
				return ARMInstructionType::ASR;
			}
			if (op2 == 0b11u)
			{
				return ARMInstructionType::ROR;
			}

			return ARMInstructionType::UNIMPLEMENTED;
		}

		ARMInstructionType constexpr decode_miscellaneous(ArmInstruction instruction)
		{
			const ArmInstruction op = (instruction >> 20) & 0b11u;
			const ArmInstruction op2 = (instruction >> 4) & 0b111u;

			if (op2 == 0b000u)
			{
				const ArmInstruction b = (instruction >> 9) & 0b1u;

				if (b == 1)
				{
					//v7VE instructions, MRS/MSR (Banked register)
					return ARMInstructionType::UNIMPLEMENTED;
				}
				else
				{
					//const ArmInstruction op1 = (instruction >> 16) & 0b1111u;
					if ((op & 0b01u) == 0b00u)
					{
						return ARMInstructionType::MRS;
					}
					if (op == 0b01u)
					{
						//NOTE(ches) all 4 cases of op1 are some kind of MSR
						return ARMInstructionType::MSR;
					}
					if (op == 0b11u)
					{
						return ARMInstructionType::MSR;
					}
				}
			}
			if (op2 == 0b001u)
			{
				if (op == 0b01u)
				{
					return ARMInstructionType::BX;
				}
				if (op == 0b11u)
				{
					// v5T instruction, CLZ Count Leading Zeros
					return ARMInstructionType::UNIMPLEMENTED;
				}
			}
			if (op2 == 0b010u)
			{
				// v5TEJ instruction, BXJ Branch and Exchange Jazelle
				return ARMInstructionType::UNIMPLEMENTED;
			}
			if (op2 == 0b011u)
			{
				// v5T instruction, BLX (register) Branch with Link and Exchange
				return ARMInstructionType::UNIMPLEMENTED;
			}
			if (op2 == 0b101u)
			{
				// Saturating addition and subtraction are v5 and up
				return ARMInstructionType::UNIMPLEMENTED;
			}
			if (op2 == 0b110u)
			{
				// v7VE instruction, ERET Exception Return
				return ARMInstructionType::UNIMPLEMENTED;
			}
			if (op2 == 0b111u)
			{
				// either v5T instruction BKPT Breakpoint, the v7VE instruction
				// HVC Hypervisor Call, or Security Extenions SMC/ (previously SMI)
				// but none of those are supported here
				return ARMInstructionType::UNIMPLEMENTED;
			}

			return ARMInstructionType::UNIMPLEMENTED;
		}

		ARMInstructionType constexpr decode_multiply_and_multiply_accumulate(ArmInstruction instruction)
		{
			const ArmInstruction op = (instruction >> 20) & 0b1111u;
			if ((op & 0b1110u) == 0b0000u)
			{
				return ARMInstructionType::MUL;
			}
			if ((op & 0b1110u) == 0b0010u)
			{
				return ARMInstructionType::MLA;
			}
			if ((op & 0b1100u) == 0b0100u)
			{
				// 0100 is UMAAL Unsigned Multiply Accumulate Accumulate Long in v6
				// 0101 is undefined
				// 0110 is MLS Multiply and Subtract in v6T2
				// 0111 is undefined
				return ARMInstructionType::UNIMPLEMENTED;
			}
			if ((op & 0b1110u) == 0b1000u)
			{
				return ARMInstructionType::UMULL;
			}
			if ((op & 0b1110u) == 0b1010u)
			{
				return ARMInstructionType::UMLAL;
			}
			if ((op & 0b1110u) == 0b1100u)
			{
				return ARMInstructionType::SMULL;
			}
			if ((op & 0b1110u) == 0b1110u)
			{
				return ARMInstructionType::SMLAL;
			}
			return ARMInstructionType::UNIMPLEMENTED;
		}

		ARMInstructionType constexpr decode_synchronization_primitives(ArmInstruction instruction)
		{
			const ArmInstruction op = (instruction >> 20) & 0b1111u;

			if ((op & 0b1011u) == 0b0000u)
			{
				return ARMInstructionType::SWP;
			}
			// everything else is v6 or v6K and above
			return ARMInstructionType::UNIMPLEMENTED;
		}

		ARMInstructionType constexpr decode_extra_load_store(ArmInstruction instruction)
		{
			const ArmInstruction op1 = (instruction >> 20) & 0b00101u;
			const ArmInstruction op2 = (instruction >> 5) & 0b11u;
			//const ArmInstruction rn = (instruction >> 16) & 0b1111u;

			if (op2 == 0b01u)
			{
				if (op1 == 0b00000u)
				{
					return ARMInstructionType::STRH;
				}
				if (op1 == 0b00001u)
				{
					return ARMInstructionType::LDRH;
				}
				if (op1 == 0b00100u)
				{
					return ARMInstructionType::STRH;
				}
				if (op1 == 0b00101u)
				{
					return ARMInstructionType::LDRH;
				}
			}
			if (op2 == 0b10u)
			{
				if (op1 == 0b00000u)
				{
					// LDRD Load Dual is v5TE
					return ARMInstructionType::UNIMPLEMENTED;
				}
				if (op1 == 0b00001u)
				{
					return ARMInstructionType::LDRSB;
				}
				if (op1 == 0b00100u)
				{
					// LDRD Load Dual is v5TE
					return ARMInstructionType::UNIMPLEMENTED;
				}
				if (op1 == 0b00101u)
				{
					return ARMInstructionType::LDRSB;
				}
			}
			if (op2 == 0b11u)
			{
				if (op1 == 0b00000u)
				{
					// STRD Store Register Dual is v5TE
					return ARMInstructionType::UNIMPLEMENTED;
				}
				if (op1 == 0b00001u)
				{
					return ARMInstructionType::LDRSH;
				}
				if (op1 == 0b00100u)
				{
					// STRD Store Register Dual is v5TE
					return ARMInstructionType::UNIMPLEMENTED;
				}
				if (op1 == 0b00101u)
				{
					return ARMInstructionType::LDRSH;
				}
			}

			return ARMInstructionType::UNIMPLEMENTED;
		}

		ARMInstructionType constexpr decode_msr_and_hints(ArmInstruction instruction)
		{
			const ArmInstruction op = (instruction >> 22) & 0b1u;
			const ArmInstruction op1 = (instruction >> 16) & 0b1111u;

			if (op == 0b0u)
			{
				if (op1 == 0b0000u)
				{
					//const ArmInstruction op2 = instruction & 0b1111'1111u;

					// 00000000 = NOP No Operation hint, v6K and v6T2
					// 00000001 = YIELD Yield hint, v6K
					// 00000010 = WFE Wait For Event hint, v6K
					// 00000011 = WFI Wait For Interrupt hint, v6K
					// 00000100 = SEV Send Event hint, v6K
					// 00010100 = CSDB Consumption of Speculative Data Barrier, v7
					// 1111xxxx = DBG Debug hint, v7

					return ARMInstructionType::UNIMPLEMENTED;
				}
				if (op1 == 0b0100u || (op1 & 0b1011u) == 0b1000u)
				{
					return ARMInstructionType::MSR;
				}
				if ((op1 & 0b0011u) == 0b0001u || (op1 & 0b0010u) == 0b0010u)
				{
					return ARMInstructionType::MSR;
				}
			}
			else
			{
				return ARMInstructionType::MSR;
			}
			return ARMInstructionType::UNIMPLEMENTED;
		}

		ARMInstructionType constexpr decode_load_store_word_and_unsigned_byte(ArmInstruction instruction)
		{
			const ArmInstruction op1 = (instruction >> 20) & 0b11111u;

			if ((op1 & 0b00101u) == 0b00000u && (op1 & 0b10111u) != 0b00010u)
			{
				return ARMInstructionType::STR;
			}
			if ((op1 & 0b10111u) == 0b00010u)
			{
				return ARMInstructionType::STRT;
			}
			if ((op1 & 0b00101u) == 0b00001u && (op1 & 0b10111u) != 0b00011u)
			{
				return ARMInstructionType::LDR;
			}
			if ((op1 & 0b10111u) == 0b00011u)
			{
				return ARMInstructionType::LDRT;
			}
			if ((op1 & 0b00101u) == 0b00100u && (op1 & 0b10111u) != 0b00110u)
			{
				return ARMInstructionType::STRB;
			}
			if ((op1 & 0b10111u) == 0b00110u)
			{
				return ARMInstructionType::STRBT;
			}
			if ((op1 & 0b00101u) == 0b00101u && (op1 & 0b10111u) != 0b00111u)
			{
				return ARMInstructionType::LDRB;
			}
			if ((op1 & 0b10111u) == 0b00111u)
			{
				return ARMInstructionType::LDRBT;
			}

			return ARMInstructionType::UNIMPLEMENTED;
		}

		ARMInstructionType constexpr decode_media_instructions(ArmInstruction instruction)
		{
			const ArmInstruction op1 = (instruction >> 20) & 0b11111u;

			if ((op1 & 0b11100u) == 0b00000u)
			{
				// Parallel addition and subtration (signed) are not on v4T:
				// SADD16, SASX, SSAX, SSUB16, SADD8, SSUB8
				// QADD16, QASX, QSAX, QSUB16, QADD8, QSUB8
				// SHADD16, SHASX, SHSAX, SHSUB16, SHADD8, SHSUB8
				return ARMInstructionType::UNIMPLEMENTED;
			}
			if ((op1 & 0b11100u) == 0b00100u)
			{
				// Parallel addition and subtration (unsigned) are not on v4T:
				// UADD16, UASX, USAX, USUB16, UADD8, USUB8
				// UQADD16, UQASX, UQSAX, UQSUB16, UQADD8, UQSUB8
				// UHADD16, UHASX, UHSAX, UHSUB16, UHADD8, UHSUB8
				return ARMInstructionType::UNIMPLEMENTED;
			}
			if ((op1 & 0b11000u) == 0b01000u)
			{
				// Packing, unpacking, saturation, and reversal instructions are v6+

				// PKH, SXTAB16, SXTB16, SEL, SSAT, SSAT16, SXTAB, SXTB
				// REV, SXTAH, SXTH, REV16, UXTAB16, UXTB16, USAT, USAT16
				// UXTAB, UXTB, RBIT, UXTAHm UXTH, REVSH
				return ARMInstructionType::UNIMPLEMENTED;
			}
			if ((op1 & 0b11000u) == 0b10000u)
			{
				// Signed multiply instructions are v6+

				// SMLAD, SMUAD, SMLSD, SMUSD, SDIV, UDIV, SMLALD, SMLSLD
				// SMMLA, SMMUL, SMMLS
				return ARMInstructionType::UNIMPLEMENTED;
			}
			const ArmInstruction op2 = (instruction >> 5) & 0b111u;

			if (op1 == 0b11111u && op2 == 0b111u) {
				const ArmInstruction cond = (instruction >> 28) & 0b1111u;

				if (cond == 0b1110u) {
					return ARMInstructionType::UDF;
				}
				// not 1110 does not have a mnemonic, we are considering it undefined
			}

			// const ArmInstruction op2 = (instruction >> 5) & 0b111u;
			// const ArmInstruction rd = (instruction >> 12) & 0b1111u;
			// const ArmInstruction rn = instruction & 0b1111u;

			// op1 = 11000, op2 = 000, rd = 1111 is USAD8 in v6
			// op1 = 11000, op2 = 000, rd = 1111 is USADA8 in v6
			// op1 = 1101x, op2 = x10, is SBFX in v6T2
			// op1 = 1110x, op2 = x00, rn = 1111 is BFC in v6T2
			// op1 = 1110x, op2 = x00, rn != 1111 is BFI in v6T2
			// op1 = 1111x, op2 = x10, rn != 1111 is UBFX in v6T2
		
			return ARMInstructionType::UNIMPLEMENTED;
		}

		ARMInstructionType constexpr decode_branch_branch_with_link_and_block_data_transfer(ArmInstruction instruction)
		{
			const ArmInstruction op = (instruction >> 20) & 0b111111u;
			const ArmInstruction rn = (instruction >> 16) & 0b1111u;
			const ArmInstruction r = (instruction >> 15) & 0b1u;

			if ((op & 0x111101) == 0x000000) {
				return ARMInstructionType::STMDA;
			}
			if ((op & 0x111101) == 0x000001) {
				return ARMInstructionType::LDMDA;
			}
			if ((op & 0x111101) == 0x001000) {
				return ARMInstructionType::STMIA;
			}
			if (op == 0x001001) {
				return ARMInstructionType::LDMIA;
			}
			if (op == 0x001011) {
				if (rn == 0b1101u) {
					return ARMInstructionType::POP;
				}
				else {
					return ARMInstructionType::LDMIA;
				}
			}
			if (op == 0x010000) {
				return ARMInstructionType::STMDB;
			}
			if (op == 0x010010) {
				if (rn == 0b1101u) {
					return ARMInstructionType::PUSH;
				}
				else {
					return ARMInstructionType::STMDB;
				}
			}
			if ((op & 0x111101) == 0x010001) {
				return ARMInstructionType::LDMDB;
			}
			if ((op & 0x111101) == 0x011000) {
				return ARMInstructionType::STMIB;
			}
			if ((op & 0x111101) == 0x011001) {
				return ARMInstructionType::LDMIB;
			}
			if ((op & 0x100101) == 0x000100) {
				return ARMInstructionType::STM;
			}
			if ((op & 0x100101) == 0x000101) {
				if (r == 0x0) {
					return ARMInstructionType::LDM;
				}
				else {
					return ARMInstructionType::LDM_EXCEPTION;
				}
			}
			if ((op & 0x110000) == 0x100000) {
				return ARMInstructionType::B;
			}
			if ((op & 0x110000) == 0x110000) {
				return ARMInstructionType::BL;
			}

			return ARMInstructionType::UNIMPLEMENTED;
		}

		ARMInstructionType constexpr decode_coprocessor_and_supervisor_call(ArmInstruction instruction)
		{
			const ArmInstruction op1 = (instruction >> 20) & 0b111111u;

			if ((op1 & 0b000001u) == 0b000000u) {
				// Technically, undefined but I think not the mnemonic
				return ARMInstructionType::UNIMPLEMENTED;
			}
			if ((op1 & 0b110000u) == 0b110000u) {
				// SVC?
				return ARMInstructionType::SWI;
			}
		
			const ArmInstruction coproc = (instruction >> 8) & 0b1111u;
			const ArmInstruction op = (instruction >> 4) & 0b1u;

			if ((coproc & 0x1110) != 0b1010u) {
				if ((op1 & 0b100001u) == 0b000000u && (op1 & 0b111011u) != 0b000000u) {
					return ARMInstructionType::STC;
				}
				if ((op1 & 0b100001u) == 0b000001u && (op1 & 0b111011u) != 0b000001u) {
					// const ArmInstruction rn = (instruction >> 16) & 0b1111u;
					// rn = 1111 is Load Coprocessor (literal)
					// rn != 1111 is Load Coprocessor (immediate)
					return ARMInstructionType::LDC;
				}
				if (op1 == 0b000100u || op1 == 0b000101u) {
					// 000100 = MCRR, v5TE
					// 000101 = MRRC, v5TE
					return ARMInstructionType::UNIMPLEMENTED;
				}
				if ((op1 & 0b110000u) == 0b100000u && op == 0b0u) {
					return ARMInstructionType::CDP;
				}
				if ((op1 & 0b110001u) == 0b100000u && op == 0b1u) {
					return ARMInstructionType::MCR;
				}
				if ((op1 & 0b110001u) == 0b100001u && op == 0b1u) {
					return ARMInstructionType::MRC;
				}
			}
			else {
				// coproc = 101x

				// op1 = 0xxxxx (!000x0x) - Advanced SIMD and Floating-point (VFP) 
				// op1 = 00010x - 64-bit transfers between ARM core and extension
				// registers
				// op1 = 10xxxx, op = 0 - Floating-point data-processing
				// instructions
				// op1 = 10xxxx, op = 1 - 8, 16, and 32-bit transfer between
				// ARM core and extension registers

				// We don't have any of these
				return ARMInstructionType::UNIMPLEMENTED;
			}

			return ARMInstructionType::UNIMPLEMENTED;
		}

		ARMInstructionType constexpr decode_unconditional_instruction(ArmInstruction instruction)
		{
			// const ArmInstruction op1 = (instruction >> 20) & 0b11111111u;

			// op1 = 0xxxxxxx:
		
			// SRS,RFE, MCRR, MRRC are v6
			// BL, STC, LDC, CDP, MCR, MRC are v5
		
			// op1 != 0xxxxxxx:

			// op1 = 01111111, op2 = 1111 is pernamently undefined but on v5
			// some PLD is v5TE
			// CPS, SETEND are v6
			// CLREX is v6K
			// DSB, ISB are v6T2
			// Advanced SIMD, PLI, DMB are v7
			// Memory hints, some PLD are MP Ext (which are in turn were 
			// introduced for v7 chips)
			// The rest are, and I quote the spec, "unpredictable".
		
			return ARMInstructionType::UNIMPLEMENTED;
		}
	}

#pragma endregion

#pragma region Thumb Decoding

	// https://developer.arm.com/documentation/ddi0406/cb/Application-Level-Architecture/Thumb-Instruction-Set-Encoding/Thumb-instruction-set-encoding?lang=en
	namespace DecodeThumb {

		bool constexpr is_32_bit(ThumbInstruction instruction) {
			const ThumbInstruction important_bits = (instruction >> 11) & 0b11111u;
			return important_bits == 0b11101u
				|| important_bits == 0b11110u
				|| important_bits == 0b11111u;
		}

		ThumbInstructionType constexpr decode_16(ThumbInstruction instruction)
		{
			const ThumbInstruction opcode = (instruction >> 10) & 0b111111u;

			if ((opcode & 0b110000u) == 0b000000u) {
				// Shift (immediate), add, subtract, move, and compare
				return decode_16_shift_add_sub_mov_cmp(instruction);
			}
			if (opcode == 0b010000u) {
				// Data-processing
				return decode_16_data_processing(instruction);
			}
			if (opcode == 0b010001u) {
				// Special data instructions and branch and exchange
				return decode_16_special_data_branch_exchange(instruction);
			}
			if ((opcode & 0b111110u) == 0b010010u) {
				return ThumbInstructionType::LDR;
			}
			if ((opcode & 0b111100u) == 0b010100u
				|| (opcode & 0b111000u) == 0b011000u
				|| (opcode & 0b111000u) == 0b100000u) {
				// Load/store single data item
				return decode_16_load_store_single_data(instruction);
			}
			if ((opcode & 0b111110u) == 0b101000u) {
				// Generate PC-relative address, see ADR
				return ThumbInstructionType::ADD;
			}
			if ((opcode & 0b111110u) == 0b101010u) {
				// Generate SP-relative address
				return ThumbInstructionType::ADD;
			}
			if ((opcode & 0b111100u) == 0b101100u) {
				// Miscellaneous 16-bit instructions
				return decode_16_misc(instruction);
			}
			if ((opcode & 0b111110u) == 0b110000u) {
				return ThumbInstructionType::STMIA;
			}
			if ((opcode & 0b111110u) == 0b110010u) {
				// Load multiple registers, see LDM/LDMIA/LDMFD (Thumb)
				return ThumbInstructionType::LDMIA;
			}
			if ((opcode & 0b111100u) == 0b110100u) {
				// Conditional branch, and Supervisor Call
				return decode_16_conditional_branch_supervisor(instruction);
			}
			if ((opcode & 0b111110u) == 0b111000u) {
				return ThumbInstructionType::B;
			}

			return ThumbInstructionType::UNIMPLEMENTED;
		}

		ThumbInstructionType constexpr decode_16_shift_add_sub_mov_cmp(ThumbInstruction instruction)
		{
			const ThumbInstruction opcode = (instruction >> 9) & 0b11111u;

			if ((opcode & 0b11100u) == 0b00000u) {
				if (((instruction >> 6) & 0b11111111u) == 0b00000000u) {
					// opcode = 0b00000u and bits[8:6] are 0b000u
					// MOV (register, Thumb)
					return ThumbInstructionType::MOV;
				}
				return ThumbInstructionType::LSL;
			}
			if ((opcode & 0b11100u) == 0b00100u) {
				return ThumbInstructionType::LSR;
			}
			if ((opcode & 0b11100u) == 0b01000u) {
				return ThumbInstructionType::ASR;
			}
			if (opcode == 0b01100u) {
				// Add register
				return ThumbInstructionType::ADD;
			}
			if (opcode == 0b01101u) {
				// Subtract register
				return ThumbInstructionType::SUB;
			}
			if (opcode == 0b01110u) {
				// Add 3-bit immediate
				return ThumbInstructionType::ADD;
			}
			if (opcode == 0b01111u) {
				// Subtract 3-bit immediate
				return ThumbInstructionType::SUB;
			}
			if ((opcode & 0b11100u) == 0b10000u) {
				return ThumbInstructionType::MOV;
			}
			if ((opcode & 0b11100u) == 0b10100u) {
				return ThumbInstructionType::CMP;
			}
			if ((opcode & 0b11100u) == 0b11000u) {
				// Add 8-bit immediate
				return ThumbInstructionType::ADD;
			}
			if ((opcode & 0b11100u) == 0b11100u) {
				// Subtract 8-bit immediate
				return ThumbInstructionType::SUB;
			}

			return ThumbInstructionType::UNIMPLEMENTED;
		}

		ThumbInstructionType constexpr decode_16_data_processing(ThumbInstruction instruction)
		{
			const ThumbInstruction opcode = (instruction >> 6) & 0b1111u;

			switch (opcode) {
			case 0b0000u: return ThumbInstructionType::AND;
			case 0b0001u: return ThumbInstructionType::EOR;
			case 0b0010u: return ThumbInstructionType::LSL;
			case 0b0011u: return ThumbInstructionType::LSR;
			case 0b0100u: return ThumbInstructionType::ASR;
			case 0b0101u: return ThumbInstructionType::ADC;
			case 0b0110u: return ThumbInstructionType::SBC;
			case 0b0111u: return ThumbInstructionType::ROR;
			case 0b1000u: return ThumbInstructionType::TST;
			case 0b1001u: return ThumbInstructionType::RSB;
			case 0b1010u: return ThumbInstructionType::CMP;
			case 0b1011u: return ThumbInstructionType::CMN;
			case 0b1100u: return ThumbInstructionType::ORR;
			case 0b1101u: return ThumbInstructionType::MUL;
			case 0b1110u: return ThumbInstructionType::BIC;
			case 0b1111u: return ThumbInstructionType::MVN;
			}

			return ThumbInstructionType::UNIMPLEMENTED;
		}

		ThumbInstructionType constexpr decode_16_special_data_branch_exchange(ThumbInstruction instruction)
		{
			const ThumbInstruction opcode = (instruction >> 6) & 0b1111u;

			if (opcode == 0b0000u) {
				// Add low registers, v6T2
				return ThumbInstructionType::UNIMPLEMENTED;
			}
			if (opcode == 0b0001u || (opcode & 0b1110u) == 0b0010u) {
				return ThumbInstructionType::ADD;
			}
			if ((opcode & 0b1100u) == 0b0100u) {
				return ThumbInstructionType::CMP;
			}
			if (opcode == 0b1000u) {
				// Move low registers, v6
				return ThumbInstructionType::UNIMPLEMENTED;
			}
			if (opcode == 0b1001u || (opcode & 0b1110u) == 0b1010u) {
				return ThumbInstructionType::MOV;
			}
			if ((opcode & 0b1110u) == 0b1100u) {
				return ThumbInstructionType::BX;
			}
			if ((opcode & 0b1110u) == 0b1110u) {
				// Branch with Link and Exchange, v5T
				return ThumbInstructionType::UNIMPLEMENTED;
			}

			return ThumbInstructionType::UNIMPLEMENTED;
		}

		ThumbInstructionType constexpr decode_16_load_store_single_data(ThumbInstruction instruction)
		{
			const ThumbInstruction opA = (instruction >> 12) & 0b1111u;
			const ThumbInstruction opB = (instruction >> 9) & 0b111u;

			if (opA == 0b0101u) {
				switch (opB) {
				case 0b000u: return ThumbInstructionType::STR;
				case 0b001u: return ThumbInstructionType::STRH;
				case 0b010u: return ThumbInstructionType::STRB;
				case 0b011u: return ThumbInstructionType::LDRSB;
				case 0b100u: return ThumbInstructionType::LDR;
				case 0b101u: return ThumbInstructionType::LDRH;
				case 0b110u: return ThumbInstructionType::LDRB;
				case 0b111u: return ThumbInstructionType::LDRSH;
				}
				return ThumbInstructionType::UNIMPLEMENTED;
			}
			else if (opA == 0b0110u) {
				if ((opB & 0b100u) == 0b000u) {
					return ThumbInstructionType::STR;
				}
				else {
					return ThumbInstructionType::LDR;
				}
			}
			else if (opA == 0b0111u) {
				if ((opB & 0b100u) == 0b000u) {
					return ThumbInstructionType::STRB;
				}
				else {
					return ThumbInstructionType::LDRB;
				}
			}
			else if (opA == 0b1000u) {
				if ((opB & 0b100u) == 0b000u) {
					return ThumbInstructionType::STRH;
				}
				else {
					return ThumbInstructionType::LDRH;
				}
			}
			else if (opA == 0b1001u) {
				if ((opB & 0b100u) == 0b000u) {
					// Store register SP relative
					return ThumbInstructionType::STR;
				}
				else {
					// Load register SP relative
					return ThumbInstructionType::LDR;
				}
			}
			else {
				return ThumbInstructionType::UNIMPLEMENTED;
			}
		}

		ThumbInstructionType constexpr decode_16_misc(ThumbInstruction instruction)
		{
			const ThumbInstruction opcode = (instruction >> 5) & 0b1111111u;
		
			if ((opcode & 0b1111100u) == 0b0000000u) {
				// Add immediate to SP
				return ThumbInstructionType::ADD;
			}
			if ((opcode & 0b1111100u) == 0b0000100u) {
				// Subtract immediate from SP
				return ThumbInstructionType::SUB;
			}
			if ((opcode & 0b1110000u) == 0b0100000u) {
				return ThumbInstructionType::PUSH;
			}
			if ((opcode & 0b1110000u) == 0b1100000u) {
				return ThumbInstructionType::POP;
			}

			// opcode = 0001xxx - CBNZ/CBZ Compare and Branch on Zero - v6T2
			// opcode = 001000x - SXTH Signed Extend Halfword - v6
			// opcode = 001001x - SXTB Signed Extend Byte - v6
			// opcode = 001010x - UXTH Unsigned Extend Halfword - v6
			// opcode = 001011x - UXTB Unsigned Extend Byte - v6
			// opcode = 0011xxx - CBNZ/CBZ Compare and Branch on Zero - v6T2
			// opcode = 0110010 - STEND Set Endianness - v6
			// opcode = 0110011 - CPS Change Processor State - v6
			// opcode = 1001xxx - CBNZ/CBZ Compare and Branch on Nonzero - v6T2
			// opcode = 101000x - REV Byte-Reverse Word - v6
			// opcode = 101001x - REV16 Byte-Reverse Packed Halfword - v6
			// opcode = 101011x - REVSH Byte-Reverse Signed Halfword - v6
			// opcode = 1011xxx - CBNZ/CBZ Compare and Branch on Nonzero - v6T2
			// opcode = 1110xxx - BKPT Breakpoint - v5
			// opcode = 1111xxx - if-then and hints:
			// IT, NOP are v6T2
			// YIELD, WFE, WFI, SEV are v7

			return ThumbInstructionType::UNIMPLEMENTED;
		}

		ThumbInstructionType constexpr decode_16_conditional_branch_supervisor(ThumbInstruction instruction)
		{
			const ThumbInstruction opcode = (instruction >> 8) & 0b1111u;

			if (opcode == 0b1110u) {
				// Permanently undefined
				return ThumbInstructionType::UNIMPLEMENTED;
			}
			else if (opcode == 0b1111u) {
				// or SVC, supervisor call, previously called SWI
				return ThumbInstructionType::SWI;
			}
			else {
				// not 111x
				return ThumbInstructionType::B;
			}
		}

		ThumbInstructionType constexpr decode_32(ThumbInstruction first_instruction, 
			ThumbInstruction second_instruction)
		{
			const ThumbInstruction op1 = (first_instruction >> 11) & 0b11u;
			const ThumbInstruction op2 = (first_instruction >> 4) & 0b1111111u;

			if (op1 == 0b01u) {
				if ((op2 & 0b1100100u) == 0b0000000u) {
					return decode_32_load_store_multiple(first_instruction);
				}
				if ((op2 & 0b1100100u) == 0b0000100u) {
					// STREX Store Register Exclusive is v6T2
					// LDREX Loard Register Exclusive is v6T2
					// STRD Store Register Dual is v6T2
					// LDRD Loard Register immediate or dual are v6T2
					// STREXB Store Register Exclusive Byte is v7
					// STREXH Store Register Exclusive halfword is v7
					// STREXD Store Register Exclusive Doubleword is v7
					// TBB Table Branch Byte is v6T2
					// TBH Table Branch Halfword is v6T2
					// LDREXB Loard Register Exclusive Byte is v7
					// LDREXH Loard Register Exclusive Halfword is v7
					// LDREXD Loard Register Exclusive Doubleword is v7
					return ThumbInstructionType::UNIMPLEMENTED;
				}
				if ((op2 & 0b1100000u) == 0b0100000u) {
					return decode_32_data_processing_shifted_register(first_instruction,
						second_instruction);
				}
				if ((op2 & 0b1000000u) == 0b1000000u) {
					// Coprocessor, Advanced SIMD, and Floating-point instructions
					// These encodings are all available in ARMv6T2 and above.
					return ThumbInstructionType::UNIMPLEMENTED;
				}
			}
			else if (op1 == 0b10u) {
				const ThumbInstruction op = (second_instruction >> 15) & 0b1u;

				if (op == 0b1u) {

					const ThumbInstruction op1_misc = (second_instruction >> 12) & 0b111u;
					// const ThumbInstruction imm8 = second_instruction & 0b1111'1111u;
					// const ThumbInstruction op = (first_instruction >> 4) & 0b111'1111u;
					// const ThumbInstruction op2 = (second_instruction >> 8) & 0b1111u;

					// op1_misc == 0b000u, op == 0b111111ux
					// 1111110 - HVC Hypervisor Call is v7TE
					// 1111111 - SMC/SMI Secure Monitor Call is Security Extensions

					// op1_misc == 0b010u, op = 0b1111111u
					// Permanently undefined

					// op1_misc == 0b0ux0
					// NOTE(ches) These should all be unimplemented, from what I can tell
					// https://developer.arm.com/documentation/ddi0406/cb/Application-Level-Architecture/Thumb-Instruction-Set-Encoding/32-bit-Thumb-instruction-encoding/Branches-and-miscellaneous-control?lang=en
					// MSR Move to Banked or Special Register
					// B Conditional Branch - v6T2
					// MSR (Banked Register) Move to Banked or Special register - v7VE
					// BXJ Branch and Exchange Jazelle - v6T2
					// ERET Exception Return - v6T2
					// SUBS PC, LR Exception Return - v6T2
					// MRS (Banked Register) Move from Banked or Special register - v7VE

					if ((op1_misc & 0b101u) == 0b101u) {
						return ThumbInstructionType::BL;
					}

					return ThumbInstructionType::UNIMPLEMENTED;
				}
				if ((op2 & 0b0100000u) == 0b0000000u) {
					// Data-processing (modified immediate)
					// These encodings are all available in ARMv6T2 and above.
					return ThumbInstructionType::UNIMPLEMENTED;
				}
				if ((op2 & 0b0100000u) == 0b0100000u) {
					// Data-processing (plain binary immediate)
					// These encodings are all available in ARMv6T2 and above.
					return ThumbInstructionType::UNIMPLEMENTED;
				}
			}
			else if (op1 == 0b11u) {
				if ((op2 & 0b1110001u) == 0b0000000u) {
					return decode_32_load_single(first_instruction,
						second_instruction);
				}
				if ((op2 & 0b1100111u) == 0b0000001u) {
					return decode_32_load_byte_memory_hints(first_instruction,
						second_instruction);
				}
				if ((op2 & 0b1100111u) == 0b0000011u) {
					return decode_32_load_halfword_memory_hints(first_instruction,
						second_instruction);
				}
				if ((op2 & 0b1100111u) == 0b0000101u) {
					return decode_32_load_word(first_instruction,
						second_instruction);
				}
				if ((op2 & 0b1100111u) == 0b0000111u) {
					// explicitly undefined
					return ThumbInstructionType::UNIMPLEMENTED;
				}
				if ((op2 & 0b1110001u) == 0b0010000u) {
					// Advanced SIMD element or structure load/store instructions
					// We don't have these
					return ThumbInstructionType::UNIMPLEMENTED;
				}
				if ((op2 & 0b1110000u) == 0b0100000u) {
					return decode_32_data_processing_register(first_instruction,
						second_instruction);
				}
				if ((op2 & 0b1111000u) == 0b0110000u) {
					return decode_32_multiply_multiply_accumulate_absolute_difference(
						first_instruction, second_instruction);
				}
				if ((op2 & 0b1111000u) == 0b0111000u) {
					// Long multiply, long multiply accumulate, and divide
					// These are all v6T2 or v7-R
					return ThumbInstructionType::UNIMPLEMENTED;
				}
				if ((op2 & 0b1000000u) == 0b1000000u) {
					// Coprocessor, Advanced SIMD, and Floating-point instructions
					// These encodings are all available in ARMv6T2 and above.
					return ThumbInstructionType::UNIMPLEMENTED;
				}
			}
			else {
				// This must be a 16-bit instruction, shouldn't have gotten here
				return ThumbInstructionType::UNIMPLEMENTED;
			}

			return ThumbInstructionType::UNIMPLEMENTED;
		}

		ThumbInstructionType constexpr decode_32_load_store_multiple(
			ThumbInstruction first_instruction)
		{
			const ThumbInstruction op = (first_instruction >> 7) & 0b11u;
			const ThumbInstruction l = (first_instruction >> 4) & 0b1u;
			const ThumbInstruction wrn = (((first_instruction >> 5) & 0b1u) << 4) 
				| (first_instruction & 0b1111u);

			if (op == 0b01u) {
				if (l == 0b0u) {
					return ThumbInstructionType::STMIA;
				}
				else if (wrn == 0b11101u) {
					return ThumbInstructionType::POP;
				}
				else {
					return ThumbInstructionType::LDMIA;
				}
			}
			else if (op == 0b10u) {
				if (l == 0b1u) {
					// I don't think we have LDMDB
					return ThumbInstructionType::UNIMPLEMENTED;
				}
				else if (wrn == 0b11101u) {
					return ThumbInstructionType::PUSH;
				}
				else {
					// I don't think we have STMDB
					return ThumbInstructionType::UNIMPLEMENTED;
				}
			}
			else {
				// 0b00u, 0b11u
				// SRS Store Return State is ARMv6T2
				// RFE Return From Exception is ARMv6T2
				return ThumbInstructionType::UNIMPLEMENTED;
			}
		}

		ThumbInstructionType constexpr decode_32_data_processing_shifted_register(
			ThumbInstruction first_instruction, 
			ThumbInstruction second_instruction)
		{

			const ThumbInstruction op = (first_instruction >> 5) & 0b1111u;
			const ThumbInstruction rn = first_instruction & 0b111u;
			const ThumbInstruction rds = (((second_instruction >> 8) & 0b1111u) << 1)
				| ((first_instruction >> 4) & 0b1u);

			if (op == 0b0000u) {
				if (rds == 0b11111u) {
					return ThumbInstructionType::TST;
				}
				else {
					return ThumbInstructionType::AND;
				}
			}
			else if (op == 0b0001u) {
				return ThumbInstructionType::BIC;
			}
			else if (op == 0b0010u) {
				if (rn == 0b11111u) {
					const ThumbInstruction imm3imm2 = 
						(((second_instruction >> 12) & 0b111u) << 2)
						| ((second_instruction >> 6) & 0b11u);
					const ThumbInstruction type = (second_instruction >> 4) & 0b11u;

					if (type == 0b00u) {
						if (imm3imm2 == 0b00000u) {
							return ThumbInstructionType::MOV;
						}
						else {
							return ThumbInstructionType::LSL;
						}
					}
					else if (type == 0b01u) {
						return ThumbInstructionType::LSR;
					}
					else if (type == 0b10u) {
						return ThumbInstructionType::ASR;
					}
					else {
						// type == 0b11u
						if (imm3imm2 == 0b00000u) {
							//TODO(ches) figure out if we support this
							// RRX Rotate Right with Extend
							return ThumbInstructionType::UNIMPLEMENTED;
						}
						else {
							return ThumbInstructionType::ROR;
						}
					}
				}
				else {
					return ThumbInstructionType::ORR;
				}
			}
			else if (op == 0b0011u) {
				if (rn == 0b11111u) {
					return ThumbInstructionType::MVN;
				}
				else {
					// ORN Bitwise OR NOT is ARMv6T2
					return ThumbInstructionType::UNIMPLEMENTED;
				}
			}
			else if (op == 0b0100u) {
				if (rds == 0b11111u) {
					//TODO(ches) figure out if we support this
					// TEQ Test Equivalence
					return ThumbInstructionType::UNIMPLEMENTED;
				}
				else {
					return ThumbInstructionType::EOR;
				}
			}
			else if (op == 0b0110u) {
				// PKH Pakc Halfword is ARMv6T2
				return ThumbInstructionType::UNIMPLEMENTED;
			}
			else if (op == 0b1000u) {
				if (rds == 0b11111u) {
					return ThumbInstructionType::CMN;
				}
				else {
					return ThumbInstructionType::ADD;
				}
			}
			else if (op == 0b1010u) {
				return ThumbInstructionType::ADC;
			}
			else if (op == 0b1011u) {
				return ThumbInstructionType::SBC;
			}
			else if (op == 0b1101u) {
				if (rds == 0b11111u) {
					return ThumbInstructionType::CMP;
				}
				else {
					return ThumbInstructionType::SUB;
				}
			}
			else if (op == 0b1110u) {
				return ThumbInstructionType::RSB;
			}

			return ThumbInstructionType::UNIMPLEMENTED;
		}

		ThumbInstructionType constexpr decode_32_load_single(
			ThumbInstruction first_instruction, 
			ThumbInstruction second_instruction)
		{
			const ThumbInstruction op1 = (first_instruction >> 5) & 0b111u;
			const ThumbInstruction op2 = (second_instruction >> 6) & 0b111111u;

			if (op1 == 0b000u) {
				if (((op2 & 0b100100u) == 0b100100u)
					|| ((op2 & 0b111100u) == 0b110000u)
					|| (op2 == 0b000000u)) {
					return ThumbInstructionType::STRB;
				}
				// op2 == 0b1110uxx, STRBT Store Register Byte Unprivileged
			}
			else if (op1 == 0b001u) {
				if (((op2 & 0b100100u) == 0b100100u)
					|| ((op2 & 0b111100u) == 0b11000u)
					|| (op2 == 0b000000u)) {
					return ThumbInstructionType::STRH;
				}
				// op2 == 0b1110uxx, STRBT Store Register Byte Unprivileged
			}
			else if (op1 == 0b010u) {
				if (((op2 & 0b100100u) == 0b100100u)
					|| ((op2 & 0b111100u) == 0b110000u)
					|| (op2 == 0b000000u)) {
					return ThumbInstructionType::STR;
				}
				// op2 == 0b1110uxx, STRBT Store Register Byte Unprivileged
			}
			else if (op1 == 0b100u) {
				return ThumbInstructionType::STRB;
			}
			else if (op1 == 0b101u) {
				return ThumbInstructionType::STRH;
			}
			else if (op1 == 0b110u) {
				return ThumbInstructionType::STR;
			}

			return ThumbInstructionType::UNIMPLEMENTED;
		}

		ThumbInstructionType constexpr decode_32_load_byte_memory_hints(
			ThumbInstruction first_instruction, 
			ThumbInstruction second_instruction)
		{
			const ThumbInstruction op1 = (first_instruction >> 7) & 0b11u;
			const ThumbInstruction rn = first_instruction & 0b1111u;
			const ThumbInstruction op2 = (second_instruction >> 6) & 0b111111u;
			const ThumbInstruction rt = (second_instruction >> 12) & 0b1111u;

			if (op1 == 0b00u && op2 == 0b000000u && rn != 0b1111u) {
				if (rt != 0b1111u) {
					return ThumbInstructionType::LDRB;
				}
				// PLD Preload Data is at least v5TE
			}
			else if ((op1 & 0b10u) == 0b00u && rn == 0b1111u) {
				if (rt != 0b1111u) {
					return ThumbInstructionType::LDRB;
				}
				// PLD Preload Data is at least v5TE
			}
			else if (op1 == 0b00u) {
				if ((op2 & 0b100100u) == 0b100100u && rn != 0b1111u) {
					return ThumbInstructionType::LDRB;
				}
				else if ((op2 & 0b111100u) == 0b110000u && rn != 0b1111u) {
					return ThumbInstructionType::LDRB;
				}
				// op2 == 0b1100uxx, rn != 0b1111u, rt == 0b1111u is PLD
				// op2 == 0b1110uxx, rn != 0b1111u is LDRBT, which I don't think we have
			}
			else if (op1 == 0b01u && rn != 0b1111u) {
				if (rt != 0b1111u) {
					return ThumbInstructionType::LDRB;
				}
				// PLD Preload Data is at least v5TE
			}
			else if (op1 == 0b10u && op2 == 0b000000u && rn != 0b1111u) {
				if (rt != 0b1111u) {
					return ThumbInstructionType::LDRSB;
				}
				// else PLI Preload Instruction, v7
			}
			else if ((op1 & 0b10u) == 0b10u && rn == 0b1111u) {
				if (rt != 0b1111u) {
					return ThumbInstructionType::LDRSB;
				}
				// else PLI Preload Instruction, v7
			}
			else if (op1 == 0b10u) {
				if ((op2 & 0b100100u) == 0b100100u && rn != 0b1111u) {
					return ThumbInstructionType::LDRSB;
				}
				else if ((op2 & 0b111100u) == 0b110000u && rn != 0b1111u) {
					return ThumbInstructionType::LDRSB;
				}
				// op2 == 0b1100uxx, rn != 0b1111u, rt == 0b1111u is PLI
				// op2 == 0b1110uxx, rn != 0b1111u is LDRSBT, which I don't think we have
			}
			else if (op1 == 0b11u && rn != 0b1111u) {
				if (rt != 0b1111u) {
					return ThumbInstructionType::LDRSB;
				}
				// else PLI Preload Instruction, v7
			}
			return ThumbInstructionType::UNIMPLEMENTED;
		}

		ThumbInstructionType constexpr decode_32_load_halfword_memory_hints(
			ThumbInstruction first_instruction, 
			ThumbInstruction second_instruction)
		{
			const ThumbInstruction op1 = (first_instruction >> 7) & 0b11u;
			const ThumbInstruction rn = first_instruction & 0b1111u;
			const ThumbInstruction op2 = (second_instruction >> 6) & 0b111111u;
			const ThumbInstruction rt = (second_instruction >> 12) & 0b1111u;

			if ((op1 & 0b10u) == 0b00u && rn == 0b1111u) {
				if (rt != 0b1111u) {
					return ThumbInstructionType::LDRH;
				}
				// PLD Preload Data is v5TE
			}
			else if ((op1 == 0b00u && (op2 & 0b100100u) == 0b100100u && rn != 0b1111u)
				|| (op1 == 0b00u && (op2 & 0b111100u) == 0b110000u && rn != 0b1111u && rt != 0b1111u)
				|| (op1 == 0b01u && rn != 0b1111u && rt != 0b1111u)
				) {
				return ThumbInstructionType::LDRH;
			}
			else if (op1 == 0b00u && op2 == 0b000000u && rn != 0b1111u && rt != 0b1111u) {
				// op2 == 0b1110uxx, rn != 0b1111u - LDRHT Load Register Halfword Unprivileged is v6T2
				// op2 == 0b000000u, rn != 0b1111u, rt == 0b1111u - PLD
				// op2 == 0b1100uxx, rn != 0b1111u, rt == 0b1111u - PLD
				return ThumbInstructionType::LDRH;
			}
			// op1 == 0b01u, rn != 0b1111u, rt == 0b1111u - PLD
			else if ((op1 == 0b10u && (op2 & 0b100100u) == 0b100100u && rn != 0b1111u)
				|| (op1 == 0b10u && (op2 & 0b111100u) == 0b110000u && rn != 0b1111u && rt != 0b1111u)
				|| (op1 == 0b11u && rn == 0b1111u && rt != 0b1111u)
				|| ((op1 & 0b10u) == 0b10u && rn == 0b1111u && rt != 0b1111u)
				|| (op1 == 0b10u && op2 == 0b000000u && rn != 0b1111u && rt != 0b1111u)
				) {
				return ThumbInstructionType::LDRSH;
			}
			// LDRSHT is ambiguous in the spec regarding rt, but we don't have that anyway
			else if ((op1 == 0b10u && op2 == 0b000000u && rn != 0b1111u && rt == 0b1111u)
				|| (op1 == 0b10u && (op2 & 0b111100u) == 0b110000u && rn != 0b1111u && rt == 0b1111u)
				|| ((op1 & 0b10u) == 0b10u && rn == 0b1111u && rt == 0b1111u)
				|| (op1 == 0b11u && rn != 0b1111u && rt == 0b1111u)
				) {
				// Unallocated memory hint (treat as NOP)
				return ThumbInstructionType::NOP;
			}

			return ThumbInstructionType::UNIMPLEMENTED;
		}

		ThumbInstructionType constexpr decode_32_load_word(
			ThumbInstruction first_instruction, 
			ThumbInstruction second_instruction)
		{
			const ThumbInstruction op1 = (first_instruction >> 7) & 0b11u;
			const ThumbInstruction rn = first_instruction & 0b1111u;
			const ThumbInstruction op2 = (second_instruction >> 6) & 0b111111u;

			if ((op1 == 0b00u && op2 == 0b000000u && rn != 0b1111u)
			|| (op1 == 0b00u && (op2 & 0b100100u) == 0b100100u && rn != 0b1111u)
			|| (op1 == 0b00u && (op2 & 0b111100u) == 0b110000u && rn != 0b1111u)
			|| (op1 == 0b01u && rn != 0b1111u)
			|| ((op1 & 0b10u) == 0b00u && rn == 0b1111u)
			) {
				return ThumbInstructionType::LDR;
			}
			// op1 == 0b00u, op2 == 1110xx, rn != 0b1111u - LDRT Load Register Unprivileged
		
			return ThumbInstructionType::UNIMPLEMENTED;
		}

		ThumbInstructionType constexpr decode_32_data_processing_register(
			ThumbInstruction first_instruction, 
			ThumbInstruction second_instruction)
		{
			const ThumbInstruction op1 = (first_instruction >> 4) & 0b1111u;
			const ThumbInstruction op2 = (second_instruction >> 4) & 0b1111u;

			if ((op1 & 0b1110u) == 0b0000u && op2 == 0b0000u) {
				return ThumbInstructionType::LSL;
			}
			else if ((op1 & 0b1110u) == 0b0010u && op2 == 0b0000u) {
				return ThumbInstructionType::LSR;
			}
			else if ((op1 & 0b1110u) == 0b0100u && op2 == 0b0000u) {
				return ThumbInstructionType::ASR;
			}
			else if ((op1 & 0b1110u) == 0b0110u && op2 == 0b0000u) {
				return ThumbInstructionType::ROR;
			}
			// Everything else is newer
			// https://developer.arm.com/documentation/ddi0406/cb/Application-Level-Architecture/Thumb-Instruction-Set-Encoding/32-bit-Thumb-instruction-encoding/Data-processing--register-?lang=en

			return ThumbInstructionType::UNIMPLEMENTED;
		}

		ThumbInstructionType constexpr decode_32_multiply_multiply_accumulate_absolute_difference(
			ThumbInstruction first_instruction, 
			ThumbInstruction second_instruction)
		{
			const ThumbInstruction op1 = (first_instruction >> 4) & 0b111u;
			const ThumbInstruction op2 = (second_instruction >> 4) & 0b11u;
			const ThumbInstruction ra = (second_instruction >> 12) & 0b1111u;

			if (op1 == 0b000u && op2 == 0b00u && ra == 0b1111u) {
				return ThumbInstructionType::MUL;
			}

			// We don't have the rest of these in thumb mode
			// https://developer.arm.com/documentation/ddi0406/cb/Application-Level-Architecture/Thumb-Instruction-Set-Encoding/32-bit-Thumb-instruction-encoding/Multiply--multiply-accumulate--and-absolute-difference?lang=en
			return ThumbInstructionType::UNIMPLEMENTED;
		}

	}

#pragma endregion

	ARMInstructionType ARM7TDMI::decode_arm(ArmInstruction instruction)
	{
		return DecodeArm::decode(instruction);
	}

	ThumbInstructionType ARM7TDMI::decode_thumb(ThumbInstruction instruction, 
		ThumbInstruction next_instruction)
	{
		//TODO(ches) figure out how to pull instructions, rather than paramters

		if (DecodeThumb::is_32_bit(instruction)) {
			return DecodeThumb::decode_16(instruction);
		}
		else {
			return DecodeThumb::decode_32(instruction, next_instruction);
		}
	
	}

	void ARM7TDMI::set_flag_N(bool flag) {
		if (flag) {
			CPSR |= SIGN_FLAG_BITS;
		}
		else {
			CPSR &= ~SIGN_FLAG_BITS;
		}
	}

	void ARM7TDMI::set_flag_Z(bool flag) {
		if (flag) {
			CPSR |= ZERO_FLAG_BITS;
		}
		else {
			CPSR &= ~ZERO_FLAG_BITS;
		}
	}

	void ARM7TDMI::set_flag_C(bool flag) {
		if (flag) {
			CPSR |= CARRY_FLAG_BITS;
		}
		else {
			CPSR &= ~CARRY_FLAG_BITS;
		}
	}

	void ARM7TDMI::set_flag_V(bool flag) {
		if (flag) {
			CPSR |= OVERFLOW_FLAG_BITS;
		}
		else {
			CPSR &= ~OVERFLOW_FLAG_BITS;
		}
	}

	void ARM7TDMI::set_flag_I(bool flag) {
		if (flag) {
			CPSR |= IRQ_DISABLE_FLAG_BITS;
		}
		else {
			CPSR &= ~IRQ_DISABLE_FLAG_BITS;
		}
	}

	void ARM7TDMI::set_flag_F(bool flag) {
		if (flag) {
			CPSR |= FIQ_DISABLE_FLAG_BITS;
		}
		else {
			CPSR &= ~FIQ_DISABLE_FLAG_BITS;
		}
	}

	void ARM7TDMI::set_flag_T(bool flag) {
		if (flag) {
			CPSR |= STATE_FLAG_BITS;
		}
		else {
			CPSR &= ~STATE_FLAG_BITS;
		}
	}

	void ARM7TDMI::set_flag_mode(ArmMode mode) {
		Word result = 0;
		switch (mode) {
		case ArmMode::USR:
			result = MODE_USER;
			break;
		case ArmMode::FIQ:
			result = MODE_FIQ;
			break;
		case ArmMode::IRQ:
			result = MODE_IRQ;
			break;
		case ArmMode::SVC:
			result = MODE_SUPERVISOR;
			break;
		case ArmMode::ABT:
			result = MODE_ABORT;
			break;
		case ArmMode::UND:
			result = MODE_UNDEFINED;
			break;
		case ArmMode::SYS:
			result = MODE_SYSTEM;
			break;
		default:
			// Illegal values put the processor into an unrecoverable state
			LOG_FATAL("Invalid processor mode");
		}

		CPSR &= ~MODE_FLAG_BITS;
		CPSR |= result;
	}

	void ARM7TDMI::write_register(Word register_id, Word value) {
		const ArmMode mode = get_flag_mode();

		switch (register_id) {
		//These share registers for every mode
		case 0: 
			R0 = value;
			break;
		case 1: 
			R1 = value;
			break;
		case 2: 
			R2 = value;
			break;
		case 3: 
			R3 = value;
			break;
		case 4: 
			R4 = value;
			break;
		case 5: 
			R5 = value;
			break;
		case 6: 
			R6 = value;
			break;
		case 7: 
			R7 = value;
			break;
		case 15: 
			R15 = value;
			break;

		// These are partially banked
		case 8:
			if (mode != ArmMode::FIQ) {
				R8 = value;
			}
			else [[unlikely]] {
				R8_fiq = value;
			}
			break;
		case 9:
			if (mode != ArmMode::FIQ) {
				R9 = value;
			}
			else [[unlikely]] {
				R9_fiq = value;
			}
			break;
		case 10:
			if (mode != ArmMode::FIQ) {
				R10 = value;
			}
			else [[unlikely]] {
				R10_fiq = value;
			}
			break;
		case 11:
			if (mode != ArmMode::FIQ) {
				R11 = value;
			}
			else [[unlikely]] {
				R11_fiq = value;
			}
			break;
		case 12:
			if (mode != ArmMode::FIQ) {
				R12 = value;
			}
			else [[unlikely]] {
				R12_fiq = value;
			}
			break;

		//These are banked
		case 13:
			switch (mode) {
			case ArmMode::SYS:
			case ArmMode::USR: 
				R13 = value;
				break;
			case ArmMode::FIQ: 
				R13_fiq = value;
				break;
			case ArmMode::IRQ: 
				R13_irq = value;
				break;
			case ArmMode::SVC: 
				R13_svc = value;
				break;
			case ArmMode::ABT: 
				R13_abt = value;
				break;
			case ArmMode::UND: 
				R13_und = value;
				break;
			}
			break;
		case 14:
			switch (mode) {
			case ArmMode::SYS:
			case ArmMode::USR: 
				R14 = value;
				break;
			case ArmMode::FIQ: 
				R14_fiq = value;
				break;
			case ArmMode::IRQ: 
				R14_irq = value;
				break;
			case ArmMode::SVC: 
				R14_svc = value;
				break;
			case ArmMode::ABT: 
				R14_abt = value;
				break;
			case ArmMode::UND: 
				R14_und = value;
				break;
			}
			break;
		default:
			LOG_FATAL("Unknown register ID");
			break;
		}
	}

	void ARM7TDMI::reset() {
		set_flag_mode(ArmMode::SVC);
		set_flag_I(false);
		set_flag_F(false);
		set_flag_T(false);
		R15 = 0;
	}

}
