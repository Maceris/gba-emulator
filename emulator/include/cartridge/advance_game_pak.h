#pragma once

#include <cstdint>

#include "game_pak.h"

namespace emulator {
	struct AdvanceGamePak : public GamePak
	{
		AdvanceGamePak();
		AdvanceGamePak(const AdvanceGamePak&) = delete;
		AdvanceGamePak(AdvanceGamePak&&) = delete;
		AdvanceGamePak& operator=(const AdvanceGamePak&) = delete;
		AdvanceGamePak& operator=(AdvanceGamePak&&) = delete;
		~AdvanceGamePak();
	};

	//TODO(ches) don't bother with packed structs, write a deserializer

#pragma pack(push, 1)
	struct [[gnu::packed]] GBA_ROM_Header {
		/// <summary>
		/// 32bit ARM branch opcode, e.g. "B rom_start".
		/// </summary>
		uint32_t rom_entry_point;

		/// <summary>
		/// Real cartridges contain the Nintendo logo as a compressed bitmap,
		/// to be displayed during the boot procedure. The real BIOS would
		/// also check this header and lock up if does not match.
		/// </summary>
		char logo[156];

		/// <summary>
		/// Uppercase ascii, max 12 characters.
		/// </summary>
		char game_title[12];

		/// <summary>
		/// Uppercase ascii, 4 characters.
		/// </summary>
		char game_code[4];

		/// <summary>
		/// Uppercase ascii, 2 characters.
		/// </summary>
		char maker_code[2];

		/// <summary>
		/// Must be 0x96.
		/// </summary>
		uint8_t fixed_value;

		/// <summary>
		/// 0x00 for current GBA models.
		/// </summary>
		uint8_t main_unit_code;

		/// <summary>
		/// Normally 0x00. With the hardware debugger, bit 7 identifies the
		/// debugging handlers entry point and size of DACS 
		/// (Debugging And Communication System) memory.
		/// Bit7=0: 9FFC000h/8MBIT DACS, Bit7=1: 9FE2000h/1MBIT DACS.
		/// </summary>
		uint8_t device_type;

		/// <summary>
		/// Should be zero filled.
		/// </summary>
		char reserved_1[7];

		/// <summary>
		/// Usually 0x00.
		/// </summary>
		uint8_t software_version;

		/// <summary>
		/// Header checksum, required. Calculated as
		/// 
		/// chk=0; for (i=0x0A0 to 0x0BC) {chk=chk-[i];} 
		/// chk=(chk-0x19) and 0x0FF;
		/// </summary>
		uint8_t complement_check;

		/// <summary>
		/// Should be zero filled.
		/// </summary>
		char reserved_2[2];
	};

	/// <summary>
	/// For Multiboot, the regular header is transferred as header-block 
	/// (loaded to 0x2000000-0x20000BF), and this header information 
	/// is at the beginning of the actual program/data-block 
	/// (loaded to 0x20000C0 and up). This extended header consists of 
	/// Multiboot Entry point(s), and of two reserved bytes which are 
	/// overwritten by the boot procedure.
	/// </summary>
	struct [[gnu::packed]] GBA_ROM_Multiboot {
		/// <summary>
		/// 32bit ARM branch opcode, e.g. "B ram_start".
		/// </summary>
		uint32_t ram_entry_point;

		/// <summary>
		/// Initialized as 0x00, BIOS overwrites the value.
		/// </summary>
		uint8_t boot_mode;

		/// <summary>
		/// Initialized as 0x00, BIOS overwrites the value.
		/// </summary>
		uint8_t slave_id_number;

		/// <summary>
		/// No known use.
		/// </summary>
		char unused[26];

		/// <summary>
		/// 32bit ARM branch opcode, e.g. "B joy_start".
		/// </summary>
		uint32_t joybus_entry_point;
	};

#pragma pack(pop)
}
