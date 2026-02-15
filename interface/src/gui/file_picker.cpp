#include "gui/file_picker.h"

#include "imgui.h"

#include "gui/gui.h"

namespace gui {

	FilePicker::FilePicker()
		: file_type_filter{ FileTypes::ANY }
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

	void draw_window_file_picker() {
		ImGui::SetNextWindowPos(ImVec2(10, 30), ImGuiCond_Once);
		ImGui::SetNextWindowSize(ImVec2(500, 300), ImGuiCond_Once);

		if (ImGui::Begin("File Picker", &g_gui_state.show_window_file_picker)) {

			ImGui::End();
		}
	}

}
