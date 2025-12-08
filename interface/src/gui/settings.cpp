#include "gui/settings.h"

#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>

#include "debugging/logger.h"
#include "gui/key_binding.h"

namespace gui {
	Settings g_settings;

	[[nodiscard]]
	static std::filesystem::path settings_file_path() {
		return std::filesystem::current_path().append("gba_settings.ini");
	}

	void set_default_settings() {
		g_settings = Settings();
	}

	bool load_settings() {
		//TODO(ches) load settings
		std::ifstream input_file(settings_file_path());

		if (!input_file.is_open()) {
			LOG_WARNING("Failed to open settings file for reading");
			return false;
		}

		return false;
	}

	static constexpr const char* to_string(bool b) {
		return b ? "true" : "false";
	}

	static constexpr const char* to_string(Settings::Options::Video::Size size) {
		switch (size) {
		case Settings::Options::Video::Size::X1: return "X1";
		case Settings::Options::Video::Size::X2: return "X2";
		case Settings::Options::Video::Size::X3: return "X3";
		case Settings::Options::Video::Size::X4: return "X4";
		case Settings::Options::Video::Size::FULL_SCREEN: return "FULL_SCREEN";
		}
		return "?";
	}

	static constexpr const char* to_string(Settings::Options::FrameSkip frame_skip) {
		switch (frame_skip) {
		case Settings::Options::FrameSkip::AUTOMATIC: return "AUTOMATIC";
		case Settings::Options::FrameSkip::X0 : return "X0";
		case Settings::Options::FrameSkip::X1 : return "X1";
		case Settings::Options::FrameSkip::X2 : return "X2";
		case Settings::Options::FrameSkip::X3 : return "X3";
		case Settings::Options::FrameSkip::X4 : return "X4";
		case Settings::Options::FrameSkip::X5 : return "X5";
		case Settings::Options::FrameSkip::X6 : return "X6";
		case Settings::Options::FrameSkip::X7 : return "X7";
		case Settings::Options::FrameSkip::X8 : return "X8";
		case Settings::Options::FrameSkip::X9 : return "X9";
		}
		return "?";
	}

	static constexpr const char* to_string(Settings::Options::Filter filter) {
		switch (filter) {
		case Settings::Options::Filter::NORMAL: return "NORMAL";
		case Settings::Options::Filter::BILINEAR: return "BILINEAR";
		}
		return "?";
	}

	static constexpr const char* to_string(Settings::Options::Emulator::ShowSpeed show_speed) {
		switch (show_speed) {
		case Settings::Options::Emulator::ShowSpeed::NONE: return "NONE";
		case Settings::Options::Emulator::ShowSpeed::PERCENTAGE: return "PERCENTAGE";
		case Settings::Options::Emulator::ShowSpeed::DETAILED: return "DETAILED";
		}
		return "?";
	}

	static constexpr const char* to_string(Settings::Options::Emulator::SaveType save_type) {
		switch (save_type) {
		case Settings::Options::Emulator::SaveType::AUTOMATIC: return "AUTOMATIC";
		case Settings::Options::Emulator::SaveType::EEPROM: return "EEPROM";
		case Settings::Options::Emulator::SaveType::SRAM: return "SRAM";
		case Settings::Options::Emulator::SaveType::FLASH: return "FLASH";
		case Settings::Options::Emulator::SaveType::EEPROM_AND_SENSOR: return "EEPROM_AND_SENSOR";
		case Settings::Options::Emulator::SaveType::NONE: return "NONE";
		}
		return "?";
	}

	static constexpr const char* to_string(Settings::Options::Emulator::SaveSize save_size) {
		switch (save_size) {
		case Settings::Options::Emulator::SaveSize::FLASH_32K: return "FLASH_32K";
		case Settings::Options::Emulator::SaveSize::FLASH_64K: return "FLASH_64K";
		case Settings::Options::Emulator::SaveSize::FLASH_128K: return "FLASH_128K";
		}
		return "?";
	}

	static constexpr const char* to_string(Settings::Options::Emulator::Format format) {
		switch (format) {
		case Settings::Options::Emulator::Format::PNG: return "PNG";
		case Settings::Options::Emulator::Format::BMP: return "BMP";
		}
		return "?";
	}

