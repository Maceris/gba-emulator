#include "gui/file_picker.h"

#include <algorithm>
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

	constexpr ImVec4 FOLDER_TEXT_COLOR = { 0.09f, 0.13f, 1.0f, 1.0f };

	FileEntry::FileEntry(const std::string& name, bool is_directory)
		: name{ name }
		, is_directory{ is_directory }
	{}
	FileEntry::FileEntry(const FileEntry&) = default;
	FileEntry::FileEntry(FileEntry&&) = default;
	FileEntry& FileEntry::operator=(const FileEntry&) = default;
	FileEntry& FileEntry::operator=(FileEntry&&) = default;
	FileEntry::~FileEntry() = default;

	FilePicker::FilePicker()
		: file_type_filter{ FileTypes::ANY }
		, current_path{}
		, current_path_string{}
		, root_path{}
		, drive_names{ 0 }
		, drive_count{ 0 }
		, selected_drive{ 0 }
		, current_directory_entries{}
	{
		initialize();
	}

	FilePicker::~FilePicker() = default;

	void FilePicker::initialize() {
		current_path = std::filesystem::current_path();
		root_path = current_path.root_path().generic_string();
		update_directory_info();

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
					selected_drive = static_cast<int>(drive_count);
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

	void FilePicker::select_file(const std::string& child_name) {
		//TODO(ches) do something with the selected file

		close();
	}

	void FilePicker::close() {
		g_gui_state.show_window_file_picker = false;
	}

	void FilePicker::navigate_to_parent() {
		if (current_path_string == root_path) {
			return;
		}
		current_path = current_path.parent_path();
		update_directory_info();
	}

	void FilePicker::navigate_to_child(const std::string& child_name) {
		current_path = current_path / child_name;
		update_directory_info();
	}

	static bool matches(FileTypes filter, const std::string& name) {
		if (filter == FileTypes::ANY) {
			return true;
		}

		size_t last_period = name.find_last_of(".");
		if (last_period == std::string::npos) {
			// not found
			return false;
		}
		std::string extension = name.substr(last_period);
		const char* extension_c = extension.c_str();

		switch (filter) {
		case FileTypes::ANY: return true;
		case FileTypes::GBA:
			if (strncmp(extension_c, ".gba", 5) == 0) {
				return true;
			}
		case FileTypes::GBC:
			if (strncmp(extension_c, ".gbc", 5) == 0) {
				return true;
			}
			if (strncmp(extension_c, ".gb", 4) == 0) {
				return true;
			}
		}
	}

	void FilePicker::update_directory_info() {
		current_path_string = current_path.generic_string();
		current_directory_entries.clear();

		for (const auto& entry : std::filesystem::directory_iterator(current_path)) {
			bool directory = std::filesystem::is_directory(entry);
			std::string name = entry.path().generic_string();
			
			if (matches(file_type_filter, name)) {
				current_directory_entries.emplace_back(name, directory);
			}
		}

		std::sort(current_directory_entries.begin(), current_directory_entries.end(),
			[](const FileEntry& a, const FileEntry& b) {
				// returns true if a should come before b
				if (a.is_directory && !b.is_directory) {
					return true;
				}
				if (!a.is_directory && b.is_directory) {
					return false;
				}
				return a.name < b.name;
			});

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
			ImGui::Combo("##drives", &picker.selected_drive, picker.drive_names, 
				static_cast<int>(picker.drive_count));
			ImGui::SameLine();
#endif

			if (ImGui::Button("Up")) {
				picker.navigate_to_parent();
			}
			ImGui::SameLine();

			ImGui::Text("%s", picker.current_path_string.c_str());

			const ImVec4& window_bg = ImGui::GetStyleColorVec4(ImGuiCol_WindowBg);

			ImGui::PushStyleColor(ImGuiCol_Button, window_bg);

			for (const auto& value : picker.current_directory_entries) {
				if (value.is_directory) {
					ImGui::PushStyleColor(ImGuiCol_Text, FOLDER_TEXT_COLOR);
				}

				if (ImGui::Button(value.name.c_str())) {
					if (value.is_directory) {
						picker.navigate_to_child(value.name);
						ImGui::PopStyleColor();
						break;
					}
					else {
						//TODO(ches) Pick file
					}
				}

				if (value.is_directory) {
					ImGui::PopStyleColor();
				}
			}

			ImGui::PopStyleColor();// Button background

			ImGui::End();
		}
	}

}
