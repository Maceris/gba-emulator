#pragma once

#include "cpu/cpu.h"

struct SystemOnAChip
{
	ARM7TDMI gba_cpu;
	SM83 gbc_cpu;
};
