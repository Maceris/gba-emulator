#pragma once

#include <cstdint>
#include <string>

namespace gui {

	struct ColorGroup {
		uint32_t color_1;
		uint32_t color_2;
		uint32_t color_3;
		uint32_t color_4;
	};

	struct ColorSet {
		ColorGroup background;
		ColorGroup sprite;
	};

	constexpr ColorSet COLOR_SET_STANDARD = {
		{
			0xF8F8F8,
			0xA8A8A8,
			0x606060,
			0x000000
		},
		{
			0xF8F8F8,
			0xA8A8A8,
			0x606060,
			0x000000
		}
	};

	constexpr auto SAVE_FILE_VERSION = 1;

	struct Settings {
		struct Options {
			struct Video {
				bool vsync = false;
				enum class Size {
					X1,
					X2,
					X3,
					X4,
					FULL_SCREEN,
				} size = Size::X1;
				bool show_menu = true;
			} video;
			enum class FrameSkip {
				AUTOMATIC,
				X0,
				X1,
				X2,
				X3,
				X4,
				X5,
				X6,
				X7,
				X8,
				X9,
			} frame_skip = FrameSkip::AUTOMATIC;
			enum class Filter {
				NORMAL,
				BILINEAR
			} filter = Filter::NORMAL;
			struct Emulator {
				bool pause_when_inactive = false;
				bool speed_up_toggle = false;
				bool automatic_ips_patching = false;
				bool real_time_clock = false;
				struct Directories {
					std::string rom = "";
					std::string gb_rom = "";
					std::string battery = "";
					std::string save_game = "";
					std::string capture = "";
				} directories;
				/// <summary>
				/// Rewind interval in seconds (0..600), 0 to disable rewind.
				/// </summary>
				int rewind_interval = 0;
				enum class ShowSpeed {
					NONE,
					PERCENTAGE,
					DETAILED
				} show_speed = ShowSpeed::PERCENTAGE;
				bool speed_transparent = true;
				enum class SaveType {
					AUTOMATIC,
					EEPROM,
					SRAM,
					FLASH,
					EEPROM_AND_SENSOR,
					NONE,
				} save_type = SaveType::AUTOMATIC;
				enum class SaveSize {
					FLASH_32K,
					FLASH_64K,
					FLASH_128K,
				} save_size = SaveSize::FLASH_64K;
				bool save_automatic_size_detection = true;
				bool use_bios_file = true;
				bool skip_bios_file = false;
				enum class Format {
					PNG,
					BMP,
				} format = Format::PNG;
			} emulator;
			struct Sound {
				enum class Status {
					ON,
					MUTE,
					OFF
				} sound_status = Status::ON;
				bool echo = false;
				bool low_pass_filter = false;
				bool reverse_stereo = false;
				bool channel_1 = true;
				bool channel_2 = true;
				bool channel_3 = true;
				bool channel_4 = true;
				bool direct_sound_a = true;
				bool direct_sound_b = true;
				enum class Frequency {
					KHZ_11,
					KHZ_22,
					KHZ_44,
				} frequency = Frequency::KHZ_22;
				enum class Volume {
					QUARTER,
					HALF,
					X1,
					X2,
					X3,
					X4,
				} volume = Volume::X1;
			} sound;
			struct Gameboy {
				bool border = false;
				bool border_automatic = false;
				bool printer = false;
				enum class Type {
					AUTOMATIC,
					GBA,
					GBC,
					SGB,
					SGB2,
					GB
				} type = Type::AUTOMATIC;
				enum class Colors {
					REAL,
					GAMEBOY,
				} colors = Colors::REAL;
				ColorSet color_set = COLOR_SET_STANDARD;
			} gameboy;
		} options;
		struct Controls {
			struct Autofire {
				bool a = false;
				bool b = false;
				bool l = false;
				bool r = false;
			} autofire;
		} controls;
		struct Cheats {
			bool autoload_cheats = false;
			bool disable_cheats = false;
		} cheats;
	};

	extern Settings g_settings;

	/// <summary>
	/// Reset any settings, and set everything to the
	/// defaults.
	/// </summary>
	void set_default_settings();

	/// <summary>
	/// Attempt to load settings from file. If we fail to 
	/// load settings, they might not be in a valid state and should probably
	/// be reset to the defaults.
	/// </summary>
	/// <returns>Whether we successfully loaded settings.</returns>
	bool load_settings();

	/// <summary>
	/// Save all settings to file.
	/// </summary>
	void save_settings();

}