#pragma once

#include "memory/memory_types.h"

constexpr AddressRange MEMORY_INTERNAL_BIOS                      = { 0x00000000, 0x00003FFF };
constexpr AddressRange MEMORY_INTERNAL_WRAM_ON_BOARD             = { 0x02000000, 0x0203FFFF };
constexpr AddressRange MEMORY_INTERNAL_WRAM_ON_CHIP              = { 0x03000000, 0x03007FFF };
constexpr AddressRange MEMORY_INTERNAL_IO_REGISTERS              = { 0x04000000, 0x040003FE };

constexpr AddressRange MEMORY_DISPLAY_PALETTE                    = { 0x05000000, 0x050003FF };
constexpr AddressRange MEMORY_DISPLAY_VRAM                       = { 0x06000000, 0x06017FFF };
constexpr AddressRange MEMORY_DISPLAY_OAM                        = { 0x07000000, 0x070003FF };

constexpr AddressRange MEMORY_EXTERNAL_GAME_PAK_ROM_WAIT_STATE_0 = { 0x08000000, 0x09FFFFFF };
constexpr AddressRange MEMORY_EXTERNAL_GAME_PAK_ROM_WAIT_STATE_1 = { 0x0A000000, 0x0BFFFFFF };
constexpr AddressRange MEMORY_EXTERNAL_GAME_PAK_ROM_WAIT_STATE_2 = { 0x0C000000, 0x0DFFFFFF };
constexpr AddressRange MEMORY_EXTERNAL_GAME_PAK_SRAM             = { 0x0E000000, 0x0E00FFFF };

constexpr MemoryAccessInfo MEM_INFO_BIOS_ROM =
{
	.bus_width = 32,
	.supports_8_bit_read = true,
	.supports_8_bit_write = false,
	.cycles_for_8_bit_access = 1,
	.supports_16_bit_read = true,
	.supports_16_bit_write = false,
	.cycles_for_16_bit_access = 1,
	.supports_32_bit_read = true,
	.supports_32_bit_write = false,
	.cycles_for_32_bit_access = 1
};

constexpr MemoryAccessInfo MEM_INFO_WORK_RAM_32K =
{
	.bus_width = 32,
	.supports_8_bit_read = true,
	.supports_8_bit_write = true,
	.cycles_for_8_bit_access = 1,
	.supports_16_bit_read = true,
	.supports_16_bit_write = true,
	.cycles_for_16_bit_access = 1,
	.supports_32_bit_read = true,
	.supports_32_bit_write = true,
	.cycles_for_32_bit_access = 1
};

constexpr MemoryAccessInfo MEM_INFO_IO =
{
	.bus_width = 32,
	.supports_8_bit_read = true,
	.supports_8_bit_write = true,
	.cycles_for_8_bit_access = 1,
	.supports_16_bit_read = true,
	.supports_16_bit_write = true,
	.cycles_for_16_bit_access = 1,
	.supports_32_bit_read = true,
	.supports_32_bit_write = true,
	.cycles_for_32_bit_access = 1
};

constexpr MemoryAccessInfo MEM_INFO_OAM = 
{
	.bus_width = 32,
	.supports_8_bit_read = true,
	.supports_8_bit_write = false,
	.cycles_for_8_bit_access = 1,// +1 if accessing video memory at the same time
	.supports_16_bit_read = true,
	.supports_16_bit_write = true,
	.cycles_for_16_bit_access = 1,// +1 if accessing video memory at the same time
	.supports_32_bit_read = true,
	.supports_32_bit_write = true,
	.cycles_for_32_bit_access = 1// +1 if accessing video memory at the same time
};

constexpr MemoryAccessInfo MEM_INFO_WORK_RAM_256K =
{
	.bus_width = 16,
	.supports_8_bit_read = true,
	.supports_8_bit_write = true,
	.cycles_for_8_bit_access = 3,// Default waitstate settings
	.supports_16_bit_read = true,
	.supports_16_bit_write = true,
	.cycles_for_16_bit_access = 3,// Default waitstate settings
	.supports_32_bit_read = true,
	.supports_32_bit_write = true,
	.cycles_for_32_bit_access = 6// Default waitstate settings
};

constexpr MemoryAccessInfo MEM_INFO_PALETTE_RAM =
{
	.bus_width = 16,
	.supports_8_bit_read = true,
	.supports_8_bit_write = false,
	.cycles_for_8_bit_access = 1,// +1 if accessing video memory at the same time
	.supports_16_bit_read = true,
	.supports_16_bit_write = true,
	.cycles_for_16_bit_access = 1,// +1 if accessing video memory at the same time
	.supports_32_bit_read = true,
	.supports_32_bit_write = true,
	.cycles_for_32_bit_access = 2// +1 if accessing video memory at the same time
};

constexpr MemoryAccessInfo MEM_INFO_VRAM =
{
	.bus_width = 16,
	.supports_8_bit_read = true,
	.supports_8_bit_write = false,
	.cycles_for_8_bit_access = 1,// +1 if accessing video memory at the same time
	.supports_16_bit_read = true,
	.supports_16_bit_write = true,
	.cycles_for_16_bit_access = 1,// +1 if accessing video memory at the same time
	.supports_32_bit_read = true,
	.supports_32_bit_write = true,
	.cycles_for_32_bit_access = 2// +1 if accessing video memory at the same time
};

constexpr MemoryAccessInfo MEM_INFO_GAME_PAK_ROM =
{
	.bus_width = 16,
	.supports_8_bit_read = true,
	.supports_8_bit_write = false,
	.cycles_for_8_bit_access = 5,// Default waitstate settings, separate timings for sequential and non-sequential accesses
	.supports_16_bit_read = true,
	.supports_16_bit_write = false,
	.cycles_for_16_bit_access = 5,// Default waitstate settings, separate timings for sequential and non-sequential accesses
	.supports_32_bit_read = true,
	.supports_32_bit_write = false,
	.cycles_for_32_bit_access = 8// Default waitstate settings, separate timings for sequential and non-sequential accesses
};

constexpr MemoryAccessInfo MEM_INFO_GAME_PAK_FLASH =
{
	.bus_width = 16,
	.supports_8_bit_read = true,
	.supports_8_bit_write = false,
	.cycles_for_8_bit_access = 5,// Default waitstate settings, separate timings for sequential and non-sequential accesses
	.supports_16_bit_read = true,
	.supports_16_bit_write = true,
	.cycles_for_16_bit_access = 5,// Default waitstate settings, separate timings for sequential and non-sequential accesses
	.supports_32_bit_read = true,
	.supports_32_bit_write = true,
	.cycles_for_32_bit_access = 8// Default waitstate settings, separate timings for sequential and non-sequential accesses
};

constexpr MemoryAccessInfo MEM_INFO_GAME_PAK_SRAM =
{
	.bus_width = 8,
	.supports_8_bit_read = true,
	.supports_8_bit_write = true,
	.cycles_for_8_bit_access = 5,// Default waitstate settings
	.supports_16_bit_read = false,
	.supports_16_bit_write = false,
	.cycles_for_16_bit_access = 5,// Default waitstate settings
	.supports_32_bit_read = false,
	.supports_32_bit_write = false,
	.cycles_for_32_bit_access = 5// Default waitstate settings
};
