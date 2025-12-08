#include "gui/key_binding.h"

#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>

#include "debugging/logger.h"

namespace gui {

    /// <summary>
    /// Contains the string form of all the known sane+supported, key bindings.
    /// </summary>
    std::map<uint64_t, const char*> key_string_cache;
    std::map<uint64_t, Command> key_bindings;
    std::map<Command, KeyBinding> command_bindings;

    static void populate_cache(std::map<uint64_t, const char*>& cache);

    [[nodiscard]]
    uint64_t KeyBinding::to_map_key() const {
        return static_cast<uint64_t>(mod) << 32 | static_cast<uint64_t>(key);
    }

    [[nodiscard]]
    static std::filesystem::path keybinds_file_path() {
        return std::filesystem::current_path().append("gba_keybinds.ini");
    }

    const char* to_string(const Key key)
    {
        switch (key) {
        case Key::NONE: return "";
        case Key::A: return "A";
        case Key::B: return "B";
        case Key::C: return "C";
        case Key::D: return "D";
        case Key::E: return "E";
        case Key::F: return "F";
        case Key::G: return "G";
        case Key::H: return "H";
        case Key::I: return "I";
        case Key::J: return "J";
        case Key::K: return "K";
        case Key::L: return "L";
        case Key::M: return "M";
        case Key::N: return "N";
        case Key::O: return "O";
        case Key::P: return "P";
        case Key::Q: return "Q";
        case Key::R: return "R";
        case Key::S: return "S";
        case Key::T: return "T";
        case Key::U: return "U";
        case Key::V: return "V";
        case Key::W: return "W";
        case Key::X: return "X";
        case Key::Y: return "Y";
        case Key::Z: return "Z";
        case Key::ZERO: return "0";
        case Key::ONE: return "1";
        case Key::TWO: return "2";
        case Key::THREE: return "3";
        case Key::FOUR: return "4";
        case Key::FIVE: return "5";
        case Key::SIX: return "6";
        case Key::SEVEN: return "7";
        case Key::EIGHT: return "8";
        case Key::NINE: return "9";
        case Key::NUMPAD_ZERO: return "NumPad0";
        case Key::NUMPAD_ONE: return "NumPad1";
        case Key::NUMPAD_TWO: return "NumPad2";
        case Key::NUMPAD_THREE: return "NumPad3";
        case Key::NUMPAD_FOUR: return "NumPad4";
        case Key::NUMPAD_FIVE: return "NumPad5";
        case Key::NUMPAD_SIX: return "NumPad6";
        case Key::NUMPAD_SEVEN: return "NumPad7";
        case Key::NUMPAD_EIGHT: return "NumPad8";
        case Key::NUMPAD_NINE: return "NumPad9";
        case Key::NUM_LOCK: return "NumLock";
        case Key::NUMPAD_ADD: return "NumPad+";
        case Key::NUMPAD_DIVIDE: return "NumPad/";
        case Key::NUMPAD_ENTER: return "NumPadEnter";
        case Key::NUMPAD_MULTIPLY: return "NumPad*";
        case Key::NUMPAD_PERIOD: return "NumPad.";
        case Key::NUMPAD_SUBTRACT: return "NumPad-";
        case Key::AMPERSAND: return "&";
        case Key::APOSTROPHE: return "`";
        case Key::ASTERISK: return "*";
        case Key::AT: return "@";
        case Key::BACK_SLASH: return "\\";
        case Key::CARET: return "^";
        case Key::COLON: return ":";
        case Key::COMMA: return ",";
        case Key::DOLLAR: return "$";
        case Key::DOUBLE_QUOTE: return "\"";
        case Key::EQUALS: return "=";
        case Key::EURO: return "Euro";
        case Key::EXCLAMATION_MARK: return "!";
        case Key::FORWARD_SLASH: return "/";
        case Key::GREATER_THAN: return ">";
        case Key::LEFT_BRACE: return "{";
        case Key::LEFT_BRACKET: return "[";
        case Key::LEFT_PARENTHESES: return "(";
        case Key::LESS_THAN: return "<";
        case Key::MINUS: return "-";
        case Key::NUMBER_SIGN: return "#";
        case Key::PERCENT: return "%";
        case Key::PERIOD: return ".";
        case Key::PIPE: return "|";
        case Key::PLUS: return "+";
        case Key::POUND: return "Pound";
        case Key::QUESTION_MARK: return "?";
        case Key::RIGHT_BRACE: return "}";
        case Key::RIGHT_BRACKET: return "]";
        case Key::RIGHT_PARENTHESES: return ")";
        case Key::SEMICOLON: return ";";
        case Key::SINGLE_QUOTE: return "'";
        case Key::UNDERSCORE: return "_";
        case Key::ARROW_DOWN: return "Down";
        case Key::ARROW_LEFT: return "Left";
        case Key::ARROW_RIGHT: return "Right";
        case Key::ARROW_UP: return "Up";
        case Key::BACKSPACE: return "Backspace";
        case Key::DELETE: return "Delete";
        case Key::END: return "End";
        case Key::ENTER: return "Enter";
        case Key::ESCAPE: return "Esc";
        case Key::HOME: return "Home";
        case Key::INSERT: return "Insert";
        case Key::MENU: return "Menu";
        case Key::PAGE_DOWN: return "PageDown";
        case Key::PAGE_UP: return "PageUp";
        case Key::SPACE: return "Space";
        case Key::SUPER: return "Super";
        case Key::TAB: return "Tab";
        case Key::F1: return "F1";
        case Key::F2: return "F2";
        case Key::F3: return "F3";
        case Key::F4: return "F4";
        case Key::F5: return "F5";
        case Key::F6: return "F6";
        case Key::F7: return "F7";
        case Key::F8: return "F8";
        case Key::F9: return "F9";
        case Key::F10: return "F10";
        case Key::F11: return "F11";
        case Key::F12: return "F12";
        case Key::GAMEPAD_BACK: return "GamePadBack";
        case Key::GAMEPAD_DPAD_DOWN: return "GamepadDPadDown";
        case Key::GAMEPAD_DPAD_LEFT: return "GamepadDPadLeft";
        case Key::GAMEPAD_DPAD_RIGHT: return "GamepadDPadRight";
        case Key::GAMEPAD_DPAD_UP: return "GamepadDPadUp";
        case Key::GAMEPAD_FACE_DOWN: return "GamepadFaceDown";
        case Key::GAMEPAD_FACE_LEFT: return "GamepadFaceLeft";
        case Key::GAMEPAD_FACE_RIGHT: return "GamepadFaceRight";
        case Key::GAMEPAD_FACE_UP: return "GamepadFaceUp";
        case Key::GAMEPAD_L1: return "GamepadL1";
        case Key::GAMEPAD_L2: return "GamepadL2";
        case Key::GAMEPAD_L3: return "GamepadL3";
        case Key::GAMEPAD_LSTICK_BUTTON: return "GamepadLStickButton";
        case Key::GAMEPAD_LSTICK_DOWN: return "GamepadLStickDown";
        case Key::GAMEPAD_LSTICK_LEFT: return "GamepadLStickLeft";
        case Key::GAMEPAD_LSTICK_RIGHT: return "GamepadLStickRight";
        case Key::GAMEPAD_LSTICK_UP: return "GamepadLStickUp";
        case Key::GAMEPAD_R1: return "GamepadR1";
        case Key::GAMEPAD_R2: return "GamepadR2";
        case Key::GAMEPAD_R3: return "GamepadR3";
        case Key::GAMEPAD_RSTICK_BUTTON: return "GamepadRStickButton";
        case Key::GAMEPAD_RSTICK_DOWN: return "GamepadRStickDown";
        case Key::GAMEPAD_RSTICK_LEFT: return "GamepadRStickLeft";
        case Key::GAMEPAD_RSTICK_RIGHT: return "GamepadRStickRight";
        case Key::GAMEPAD_RSTICK_UP: return "GamepadRStickUp";
        case Key::GAMEPAD_SELECT: return "GamepadSelect";
        case Key::GAMEPAD_START: return "GamepadStart";
        case Key::_count: return "";
        }
        return "";
    }

