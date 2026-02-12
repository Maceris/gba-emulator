#include "cartridge/rom.h"

#include "memory/memory_types.h"

namespace emulator {

	ROM::ROM() = default;
	ROM::~ROM() = default;

	static bool matches_n(char letter) {
		return letter >= '0' && letter <= '9' || letter == 'n';
	}

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

		// 1234  1234  1234  1234
		// EEPR  OM_V  nnn0  
		// SRAM  _Vnn  n000  
		// FLAS  H_Vn  nn00  
		// FLAS  H512  _Vnn  n000
		// FLAS  H1M_  Vnnn  

		constexpr size_t STRING_ALIGNMENT = sizeof(Word);

		constexpr Word EEPROM_START = ('E' << 24) + ('E' << 16) + ('P' << 8) + 'R';
		constexpr Word EEPROM_SECOND = ('O' << 24) + ('M' << 16) + ('_' << 8) + 'V';
		constexpr Word SRAM_START = ('S' << 24) + ('R' << 16) + ('A' << 8) + 'M';
		constexpr Word FLASH_START = ('F' << 24) + ('L' << 16) + ('A' << 8) + 'S';

		// 4 groups of 4 bytes
		constexpr size_t MAX_STRING_LENGTH = 4ll * 4;
		// 3 groups of 4 bytes
		constexpr size_t MIN_STRING_LENGTH = 4ll * 3;

		// If we scan up to MAX_STRING_LENGTH bytes ahead, we will have this
		// many extra bytes left over at the end.
		const size_t leftover_bytes = rom.rom_size % MAX_STRING_LENGTH;

		Word* word_pointer = 0;
		Word word = 0;
		// From left to right, the 4 bytes in a group of 4 letters
		char letter_1;
		char letter_2;
		char letter_3;
		char letter_4;
		// We can safely scan this for the longest string without running over
		for (size_t i = 0; i < rom.rom_size - leftover_bytes; ++i) {
			//TODO(ches) scan for the backup type
			word_pointer = (Word*)(((char*)rom.data) + i);
			word = *word_pointer;
			
			if (word == EEPROM_START) {
				word_pointer += 1;
				word = *word_pointer;
				if (word != EEPROM_SECOND) {
					continue;
				}
				word_pointer += 1;
				word = *word_pointer;

				letter_1 = (word >> 3) & 0xff;
				letter_2 = (word >> 2) & 0xff;
				letter_3 = (word >> 1) & 0xff;
				letter_4 = word & 0xff;
				if (!matches_n(letter_1)
				 || !matches_n(letter_2)
				 || !matches_n(letter_3)
				 || !matches_n(letter_4)) {
					continue;
				}
				return BackupType::EEPROM;
			}
			else if (word == SRAM_START) {

			}
			else if (word == FLASH_START) {

			}
			
			letter_1 = (word >> 3) & 0xff;
			letter_2 = (word >> 2) & 0xff;
			letter_3 = (word >> 1) & 0xff;
			letter_4 = word & 0xff;

			if (!matches_n(letter_1)
			 || !matches_n(letter_2) 
			 || !matches_n(letter_3) 
			 || !matches_n(letter_4)) {
				continue;
			}
			

		}

		// last lil nub of data, what cruel person would put the string there??
		if (leftover_bytes >= MIN_STRING_LENGTH) {

		}
	}
}