#include "cpu/arm7tdmi.h"
#include "cpu/arm7tdmi_decode.h"

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
		// 1111 = NV
		return static_cast<ARMCond>(cond);
	}

#pragma region ARM7TDMI ARM Instructions
	void ARM7TDMI::arm_adc(ArmInstruction instruction)
	{
		// cond 00I0 101S Rn Rd operand2
		const ArmInstruction cond = (instruction >> 28) & 0b1111u;
		// First operand register. If this is the PC, it reads as the
		// instruction's address + 8, or + 12 when operand 2 is a register
		// shifted by a register.
		const ArmInstruction rn = (instruction >> 16) & 0b1111u;
		// Destination register
		const ArmInstruction rd = (instruction >> 12) & 0b1111u;

		// S, Whether we should update the flags
		const bool update_flags = ((instruction >> 20) & 0b1u) == 0b1u;
		// I, Whether operand 2 is a rotated immediate or a shifted register
		const bool is_immediate = ((instruction >> 25) & 0b1u) == 0b1u;
		// Whether a register operand 2 is shifted by a register (Rs) or by
		// an immediate amount
		const bool is_shift_by_register = ((instruction >> 4) & 0b1u) == 0b1u;

		// TODO(ches) handle Rd being the PC. Writing the PC is a branch, and
		// with S set the SPSR of the current mode is also copied to the CPSR
		// (exception return) instead of the flags being updated.

		// TODO(ches) finish the decoding and processing
		if (is_immediate) {
			// Operand 2 is an 8-bit immediate rotated right by twice the
			// 4-bit rotate amount. With a rotate of 0 the carry out of the
			// shifter is the current C flag, otherwise it is bit 31 of the
			// result.
			const ArmInstruction rotate = (instruction >> 8) & 0b1111u;
			const ArmInstruction imm8 = instruction & 0b1111'1111u;

		}
		else if (is_shift_by_register) {
			// Operand 2 is Rm shifted by the amount in the bottom byte of Rs.
			// Bit 7 must be 0, otherwise this would be the multiply or
			// halfword transfer space. Takes an extra internal cycle.
			const ArmInstruction rs = (instruction >> 8) & 0b1111u;
			const ArmInstruction shift_type = (instruction >> 5) & 0b11u;
			const ArmInstruction rm = instruction & 0b1111u;

		}
		else {
			// Operand 2 is Rm shifted by a 5-bit immediate amount.
			const ArmInstruction shift_amount = (instruction >> 7) & 0b1'1111u;
			const ArmInstruction shift_type = (instruction >> 5) & 0b11u;
			const ArmInstruction rm = instruction & 0b1111u;

			if (shift_type == 0b00u) {
				// LSL, an amount of 0 leaves Rm and the C flag unchanged
			}
			else if (shift_type == 0b01u) {
				// LSR, an amount of 0 encodes LSR #32
			}
			else if (shift_type == 0b10u) {
				// ASR, an amount of 0 encodes ASR #32
			}
			else /* if (shift_type == 0b11u) */ {
				// ROR, an amount of 0 encodes RRX (rotate right by 1 through
				// the C flag)
			}

		}

	}

	void ARM7TDMI::arm_add(ArmInstruction instruction)
	{}

	void ARM7TDMI::arm_and(ArmInstruction instruction)
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

	void ARM7TDMI::arm_orr(ArmInstruction instruction)
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

	void ARM7TDMI::arm_swpb(ArmInstruction instruction)
	{}

	void ARM7TDMI::arm_teq(ArmInstruction instruction)
	{}

	void ARM7TDMI::arm_tst(ArmInstruction instruction)
	{}

	void ARM7TDMI::arm_umlal(ArmInstruction instruction)
	{}

	void ARM7TDMI::arm_umull(ArmInstruction instruction)
	{}

	void ARM7TDMI::arm_undefined(ArmInstruction instruction)
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

	void ARM7TDMI::thumb_or(ThumbInstruction instruction)
	{}

	void ARM7TDMI::thumb_pop(ThumbInstruction instruction)
	{}

	void ARM7TDMI::thumb_push(ThumbInstruction instruction)
	{}

	void ARM7TDMI::thumb_ror(ThumbInstruction instruction)
	{}

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

	void ARM7TDMI::thumb_undefined(ThumbInstruction instruction)
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

#pragma endregion

	ARMInstructionType ARM7TDMI::decode_arm(ArmInstruction instruction)
	{
		return DecodeArm::decode(instruction);
	}

	ThumbInstructionType ARM7TDMI::decode_thumb(ThumbInstruction instruction)
	{
		return DecodeThumb::decode(instruction);
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
