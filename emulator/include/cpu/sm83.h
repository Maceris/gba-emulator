#pragma once

#include "memory/memory_types.h"

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
