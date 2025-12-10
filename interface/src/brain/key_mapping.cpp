#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

#include "brain/brain.h"
#include "brain/key_mapping.h"

namespace brain {

    static gui::Key map_key(int key) {
		switch (key) {
        // Letters
        case GLFW_KEY_A: return gui::Key::A;
        case GLFW_KEY_B: return gui::Key::B;
        case GLFW_KEY_C: return gui::Key::C;
        case GLFW_KEY_D: return gui::Key::D;
        case GLFW_KEY_E: return gui::Key::E;
        case GLFW_KEY_F: return gui::Key::F;
        case GLFW_KEY_G: return gui::Key::G;
        case GLFW_KEY_H: return gui::Key::H;
        case GLFW_KEY_I: return gui::Key::I;
        case GLFW_KEY_J: return gui::Key::J;
        case GLFW_KEY_K: return gui::Key::K;
        case GLFW_KEY_L: return gui::Key::L;
        case GLFW_KEY_M: return gui::Key::M;
        case GLFW_KEY_N: return gui::Key::N;
        case GLFW_KEY_O: return gui::Key::O;
        case GLFW_KEY_P: return gui::Key::P;
        case GLFW_KEY_Q: return gui::Key::Q;
        case GLFW_KEY_R: return gui::Key::R;
        case GLFW_KEY_S: return gui::Key::S;
        case GLFW_KEY_T: return gui::Key::T;
        case GLFW_KEY_U: return gui::Key::U;
        case GLFW_KEY_V: return gui::Key::V;
        case GLFW_KEY_W: return gui::Key::W;
        case GLFW_KEY_X: return gui::Key::X;
        case GLFW_KEY_Y: return gui::Key::Y;
        case GLFW_KEY_Z: return gui::Key::Z;
        // Numbers
        case GLFW_KEY_0: return gui::Key::ZERO;
        case GLFW_KEY_1: return gui::Key::ONE;
        case GLFW_KEY_2: return gui::Key::TWO;
        case GLFW_KEY_3: return gui::Key::THREE;
        case GLFW_KEY_4: return gui::Key::FOUR;
        case GLFW_KEY_5: return gui::Key::FIVE;
        case GLFW_KEY_6: return gui::Key::SIX;
        case GLFW_KEY_7: return gui::Key::SEVEN;
        case GLFW_KEY_8: return gui::Key::EIGHT;
        case GLFW_KEY_9: return gui::Key::NINE;
        // Numpad
        case GLFW_KEY_KP_0: return gui::Key::NUMPAD_ZERO;
        case GLFW_KEY_KP_1: return gui::Key::NUMPAD_ONE;
        case GLFW_KEY_KP_2: return gui::Key::NUMPAD_TWO;
        case GLFW_KEY_KP_3: return gui::Key::NUMPAD_THREE;
        case GLFW_KEY_KP_4: return gui::Key::NUMPAD_FOUR;
        case GLFW_KEY_KP_5: return gui::Key::NUMPAD_FIVE;
        case GLFW_KEY_KP_6: return gui::Key::NUMPAD_SIX;
        case GLFW_KEY_KP_7: return gui::Key::NUMPAD_SEVEN;
        case GLFW_KEY_KP_8: return gui::Key::NUMPAD_EIGHT;
        case GLFW_KEY_KP_9: return gui::Key::NUMPAD_NINE;
        case GLFW_KEY_NUM_LOCK: return gui::Key::NUM_LOCK;
        case GLFW_KEY_KP_ADD: return gui::Key::NUMPAD_ADD;
        case GLFW_KEY_KP_DIVIDE: return gui::Key::NUMPAD_DIVIDE;
        case GLFW_KEY_KP_ENTER: return gui::Key::NUMPAD_ENTER;
        case GLFW_KEY_KP_MULTIPLY: return gui::Key::NUMPAD_MULTIPLY;
        case GLFW_KEY_KP_DECIMAL: return gui::Key::NUMPAD_PERIOD;
        case GLFW_KEY_KP_SUBTRACT: return gui::Key::NUMPAD_SUBTRACT;
        // Symbols
        case GLFW_KEY_APOSTROPHE: return gui::Key::APOSTROPHE;
        case GLFW_KEY_BACKSLASH: return gui::Key::BACK_SLASH;
        case GLFW_KEY_COMMA: return gui::Key::COMMA;
        case GLFW_KEY_EQUAL: return gui::Key::EQUALS;
        case GLFW_KEY_SLASH: return gui::Key::FORWARD_SLASH;
        case GLFW_KEY_LEFT_BRACKET: return gui::Key::LEFT_BRACKET;
        case GLFW_KEY_MINUS: return gui::Key::MINUS;
        case GLFW_KEY_PERIOD: return gui::Key::PERIOD;
        case GLFW_KEY_RIGHT_BRACKET: return gui::Key::RIGHT_BRACKET;
        case GLFW_KEY_SEMICOLON: return gui::Key::SEMICOLON;
        // Special keys
        case GLFW_KEY_DOWN: return gui::Key::ARROW_DOWN;
        case GLFW_KEY_LEFT: return gui::Key::ARROW_LEFT;
        case GLFW_KEY_RIGHT: return gui::Key::ARROW_RIGHT;
        case GLFW_KEY_UP: return gui::Key::ARROW_UP;
        case GLFW_KEY_BACKSPACE: return gui::Key::BACKSPACE;
        case GLFW_KEY_DELETE: return gui::Key::DELETE;
        case GLFW_KEY_END: return gui::Key::END;
        case GLFW_KEY_ENTER: return gui::Key::ENTER;
        case GLFW_KEY_ESCAPE: return gui::Key::ESCAPE;
        case GLFW_KEY_HOME: return gui::Key::HOME;
        case GLFW_KEY_INSERT: return gui::Key::INSERT;
        case GLFW_KEY_MENU: return gui::Key::MENU;
        case GLFW_KEY_PAGE_DOWN: return gui::Key::PAGE_DOWN;
        case GLFW_KEY_PAGE_UP: return gui::Key::PAGE_UP;
        case GLFW_KEY_SPACE: return gui::Key::SPACE;
        case GLFW_KEY_RIGHT_SUPER:
        case GLFW_KEY_LEFT_SUPER: return gui::Key::SUPER;
        case GLFW_KEY_TAB: return gui::Key::TAB;
        // Function keys
        case GLFW_KEY_F1: return gui::Key::F1;
        case GLFW_KEY_F2: return gui::Key::F2;
        case GLFW_KEY_F3: return gui::Key::F3;
        case GLFW_KEY_F4: return gui::Key::F4;
        case GLFW_KEY_F5: return gui::Key::F5;
        case GLFW_KEY_F6: return gui::Key::F6;
        case GLFW_KEY_F7: return gui::Key::F7;
        case GLFW_KEY_F8: return gui::Key::F8;
        case GLFW_KEY_F9: return gui::Key::F9;
        case GLFW_KEY_F10: return gui::Key::F10;
        case GLFW_KEY_F11: return gui::Key::F11;
        case GLFW_KEY_F12: return gui::Key::F12;
        // Gamepad
        //TODO(ches) gui::Key::GAMEPAD_BACK;
        //TODO(ches) gui::Key::GAMEPAD_DPAD_DOWN;
        //TODO(ches) gui::Key::GAMEPAD_DPAD_LEFT;
        //TODO(ches) gui::Key::GAMEPAD_DPAD_RIGHT;
        //TODO(ches) gui::Key::GAMEPAD_DPAD_UP;
        //TODO(ches) gui::Key::GAMEPAD_FACE_DOWN;
        //TODO(ches) gui::Key::GAMEPAD_FACE_LEFT;
        //TODO(ches) gui::Key::GAMEPAD_FACE_RIGHT;
        //TODO(ches) gui::Key::GAMEPAD_FACE_UP;
        //TODO(ches) gui::Key::GAMEPAD_L1;
        //TODO(ches) gui::Key::GAMEPAD_L2;
        //TODO(ches) gui::Key::GAMEPAD_L3;
        //TODO(ches) gui::Key::GAMEPAD_LSTICK_BUTTON;
        //TODO(ches) gui::Key::GAMEPAD_LSTICK_DOWN;
        //TODO(ches) gui::Key::GAMEPAD_LSTICK_LEFT;
        //TODO(ches) gui::Key::GAMEPAD_LSTICK_RIGHT;
        //TODO(ches) gui::Key::GAMEPAD_LSTICK_UP;
        //TODO(ches) gui::Key::GAMEPAD_R1;
        //TODO(ches) gui::Key::GAMEPAD_R2;
        //TODO(ches) gui::Key::GAMEPAD_R3;
        //TODO(ches) gui::Key::GAMEPAD_RSTICK_BUTTON;
        //TODO(ches) gui::Key::GAMEPAD_RSTICK_DOWN;
        //TODO(ches) gui::Key::GAMEPAD_RSTICK_LEFT;
        //TODO(ches) gui::Key::GAMEPAD_RSTICK_RIGHT;
        //TODO(ches) gui::Key::GAMEPAD_RSTICK_UP;
        //TODO(ches) gui::Key::GAMEPAD_SELECT;
        //TODO(ches) gui::Key::GAMEPAD_START;
		}
		
		return gui::Key::NONE;
	}

    static gui::KeyMod map_key_mod(int mod) {
        if ((mod & GLFW_MOD_ALT) != 0) {
            return gui::KeyMod::ALT;
        }
        if ((mod & GLFW_MOD_SHIFT) != 0) {
            return gui::KeyMod::SHIFT;
        }
        if ((mod & GLFW_MOD_CONTROL) != 0) {
            return gui::KeyMod::CTRL;
        }

        return gui::KeyMod::NONE;
    }

	void key_callback(int key, int scancode, int action, int mods) {
        gui::KeyBinding binding = { map_key_mod(mods), map_key(key) };

        if (!gui::has_binding(binding)) {
            return;
        }

        Command command = gui::get_binding(binding);
        g_brain_data->command_queue.add(command);
	}
}
