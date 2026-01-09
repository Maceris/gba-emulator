#include "gtest/gtest.h"

#include "cpu/cpu.h"

TEST(CPUTest, TypeChecks)
{
	EXPECT_EQ(sizeof(emulator::ArmInstruction), 4);
	EXPECT_EQ(sizeof(emulator::ThumbInstruction), 2);
}
