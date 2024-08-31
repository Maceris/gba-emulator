#include "gtest/gtest.h"

#include "cpu/cpu.h"

TEST(CPUTest, TypeChecks)
{
	EXPECT_EQ(sizeof(ArmInstruction), 4);
	EXPECT_EQ(sizeof(ThumbInstruction), 2);
}
