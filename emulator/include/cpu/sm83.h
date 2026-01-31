#pragma once

#include "memory/memory_types.h"

namespace emulator {

	/// <summary>
	/// A Sharp SM83 (LR35902) CPU running at either 4.194304 MHz or
	/// 8.388608 MHz for backward compatibilty with Game Boy and Game Boy color
	/// games.
	/// 
	/// A hybrid between the Intel 8080 and the Zilog Z80 processors.
	/// </summary>
	struct SM83
	{
		SM83();
		SM83(const SM83&) = delete;
		SM83(SM83&&) = delete;
		SM83& operator=(const SM83&) = delete;
		SM83& operator=(SM83&&) = delete;
		~SM83();

		void sm83_adc();
		void sm83_add();
		void sm83_and();
		void sm83_bit();
		void sm83_call();
		void sm83_ccf();
		void sm83_cp();
		void sm83_cpl();
		void sm83_daa();
		void sm83_dec();
		void sm83_di();
		void sm83_ei();
		void sm83_halt();
		void sm83_inc();
		void sm83_jp();
		void sm83_jr();
		void sm83_ld();
		void sm83_ldh();
		void sm83_nop();
		void sm83_or();
		void sm83_pop();
		void sm83_push();
		void sm83_res();
		void sm83_ret();
		void sm83_reti();
		void sm83_rl();
		void sm83_rla();
		void sm83_rlc();
		void sm83_rlca();
		void sm83_rr();
		void sm83_rra();
		void sm83_rrc();
		void sm83_rst();
		void sm83_sbc();
		void sm83_scf();
		void sm83_set();
		void sm83_sla();
		void sm83_sra();
		void sm83_srl();
		void sm83_stop();
		void sm83_sub();
		void sm83_swap();
		void sm83_xor();
	};
}