    Key key_from_string(const char* text, const size_t length)
    {
        switch (length) {
        case 1:
            if (strncmp(text, "A", length) == 0) return Key::A;
            if (strncmp(text, "B", length) == 0) return Key::B;
            if (strncmp(text, "C", length) == 0) return Key::C;
            if (strncmp(text, "D", length) == 0) return Key::D;
            if (strncmp(text, "E", length) == 0) return Key::E;
            if (strncmp(text, "F", length) == 0) return Key::F;
            if (strncmp(text, "G", length) == 0) return Key::G;
            if (strncmp(text, "H", length) == 0) return Key::H;
            if (strncmp(text, "I", length) == 0) return Key::I;
            if (strncmp(text, "J", length) == 0) return Key::J;
            if (strncmp(text, "K", length) == 0) return Key::K;
            if (strncmp(text, "L", length) == 0) return Key::L;
            if (strncmp(text, "M", length) == 0) return Key::M;
            if (strncmp(text, "N", length) == 0) return Key::N;
            if (strncmp(text, "O", length) == 0) return Key::O;
            if (strncmp(text, "P", length) == 0) return Key::P;
            if (strncmp(text, "Q", length) == 0) return Key::Q;
            if (strncmp(text, "R", length) == 0) return Key::R;
            if (strncmp(text, "S", length) == 0) return Key::S;
            if (strncmp(text, "T", length) == 0) return Key::T;
            if (strncmp(text, "U", length) == 0) return Key::U;
            if (strncmp(text, "V", length) == 0) return Key::V;
            if (strncmp(text, "W", length) == 0) return Key::W;
            if (strncmp(text, "X", length) == 0) return Key::X;
            if (strncmp(text, "Y", length) == 0) return Key::Y;
            if (strncmp(text, "Z", length) == 0) return Key::Z;
            if (strncmp(text, "0", length) == 0) return Key::ZERO;
            if (strncmp(text, "1", length) == 0) return Key::ONE;
            if (strncmp(text, "2", length) == 0) return Key::TWO;
            if (strncmp(text, "3", length) == 0) return Key::THREE;
            if (strncmp(text, "4", length) == 0) return Key::FOUR;
            if (strncmp(text, "5", length) == 0) return Key::FIVE;
            if (strncmp(text, "6", length) == 0) return Key::SIX;
            if (strncmp(text, "7", length) == 0) return Key::SEVEN;
            if (strncmp(text, "8", length) == 0) return Key::EIGHT;
            if (strncmp(text, "9", length) == 0) return Key::NINE;
            if (strncmp(text, "&", length) == 0) return Key::AMPERSAND;
            if (strncmp(text, "`", length) == 0) return Key::APOSTROPHE;
            if (strncmp(text, "*", length) == 0) return Key::ASTERISK;
            if (strncmp(text, "@", length) == 0) return Key::AT;
            if (strncmp(text, "\\", length) == 0) return Key::BACK_SLASH;
            if (strncmp(text, "^", length) == 0) return Key::CARET;
            if (strncmp(text, ":", length) == 0) return Key::COLON;
            if (strncmp(text, ",", length) == 0) return Key::COMMA;
            if (strncmp(text, "$", length) == 0) return Key::DOLLAR;
            if (strncmp(text, "\"", length) == 0) return Key::DOUBLE_QUOTE;
            if (strncmp(text, "=", length) == 0) return Key::EQUALS;
            if (strncmp(text, "!", length) == 0) return Key::EXCLAMATION_MARK;
            if (strncmp(text, "/", length) == 0) return Key::FORWARD_SLASH;
            if (strncmp(text, ">", length) == 0) return Key::GREATER_THAN;
            if (strncmp(text, "{", length) == 0) return Key::LEFT_BRACE;
            if (strncmp(text, "[", length) == 0) return Key::LEFT_BRACKET;
            if (strncmp(text, "(", length) == 0) return Key::LEFT_PARENTHESES;
            if (strncmp(text, "<", length) == 0) return Key::LESS_THAN;
            if (strncmp(text, "-", length) == 0) return Key::MINUS;
            if (strncmp(text, "#", length) == 0) return Key::NUMBER_SIGN;
            if (strncmp(text, "%", length) == 0) return Key::PERCENT;
            if (strncmp(text, ".", length) == 0) return Key::PERIOD;
            if (strncmp(text, "|", length) == 0) return Key::PIPE;
            if (strncmp(text, "+", length) == 0) return Key::PLUS;
            if (strncmp(text, "?", length) == 0) return Key::QUESTION_MARK;
            if (strncmp(text, "}", length) == 0) return Key::RIGHT_BRACE;
            if (strncmp(text, "]", length) == 0) return Key::RIGHT_BRACKET;
            if (strncmp(text, ")", length) == 0) return Key::RIGHT_PARENTHESES;
            if (strncmp(text, ";", length) == 0) return Key::SEMICOLON;
            if (strncmp(text, "'", length) == 0) return Key::SINGLE_QUOTE;
            if (strncmp(text, "_", length) == 0) return Key::UNDERSCORE;
            break;
        case 2:
            if (strncmp(text, "Up", length) == 0) return Key::ARROW_UP;
            if (strncmp(text, "F1", length) == 0) return Key::F1;
            if (strncmp(text, "F2", length) == 0) return Key::F2;
            if (strncmp(text, "F3", length) == 0) return Key::F3;
            if (strncmp(text, "F4", length) == 0) return Key::F4;
            if (strncmp(text, "F5", length) == 0) return Key::F5;
            if (strncmp(text, "F6", length) == 0) return Key::F6;
            if (strncmp(text, "F7", length) == 0) return Key::F7;
            if (strncmp(text, "F8", length) == 0) return Key::F8;
            if (strncmp(text, "F9", length) == 0) return Key::F9;
            break;
        case 3:
            if (strncmp(text, "End", length) == 0) return Key::END;
            if (strncmp(text, "Esc", length) == 0) return Key::ESCAPE;
            if (strncmp(text, "Tab", length) == 0) return Key::TAB;
            if (strncmp(text, "F10", length) == 0) return Key::F10;
            if (strncmp(text, "F11", length) == 0) return Key::F11;
            if (strncmp(text, "F12", length) == 0) return Key::F12;
            break;
        case 4:
            if (strncmp(text, "Euro", length) == 0) return Key::EURO;
            if (strncmp(text, "Down", length) == 0) return Key::ARROW_DOWN;
            if (strncmp(text, "Left", length) == 0) return Key::ARROW_LEFT;
            if (strncmp(text, "Home", length) == 0) return Key::HOME;
            if (strncmp(text, "Menu", length) == 0) return Key::MENU;
            break;
        case 5:
            if (strncmp(text, "Pound", length) == 0) return Key::POUND;
            if (strncmp(text, "Right", length) == 0) return Key::ARROW_RIGHT;
            if (strncmp(text, "Enter", length) == 0) return Key::ENTER;
            if (strncmp(text, "Space", length) == 0) return Key::SPACE;
            if (strncmp(text, "Super", length) == 0) return Key::SUPER;
            break;
        case 6:
            if (strncmp(text, "Delete", length) == 0) return Key::DELETE;
            if (strncmp(text, "Insert", length) == 0) return Key::INSERT;
            if (strncmp(text, "PageUp", length) == 0) return Key::PAGE_UP;
            break;
        case 7:
            if (strncmp(text, "NumPad0", length) == 0) return Key::NUMPAD_ZERO;
            if (strncmp(text, "NumPad1", length) == 0) return Key::NUMPAD_ONE;
            if (strncmp(text, "NumPad2", length) == 0) return Key::NUMPAD_TWO;
            if (strncmp(text, "NumPad3", length) == 0) return Key::NUMPAD_THREE;
            if (strncmp(text, "NumPad4", length) == 0) return Key::NUMPAD_FOUR;
            if (strncmp(text, "NumPad5", length) == 0) return Key::NUMPAD_FIVE;
            if (strncmp(text, "NumPad6", length) == 0) return Key::NUMPAD_SIX;
            if (strncmp(text, "NumPad7", length) == 0) return Key::NUMPAD_SEVEN;
            if (strncmp(text, "NumPad8", length) == 0) return Key::NUMPAD_EIGHT;
            if (strncmp(text, "NumPad9", length) == 0) return Key::NUMPAD_NINE;
            if (strncmp(text, "NumLock", length) == 0) return Key::NUM_LOCK;
            if (strncmp(text, "NumPad+", length) == 0) return Key::NUMPAD_ADD;
            if (strncmp(text, "NumPad/", length) == 0) return Key::NUMPAD_DIVIDE;
            if (strncmp(text, "NumPad*", length) == 0) return Key::NUMPAD_MULTIPLY;
            if (strncmp(text, "NumPad.", length) == 0) return Key::NUMPAD_PERIOD;
            if (strncmp(text, "NumPad-", length) == 0) return Key::NUMPAD_SUBTRACT;
            break;
        case 8:
            if (strncmp(text, "PageDown", length) == 0) return Key::PAGE_DOWN;
            break;
        case 9:
            if (strncmp(text, "Backspace", length) == 0) return Key::BACKSPACE;
            if (strncmp(text, "GamepadL1", length) == 0) return Key::GAMEPAD_L1;
            if (strncmp(text, "GamepadL2", length) == 0) return Key::GAMEPAD_L2;
            if (strncmp(text, "GamepadL3", length) == 0) return Key::GAMEPAD_L3;
            if (strncmp(text, "GamepadR1", length) == 0) return Key::GAMEPAD_R1;
            if (strncmp(text, "GamepadR2", length) == 0) return Key::GAMEPAD_R2;
            if (strncmp(text, "GamepadR3", length) == 0) return Key::GAMEPAD_R3;
            break;
        case 11:
            if (strncmp(text, "NumPadEnter", length) == 0) return Key::NUMPAD_ENTER;
            if (strncmp(text, "GamePadBack", length) == 0) return Key::GAMEPAD_BACK;
            break;
        case 12:
            if (strncmp(text, "GamepadStart", length) == 0) return Key::GAMEPAD_START;
            break;
        case 13:
            if (strncmp(text, "GamepadSelect", length) == 0) return Key::GAMEPAD_SELECT;
            if (strncmp(text, "GamepadDPadUp", length) == 0) return Key::GAMEPAD_DPAD_UP;
            if (strncmp(text, "GamepadFaceUp", length) == 0) return Key::GAMEPAD_FACE_UP;
            break;
        case 15:
            if (strncmp(text, "GamepadDPadDown", length) == 0) return Key::GAMEPAD_DPAD_DOWN;
            if (strncmp(text, "GamepadDPadLeft", length) == 0) return Key::GAMEPAD_DPAD_LEFT;
            if (strncmp(text, "GamepadFaceDown", length) == 0) return Key::GAMEPAD_FACE_DOWN;
            if (strncmp(text, "GamepadFaceLeft", length) == 0) return Key::GAMEPAD_FACE_LEFT;
            if (strncmp(text, "GamepadLStickUp", length) == 0) return Key::GAMEPAD_LSTICK_UP;
            if (strncmp(text, "GamepadRStickUp", length) == 0) return Key::GAMEPAD_RSTICK_UP;
            break;
        case 16:
            if (strncmp(text, "GamepadDPadRight", length) == 0) return Key::GAMEPAD_DPAD_RIGHT;
            if (strncmp(text, "GamepadFaceRight", length) == 0) return Key::GAMEPAD_FACE_RIGHT;
            break;
        case 17:
            if (strncmp(text, "GamepadLStickDown", length) == 0) return Key::GAMEPAD_LSTICK_DOWN;
            if (strncmp(text, "GamepadLStickLeft", length) == 0) return Key::GAMEPAD_LSTICK_LEFT;
            if (strncmp(text, "GamepadRStickDown", length) == 0) return Key::GAMEPAD_RSTICK_DOWN;
            if (strncmp(text, "GamepadRStickLeft", length) == 0) return Key::GAMEPAD_RSTICK_LEFT;
            break;
        case 18:
            if (strncmp(text, "GamepadLStickRight", length) == 0) return Key::GAMEPAD_LSTICK_RIGHT;
            if (strncmp(text, "GamepadRStickRight", length) == 0) return Key::GAMEPAD_RSTICK_RIGHT;
            break;
        case 19:
            if (strncmp(text, "GamepadLStickButton", length) == 0) return Key::GAMEPAD_LSTICK_BUTTON;
            if (strncmp(text, "GamepadRStickButton", length) == 0) return Key::GAMEPAD_RSTICK_BUTTON;
            break;
        }
        return Key::NONE;
    }

