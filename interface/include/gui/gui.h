#pragma once

namespace gui {

	struct GuiState {
		bool show_window_disassembler = false;
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