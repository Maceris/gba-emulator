#include "gui/file_picker.h"

#if defined(WIN32)
#include <Windows.h>
#endif

#include "imgui.h"

#include "debugging/logger.h"
#include "gui/gui.h"

namespace gui {

#if defined(WIN32)
	// Just keep this data around forever
	DWORD drive_string_size = MAX_PATH;
	char logical_drive_list[MAX_PATH] = { 0 };
#endif

	FilePicker::FilePicker()
		: file_type_filter{ FileTypes::ANY }
		, current_path{}
		, current_path_string{}
		, root_path{}
		, drive_names{ 0 }
		, drive_count{ 0 }
		, selected_drive{ 0 }
	{
		initialize();
	}

	FilePicker::~FilePicker() = default;

	void FilePicker::initialize() {
		current_path = std::filesystem::current_path();
		current_path_string = current_path.generic_string();
		root_path = current_path.root_path().generic_string();

		Logger::init();

#if defined(WIN32)
		DWORD result = GetLogicalDriveStringsA(drive_string_size, logical_drive_list);

		size_t chars_read = 0;
		size_t string_length = 0;
		if (result > 0 && result <= MAX_PATH) {
			char* drive_name = logical_drive_list;

			LOG_INFO(root_path);

			while (*drive_name) {
				drive_names[drive_count] = drive_name;
				string_length = strnlen(drive_name, MAX_PATH - chars_read) + 1;
				std::replace(drive_name, drive_name + string_length, '\\', '/');

				if (strncmp(drive_name, root_path.c_str(), string_length) == 0) {
					// Confusing name, but the current index
					selected_drive = drive_count;
				}

				chars_read += string_length;
				drive_name += string_length;
				drive_count += 1;
			}
		}
		else {
			LOG_FATAL("Failed to list drives");
		}
#endif

	}

	void FilePicker::select_file() {
		//TODO(ches) figure out parameter(s)
		//TODO(ches) do something with the selected file

		close();
	}

	void FilePicker::close() {
		g_gui_state.show_window_file_picker = false;
	}

	void FilePicker::navigate_to_parent() {
		update_directory_info();
	}

	void FilePicker::navigate_to_child() {
		update_directory_info();
	}

	void FilePicker::update_directory_info() {
		current_path_string = current_path.generic_string();
	}

	void draw_window_file_picker() {
		ImGui::SetNextWindowPos(ImVec2(10, 30), ImGuiCond_Once);
		ImGui::SetNextWindowSize(ImVec2(500, 300), ImGuiCond_Once);

		if (ImGui::Begin("File Picker", &g_gui_state.show_window_file_picker)) {

			//TODO(ches) drive dropdown

			//TODO(ches) parent folder button
			//TODO(ches) navigate to child folders
			//TODO(ches) list entries in folder, cached preferably

			FilePicker& picker = g_gui_state.file_picker;

#if defined(WIN32)
			ImGui::SetNextItemWidth(70);
			ImGui::Combo("##drives", &picker.selected_drive, picker.drive_names, picker.drive_count);
			ImGui::SameLine();
#endif

			ImGui::Text("%s", picker.current_path_string.c_str());

			ImGui::End();
		}
	}

}