    const char* to_string(const KeyMod mod)
    {
        switch (mod) {
        case KeyMod::NONE: return "";
        case KeyMod::SHIFT: return "Shift";
        case KeyMod::CTRL: return "Ctrl";
        case KeyMod::ALT: return "Alt";
        case KeyMod::_count: return "";
        }
        return "";
    }

    KeyMod mod_from_string(const char* text, const size_t length) {
        if (length == 3 && strncmp(text, "Alt", length) == 0) return KeyMod::ALT;
        if (length == 4 && strncmp(text, "Ctrl", length) == 0) return KeyMod::CTRL;
        if (length == 5 && strncmp(text, "Shift", length) == 0) return KeyMod::SHIFT;
        
        return KeyMod::NONE;
    }

    const char* to_string(const KeyBinding binding)
    {
        static bool initialized_cache = false;
        if (!initialized_cache) {
            initialized_cache = true;
            populate_cache(key_string_cache);
        }

        uint64_t cache_key = binding.to_map_key();

        const auto result = key_string_cache.find(cache_key);

        if (result == key_string_cache.end()) {
            return "";
        }
        return result->second;
    }

    KeyBinding binding_from_string(const std::string binding_string) {
        const size_t plus = binding_string.find("+");
        if (plus > 0 && plus < binding_string.size() - 1 && plus != std::string::npos) {
            // we have a plus
            KeyMod mod = mod_from_string(binding_string.data(), plus);
            if (mod == KeyMod::NONE) {
                LOG_WARNING(std::format("Unknown keymod in {}", binding_string));
                return { KeyMod::NONE , Key::NONE };
            }
            Key key = key_from_string(binding_string.data() + (plus + 1), binding_string.length() - (plus + 1));
            if (key == Key::NONE) {
                LOG_WARNING(std::format("Unknown key in {}", binding_string));
                return { KeyMod::NONE , Key::NONE };
            }
            return { mod, key };
        }
        Key key = key_from_string(binding_string.data(), binding_string.length());
        if (key == Key::NONE) {
            LOG_WARNING(std::format("Unknown key in {}", binding_string));
            return { KeyMod::NONE , Key::NONE };
        }
        return { KeyMod::NONE, key };
    }

