#pragma once

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

		void select_file();
		void close();
	};

	void draw_window_file_picker();

}