	static constexpr const char* to_string(Settings::Options::Sound::Status sound_status) {
		switch (sound_status) {
		case Settings::Options::Sound::Status::ON: return "ON";
		case Settings::Options::Sound::Status::MUTE: return "MUTE";
		case Settings::Options::Sound::Status::OFF: return "OFF";
		}
		return "?";
	}

	static constexpr const char* to_string(Settings::Options::Sound::Frequency frequency) {
		switch (frequency) {
		case Settings::Options::Sound::Frequency::KHZ_11: return "KHZ_11";
		case Settings::Options::Sound::Frequency::KHZ_22: return "KHZ_22";
		case Settings::Options::Sound::Frequency::KHZ_44: return "KHZ_44";
		}
		return "?";
	}

	static constexpr const char* to_string(Settings::Options::Sound::Volume volume) {
		switch (volume) {
		case Settings::Options::Sound::Volume::QUARTER: return "QUARTER";
		case Settings::Options::Sound::Volume::HALF: return "HALF";
		case Settings::Options::Sound::Volume::X1: return "X1";
		case Settings::Options::Sound::Volume::X2: return "X2";
		case Settings::Options::Sound::Volume::X3: return "X3";
		case Settings::Options::Sound::Volume::X4: return "X4";
		}
		return "?";
	}

	static constexpr const char* to_string(Settings::Options::Gameboy::Type type) {
		switch (type) {
		case Settings::Options::Gameboy::Type::AUTOMATIC: return "AUTOMATIC";
		case Settings::Options::Gameboy::Type::GBA: return "GBA";
		case Settings::Options::Gameboy::Type::GBC: return "GBC";
		case Settings::Options::Gameboy::Type::SGB: return "SGB";
		case Settings::Options::Gameboy::Type::SGB2: return "SGB2";
		case Settings::Options::Gameboy::Type::GB: return "GB";
		}
		return "?";
	}

	static constexpr const char* to_string(Settings::Options::Gameboy::Colors colors) {
		switch (colors) {
		case Settings::Options::Gameboy::Colors::REAL: return "REAL";
		case Settings::Options::Gameboy::Colors::GAMEBOY: return "GAMEBOY";
		}
		return "?";
	}

	static std::string color_to_string(uint32_t color) {
		return std::format("{:#08x}", color);
	}

