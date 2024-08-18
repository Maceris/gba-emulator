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