    void map_key(const KeyBinding key, const Command command) {
        const auto command_mapped_to_key = key_bindings.find(key.to_map_key());
        if (command_mapped_to_key != key_bindings.end()) {
            command_bindings.erase(command_mapped_to_key->second);
            key_bindings.erase(command_mapped_to_key);
        }
        
        const auto key_mapped_to_command = command_bindings.find(command);
        if (key_mapped_to_command != command_bindings.end()) {
            key_bindings.erase(key_mapped_to_command->second.to_map_key());
            command_bindings.erase(key_mapped_to_command);
        }

        key_bindings.emplace(key.to_map_key(), command);
        command_bindings.emplace(command, key);
    }

    void unmap_key(const KeyBinding key) {
        const auto existing = key_bindings.find(key.to_map_key());

        if (existing != key_bindings.end()) {
            command_bindings.erase(existing->second);
        }
        key_bindings.erase(key.to_map_key());
    }

    void unmap_command(const Command command) {
        const auto existing = command_bindings.find(command);

        if (existing != command_bindings.end()) {
            key_bindings.erase(existing->second.to_map_key());
        }
        command_bindings.erase(command);
    }

    bool has_binding(const Command command) {
        return command_bindings.find(command) != command_bindings.end();
    }

    bool has_binding(KeyBinding key) {
        return key_bindings.find(key.to_map_key()) != key_bindings.end();
    }

    KeyBinding get_binding(const Command command) {
        const auto result = command_bindings.find(command);
        if (result == command_bindings.end()) {
            return { KeyMod::NONE, Key::NONE };
        }
        return result->second;
    }

    Command get_binding(const KeyBinding key) {
        const auto result = key_bindings.find(key.to_map_key());
        if (result == key_bindings.end()) {
            return Command::_count;
        }
        return result->second;
    }

    void clear_all_bindings() {
        key_bindings.clear();
        command_bindings.clear();
    }

    void set_default_bindings() {
        clear_all_bindings();

        map_key({ KeyMod::NONE, Key::ARROW_UP }, Command::ControlsUp);
        map_key({ KeyMod::NONE, Key::ARROW_DOWN }, Command::ControlsDown);
        map_key({ KeyMod::NONE, Key::ARROW_LEFT }, Command::ControlsLeft);
        map_key({ KeyMod::NONE, Key::ARROW_RIGHT }, Command::ControlsRight);
        map_key({ KeyMod::NONE, Key::Z }, Command::ControlsB);
        map_key({ KeyMod::NONE, Key::X }, Command::ControlsA);
        map_key({ KeyMod::NONE, Key::A }, Command::ControlsL);
        map_key({ KeyMod::NONE, Key::S }, Command::ControlsR);
        map_key({ KeyMod::NONE, Key::BACKSPACE }, Command::ControlsSelect);
        map_key({ KeyMod::NONE, Key::ENTER }, Command::ControlsStart);
        map_key({ KeyMod::NONE, Key::SPACE }, Command::ControlsSpeed);
        map_key({ KeyMod::NONE, Key::F12 }, Command::ControlsScreenCapture);
        map_key({ KeyMod::NONE, Key::NUMPAD_EIGHT }, Command::ControlsMotionUp);
        map_key({ KeyMod::NONE, Key::NUMPAD_TWO }, Command::ControlsMotionDown);
        map_key({ KeyMod::NONE, Key::NUMPAD_FOUR }, Command::ControlsMotionLeft);
        map_key({ KeyMod::NONE, Key::NUMPAD_SIX }, Command::ControlsMotionRight);
        
        map_key({ KeyMod::CTRL, Key::O }, Command::FileOpenGameboyAdvance);
        map_key({ KeyMod::CTRL, Key::L }, Command::FileLoad);
        map_key({ KeyMod::CTRL, Key::S }, Command::FileSave);
        map_key({ KeyMod::NONE, Key::F1 }, Command::FileLoadGame01);
        map_key({ KeyMod::NONE, Key::F2 }, Command::FileLoadGame02);
        map_key({ KeyMod::NONE, Key::F3 }, Command::FileLoadGame03);
        map_key({ KeyMod::NONE, Key::F4 }, Command::FileLoadGame04);
        map_key({ KeyMod::NONE, Key::F5 }, Command::FileLoadGame05);
        map_key({ KeyMod::NONE, Key::F6 }, Command::FileLoadGame06);
        map_key({ KeyMod::NONE, Key::F7 }, Command::FileLoadGame07);
        map_key({ KeyMod::NONE, Key::F8 }, Command::FileLoadGame08);
        map_key({ KeyMod::NONE, Key::F9 }, Command::FileLoadGame09);
        map_key({ KeyMod::NONE, Key::F10 }, Command::FileLoadGame10);
        map_key({ KeyMod::SHIFT, Key::F1 }, Command::FileSaveGame01);
        map_key({ KeyMod::SHIFT, Key::F2 }, Command::FileSaveGame02);
        map_key({ KeyMod::SHIFT, Key::F3 }, Command::FileSaveGame03);
        map_key({ KeyMod::SHIFT, Key::F4 }, Command::FileSaveGame04);
        map_key({ KeyMod::SHIFT, Key::F5 }, Command::FileSaveGame05);
        map_key({ KeyMod::SHIFT, Key::F6 }, Command::FileSaveGame06);
        map_key({ KeyMod::SHIFT, Key::F7 }, Command::FileSaveGame07);
        map_key({ KeyMod::SHIFT, Key::F8 }, Command::FileSaveGame08);
        map_key({ KeyMod::SHIFT, Key::F9 }, Command::FileSaveGame09);
        map_key({ KeyMod::SHIFT, Key::F10 }, Command::FileSaveGame10);
        map_key({ KeyMod::CTRL, Key::F1 }, Command::FileRecent01);
        map_key({ KeyMod::CTRL, Key::F2 }, Command::FileRecent02);
        map_key({ KeyMod::CTRL, Key::F3 }, Command::FileRecent03);
        map_key({ KeyMod::CTRL, Key::F4 }, Command::FileRecent04);
        map_key({ KeyMod::CTRL, Key::F5 }, Command::FileRecent05);
        map_key({ KeyMod::CTRL, Key::F6 }, Command::FileRecent06);
        map_key({ KeyMod::CTRL, Key::F7 }, Command::FileRecent07);
        map_key({ KeyMod::CTRL, Key::F8 }, Command::FileRecent08);
        map_key({ KeyMod::CTRL, Key::F9 }, Command::FileRecent09);
        map_key({ KeyMod::CTRL, Key::F10 }, Command::FileRecent10);
        map_key({ KeyMod::CTRL, Key::P }, Command::FilePause);
        map_key({ KeyMod::CTRL, Key::R }, Command::FileReset);
        map_key({ KeyMod::NONE, Key::ESCAPE }, Command::FileToggleMenu);
        map_key({ KeyMod::CTRL, Key::X }, Command::FileExit);
        map_key({ KeyMod::CTRL, Key::C }, Command::CheatsSearch);
        map_key({ KeyMod::CTRL, Key::N }, Command::ToolsNextFrame);
    }

