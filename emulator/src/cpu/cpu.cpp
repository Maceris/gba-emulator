#include "cpu/cpu.h"


#pragma region ARM7TDMI ARM Instructions
void ARM7TDMI::arm_adc(ArmInstruction instruction)
{}

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

void ARM7TDMI::arm_ldr(ArmInstruction instruction)
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

void ARM7TDMI::arm_str(ArmInstruction instruction)
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

void ARM7TDMI::arm_umlal(ArmInstruction instruction)
{}

void ARM7TDMI::arm_umull(ArmInstruction instruction)
{}

#pragma endregion

#pragma region ARM7TDMI Thumb Instructions
void ARM7TDMI::thumb_add(ThumbInstruction instruction)
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

#pragma endregion

void ARM7TDMI::fetch()
{}

void ARM7TDMI::decode()
{}

void ARM7TDMI::execute()
{}

#pragma region ARM Decoding

void ARM7TDMI::decode_arm()
{}

void ARM7TDMI::decode_thumb()
{}

void ARM7TDMI::is_arm_data_processing_or_psr_transfer()
{}

void ARM7TDMI::is_arm_multiply()
{}

void ARM7TDMI::is_arm_multiply_long()
{}

void ARM7TDMI::is_arm_single_data_swap()
{}

void ARM7TDMI::is_arm_branch_exchange()
{}

void ARM7TDMI::is_arm_halfword_data_transfer_register_offset()
{}

void ARM7TDMI::is_arm_halfword_data_transfer_immediate_offset()
{}

void ARM7TDMI::is_arm_single_data_transfer()
{}

void ARM7TDMI::is_arm_undefined()
{}

void ARM7TDMI::is_arm_block_data_transfer()
{}

void ARM7TDMI::is_arm_branch()
{}

void ARM7TDMI::is_arm_coprocessor_data_transfer()
{}

void ARM7TDMI::is_arm_coprocessor_data_operation()
{}

void ARM7TDMI::is_arm_coprocessor_register_transfer()
{}

void ARM7TDMI::is_arm_software_interrupt()
{}


#pragma endregion

#pragma region SM83 Instructions
void SM83::asm_adc()
{}

void SM83::asm_add()
{}

void SM83::asm_and()
{}

void SM83::asm_bit()
{}

void SM83::asm_call()
{}

void SM83::asm_ccf()
{}

void SM83::asm_cp()
{}

void SM83::asm_cpl()
{}

void SM83::asm_daa()
{}

void SM83::asm_dec()
{}

void SM83::asm_di()
{}

void SM83::asm_ei()
{}

void SM83::asm_halt()
{}

void SM83::asm_inc()
{}

void SM83::asm_jp()
{}

void SM83::asm_jr()
{}

void SM83::asm_ld()
{}

void SM83::asm_ldh()
{}

void SM83::asm_nop()
{}

void SM83::asm_or()
{}

void SM83::asm_pop()
{}

void SM83::asm_push()
{}

void SM83::asm_res()
{}

void SM83::asm_ret()
{}

void SM83::asm_reti()
{}

void SM83::asm_rl()
{}

void SM83::asm_rla()
{}

void SM83::asm_rlc()
{}

void SM83::asm_rlca()
{}

void SM83::asm_rr()
{}

void SM83::asm_rra()
{}

void SM83::asm_rrc()
{}

void SM83::asm_rst()
{}

void SM83::asm_sbc()
{}

void SM83::asm_scf()
{}

void SM83::asm_set()
{}

void SM83::asm_sla()
{}

void SM83::asm_sra()
{}

void SM83::asm_srl()
{}

void SM83::asm_stop()
{}

void SM83::asm_sub()
{}

void SM83::asm_swap()
{}

void SM83::asm_xor()
{}

#pragma endregion
