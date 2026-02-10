#include "cartridge/rom.h"

#include "memory/memory_types.h"

namespace emulator {

	BackupType scan_for_backup_IDs(const ROM& rom) {
		if (!rom.data || rom.rom_size == 0) {
			return BackupType::NONE;
		}

		// EEPROM_Vnnn    EEPROM 512 bytes or 8 Kbytes (4Kbit or 64Kbit)
		// SRAM_Vnnn      SRAM 32 Kbytes(256Kbit)
		// FLASH_Vnnn     FLASH 64 Kbytes(512Kbit) (ID used in older files)
		// FLASH512_Vnnn  FLASH 64 Kbytes(512Kbit) (ID used in newer files)
		// FLASH1M_Vnnn   FLASH 128 Kbytes(1Mbit)
		
		// EEPR  OM_V  nnn0  
		// SRAM  _Vnn  n000  
		// FLAS  H_Vn  nn00  
		// FLAS  H512  _Vnn  n000
		// FLAS  H1M_  Vnnn  
		
		// 1234  1234  1234  1234
		constexpr size_t STRING_ALIGNMENT = sizeof(Word);

		for (size_t i = 0; i < rom.rom_size; ++i) {
			//TODO(ches) scan for the backup type
		}
	}
}