    bool load_key_bindings() {
        //TODO(ches) load key bindings
        std::ifstream input_file(keybinds_file_path());

        bool result = true;

        if (!input_file.is_open()) {
            LOG_WARNING("Failed to open key bindings file for reading");
            return false;
        }

        std::string line;

        while (std::getline(input_file, line)) {
            const size_t equals = line.find('=');
            if (equals == std::string::npos) {
                LOG_WARNING("Error loading key bindings: Invalid config line, missing an equals");
                result = false;
                break;
            }
            if (equals == 0 || equals == line.length() - 1) {
                LOG_WARNING("Error loading key bindings: Missing a side of the equals");
                result = false;
                break;
            }

            bool found_command = false;
            Command command;
            for (const auto& [key, value] : COMMAND_NAMES) {
                if (strncmp(line.data(), value, equals) == 0) {
                    command = key;
                    found_command = true;
                    break;
                }
            }
            if (!found_command) {
                LOG_WARNING(std::format("Error loading key bindings: Could not find command {}", 
                    line.substr(0, equals)));
                result = false;
                break;
            }

            std::string binding_string = line.substr(equals+1);
            KeyBinding binding = binding_from_string(binding_string);
            if (binding.key == Key::NONE) {
                LOG_WARNING(std::format("Unknown binding {}", binding_string));
                result = false;
                break;
            }

            map_key(binding, command);
        }

        input_file.close();

        return result;
    }

    void save_key_bindings() {
        std::ofstream output_file(keybinds_file_path(), std::ios::trunc);

        if (!output_file.is_open()) {
            LOG_ERROR("Failed to open key bindings file for writing");
            return;
        }

        for (const auto& [key, value] : command_bindings) {
            const auto& command_name = COMMAND_NAMES.find(key);
            LOG_ASSERT(command_name != COMMAND_NAMES.end());

            output_file << command_name->second;
            output_file << "=";
            output_file << to_string(value);
            output_file << "\n";
        }
        output_file.close();
    }

