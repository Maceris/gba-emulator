
#include "brain/brain.h"
#include "debugging/logger.h"
#include "gui/gui.h"
#include "gui/key_binding.h"
#include "gui/settings.h"
#include "memory/memory_util.h"
#include "rendering/render.h"

namespace gba {
	/// <summary>
	/// The main method, called from any entrypoint.
	/// </summary>
	/// <returns></returns>
	int main();

	/// <summary>
	/// Setup the program and rendering information.
	/// </summary>
	void initialize();

	/// <summary>
	/// Clean up the scene and rendering pipeline, prepare to end the program.
	/// </summary>
	void cleanup();
}

int main(int argc, char* argv[])
{
	return gba::main();
}

int gba::main()
{
	initialize();

	brain::run_application();

	cleanup();
	return 0;
}

void gba::initialize() {
	Logger::init();
	Logger::set_display_flags("Debug", FLAG_WRITE_TO_DEBUGGER);

	gui::initialize_gui();

	if (!gui::load_settings()) {
		gui::set_default_settings();
		gui::save_settings();
	}
#if _DEBUG
	//TODO(ches) find a way to notice that we are missing settings and only save then
	gui::save_settings();
#endif

	if (!gui::load_key_bindings()) {
		gui::set_default_bindings();
		gui::save_key_bindings();
	}
#if _DEBUG
	//TODO(ches) just save when we change these
	gui::save_key_bindings();
#endif

	render::initialize();
}

void gba::cleanup()
{
	render::cleanup();
	Logger::destroy();
}
