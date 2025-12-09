#include "brain/commands.h"

#define GBA_GUI_COMMANDS_MAPPING(X) { Command::X, #X },
#define GBA_GUI_COMMANDS_END_OF_LIST

namespace brain {
	std::map<Command, const char*> COMMAND_NAMES = {
		GBA_GUI_COMMANDS_LIST
	};
}

#undef GBA_GUI_COMMANDS_MAPPING
#undef GBA_GUI_COMMANDS_END_OF_LIST