    static void populate_cache(std::map<uint64_t, const char*>& cache) {
        //NOTE(ches) Look, I don't know, man.
        cache.emplace(static_cast<uint64_t>(Key::A), "A");
        cache.emplace(static_cast<uint64_t>(Key::B), "B");
        cache.emplace(static_cast<uint64_t>(Key::C), "C");
        cache.emplace(static_cast<uint64_t>(Key::D), "D");
        cache.emplace(static_cast<uint64_t>(Key::E), "E");
        cache.emplace(static_cast<uint64_t>(Key::F), "F");
        cache.emplace(static_cast<uint64_t>(Key::G), "G");
        cache.emplace(static_cast<uint64_t>(Key::H), "H");
        cache.emplace(static_cast<uint64_t>(Key::I), "I");
        cache.emplace(static_cast<uint64_t>(Key::J), "J");
        cache.emplace(static_cast<uint64_t>(Key::K), "K");
        cache.emplace(static_cast<uint64_t>(Key::L), "L");
        cache.emplace(static_cast<uint64_t>(Key::M), "M");
        cache.emplace(static_cast<uint64_t>(Key::N), "N");
        cache.emplace(static_cast<uint64_t>(Key::O), "O");
        cache.emplace(static_cast<uint64_t>(Key::P), "P");
        cache.emplace(static_cast<uint64_t>(Key::Q), "Q");
        cache.emplace(static_cast<uint64_t>(Key::R), "R");
        cache.emplace(static_cast<uint64_t>(Key::S), "S");
        cache.emplace(static_cast<uint64_t>(Key::T), "T");
        cache.emplace(static_cast<uint64_t>(Key::U), "U");
        cache.emplace(static_cast<uint64_t>(Key::V), "V");
        cache.emplace(static_cast<uint64_t>(Key::W), "W");
        cache.emplace(static_cast<uint64_t>(Key::X), "X");
        cache.emplace(static_cast<uint64_t>(Key::Y), "Y");
        cache.emplace(static_cast<uint64_t>(Key::Z), "Z");
        cache.emplace(static_cast<uint64_t>(Key::ZERO), "0");
        cache.emplace(static_cast<uint64_t>(Key::ONE), "1");
        cache.emplace(static_cast<uint64_t>(Key::TWO), "2");
        cache.emplace(static_cast<uint64_t>(Key::THREE), "3");
        cache.emplace(static_cast<uint64_t>(Key::FOUR), "4");
        cache.emplace(static_cast<uint64_t>(Key::FIVE), "5");
        cache.emplace(static_cast<uint64_t>(Key::SIX), "6");
        cache.emplace(static_cast<uint64_t>(Key::SEVEN), "7");
        cache.emplace(static_cast<uint64_t>(Key::EIGHT), "8");
        cache.emplace(static_cast<uint64_t>(Key::NINE), "9");
        cache.emplace(static_cast<uint64_t>(Key::NUMPAD_ZERO), "NumPad0");
        cache.emplace(static_cast<uint64_t>(Key::NUMPAD_ONE), "NumPad1");
        cache.emplace(static_cast<uint64_t>(Key::NUMPAD_TWO), "NumPad2");
        cache.emplace(static_cast<uint64_t>(Key::NUMPAD_THREE), "NumPad3");
        cache.emplace(static_cast<uint64_t>(Key::NUMPAD_FOUR), "NumPad4");
        cache.emplace(static_cast<uint64_t>(Key::NUMPAD_FIVE), "NumPad5");
        cache.emplace(static_cast<uint64_t>(Key::NUMPAD_SIX), "NumPad6");
        cache.emplace(static_cast<uint64_t>(Key::NUMPAD_SEVEN), "NumPad7");
        cache.emplace(static_cast<uint64_t>(Key::NUMPAD_EIGHT), "NumPad8");
        cache.emplace(static_cast<uint64_t>(Key::NUMPAD_NINE), "NumPad9");
        cache.emplace(static_cast<uint64_t>(Key::NUM_LOCK), "NumLock");
        cache.emplace(static_cast<uint64_t>(Key::NUMPAD_ADD), "NumPad+");
        cache.emplace(static_cast<uint64_t>(Key::NUMPAD_DIVIDE), "NumPad/");
        cache.emplace(static_cast<uint64_t>(Key::NUMPAD_ENTER), "NumPadEnter");
        cache.emplace(static_cast<uint64_t>(Key::NUMPAD_MULTIPLY), "NumPad*");
        cache.emplace(static_cast<uint64_t>(Key::NUMPAD_PERIOD), "NumPad.");
        cache.emplace(static_cast<uint64_t>(Key::NUMPAD_SUBTRACT), "NumPad-");
        cache.emplace(static_cast<uint64_t>(Key::AMPERSAND), "&");
        cache.emplace(static_cast<uint64_t>(Key::APOSTROPHE), "`");
        cache.emplace(static_cast<uint64_t>(Key::ASTERISK), "*");
        cache.emplace(static_cast<uint64_t>(Key::AT), "@");
        cache.emplace(static_cast<uint64_t>(Key::BACK_SLASH), "\\");
        cache.emplace(static_cast<uint64_t>(Key::CARET), "^");
        cache.emplace(static_cast<uint64_t>(Key::COLON), ":");
        cache.emplace(static_cast<uint64_t>(Key::COMMA), ",");
        cache.emplace(static_cast<uint64_t>(Key::DOLLAR), "$");
        cache.emplace(static_cast<uint64_t>(Key::DOUBLE_QUOTE), "\"");
        cache.emplace(static_cast<uint64_t>(Key::EQUALS), "=");
        cache.emplace(static_cast<uint64_t>(Key::EURO), "Euro");
        cache.emplace(static_cast<uint64_t>(Key::EXCLAMATION_MARK), "!");
        cache.emplace(static_cast<uint64_t>(Key::FORWARD_SLASH), "/");
        cache.emplace(static_cast<uint64_t>(Key::GREATER_THAN), ">");
        cache.emplace(static_cast<uint64_t>(Key::LEFT_BRACE), "{");
        cache.emplace(static_cast<uint64_t>(Key::LEFT_BRACKET), "[");
        cache.emplace(static_cast<uint64_t>(Key::LEFT_PARENTHESES), "(");
        cache.emplace(static_cast<uint64_t>(Key::LESS_THAN), "<");
        cache.emplace(static_cast<uint64_t>(Key::MINUS), "-");
        cache.emplace(static_cast<uint64_t>(Key::NUMBER_SIGN), "#");
        cache.emplace(static_cast<uint64_t>(Key::PERCENT), "%");
        cache.emplace(static_cast<uint64_t>(Key::PERIOD), ".");
        cache.emplace(static_cast<uint64_t>(Key::PIPE), "|");
        cache.emplace(static_cast<uint64_t>(Key::PLUS), "+");
        cache.emplace(static_cast<uint64_t>(Key::POUND), "Pound");
        cache.emplace(static_cast<uint64_t>(Key::QUESTION_MARK), "?");
        cache.emplace(static_cast<uint64_t>(Key::RIGHT_BRACE), "}");
        cache.emplace(static_cast<uint64_t>(Key::RIGHT_BRACKET), "]");
        cache.emplace(static_cast<uint64_t>(Key::RIGHT_PARENTHESES), ")");
        cache.emplace(static_cast<uint64_t>(Key::SEMICOLON), ";");
        cache.emplace(static_cast<uint64_t>(Key::SINGLE_QUOTE), "'");
        cache.emplace(static_cast<uint64_t>(Key::UNDERSCORE), "_");
        cache.emplace(static_cast<uint64_t>(Key::ARROW_DOWN), "Down");
        cache.emplace(static_cast<uint64_t>(Key::ARROW_LEFT), "Left");
        cache.emplace(static_cast<uint64_t>(Key::ARROW_RIGHT), "Right");
        cache.emplace(static_cast<uint64_t>(Key::ARROW_UP), "Up");
        cache.emplace(static_cast<uint64_t>(Key::BACKSPACE), "Backspace");
        cache.emplace(static_cast<uint64_t>(Key::DELETE), "Delete");
        cache.emplace(static_cast<uint64_t>(Key::END), "End");
        cache.emplace(static_cast<uint64_t>(Key::ENTER), "Enter");
        cache.emplace(static_cast<uint64_t>(Key::ESCAPE), "Esc");
        cache.emplace(static_cast<uint64_t>(Key::HOME), "Home");
        cache.emplace(static_cast<uint64_t>(Key::INSERT), "Insert");
        cache.emplace(static_cast<uint64_t>(Key::MENU), "Menu");
        cache.emplace(static_cast<uint64_t>(Key::PAGE_DOWN), "PageDown");
        cache.emplace(static_cast<uint64_t>(Key::PAGE_UP), "PageUp");
        cache.emplace(static_cast<uint64_t>(Key::SPACE), "Space");
        cache.emplace(static_cast<uint64_t>(Key::SUPER), "Super");
        cache.emplace(static_cast<uint64_t>(Key::TAB), "Tab");
        cache.emplace(static_cast<uint64_t>(Key::F1), "F1");
        cache.emplace(static_cast<uint64_t>(Key::F2), "F2");
        cache.emplace(static_cast<uint64_t>(Key::F3), "F3");
        cache.emplace(static_cast<uint64_t>(Key::F4), "F4");
        cache.emplace(static_cast<uint64_t>(Key::F5), "F5");
        cache.emplace(static_cast<uint64_t>(Key::F6), "F6");
        cache.emplace(static_cast<uint64_t>(Key::F7), "F7");
        cache.emplace(static_cast<uint64_t>(Key::F8), "F8");
        cache.emplace(static_cast<uint64_t>(Key::F9), "F9");
        cache.emplace(static_cast<uint64_t>(Key::F10), "F10");
        cache.emplace(static_cast<uint64_t>(Key::F11), "F11");
        cache.emplace(static_cast<uint64_t>(Key::F12), "F12");
        cache.emplace(static_cast<uint64_t>(Key::GAMEPAD_BACK), "GamePadBack");
        cache.emplace(static_cast<uint64_t>(Key::GAMEPAD_DPAD_DOWN), "GamepadDPadDown");
        cache.emplace(static_cast<uint64_t>(Key::GAMEPAD_DPAD_LEFT), "GamepadDPadLeft");
        cache.emplace(static_cast<uint64_t>(Key::GAMEPAD_DPAD_RIGHT), "GamepadDPadRight");
        cache.emplace(static_cast<uint64_t>(Key::GAMEPAD_DPAD_UP), "GamepadDPadUp");
        cache.emplace(static_cast<uint64_t>(Key::GAMEPAD_FACE_DOWN), "GamepadFaceDown");
        cache.emplace(static_cast<uint64_t>(Key::GAMEPAD_FACE_LEFT), "GamepadFaceLeft");
        cache.emplace(static_cast<uint64_t>(Key::GAMEPAD_FACE_RIGHT), "GamepadFaceRight");
        cache.emplace(static_cast<uint64_t>(Key::GAMEPAD_FACE_UP), "GamepadFaceUp");
        cache.emplace(static_cast<uint64_t>(Key::GAMEPAD_L1), "GamepadL1");
        cache.emplace(static_cast<uint64_t>(Key::GAMEPAD_L2), "GamepadL2");
        cache.emplace(static_cast<uint64_t>(Key::GAMEPAD_L3), "GamepadL3");
        cache.emplace(static_cast<uint64_t>(Key::GAMEPAD_LSTICK_BUTTON), "GamepadLStickButton");
        cache.emplace(static_cast<uint64_t>(Key::GAMEPAD_LSTICK_DOWN), "GamepadLStickDown");
        cache.emplace(static_cast<uint64_t>(Key::GAMEPAD_LSTICK_LEFT), "GamepadLStickLeft");
        cache.emplace(static_cast<uint64_t>(Key::GAMEPAD_LSTICK_RIGHT), "GamepadLStickRight");
        cache.emplace(static_cast<uint64_t>(Key::GAMEPAD_LSTICK_UP), "GamepadLStickUp");
        cache.emplace(static_cast<uint64_t>(Key::GAMEPAD_R1), "GamepadR1");
        cache.emplace(static_cast<uint64_t>(Key::GAMEPAD_R2), "GamepadR2");
        cache.emplace(static_cast<uint64_t>(Key::GAMEPAD_R3), "GamepadR3");
        cache.emplace(static_cast<uint64_t>(Key::GAMEPAD_RSTICK_BUTTON), "GamepadRStickButton");
        cache.emplace(static_cast<uint64_t>(Key::GAMEPAD_RSTICK_DOWN), "GamepadRStickDown");
        cache.emplace(static_cast<uint64_t>(Key::GAMEPAD_RSTICK_LEFT), "GamepadRStickLeft");
        cache.emplace(static_cast<uint64_t>(Key::GAMEPAD_RSTICK_RIGHT), "GamepadRStickRight");
        cache.emplace(static_cast<uint64_t>(Key::GAMEPAD_RSTICK_UP), "GamepadRStickUp");
        cache.emplace(static_cast<uint64_t>(Key::GAMEPAD_SELECT), "GamepadSelect");
        cache.emplace(static_cast<uint64_t>(Key::GAMEPAD_START), "GamepadStart");

        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::A), "Shift+A");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::B), "Shift+B");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::C), "Shift+C");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::D), "Shift+D");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::E), "Shift+E");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::F), "Shift+F");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::G), "Shift+G");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::H), "Shift+H");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::I), "Shift+I");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::J), "Shift+J");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::K), "Shift+K");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::L), "Shift+L");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::M), "Shift+M");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::N), "Shift+N");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::O), "Shift+O");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::P), "Shift+P");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::Q), "Shift+Q");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::R), "Shift+R");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::S), "Shift+S");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::T), "Shift+T");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::U), "Shift+U");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::V), "Shift+V");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::W), "Shift+W");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::X), "Shift+X");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::Y), "Shift+Y");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::Z), "Shift+Z");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::ZERO), "Shift+0");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::ONE), "Shift+1");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::TWO), "Shift+2");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::THREE), "Shift+3");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::FOUR), "Shift+4");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::FIVE), "Shift+5");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::SIX), "Shift+6");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::SEVEN), "Shift+7");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::EIGHT), "Shift+8");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::NINE), "Shift+9");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::NUMPAD_ZERO), "Shift+NumPad0");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::NUMPAD_ONE), "Shift+NumPad1");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::NUMPAD_TWO), "Shift+NumPad2");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::NUMPAD_THREE), "Shift+NumPad3");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::NUMPAD_FOUR), "Shift+NumPad4");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::NUMPAD_FIVE), "Shift+NumPad5");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::NUMPAD_SIX), "Shift+NumPad6");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::NUMPAD_SEVEN), "Shift+NumPad7");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::NUMPAD_EIGHT), "Shift+NumPad8");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::NUMPAD_NINE), "Shift+NumPad9");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::NUM_LOCK), "Shift+NumLock");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::NUMPAD_ADD), "Shift+NumPad+");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::NUMPAD_DIVIDE), "Shift+NumPad/");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::NUMPAD_ENTER), "Shift+NumPadEnter");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::NUMPAD_MULTIPLY), "Shift+NumPad*");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::NUMPAD_PERIOD), "Shift+NumPad.");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::NUMPAD_SUBTRACT), "Shift+NumPad-");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::AMPERSAND), "Shift+&");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::APOSTROPHE), "Shift+`");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::ASTERISK), "Shift+*");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::AT), "Shift+@");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::BACK_SLASH), "Shift+\\");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::CARET), "Shift+^");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::COLON), "Shift+:");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::COMMA), "Shift+,");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::DOLLAR), "Shift+$");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::DOUBLE_QUOTE), "Shift+\"");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::EQUALS), "Shift+=");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::EURO), "Shift+Euro");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::EXCLAMATION_MARK), "Shift+!");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::FORWARD_SLASH), "Shift+/");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::GREATER_THAN), "Shift+>");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::LEFT_BRACE), "Shift+{");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::LEFT_BRACKET), "Shift+[");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::LEFT_PARENTHESES), "Shift+(");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::LESS_THAN), "Shift+<");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::MINUS), "Shift+-");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::NUMBER_SIGN), "Shift+#");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::PERCENT), "Shift+%");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::PERIOD), "Shift+.");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::PIPE), "Shift+|");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::PLUS), "Shift++");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::POUND), "Shift+Pound");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::QUESTION_MARK), "Shift+?");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::RIGHT_BRACE), "Shift+}");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::RIGHT_BRACKET), "Shift+]");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::RIGHT_PARENTHESES), "Shift+)");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::SEMICOLON), "Shift+;");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::SINGLE_QUOTE), "Shift+'");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::UNDERSCORE), "Shift+_");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::ARROW_DOWN), "Shift+Down");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::ARROW_LEFT), "Shift+Left");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::ARROW_RIGHT), "Shift+Right");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::ARROW_UP), "Shift+Up");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::BACKSPACE), "Shift+Backspace");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::DELETE), "Shift+Delete");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::END), "Shift+End");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::ENTER), "Shift+Enter");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::ESCAPE), "Shift+Esc");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::HOME), "Shift+Home");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::INSERT), "Shift+Insert");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::MENU), "Shift+Menu");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::PAGE_DOWN), "Shift+PageDown");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::PAGE_UP), "Shift+PageUp");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::SPACE), "Shift+Space");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::SUPER), "Shift+Super");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::TAB), "Shift+Tab");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::F1), "Shift+F1");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::F2), "Shift+F2");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::F3), "Shift+F3");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::F4), "Shift+F4");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::F5), "Shift+F5");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::F6), "Shift+F6");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::F7), "Shift+F7");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::F8), "Shift+F8");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::F9), "Shift+F9");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::F10), "Shift+F10");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::F11), "Shift+F11");
        cache.emplace(static_cast<uint64_t>(KeyMod::SHIFT) << 32 | static_cast<uint64_t>(Key::F12), "Shift+F12");

        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::A), "Ctrl+A");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::B), "Ctrl+B");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::C), "Ctrl+C");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::D), "Ctrl+D");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::E), "Ctrl+E");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::F), "Ctrl+F");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::G), "Ctrl+G");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::H), "Ctrl+H");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::I), "Ctrl+I");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::J), "Ctrl+J");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::K), "Ctrl+K");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::L), "Ctrl+L");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::M), "Ctrl+M");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::N), "Ctrl+N");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::O), "Ctrl+O");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::P), "Ctrl+P");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::Q), "Ctrl+Q");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::R), "Ctrl+R");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::S), "Ctrl+S");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::T), "Ctrl+T");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::U), "Ctrl+U");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::V), "Ctrl+V");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::W), "Ctrl+W");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::X), "Ctrl+X");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::Y), "Ctrl+Y");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::Z), "Ctrl+Z");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::ZERO), "Ctrl+0");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::ONE), "Ctrl+1");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::TWO), "Ctrl+2");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::THREE), "Ctrl+3");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::FOUR), "Ctrl+4");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::FIVE), "Ctrl+5");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::SIX), "Ctrl+6");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::SEVEN), "Ctrl+7");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::EIGHT), "Ctrl+8");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::NINE), "Ctrl+9");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::NUMPAD_ZERO), "Ctrl+NumPad0");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::NUMPAD_ONE), "Ctrl+NumPad1");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::NUMPAD_TWO), "Ctrl+NumPad2");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::NUMPAD_THREE), "Ctrl+NumPad3");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::NUMPAD_FOUR), "Ctrl+NumPad4");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::NUMPAD_FIVE), "Ctrl+NumPad5");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::NUMPAD_SIX), "Ctrl+NumPad6");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::NUMPAD_SEVEN), "Ctrl+NumPad7");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::NUMPAD_EIGHT), "Ctrl+NumPad8");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::NUMPAD_NINE), "Ctrl+NumPad9");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::NUM_LOCK), "Ctrl+NumLock");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::NUMPAD_ADD), "Ctrl+NumPad+");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::NUMPAD_DIVIDE), "Ctrl+NumPad/");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::NUMPAD_ENTER), "Ctrl+NumPadEnter");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::NUMPAD_MULTIPLY), "Ctrl+NumPad*");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::NUMPAD_PERIOD), "Ctrl+NumPad.");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::NUMPAD_SUBTRACT), "Ctrl+NumPad-");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::AMPERSAND), "Ctrl+&");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::APOSTROPHE), "Ctrl+`");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::ASTERISK), "Ctrl+*");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::AT), "Ctrl+@");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::BACK_SLASH), "Ctrl+\\");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::CARET), "Ctrl+^");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::COLON), "Ctrl+:");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::COMMA), "Ctrl+,");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::DOLLAR), "Ctrl+$");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::DOUBLE_QUOTE), "Ctrl+\"");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::EQUALS), "Ctrl+=");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::EURO), "Ctrl+Euro");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::EXCLAMATION_MARK), "Ctrl+!");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::FORWARD_SLASH), "Ctrl+/");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::GREATER_THAN), "Ctrl+>");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::LEFT_BRACE), "Ctrl+{");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::LEFT_BRACKET), "Ctrl+[");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::LEFT_PARENTHESES), "Ctrl+(");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::LESS_THAN), "Ctrl+<");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::MINUS), "Ctrl+-");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::NUMBER_SIGN), "Ctrl+#");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::PERCENT), "Ctrl+%");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::PERIOD), "Ctrl+.");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::PIPE), "Ctrl+|");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::PLUS), "Ctrl++");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::POUND), "Ctrl+Pound");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::QUESTION_MARK), "Ctrl+?");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::RIGHT_BRACE), "Ctrl+}");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::RIGHT_BRACKET), "Ctrl+]");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::RIGHT_PARENTHESES), "Ctrl+)");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::SEMICOLON), "Ctrl+;");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::SINGLE_QUOTE), "Ctrl+'");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::UNDERSCORE), "Ctrl+_");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::ARROW_DOWN), "Ctrl+Down");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::ARROW_LEFT), "Ctrl+Left");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::ARROW_RIGHT), "Ctrl+Right");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::ARROW_UP), "Ctrl+Up");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::BACKSPACE), "Ctrl+Backspace");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::DELETE), "Ctrl+Delete");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::END), "Ctrl+End");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::ENTER), "Ctrl+Enter");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::ESCAPE), "Ctrl+Esc");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::HOME), "Ctrl+Home");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::INSERT), "Ctrl+Insert");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::MENU), "Ctrl+Menu");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::PAGE_DOWN), "Ctrl+PageDown");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::PAGE_UP), "Ctrl+PageUp");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::SPACE), "Ctrl+Space");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::SUPER), "Ctrl+Super");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::TAB), "Ctrl+Tab");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::F1), "Ctrl+F1");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::F2), "Ctrl+F2");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::F3), "Ctrl+F3");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::F4), "Ctrl+F4");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::F5), "Ctrl+F5");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::F6), "Ctrl+F6");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::F7), "Ctrl+F7");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::F8), "Ctrl+F8");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::F9), "Ctrl+F9");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::F10), "Ctrl+F10");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::F11), "Ctrl+F11");
        cache.emplace(static_cast<uint64_t>(KeyMod::CTRL) << 32 | static_cast<uint64_t>(Key::F12), "Ctrl+F12");

        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::A), "Alt+A");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::B), "Alt+B");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::C), "Alt+C");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::D), "Alt+D");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::E), "Alt+E");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::F), "Alt+F");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::G), "Alt+G");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::H), "Alt+H");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::I), "Alt+I");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::J), "Alt+J");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::K), "Alt+K");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::L), "Alt+L");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::M), "Alt+M");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::N), "Alt+N");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::O), "Alt+O");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::P), "Alt+P");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::Q), "Alt+Q");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::R), "Alt+R");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::S), "Alt+S");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::T), "Alt+T");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::U), "Alt+U");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::V), "Alt+V");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::W), "Alt+W");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::X), "Alt+X");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::Y), "Alt+Y");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::Z), "Alt+Z");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::ZERO), "Alt+0");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::ONE), "Alt+1");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::TWO), "Alt+2");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::THREE), "Alt+3");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::FOUR), "Alt+4");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::FIVE), "Alt+5");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::SIX), "Alt+6");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::SEVEN), "Alt+7");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::EIGHT), "Alt+8");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::NINE), "Alt+9");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::NUMPAD_ZERO), "Alt+NumPad0");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::NUMPAD_ONE), "Alt+NumPad1");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::NUMPAD_TWO), "Alt+NumPad2");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::NUMPAD_THREE), "Alt+NumPad3");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::NUMPAD_FOUR), "Alt+NumPad4");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::NUMPAD_FIVE), "Alt+NumPad5");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::NUMPAD_SIX), "Alt+NumPad6");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::NUMPAD_SEVEN), "Alt+NumPad7");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::NUMPAD_EIGHT), "Alt+NumPad8");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::NUMPAD_NINE), "Alt+NumPad9");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::NUM_LOCK), "Alt+NumLock");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::NUMPAD_ADD), "Alt+NumPad+");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::NUMPAD_DIVIDE), "Alt+NumPad/");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::NUMPAD_ENTER), "Alt+NumPadEnter");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::NUMPAD_MULTIPLY), "Alt+NumPad*");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::NUMPAD_PERIOD), "Alt+NumPad.");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::NUMPAD_SUBTRACT), "Alt+NumPad-");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::AMPERSAND), "Alt+&");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::APOSTROPHE), "Alt+`");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::ASTERISK), "Alt+*");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::AT), "Alt+@");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::BACK_SLASH), "Alt+\\");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::CARET), "Alt+^");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::COLON), "Alt+:");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::COMMA), "Alt+,");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::DOLLAR), "Alt+$");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::DOUBLE_QUOTE), "Alt+\"");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::EQUALS), "Alt+=");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::EURO), "Alt+Euro");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::EXCLAMATION_MARK), "Alt+!");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::FORWARD_SLASH), "Alt+/");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::GREATER_THAN), "Alt+>");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::LEFT_BRACE), "Alt+{");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::LEFT_BRACKET), "Alt+[");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::LEFT_PARENTHESES), "Alt+(");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::LESS_THAN), "Alt+<");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::MINUS), "Alt+-");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::NUMBER_SIGN), "Alt+#");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::PERCENT), "Alt+%");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::PERIOD), "Alt+.");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::PIPE), "Alt+|");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::PLUS), "Alt++");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::POUND), "Alt+Pound");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::QUESTION_MARK), "Alt+?");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::RIGHT_BRACE), "Alt+}");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::RIGHT_BRACKET), "Alt+]");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::RIGHT_PARENTHESES), "Alt+)");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::SEMICOLON), "Alt+;");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::SINGLE_QUOTE), "Alt+'");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::UNDERSCORE), "Alt+_");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::ARROW_DOWN), "Alt+Down");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::ARROW_LEFT), "Alt+Left");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::ARROW_RIGHT), "Alt+Right");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::ARROW_UP), "Alt+Up");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::BACKSPACE), "Alt+Backspace");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::DELETE), "Alt+Delete");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::END), "Alt+End");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::ENTER), "Alt+Enter");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::ESCAPE), "Alt+Esc");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::HOME), "Alt+Home");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::INSERT), "Alt+Insert");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::MENU), "Alt+Menu");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::PAGE_DOWN), "Alt+PageDown");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::PAGE_UP), "Alt+PageUp");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::SPACE), "Alt+Space");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::SUPER), "Alt+Super");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::TAB), "Alt+Tab");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::F1), "Alt+F1");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::F2), "Alt+F2");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::F3), "Alt+F3");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::F4), "Alt+F4");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::F5), "Alt+F5");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::F6), "Alt+F6");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::F7), "Alt+F7");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::F8), "Alt+F8");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::F9), "Alt+F9");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::F10), "Alt+F10");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::F11), "Alt+F11");
        cache.emplace(static_cast<uint64_t>(KeyMod::ALT) << 32 | static_cast<uint64_t>(Key::F12), "Alt+F12");
    }
}