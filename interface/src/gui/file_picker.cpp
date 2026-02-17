#include "gui/file_picker.h"

#include "imgui.h"

#include "gui/gui.h"

namespace gui {

	FilePicker::FilePicker()
		: file_type_filter{ FileTypes::ANY }
		, current_path{ std::filesystem::current_path() }
		, current_path_string{ current_path.string() }
	{}

	FilePicker::~FilePicker() = default;

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
		current_path_string = current_path.string();
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

			ImGui::Text("%s", picker.current_path_string.c_str());

			ImGui::End();
		}
	}

}
