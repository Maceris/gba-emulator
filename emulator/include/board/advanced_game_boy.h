#pragma once

#include "board/bus.h"
#include "cpu/cpu.h"
namespace emulator {

	/// <summary>
	/// A System on a Chip containing various components.
	/// </summary>
	struct AdvancedGameBoy
	{
		ARM7TDMI gba_cpu;
		SM83 gbc_cpu;
		// 32 KB WRAM
		// 96 KB VRAM
		// PPU
		// Key Controller
		// DMA
		// 2 KB CGB ROM
		// 16 KB AGB ROM
		// Sound Generator
		// Prefetch Buffer
		ARM7TDMI_Bus gba_bus;

		// 16-bit line to 256KB WRAM
		// 8/32-bit line to  6-pin serial subconnector
		// 16 bit line to game pak / shape detector switch

		//TODO(ches) draw a distinction between 32-pin and 40 pin boards

		//TODO(ches) figure out what pins we actually care about

		// 1 VDD3 - Voltage Drain Drain 3, +3.3V power line. For main CPU
		//            power and GBA games.
		// 2 IN35 - If a GB/GBC game is inserted, the cartridge slot switch
		//          is activated and IN35 is dragged to +3.3V. Otherwise (
		//          GBA, or no cartridge) IN35 is 0V.
		// 3 TP8 - Test point 8, connected to the R button.
		// 4 TP0 - Test point 0, connected to the A button.
		// 5 TP1 - Test point 1, connected to the B button.
		// 6 SO1 - Sound Output 1, for the right headphone
		// 7 SO2 - Sound Output 2, for the left headphone
		// 8 Vin - Voltage In, +3.3V
		// 9 /RES - Reset signal
		// 10 D7 - Data 7, bit 7 of the 8-bit data bus.
		// 11 D6 - Data 6, bit 6 of the 8-bit data bus.
		// 12 D5 - Data 5, bit 5 of the 8-bit data bus.
		// 13 D4 - Data 4, bit 4 of the 8-bit data bus.
		// 14 D3 - Data 3, bit 3 of the 8-bit data bus.
		// 15 D2 - Data 2, bit 2 of the 8-bit data bus.
		// 16 D1 - Data 1, bit 1 of the 8-bit data bus.
		// 17 D0 - Data 0, bit 0 of the 8-bit data bus.
		// 18 A15 - Address 15, bit 15 of the address/data bus.
		// 19 A14 - Address 14, bit 14 of the address/data bus.
		// 20 A13 - Address 13, bit 13 of the address/data bus.
		// 21 A12 - Address 12, bit 12 of the address/data bus.
		// 22 A11 - Address 11, bit 11 of the address/data bus.
		// 23 A10 - Address 10, bit 10 of the address/data bus.
		// 24 A9 -  Address 9, bit 9 of the address/data bus.
		// 25 A8 -  Address 8, bit 8 of the address/data bus.
		// 26 A7 -  Address 7, bit 7 of the address/data bus.
		// 27 A6 -  Address 6, bit 6 of the address/data bus.
		// 28 A5 -  Address 5, bit 5 of the address/data bus.
		// 29 A4 -  Address 4, bit 4 of the address/data bus.
		// 30 A3 -  Address 3, bit 3 of the address/data bus.
		// 31 A2 -  Address 2, bit 2 of the address/data bus.
		// 32 A1 -  Address 1, bit 1 of the address/data bus.
		// 33 A0 -  Address 0, bit 0 of the address/data bus.
		// 34 /CS - Chip select signal pin, used to select memory chips on
		//          the game cartridge.
		// 35 /RD - Read signal pin, used for data transfer.
		// 36 /WR - Write signal pin, used to signal write operations.
		// 37 PHI - 
		// 38 VDD35 - Voltage Drain Drain 3/5, either +3.3V or +5V depending
		//            on the cartridge switch.
		//            When a GBA game is inserted (switch not actuated), 
		//            VDD35 is connected to VDD3 (and IN35 is pulled low).
		//            If a GB/GBC game (switch actuated) is inserted, VDD35 is 
		//            connected to VDD5 (not in AGB pinout) and IN35 is +3.3V.
		// 39 GND - Ground.
		// 40 SC - 
		// 41 SD - 
		// 42 SI - 
		// 43 SO - 
		// 44 VDD2 - Voltage Drain Drain 2, +2.5V power line. For SRAM.
		// 45 WA0 - 
		// 46 WA1 - 
		// 47 WA2 - 
		// 48 WA3 - 
		// 49 WA4 - 
		// 50 WA5 - 
		// 51 WA6 - 
		// 52 WA7 - 
		// 53 /WLB - 
		// 54 /WUB - 
		// 55 /WWE - 
		// 56 WA8 - 
		// 57 WA9 - 
		// 58 WA10 - 
		// 59 WA11 - 
		// 60 WA12 - 
		// 61 WA13 - 
		// 62 WA14 - 
		// 63 WA15 - 
		// 64 GND - Ground.
		// 65 VDD2 - Voltage Drain Drain 2, +2.5V power line. For SRAM.
		// 66 WD5 - 
		// 67 WD13 - 
		// 68 WD6 - 
		// 69 WD14 - 
		// 70 WD7 - 
		// 71 WD15 - 
		// 72 WD8 - 
		// 73 WD16 - 
		// 74 WA16 - 
		// 75 WD12 - 
		// 76 WD4 - 
		// 77 WD11 - 
		// 78 WD3 - 
		// 79 WD10 - 
		// 80 WD2 - 
		// 81 WD9 - 
		// 82 WD1 - 
		// 83 /WOE - 
		// 84 DCK - 
		// 85 LP - 
		// 86 PS - 
		// 87 LDR5 - 
		// 88 LDR4 - 
		// 89 LDR3 - 
		// 90 LDR2 - 
		// 91 LDR1 - 
		// 92 LDG5 - 
		// 93 LDG4 - 
		// 94 LDG3 - 
		// 95 LDG2 - 
		// 96 LDG1 - 
		// 97 LDB5 - 
		// 98 LDB4 - 
		// 99 LDB3 - 
		// 100 LDB2 - 
		// 101 LDB1 - 
		// 102 GND - Ground.
		// 103 VDD3 - Voltage Drain Drain 3, +3.3V power line. For main CPU
		//            power and GBA games.
		// 104 SPL - 
		// 105 CLS - 
		// 106 SPS - 
		// 107 MOD - 
		// 108 REVC - 
		// 109 GNDed - Ground.
		// 110 GNDed - Ground.
		// 111 GNDed - Ground.
		// 112 GNDed - Ground.
		// 113 CK1 - 
		// 114 CK2 - 
		// 115 VDD2 - Voltage Drain Drain 2, +2.5V power line. For SRAM.
		// 116 GND - Ground.
		// 117 VDD2 - Voltage Drain Drain 2, +2.5V power line. For SRAM.
		// 118 VCNT5 - 
		// 119 TP9 - Test point 9, connected to the L button.
		// 120 TP6 - Test point 6, connected to the up D-pad.
		// 121 TP5 - Test point 5, connected to the left D-pad.
		// 122 TP7 - Test point 7, connnected to the down D-pad.
		// 123 TP4 - Test point 4, connected to the right D-pad.
		// 124 /FIQ - 
		// 125 /RESET - 
		// 126 TP2 - Test point 2, connected to the select button.
		// 127 TP3 - Test point 3, connected to the start button.
		// 128 GND - Ground.

	};

}
