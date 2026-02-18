#pragma once

#include <cstdint>
#include <filesystem>
#include <string>

namespace gui {

	enum class FileTypes {
		ANY,
		GBA,
		GBC,
	};

	struct FilePicker {
		FilePicker();
		FilePicker(const FilePicker&) = delete;
		FilePicker(FilePicker&&) = delete;
		FilePicker& operator=(const FilePicker&) = delete;
		FilePicker& operator=(FilePicker&&) = delete;
		~FilePicker();

		FileTypes file_type_filter;
		std::filesystem::path current_path;
		std::string current_path_string;
		std::string root_path;
		// Only used on windows, max one per english letter.
		char* drive_names[26];
		// Only used on windows, how many we actually found.
		size_t drive_count;
		// Only used on windows.
		int selected_drive;

		void initialize();
		void select_file();
		void close();

		void navigate_to_parent();
		void navigate_to_child();
		void update_directory_info();
	};

	void draw_window_file_picker();

}
