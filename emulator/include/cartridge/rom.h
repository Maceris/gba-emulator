#pragma once

namespace emulator {
	struct ROM
	{
		ROM();
		ROM(const ROM&) = delete;
		ROM(ROM&&) = delete;
		ROM& operator=(const ROM&) = delete;
		ROM& operator=(ROM&&) = delete;
		~ROM();

		/// <summary>
		/// Size in bytes of the data.
		/// </summary>
		size_t rom_size;
		/// <summary>
		/// Raw ROM data.
		/// </summary>
		void* data;
	};

	enum class BackupType {
		NONE,
		EEPROM,
		SRAM,
		FLASH_64KB,
		FLASH_128KB,
	};

	BackupType scan_for_backup_IDs(const ROM& rom);
}