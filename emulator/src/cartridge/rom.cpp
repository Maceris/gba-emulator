#include "cartridge/rom.h"

#include "memory/memory_types.h"

namespace emulator {

	ROM::ROM() = default;
	ROM::~ROM() = default;

	BackupType scan_for_backup_IDs(const ROM& rom) {
		if (!rom.data || rom.rom_size == 0) {
			return BackupType::NONE;
		}

		// EEPROM_Vnnn    EEPROM 512 bytes or 8 Kbytes (4Kbit or 64Kbit)
		// SRAM_Vnnn      SRAM 32 Kbytes(256Kbit)
		// FLASH_Vnnn     FLASH 64 Kbytes(512Kbit) (ID used in older files)
		// FLASH512_Vnnn  FLASH 64 Kbytes(512Kbit) (ID used in newer files)
		// FLASH1M_Vnnn   FLASH 128 Kbytes(1Mbit)
		
		// string length is always a multiple of 4 bytes, padded with zeroes

		// Shown in little-endian, but these are stored in big-endian
		// 1234  1234  1234  1234
		// EEPR  OM_V  nnn0  
		// SRAM  _Vnn  n000  
		// FLAS  H_Vn  nn00  
		// FLAS  H512  _Vnn  n000
		// FLAS  H1M_  Vnnn  

		constexpr size_t STRING_ALIGNMENT = sizeof(Word);

		// 4 groups of 4 bytes
		constexpr size_t MAX_STRING_LENGTH = 4ll * 4;
		// 3 groups of 4 bytes
		constexpr size_t MIN_STRING_LENGTH = 4ll * 3;

		// If we scan up to MAX_STRING_LENGTH bytes ahead, we will have this
		// many extra bytes left over at the end.
		const size_t leftover_bytes = rom.rom_size % MAX_STRING_LENGTH;

		Word first_word = 0;
		// From left to right, the 4 bytes in a group of 4 letters
		char letter_1;
		char letter_2;
		char letter_3;
		char letter_4;
		// We can safely scan this for the longest string without running over
		for (size_t i = 0; i < rom.rom_size - leftover_bytes; ++i) {
			//TODO(ches) scan for the backup type
			first_word = *((Word*)(((char*)rom.data) + i));
			letter_4 = first_word & 0xff;
			if (letter_4 < '0' || letter_4 > '9' && letter_4 != 'n') {
				// Must be 0 or n, or 'n'.
				continue;
			}
			letter_3 = (first_word >> 1) & 0xff;
			if (letter_3 < '0' || letter_3 > '9') {
				// Must be 0 or n, or 'n'.
				continue;
			}
			letter_2 = (first_word >> 2) & 0xff;
			letter_1 = (first_word >> 3) & 0xff;
			if (letter_2 == 'V' && letter_1 == '_') {
				// TODO(ches) Check for flash 512

			}
			else if (letter_2 < '0' || letter_2 > '9') {
				continue;
			}

			if (letter_1 == 'V') {
				// TODO(ches) Check for flash 1M

			}
			else if (letter_1 < '0' || letter_1 > '9') {
				// Must be 0 or n, or 'n'.
				continue;
			}

		}

		// last lil nub of data, what cruel person would put the string there??
		if (leftover_bytes >= MIN_STRING_LENGTH) {

		}
	}
}