	void save_settings() {
		std::ofstream output_file(settings_file_path(), std::ios::trunc);

		if (!output_file.is_open()) {
			LOG_ERROR("Failed to open settings file for writing");
			return;
		}

		output_file << "[metadata]" << "\n";
		output_file << "save_file_version=" << SAVE_FILE_VERSION << "\n";
		output_file << "[options]" << "\n";
		output_file << "frame_skip=" << to_string(g_settings.options.frame_skip) << "\n";
		output_file << "filter=" << to_string(g_settings.options.filter) << "\n";
		output_file << "[video]" << "\n";
		output_file << "vsync=" << to_string(g_settings.options.video.vsync) << "\n";
		output_file << "size=" << to_string(g_settings.options.video.size) << "\n";
		output_file << "show_menu=" << to_string(g_settings.options.video.show_menu) << "\n";
		output_file << "[emulator]" << "\n";
		output_file << "pause_when_inactive=" << to_string(g_settings.options.emulator.pause_when_inactive) << "\n";
		output_file << "speed_up_toggle=" << to_string(g_settings.options.emulator.speed_up_toggle) << "\n";
		output_file << "automatic_ips_patching=" << to_string(g_settings.options.emulator.automatic_ips_patching) << "\n";
		output_file << "real_time_clock=" << to_string(g_settings.options.emulator.real_time_clock) << "\n";
		output_file << "directory_rom=" << g_settings.options.emulator.directories.rom << "\n";
		output_file << "directory_gb_rom=" << g_settings.options.emulator.directories.gb_rom << "\n";
		output_file << "directory_battery=" << g_settings.options.emulator.directories.battery << "\n";
		output_file << "directory_save_game=" << g_settings.options.emulator.directories.save_game << "\n";
		output_file << "directory_capture=" << g_settings.options.emulator.directories.capture << "\n";
		output_file << "rewind_interval=" << g_settings.options.emulator.rewind_interval << "\n";
		output_file << "show_speed=" << to_string(g_settings.options.emulator.show_speed) << "\n";
		output_file << "speed_transparent=" << to_string(g_settings.options.emulator.speed_transparent) << "\n";
		output_file << "save_type=" << to_string(g_settings.options.emulator.save_type) << "\n";
		output_file << "save_size=" << to_string(g_settings.options.emulator.save_size) << "\n";
		output_file << "save_automatic_size_detection=" << to_string(g_settings.options.emulator.save_automatic_size_detection) << "\n";
		output_file << "use_bios_file=" << to_string(g_settings.options.emulator.use_bios_file) << "\n";
		output_file << "skip_bios_file=" << to_string(g_settings.options.emulator.skip_bios_file) << "\n";
		output_file << "format=" << to_string(g_settings.options.emulator.format) << "\n";
		output_file << "[sound]" << "\n";
		output_file << "sound_status=" << to_string(g_settings.options.sound.sound_status) << "\n";
		output_file << "echo=" << to_string(g_settings.options.sound.echo) << "\n";
		output_file << "low_pass_filter=" << to_string(g_settings.options.sound.low_pass_filter) << "\n";
		output_file << "reverse_stereo=" << to_string(g_settings.options.sound.reverse_stereo) << "\n";
		output_file << "channel_1=" << to_string(g_settings.options.sound.channel_1) << "\n";
		output_file << "channel_2=" << to_string(g_settings.options.sound.channel_2) << "\n";
		output_file << "channel_3=" << to_string(g_settings.options.sound.channel_3) << "\n";
		output_file << "channel_4=" << to_string(g_settings.options.sound.channel_4) << "\n";
		output_file << "direct_sound_a=" << to_string(g_settings.options.sound.direct_sound_a) << "\n";
		output_file << "direct_sound_b=" << to_string(g_settings.options.sound.direct_sound_b) << "\n";
		output_file << "frequency=" << to_string(g_settings.options.sound.frequency) << "\n";
		output_file << "volume=" << to_string(g_settings.options.sound.volume) << "\n";
		output_file << "[gameboy]" << "\n";
		output_file << "border=" << to_string(g_settings.options.gameboy.border) << "\n";
		output_file << "border_automatic=" << to_string(g_settings.options.gameboy.border_automatic) << "\n";
		output_file << "printer=" << to_string(g_settings.options.gameboy.printer) << "\n";
		output_file << "type=" << to_string(g_settings.options.gameboy.type) << "\n";
		output_file << "colors=" << to_string(g_settings.options.gameboy.colors) << "\n";
		output_file << "color_set_background_1=" << color_to_string(g_settings.options.gameboy.color_set.background.color_1) << "\n";
		output_file << "color_set_background_2=" << color_to_string(g_settings.options.gameboy.color_set.background.color_2) << "\n";
		output_file << "color_set_background_3=" << color_to_string(g_settings.options.gameboy.color_set.background.color_3) << "\n";
		output_file << "color_set_background_4=" << color_to_string(g_settings.options.gameboy.color_set.background.color_4) << "\n";
		output_file << "color_set_sprite_1=" << color_to_string(g_settings.options.gameboy.color_set.sprite.color_1) << "\n";
		output_file << "color_set_sprite_2=" << color_to_string(g_settings.options.gameboy.color_set.sprite.color_2) << "\n";
		output_file << "color_set_sprite_3=" << color_to_string(g_settings.options.gameboy.color_set.sprite.color_3) << "\n";
		output_file << "color_set_sprite_4=" << color_to_string(g_settings.options.gameboy.color_set.sprite.color_4) << "\n";
		output_file << "[controls]" << "\n";
		output_file << "autofire_a=" << to_string(g_settings.controls.autofire.a) << "\n";
		output_file << "autofire_b=" << to_string(g_settings.controls.autofire.b) << "\n";
		output_file << "autofire_l=" << to_string(g_settings.controls.autofire.l) << "\n";
		output_file << "autofire_r=" << to_string(g_settings.controls.autofire.r) << "\n";
		output_file << "[cheats]" << "\n";
		output_file << "autoload_cheats=" << to_string(g_settings.cheats.autoload_cheats) << "\n";
		output_file << "disable_cheats=" << to_string(g_settings.cheats.disable_cheats) << "\n";

		output_file.close();
	}

}