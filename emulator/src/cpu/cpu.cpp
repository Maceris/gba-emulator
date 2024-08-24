#include "cpu/cpu.h"


#pragma region ARM7TDMI ARM Instructions
void ARM7TDMI::arm_adc()
{}

void ARM7TDMI::arm_add()
{}

void ARM7TDMI::arm_and()
{}

void ARM7TDMI::arm_b()
{}

void ARM7TDMI::arm_bic()
{}

void ARM7TDMI::arm_bl()
{}

void ARM7TDMI::arm_bx()
{}

void ARM7TDMI::arm_cdp()
{}

void ARM7TDMI::arm_cmn()
{}

void ARM7TDMI::arm_cmp()
{}

void ARM7TDMI::arm_eor()
{}

void ARM7TDMI::arm_ldc()
{}

void ARM7TDMI::arm_ldm()
{}

void ARM7TDMI::arm_ldr()
{}

void ARM7TDMI::arm_mcr()
{}

void ARM7TDMI::arm_mla()
{}

void ARM7TDMI::arm_mov()
{}

void ARM7TDMI::arm_mrc()
{}

void ARM7TDMI::arm_mrs()
{}

void ARM7TDMI::arm_msr()
{}

void ARM7TDMI::arm_mul()
{}

void ARM7TDMI::arm_mvn()
{}

void ARM7TDMI::arm_orr()
{}

void ARM7TDMI::arm_rsb()
{}

void ARM7TDMI::arm_rsc()
{}

void ARM7TDMI::arm_sbc()
{}

void ARM7TDMI::arm_smlal()
{}

void ARM7TDMI::arm_smull()
{}

void ARM7TDMI::arm_stc()
{}

void ARM7TDMI::arm_stm()
{}

void ARM7TDMI::arm_str()
{}

void ARM7TDMI::arm_sub()
{}

void ARM7TDMI::arm_swi()
{}

void ARM7TDMI::arm_swp()
{}

void ARM7TDMI::arm_teq()
{}

void ARM7TDMI::arm_tst()
{}

void ARM7TDMI::arm_umlal()
{}

void ARM7TDMI::arm_umull()
{}

#pragma endregion

#pragma region ARM7TDMI Thumb Instructions
void ARM7TDMI::thumb_add()
{}

void ARM7TDMI::thumb_and()
{}

void ARM7TDMI::thumb_asr()
{}

void ARM7TDMI::thumb_b()
{}

void ARM7TDMI::thumb_bl()
{}

void ARM7TDMI::thumb_bx()
{}

void ARM7TDMI::thumb_beq()
{}

void ARM7TDMI::thumb_bcc()
{}

void ARM7TDMI::thumb_bcs()
{}

void ARM7TDMI::thumb_bge()
{}

void ARM7TDMI::thumb_bgt()
{}

void ARM7TDMI::thumb_bhi()
{}

void ARM7TDMI::thumb_bic()
{}

void ARM7TDMI::thumb_ble()
{}

void ARM7TDMI::thumb_bls()
{}

void ARM7TDMI::thumb_blt()
{}

void ARM7TDMI::thumb_bmi()
{}

void ARM7TDMI::thumb_bne()
{}

void ARM7TDMI::thumb_bpl()
{}

void ARM7TDMI::thumb_bvc()
{}

void ARM7TDMI::thumb_bvs()
{}

void ARM7TDMI::thumb_eor()
{}

void ARM7TDMI::thumb_cmn()
{}

void ARM7TDMI::thumb_cmp()
{}

void ARM7TDMI::thumb_ldmia()
{}

void ARM7TDMI::thumb_ldr()
{}

void ARM7TDMI::thumb_ldrb()
{}

void ARM7TDMI::thumb_ldrh()
{}

void ARM7TDMI::thumb_ldrsb()
{}

void ARM7TDMI::thumb_lsl()
{}

void ARM7TDMI::thumb_lsr()
{}

void ARM7TDMI::thumb_mov()
{}

void ARM7TDMI::thumb_mul()
{}

void ARM7TDMI::thumb_mvn()
{}

void ARM7TDMI::thumb_neg()
{}

void ARM7TDMI::thumb_or()
{}

void ARM7TDMI::thumb_pop()
{}

void ARM7TDMI::thumb_push()
{}

void ARM7TDMI::thumb_ror()
{}

void ARM7TDMI::thumb_sbc()
{}

void ARM7TDMI::thumb_stmia()
{}

void ARM7TDMI::thumb_str()
{}

void ARM7TDMI::thumb_strb()
{}

void ARM7TDMI::thumb_strh()
{}

void ARM7TDMI::thumb_sub()
{}

void ARM7TDMI::thumb_swi()
{}

void ARM7TDMI::thumb_tst()
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
