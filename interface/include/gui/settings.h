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

	struct JoypadSettings {
		//TODO(ches) these need to be bindings
		int up;
		int down;
		int left;
		int right;
		int a;
		int b;
		int l;
		int r;
		int select;
		int start;
		int speed;
		int capture;
		int gs;
	};

	struct Settings {
		struct Options {
			struct Video {
				bool vsync;
				enum class Size {
					X1,
					X2,
					X3,
					X4,
					FULL_SCREEN,
				} size;
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
			} frame_skip;
			enum class Filter {
				NORMAL,
				BILINEAR
			} filter;
			struct Emulator {
				bool pause_when_inactive;
				bool speed_up_toggle;
				bool automatic_ips_patching;
				bool real_time_clock;
				struct Directories {
					std::string rom;
					std::string gb_rom;
					std::string battery;
					std::string save_game;
					std::string capture;
				};
				int rewind_interval;
				enum class ShowSpeed {
					NONE,
					PERCENTAGE,
					DETAILED
				} show_speed;
				bool speed_transparent;
				bool use_bios_file;
				bool skip_bios_file;
				enum class Format {
					PNG,
					BMP,
				};
			} emulator;
			struct Sound {
				enum class Status {
					ON,
					MUTE,
					OFF
				} status;
				bool echo;
				bool low_pass_filter;
				bool reverse_stereo;
				bool channel_1;
				bool channel_2;
				bool channel_3;
				bool channel_4;
				bool direct_sound_a;
				bool direct_sound_b;
				enum class Frequency {
					KHZ_11,
					KHZ_22,
					KHZ_44,
				} frequency;
				enum class Volume {
					QUARTER,
					HALF,
					X1,
					X2,
					X3,
					X4,
				} volume;
			} sound;
			struct Gameboy {
				bool border;
				bool border_automatic;
				bool printer;
				enum class Type {
					AUTOMATIC,
					GBA,
					GBC,
					SGB,
					SGB2,
					GB
				} type;
				enum class Colors {
					REAL,
					GAMEBOY,
				} colors;
				ColorSet colors;
			} gameboy;
			struct Joypad {
				JoypadSettings joypad_1;
				JoypadSettings joypad_2;
				JoypadSettings joypad_3;
				JoypadSettings joypad_4;
				enum class DefaultJoypad {
					JOYPAD_1,
					JOYPAD_2,
					JOYPAD_3,
					JOYPAD_4,
				} default_joypad;
				struct Motion {
					//TODO(ches) these need to be keybindings
					int up;
					int down;
					int left;
					int right;
				} motion;
				struct Autofire {
					bool a;
					bool b;
					bool l;
					bool r;
				} autofire;
			};
		} options;
		struct Cheats {
			bool autoload_cheats;
			bool disable_cheats;

		} cheats;
	};


	void foo() {

		Settings settings;
		settings.options.video.size = Settings::Options::Video::Size::X1;
	}
}