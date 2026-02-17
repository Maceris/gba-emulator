#pragma once

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

		void select_file();
		void close();

		void navigate_to_parent();
		void navigate_to_child();
		void update_directory_info();
	};

	void draw_window_file_picker();

}
