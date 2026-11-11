#pragma once

#include "cpu/arm7tdmi.h"

namespace emulator {

	namespace DecodeArm
	{
		ARMInstructionType constexpr decode(ArmInstruction instruction);
		ARMInstructionType constexpr decode_data_processing_and_psr_transfer(ArmInstruction instruction);
		ARMInstructionType constexpr decode_psr_transfer(ArmInstruction instruction);
		ARMInstructionType constexpr decode_multiply_and_swap(ArmInstruction instruction);
		ARMInstructionType constexpr decode_halfword_and_signed_data_transfer(ArmInstruction instruction);
		ARMInstructionType constexpr decode_single_data_transfer(ArmInstruction instruction);
		ARMInstructionType constexpr decode_block_data_transfer(ArmInstruction instruction);
		ARMInstructionType constexpr decode_coprocessor_and_software_interrupt(ArmInstruction instruction);
	}

	namespace DecodeThumb {
		ThumbInstructionType constexpr decode(ThumbInstruction instruction);
		ThumbInstructionType constexpr decode_shift_add_subtract(ThumbInstruction instruction);
		ThumbInstructionType constexpr decode_move_compare_add_subtract_immediate(ThumbInstruction instruction);
		ThumbInstructionType constexpr decode_alu_operations(ThumbInstruction instruction);
		ThumbInstructionType constexpr decode_hi_register_operations_branch_exchange(ThumbInstruction instruction);
		ThumbInstructionType constexpr decode_load_store_register_offset(ThumbInstruction instruction);
		ThumbInstructionType constexpr decode_load_store_immediate_offset(ThumbInstruction instruction);
		ThumbInstructionType constexpr decode_miscellaneous(ThumbInstruction instruction);
		ThumbInstructionType constexpr decode_conditional_branch_software_interrupt(ThumbInstruction instruction);
	}

#pragma region ARM Decoding

