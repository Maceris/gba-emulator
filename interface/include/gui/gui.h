#pragma once

#include "gui/file_picker.h"

namespace gui {

	struct GuiState {
		GuiState();
		GuiState(const GuiState&) = delete;
		GuiState(GuiState&&) = delete;
		GuiState& operator=(const GuiState&) = delete;
		GuiState& operator=(GuiState&&) = delete;
		~GuiState();

		FilePicker file_picker;
		bool show_window_disassembler = false;
		bool show_window_file_picker = false;
	};

	extern GuiState g_gui_state;

	/// <summary>
	/// Draw the UI on top of a frame, intended to be called from the pipeline
	/// while it is generating commands for the buffer.
	/// </summary>
	void draw_ui();

	void draw_main_menu_bar();

	void initialize_gui();
}