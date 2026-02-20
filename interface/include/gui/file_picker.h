#pragma once

#include <cstdint>
#include <filesystem>
#include <string>
#include <vector>

namespace gui {

	enum class FileTypes {
		ANY,
		GBA,
		GBC,
	};

	struct FileEntry {
		std::string name;
		bool is_directory;

		FileEntry(std::string&& name, bool is_directory);
		FileEntry(const FileEntry&);
		FileEntry(FileEntry&&);
		FileEntry& operator=(const FileEntry&);
		FileEntry& operator=(FileEntry&&);
		~FileEntry();
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
		std::vector<FileEntry> current_directory_entries;

		void initialize();
		void select_file();
		void close();

		void navigate_to_parent();
		void navigate_to_child(const std::string& child_name);
		void update_directory_info();
	};

	void draw_window_file_picker();

}