	// ARMv4T ARM instruction encodings, as listed in the ARM7TDMI-S Technical
	// Reference Manual (ARM DDI 0234) and the ARM7TDMI Data Sheet
	// (ARM DDI 0029E), section 4.
	//
	// Anything outside of these formats (everything added in ARMv5 and later,
	// such as BLX, CLZ, BKPT, LDRD/STRD, QADD, PLD, and the cond = 1111
	// "unconditional" space) is not decoded here. On the ARM7TDMI those bit
	// patterns are either undefined (and take the undefined instruction trap)
	// or fall into one of the ARMv4T formats below.
	namespace DecodeArm
	{
		ARMInstructionType constexpr decode(ArmInstruction instruction)
		{
			// Bits 27-25 select the major instruction class. The condition
			// field (bits 31-28) does not affect decoding on ARMv4T, cond =
			// 1111 (NV) still decodes normally and simply never executes.
			const ArmInstruction op = (instruction >> 25) & 0b111u;

			switch (op)
			{
			case 0b000u:
				// Branch and exchange has to be checked before the data
				// processing space it sits inside of.
				if ((instruction & 0x0FFF'FFF0u) == 0x012F'FF10u)
				{
					return ARMInstructionType::BX;
				}
				// Bit 7 and bit 4 both set is the multiply, swap and
				// halfword transfer space.
				if ((instruction & 0b1001'0000u) == 0b1001'0000u)
				{
					const ArmInstruction sh = (instruction >> 5) & 0b11u;
					if (sh == 0b00u)
					{
						return decode_multiply_and_swap(instruction);
					}
					return decode_halfword_and_signed_data_transfer(instruction);
				}
				return decode_data_processing_and_psr_transfer(instruction);
			case 0b001u:
				return decode_data_processing_and_psr_transfer(instruction);
			case 0b010u:
				return decode_single_data_transfer(instruction);
			case 0b011u:
				if ((instruction & 0b1'0000u) != 0u)
				{
					return ARMInstructionType::UNDEFINED;
				}
				return decode_single_data_transfer(instruction);
			case 0b100u:
				return decode_block_data_transfer(instruction);
			case 0b101u:
			{
				const bool link = ((instruction >> 24) & 0b1u) == 0b1u;
				return link ? ARMInstructionType::BL : ARMInstructionType::B;
			}
			case 0b110u:
			{
				const bool load = ((instruction >> 20) & 0b1u) == 0b1u;
				return load ? ARMInstructionType::LDC : ARMInstructionType::STC;
			}
			default: /* case 0b111u: */
				return decode_coprocessor_and_software_interrupt(instruction);
			}
		}

		ARMInstructionType constexpr decode_data_processing_and_psr_transfer(ArmInstruction instruction)
		{
			const ArmInstruction opcode = (instruction >> 21) & 0b1111u;
			const bool set_flags = ((instruction >> 20) & 0b1u) == 0b1u;

			// The test and compare opcodes (10xx) without the S bit set are
			// where the PSR transfer instructions live.
			if ((opcode & 0b1100u) == 0b1000u && !set_flags)
			{
				return decode_psr_transfer(instruction);
			}

			switch (opcode)
			{
			case 0b0000u: return ARMInstructionType::AND;
			case 0b0001u: return ARMInstructionType::EOR;
			case 0b0010u: return ARMInstructionType::SUB;
			case 0b0011u: return ARMInstructionType::RSB;
			case 0b0100u: return ARMInstructionType::ADD;
			case 0b0101u: return ARMInstructionType::ADC;
			case 0b0110u: return ARMInstructionType::SBC;
			case 0b0111u: return ARMInstructionType::RSC;
			case 0b1000u: return ARMInstructionType::TST;
			case 0b1001u: return ARMInstructionType::TEQ;
			case 0b1010u: return ARMInstructionType::CMP;
			case 0b1011u: return ARMInstructionType::CMN;
			case 0b1100u: return ARMInstructionType::ORR;
			case 0b1101u: return ARMInstructionType::MOV;
			case 0b1110u: return ARMInstructionType::BIC;
			default: /* case 0b1111u: */ return ARMInstructionType::MVN;
			}
		}

		ARMInstructionType constexpr decode_psr_transfer(ArmInstruction instruction)
		{
			// MRS Rd, CPSR/SPSR
			// cond 0001 0P00 1111 Rd 0000 0000 0000
			if ((instruction & 0x0FBF'0FFFu) == 0x010F'0000u)
			{
				return ARMInstructionType::MRS;
			}
			// MSR CPSR/SPSR_<fields>, Rm
			// cond 0001 0P10 mask 1111 0000 0000 Rm
			if ((instruction & 0x0FB0'FFF0u) == 0x0120'F000u)
			{
				return ARMInstructionType::MSR;
			}
			// MSR CPSR/SPSR_<fields>, #imm
			// cond 0011 0P10 mask 1111 rotate imm8
			if ((instruction & 0x0FB0'F000u) == 0x0320'F000u)
			{
				return ARMInstructionType::MSR;
			}
			// Everything else here (CLZ, BLX, BKPT, QADD, the halfword
			// multiplies, MOVW/MOVT, ...) is ARMv5 or later.
			return ARMInstructionType::UNDEFINED;
		}

		ARMInstructionType constexpr decode_multiply_and_swap(ArmInstruction instruction)
		{
			const ArmInstruction op = (instruction >> 23) & 0b11111u;

			if (op == 0b00000u)
			{
				// cond 0000 00AS Rd Rn Rs 1001 Rm
				const bool accumulate = ((instruction >> 21) & 0b1u) == 0b1u;
				return accumulate ? ARMInstructionType::MLA : ARMInstructionType::MUL;
			}
			if (op == 0b00001u)
			{
				// cond 0000 1UAS RdHi RdLo Rs 1001 Rm
				const ArmInstruction ua = (instruction >> 21) & 0b11u;
				switch (ua)
				{
				case 0b00u: return ARMInstructionType::UMULL;
				case 0b01u: return ARMInstructionType::UMLAL;
				case 0b10u: return ARMInstructionType::SMULL;
				default: /* case 0b11u: */ return ARMInstructionType::SMLAL;
				}
			}
			// cond 0001 0B00 Rn Rd 0000 1001 Rm
			if ((instruction & 0x0FB0'0FF0u) == 0x0100'0090u)
			{
				const bool byte = ((instruction >> 22) & 0b1u) == 0b1u;
				return byte ? ARMInstructionType::SWPB : ARMInstructionType::SWP;
			}
			// The rest of this space is the ARMv6 exclusive loads/stores and
			// UMAAL, among others.
			return ARMInstructionType::UNDEFINED;
		}

		ARMInstructionType constexpr decode_halfword_and_signed_data_transfer(ArmInstruction instruction)
		{
			// cond 000P UIWL Rn Rd xxxx 1SH1 xxxx
			const bool load = ((instruction >> 20) & 0b1u) == 0b1u;
			const ArmInstruction sh = (instruction >> 5) & 0b11u;

			if (load)
			{
				switch (sh)
				{
				case 0b01u: return ARMInstructionType::LDRH;
				case 0b10u: return ARMInstructionType::LDRSB;
				case 0b11u: return ARMInstructionType::LDRSH;
				default: break;
				}
			}
			else if (sh == 0b01u)
			{
				return ARMInstructionType::STRH;
			}
			// Stores with S set are LDRD/STRD on ARMv5TE and later.
			return ARMInstructionType::UNDEFINED;
		}

		ARMInstructionType constexpr decode_single_data_transfer(ArmInstruction instruction)
		{
			// cond 01IP UBWL Rn Rd offset
			const bool pre_index = ((instruction >> 24) & 0b1u) == 0b1u;
			const bool byte = ((instruction >> 22) & 0b1u) == 0b1u;
			const bool write_back = ((instruction >> 21) & 0b1u) == 0b1u;
			const bool load = ((instruction >> 20) & 0b1u) == 0b1u;

			// Post-indexed with W set forces a user mode (unprivileged) access.
			const bool unprivileged = !pre_index && write_back;

			if (load)
			{
				if (byte)
				{
					return unprivileged ? ARMInstructionType::LDRBT : ARMInstructionType::LDRB;
				}
				return unprivileged ? ARMInstructionType::LDRT : ARMInstructionType::LDR;
			}
			if (byte)
			{
				return unprivileged ? ARMInstructionType::STRBT : ARMInstructionType::STRB;
			}
			return unprivileged ? ARMInstructionType::STRT : ARMInstructionType::STR;
		}

		ARMInstructionType constexpr decode_block_data_transfer(ArmInstruction instruction)
		{
			// cond 100P USWL Rn register_list
			const bool pre_index = ((instruction >> 24) & 0b1u) == 0b1u;
			const bool up = ((instruction >> 23) & 0b1u) == 0b1u;
			const bool psr_or_user = ((instruction >> 22) & 0b1u) == 0b1u;
			const bool load = ((instruction >> 20) & 0b1u) == 0b1u;
			const bool includes_pc = ((instruction >> 15) & 0b1u) == 0b1u;

			if (psr_or_user)
			{
				if (load && includes_pc)
				{
					return ARMInstructionType::LDM_EXCEPTION;
				}
				return load ? ARMInstructionType::LDM : ARMInstructionType::STM;
			}

			if (load)
			{
				if (pre_index)
				{
					return up ? ARMInstructionType::LDMIB : ARMInstructionType::LDMDB;
				}
				return up ? ARMInstructionType::LDMIA : ARMInstructionType::LDMDA;
			}
			if (pre_index)
			{
				return up ? ARMInstructionType::STMIB : ARMInstructionType::STMDB;
			}
			return up ? ARMInstructionType::STMIA : ARMInstructionType::STMDA;
		}

		ARMInstructionType constexpr decode_coprocessor_and_software_interrupt(ArmInstruction instruction)
		{
			// cond 1111 comment
			if (((instruction >> 24) & 0b1u) == 0b1u)
			{
				return ARMInstructionType::SWI;
			}
			// cond 1110 CP_Opc CRn CRd CP# CP 0 CRm
			if (((instruction >> 4) & 0b1u) == 0b0u)
			{
				return ARMInstructionType::CDP;
			}
			// cond 1110 CP_Opc L CRn Rd CP# CP 1 CRm
			const bool load = ((instruction >> 20) & 0b1u) == 0b1u;
			return load ? ARMInstructionType::MRC : ARMInstructionType::MCR;
		}
	}

#pragma endregion

#pragma region Thumb Decoding

	// ARMv4T Thumb instruction encodings, as listed in the ARM7TDMI-S
	// Technical Reference Manual (ARM DDI 0234) and the ARM7TDMI Data Sheet
	// (ARM DDI 0029E), section 5.
	//
	// Every ARMv4T Thumb instruction is exactly 16 bits. Thumb-2 32-bit
	// encodings, CBZ/CBNZ, IT, CPS, SXTB/UXTB, REV, BKPT, BLX, and the hint
	// instructions (NOP, YIELD, ...) are all ARMv5 or later.
	namespace DecodeThumb {

		ThumbInstructionType constexpr decode(ThumbInstruction instruction)
		{
			// Bits 15-13 select the major instruction class.
			const ThumbInstruction op = (instruction >> 13) & 0b111u;

			switch (op)
			{
			case 0b000u:
				return decode_shift_add_subtract(instruction);
			case 0b001u:
				return decode_move_compare_add_subtract_immediate(instruction);
			case 0b010u:
				if (((instruction >> 12) & 0b1u) == 0b1u)
				{
					return decode_load_store_register_offset(instruction);
				}
				if (((instruction >> 11) & 0b1u) == 0b1u)
				{
					// Format 6, PC-relative load
					return ThumbInstructionType::LDR;
				}
				if (((instruction >> 10) & 0b1u) == 0b1u)
				{
					return decode_hi_register_operations_branch_exchange(instruction);
				}
				return decode_alu_operations(instruction);
			case 0b011u:
				return decode_load_store_immediate_offset(instruction);
			case 0b100u:
			{
				// Format 10, load/store halfword, and format 11, SP-relative
				// load/store, both use bit 11 for L.
				const bool load = ((instruction >> 11) & 0b1u) == 0b1u;
				if (((instruction >> 12) & 0b1u) == 0b0u)
				{
					return load ? ThumbInstructionType::LDRH : ThumbInstructionType::STRH;
				}
				return load ? ThumbInstructionType::LDR : ThumbInstructionType::STR;
			}
			case 0b101u:
				if (((instruction >> 12) & 0b1u) == 0b0u)
				{
					// Format 12, load address (ADD Rd, PC/SP, #imm)
					return ThumbInstructionType::ADD;
				}
				return decode_miscellaneous(instruction);
			case 0b110u:
				if (((instruction >> 12) & 0b1u) == 0b0u)
				{
					// Format 15, multiple load/store
					const bool load = ((instruction >> 11) & 0b1u) == 0b1u;
					return load ? ThumbInstructionType::LDMIA : ThumbInstructionType::STMIA;
				}
				return decode_conditional_branch_software_interrupt(instruction);
			default: /* case 0b111u: */
			{
				const ThumbInstruction h = (instruction >> 11) & 0b11u;
				if (h == 0b00u)
				{
					// Format 18, unconditional branch
					return ThumbInstructionType::B;
				}
				if (h == 0b01u)
				{
					// BLX suffix, ARMv5T and later
					return ThumbInstructionType::UNDEFINED;
				}
				// Format 19, long branch with link. The high (H = 10) and low
				// (H = 11) halves are separate instructions, each executed on
				// their own.
				return ThumbInstructionType::BL;
			}
			}
		}

		ThumbInstructionType constexpr decode_shift_add_subtract(ThumbInstruction instruction)
		{
			const ThumbInstruction op = (instruction >> 11) & 0b11u;

			switch (op)
			{
			// Format 1, move shifted register
			case 0b00u: return ThumbInstructionType::LSL;
			case 0b01u: return ThumbInstructionType::LSR;
			case 0b10u: return ThumbInstructionType::ASR;
			default: /* case 0b11u: */
			{
				// Format 2, add/subtract
				const bool subtract = ((instruction >> 9) & 0b1u) == 0b1u;
				return subtract ? ThumbInstructionType::SUB : ThumbInstructionType::ADD;
			}
			}
		}

		ThumbInstructionType constexpr decode_move_compare_add_subtract_immediate(ThumbInstruction instruction)
		{
			// Format 3
			const ThumbInstruction op = (instruction >> 11) & 0b11u;

			switch (op)
			{
			case 0b00u: return ThumbInstructionType::MOV;
			case 0b01u: return ThumbInstructionType::CMP;
			case 0b10u: return ThumbInstructionType::ADD;
			default: /* case 0b11u: */ return ThumbInstructionType::SUB;
			}
		}

		ThumbInstructionType constexpr decode_alu_operations(ThumbInstruction instruction)
		{
			// Format 4
			const ThumbInstruction op = (instruction >> 6) & 0b1111u;

			switch (op)
			{
			case 0b0000u: return ThumbInstructionType::AND;
			case 0b0001u: return ThumbInstructionType::EOR;
			case 0b0010u: return ThumbInstructionType::LSL;
			case 0b0011u: return ThumbInstructionType::LSR;
			case 0b0100u: return ThumbInstructionType::ASR;
			case 0b0101u: return ThumbInstructionType::ADC;
			case 0b0110u: return ThumbInstructionType::SBC;
			case 0b0111u: return ThumbInstructionType::ROR;
			case 0b1000u: return ThumbInstructionType::TST;
			case 0b1001u: return ThumbInstructionType::NEG;
			case 0b1010u: return ThumbInstructionType::CMP;
			case 0b1011u: return ThumbInstructionType::CMN;
			case 0b1100u: return ThumbInstructionType::ORR;
			case 0b1101u: return ThumbInstructionType::MUL;
			case 0b1110u: return ThumbInstructionType::BIC;
			default: /* case 0b1111u: */ return ThumbInstructionType::MVN;
			}
		}

		ThumbInstructionType constexpr decode_hi_register_operations_branch_exchange(ThumbInstruction instruction)
		{
			// Format 5. On the ARM7TDMI, ADD/CMP/MOV with both H1 and H2 clear
			// and BX with H1 set are unpredictable rather than undefined, so
			// they decode as the instruction they appear to be.
			const ThumbInstruction op = (instruction >> 8) & 0b11u;

			switch (op)
			{
			case 0b00u: return ThumbInstructionType::ADD;
			case 0b01u: return ThumbInstructionType::CMP;
			case 0b10u: return ThumbInstructionType::MOV;
			default: /* case 0b11u: */ return ThumbInstructionType::BX;
			}
		}

		ThumbInstructionType constexpr decode_load_store_register_offset(ThumbInstruction instruction)
		{
			const ThumbInstruction op = (instruction >> 10) & 0b11u;

			if (((instruction >> 9) & 0b1u) == 0b0u)
			{
				// Format 7, load/store with register offset (bits L B)
				switch (op)
				{
				case 0b00u: return ThumbInstructionType::STR;
				case 0b01u: return ThumbInstructionType::STRB;
				case 0b10u: return ThumbInstructionType::LDR;
				default: /* case 0b11u: */ return ThumbInstructionType::LDRB;
				}
			}
			// Format 8, load/store sign-extended byte/halfword (bits H S)
			switch (op)
			{
			case 0b00u: return ThumbInstructionType::STRH;
			case 0b01u: return ThumbInstructionType::LDRSB;
			case 0b10u: return ThumbInstructionType::LDRH;
			default: /* case 0b11u: */ return ThumbInstructionType::LDRSH;
			}
		}

		ThumbInstructionType constexpr decode_load_store_immediate_offset(ThumbInstruction instruction)
		{
			// Format 9 (bits B L)
			const ThumbInstruction op = (instruction >> 11) & 0b11u;

			switch (op)
			{
			case 0b00u: return ThumbInstructionType::STR;
			case 0b01u: return ThumbInstructionType::LDR;
			case 0b10u: return ThumbInstructionType::STRB;
			default: /* case 0b11u: */ return ThumbInstructionType::LDRB;
			}
		}

		ThumbInstructionType constexpr decode_miscellaneous(ThumbInstruction instruction)
		{
			// Format 13, add offset to stack pointer
			// 1011 0000 S imm7
			if ((instruction & 0xFF00u) == 0xB000u)
			{
				return ThumbInstructionType::ADD;
			}
			// Format 14, push/pop registers
			// 1011 L10R register_list
			if ((instruction & 0xF600u) == 0xB400u)
			{
				const bool load = ((instruction >> 11) & 0b1u) == 0b1u;
				return load ? ThumbInstructionType::POP : ThumbInstructionType::PUSH;
			}
			// The rest of this space is ARMv5 and later (BKPT, CBZ, IT,
			// SXTB, REV, CPS, hints, ...).
			return ThumbInstructionType::UNDEFINED;
		}

		ThumbInstructionType constexpr decode_conditional_branch_software_interrupt(ThumbInstruction instruction)
		{
			// Format 16, conditional branch, and format 17, software interrupt
			const ThumbInstruction cond = (instruction >> 8) & 0b1111u;

			switch (cond)
			{
			case 0b0000u: return ThumbInstructionType::BEQ;
			case 0b0001u: return ThumbInstructionType::BNE;
			case 0b0010u: return ThumbInstructionType::BCS;
			case 0b0011u: return ThumbInstructionType::BCC;
			case 0b0100u: return ThumbInstructionType::BMI;
			case 0b0101u: return ThumbInstructionType::BPL;
			case 0b0110u: return ThumbInstructionType::BVS;
			case 0b0111u: return ThumbInstructionType::BVC;
			case 0b1000u: return ThumbInstructionType::BHI;
			case 0b1001u: return ThumbInstructionType::BLS;
			case 0b1010u: return ThumbInstructionType::BGE;
			case 0b1011u: return ThumbInstructionType::BLT;
			case 0b1100u: return ThumbInstructionType::BGT;
			case 0b1101u: return ThumbInstructionType::BLE;
			case 0b1110u: return ThumbInstructionType::UNDEFINED;
			default: /* case 0b1111u: */ return ThumbInstructionType::SWI;
			}
		}
	}

#pragma endregion

}
