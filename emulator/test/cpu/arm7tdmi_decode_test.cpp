#include "gtest/gtest.h"

#include "cpu/arm7tdmi_decode.h"

using emulator::ARMInstructionType;
using emulator::ThumbInstructionType;
namespace DecodeArm = emulator::DecodeArm;
namespace DecodeThumb = emulator::DecodeThumb;

TEST(ARM7TDMIDecodeTest, ArmDataProcessing)
{
	EXPECT_EQ(DecodeArm::decode(0xE081'0002u), ARMInstructionType::ADD) << "ADD r0, r1, r2";
	EXPECT_EQ(DecodeArm::decode(0xE3A0'0001u), ARMInstructionType::MOV) << "MOV r0, #1";
	EXPECT_EQ(DecodeArm::decode(0xE1A0'1112u), ARMInstructionType::MOV) << "MOV r1, r2, LSL r1";
	EXPECT_EQ(DecodeArm::decode(0xE151'0002u), ARMInstructionType::CMP) << "CMP r1, r2";
}

TEST(ARM7TDMIDecodeTest, ArmBranchAndExchange)
{
	EXPECT_EQ(DecodeArm::decode(0xE12F'FF1Eu), ARMInstructionType::BX) << "BX lr";
}

TEST(ARM7TDMIDecodeTest, ArmPsrTransfer)
{
	EXPECT_EQ(DecodeArm::decode(0xE10F'0000u), ARMInstructionType::MRS) << "MRS r0, CPSR";
	EXPECT_EQ(DecodeArm::decode(0xE129'F000u), ARMInstructionType::MSR) << "MSR CPSR_fc, r0";
	EXPECT_EQ(DecodeArm::decode(0xE328'F00Fu), ARMInstructionType::MSR) << "MSR CPSR_f, #0xF";
}

TEST(ARM7TDMIDecodeTest, ArmMultiplyAndSwap)
{
	EXPECT_EQ(DecodeArm::decode(0xE000'0291u), ARMInstructionType::MUL) << "MUL r0, r1, r2";
	EXPECT_EQ(DecodeArm::decode(0xE020'3291u), ARMInstructionType::MLA) << "MLA r0, r1, r2, r3";
	EXPECT_EQ(DecodeArm::decode(0xE081'0392u), ARMInstructionType::UMULL) << "UMULL r0, r1, r2, r3";
	EXPECT_EQ(DecodeArm::decode(0xE0A1'0392u), ARMInstructionType::UMLAL) << "UMLAL r0, r1, r2, r3";
	EXPECT_EQ(DecodeArm::decode(0xE0C1'0392u), ARMInstructionType::SMULL) << "SMULL r0, r1, r2, r3";
	EXPECT_EQ(DecodeArm::decode(0xE0E1'0392u), ARMInstructionType::SMLAL) << "SMLAL r0, r1, r2, r3";
	EXPECT_EQ(DecodeArm::decode(0xE102'0091u), ARMInstructionType::SWP) << "SWP r0, r1, [r2]";
	EXPECT_EQ(DecodeArm::decode(0xE142'0091u), ARMInstructionType::SWPB) << "SWPB r0, r1, [r2]";
}

TEST(ARM7TDMIDecodeTest, ArmHalfwordAndSignedDataTransfer)
{
	EXPECT_EQ(DecodeArm::decode(0xE1C0'00B0u), ARMInstructionType::STRH) << "STRH r0, [r0]";
	EXPECT_EQ(DecodeArm::decode(0xE1D0'00B0u), ARMInstructionType::LDRH) << "LDRH r0, [r0]";
	EXPECT_EQ(DecodeArm::decode(0xE1D0'00D0u), ARMInstructionType::LDRSB) << "LDRSB r0, [r0]";
	EXPECT_EQ(DecodeArm::decode(0xE1D0'00F0u), ARMInstructionType::LDRSH) << "LDRSH r0, [r0]";
}

TEST(ARM7TDMIDecodeTest, ArmSingleDataTransfer)
{
	EXPECT_EQ(DecodeArm::decode(0xE591'0000u), ARMInstructionType::LDR) << "LDR r0, [r1]";
	EXPECT_EQ(DecodeArm::decode(0xE5C1'0000u), ARMInstructionType::STRB) << "STRB r0, [r1]";
	EXPECT_EQ(DecodeArm::decode(0xE4B1'0004u), ARMInstructionType::LDRT) << "LDRT r0, [r1], #4";
}

TEST(ARM7TDMIDecodeTest, ArmBlockDataTransfer)
{
	EXPECT_EQ(DecodeArm::decode(0xE8BD'8000u), ARMInstructionType::LDMIA) << "LDMIA sp!, {pc}";
	EXPECT_EQ(DecodeArm::decode(0xE92D'4000u), ARMInstructionType::STMDB) << "STMDB sp!, {lr}";
	EXPECT_EQ(DecodeArm::decode(0xE8FD'8000u), ARMInstructionType::LDM_EXCEPTION) << "LDMIA sp!, {pc}^";
	EXPECT_EQ(DecodeArm::decode(0xE8D0'0002u), ARMInstructionType::LDM) << "LDMIA r0, {r1}^";
	EXPECT_EQ(DecodeArm::decode(0xE8C0'0002u), ARMInstructionType::STM) << "STMIA r0, {r1}^";
}

TEST(ARM7TDMIDecodeTest, ArmBranch)
{
	EXPECT_EQ(DecodeArm::decode(0xEA00'0000u), ARMInstructionType::B) << "B";
	EXPECT_EQ(DecodeArm::decode(0xEB00'0000u), ARMInstructionType::BL) << "BL";
}

TEST(ARM7TDMIDecodeTest, ArmCoprocessorAndSoftwareInterrupt)
{
	EXPECT_EQ(DecodeArm::decode(0xED90'0000u), ARMInstructionType::LDC) << "LDC";
	EXPECT_EQ(DecodeArm::decode(0xED80'0000u), ARMInstructionType::STC) << "STC";
	EXPECT_EQ(DecodeArm::decode(0xEE00'0000u), ARMInstructionType::CDP) << "CDP";
	EXPECT_EQ(DecodeArm::decode(0xEE01'0F10u), ARMInstructionType::MCR) << "MCR";
	EXPECT_EQ(DecodeArm::decode(0xEE11'0F10u), ARMInstructionType::MRC) << "MRC";
	EXPECT_EQ(DecodeArm::decode(0xEF00'0000u), ARMInstructionType::SWI) << "SWI 0";
}

TEST(ARM7TDMIDecodeTest, ArmUndefined)
{
	EXPECT_EQ(DecodeArm::decode(0xE7F0'00F0u), ARMInstructionType::UNDEFINED) << "undefined instruction space";
}

TEST(ARM7TDMIDecodeTest, ArmLaterArchitectureInstructionsAreUndefined)
{
	EXPECT_EQ(DecodeArm::decode(0xE16F'0F11u), ARMInstructionType::UNDEFINED) << "CLZ r0, r1 (ARMv5T)";
	EXPECT_EQ(DecodeArm::decode(0xE12F'FF31u), ARMInstructionType::UNDEFINED) << "BLX r1 (ARMv5T)";
	EXPECT_EQ(DecodeArm::decode(0xE1C0'00D0u), ARMInstructionType::UNDEFINED) << "LDRD r0, [r0] (ARMv5TE)";
	EXPECT_EQ(DecodeArm::decode(0xE1C0'00F0u), ARMInstructionType::UNDEFINED) << "STRD r0, [r0] (ARMv5TE)";
	EXPECT_EQ(DecodeArm::decode(0xE300'0000u), ARMInstructionType::UNDEFINED) << "MOVW r0, #0 (ARMv6T2)";
}

TEST(ARM7TDMIDecodeTest, ThumbShiftAddSubtract)
{
	EXPECT_EQ(DecodeThumb::decode(0x0048u), ThumbInstructionType::LSL) << "LSL r0, r1, #1";
	EXPECT_EQ(DecodeThumb::decode(0x0848u), ThumbInstructionType::LSR) << "LSR r0, r1, #1";
	EXPECT_EQ(DecodeThumb::decode(0x1048u), ThumbInstructionType::ASR) << "ASR r0, r1, #1";
	EXPECT_EQ(DecodeThumb::decode(0x1888u), ThumbInstructionType::ADD) << "ADD r0, r1, r2";
	EXPECT_EQ(DecodeThumb::decode(0x1A88u), ThumbInstructionType::SUB) << "SUB r0, r1, r2";
}

TEST(ARM7TDMIDecodeTest, ThumbMoveCompareAddSubtractImmediate)
{
	EXPECT_EQ(DecodeThumb::decode(0x2001u), ThumbInstructionType::MOV) << "MOV r0, #1";
	EXPECT_EQ(DecodeThumb::decode(0x2801u), ThumbInstructionType::CMP) << "CMP r0, #1";
	EXPECT_EQ(DecodeThumb::decode(0x3001u), ThumbInstructionType::ADD) << "ADD r0, #1";
	EXPECT_EQ(DecodeThumb::decode(0x3801u), ThumbInstructionType::SUB) << "SUB r0, #1";
}

TEST(ARM7TDMIDecodeTest, ThumbAluOperations)
{
	EXPECT_EQ(DecodeThumb::decode(0x4008u), ThumbInstructionType::AND) << "AND r0, r1";
	EXPECT_EQ(DecodeThumb::decode(0x4248u), ThumbInstructionType::NEG) << "NEG r0, r1";
	EXPECT_EQ(DecodeThumb::decode(0x4348u), ThumbInstructionType::MUL) << "MUL r0, r1";
	EXPECT_EQ(DecodeThumb::decode(0x43C8u), ThumbInstructionType::MVN) << "MVN r0, r1";
}

TEST(ARM7TDMIDecodeTest, ThumbHiRegisterOperationsBranchExchange)
{
	EXPECT_EQ(DecodeThumb::decode(0x4448u), ThumbInstructionType::ADD) << "ADD r0, r9";
	EXPECT_EQ(DecodeThumb::decode(0x46C0u), ThumbInstructionType::MOV) << "MOV r8, r8";
	EXPECT_EQ(DecodeThumb::decode(0x4770u), ThumbInstructionType::BX) << "BX lr";
}

TEST(ARM7TDMIDecodeTest, ThumbLoadStore)
{
	EXPECT_EQ(DecodeThumb::decode(0x4801u), ThumbInstructionType::LDR) << "LDR r0, [pc, #4]";
	EXPECT_EQ(DecodeThumb::decode(0x5088u), ThumbInstructionType::STR) << "STR r0, [r1, r2]";
	EXPECT_EQ(DecodeThumb::decode(0x5C88u), ThumbInstructionType::LDRB) << "LDRB r0, [r1, r2]";
	EXPECT_EQ(DecodeThumb::decode(0x5288u), ThumbInstructionType::STRH) << "STRH r0, [r1, r2]";
	EXPECT_EQ(DecodeThumb::decode(0x5688u), ThumbInstructionType::LDRSB) << "LDRSB r0, [r1, r2]";
	EXPECT_EQ(DecodeThumb::decode(0x5A88u), ThumbInstructionType::LDRH) << "LDRH r0, [r1, r2]";
	EXPECT_EQ(DecodeThumb::decode(0x5E88u), ThumbInstructionType::LDRSH) << "LDRSH r0, [r1, r2]";
	EXPECT_EQ(DecodeThumb::decode(0x6808u), ThumbInstructionType::LDR) << "LDR r0, [r1]";
	EXPECT_EQ(DecodeThumb::decode(0x7008u), ThumbInstructionType::STRB) << "STRB r0, [r1]";
	EXPECT_EQ(DecodeThumb::decode(0x8008u), ThumbInstructionType::STRH) << "STRH r0, [r1]";
	EXPECT_EQ(DecodeThumb::decode(0x8808u), ThumbInstructionType::LDRH) << "LDRH r0, [r1]";
	EXPECT_EQ(DecodeThumb::decode(0x9001u), ThumbInstructionType::STR) << "STR r0, [sp, #4]";
	EXPECT_EQ(DecodeThumb::decode(0x9801u), ThumbInstructionType::LDR) << "LDR r0, [sp, #4]";
}

TEST(ARM7TDMIDecodeTest, ThumbAddressAndStack)
{
	EXPECT_EQ(DecodeThumb::decode(0xA001u), ThumbInstructionType::ADD) << "ADD r0, pc, #4";
	EXPECT_EQ(DecodeThumb::decode(0xA801u), ThumbInstructionType::ADD) << "ADD r0, sp, #4";
	EXPECT_EQ(DecodeThumb::decode(0xB001u), ThumbInstructionType::ADD) << "ADD sp, #4";
	EXPECT_EQ(DecodeThumb::decode(0xB500u), ThumbInstructionType::PUSH) << "PUSH {lr}";
	EXPECT_EQ(DecodeThumb::decode(0xBD00u), ThumbInstructionType::POP) << "POP {pc}";
}

TEST(ARM7TDMIDecodeTest, ThumbMultipleLoadStore)
{
	EXPECT_EQ(DecodeThumb::decode(0xC003u), ThumbInstructionType::STMIA) << "STMIA r0!, {r0, r1}";
	EXPECT_EQ(DecodeThumb::decode(0xC803u), ThumbInstructionType::LDMIA) << "LDMIA r0!, {r0, r1}";
}

TEST(ARM7TDMIDecodeTest, ThumbBranchAndSoftwareInterrupt)
{
	EXPECT_EQ(DecodeThumb::decode(0xD0FEu), ThumbInstructionType::BEQ) << "BEQ";
	EXPECT_EQ(DecodeThumb::decode(0xDCFEu), ThumbInstructionType::BGT) << "BGT";
	EXPECT_EQ(DecodeThumb::decode(0xDF00u), ThumbInstructionType::SWI) << "SWI 0";
	EXPECT_EQ(DecodeThumb::decode(0xE7FEu), ThumbInstructionType::B) << "B";
	EXPECT_EQ(DecodeThumb::decode(0xF000u), ThumbInstructionType::BL) << "BL, high half";
	EXPECT_EQ(DecodeThumb::decode(0xF800u), ThumbInstructionType::BL) << "BL, low half";
}

TEST(ARM7TDMIDecodeTest, ThumbUndefined)
{
	EXPECT_EQ(DecodeThumb::decode(0xDEFEu), ThumbInstructionType::UNDEFINED) << "conditional branch, cond 1110";
}

TEST(ARM7TDMIDecodeTest, ThumbLaterArchitectureInstructionsAreUndefined)
{
	EXPECT_EQ(DecodeThumb::decode(0xE800u), ThumbInstructionType::UNDEFINED) << "BLX suffix (ARMv5T)";
	EXPECT_EQ(DecodeThumb::decode(0xBF00u), ThumbInstructionType::UNDEFINED) << "NOP hint (ARMv6T2)";
	EXPECT_EQ(DecodeThumb::decode(0xBE00u), ThumbInstructionType::UNDEFINED) << "BKPT (ARMv5T)";
	EXPECT_EQ(DecodeThumb::decode(0xB2C8u), ThumbInstructionType::UNDEFINED) << "UXTB r0, r1 (ARMv6)";
}
