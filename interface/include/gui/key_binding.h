#pragma once

#include <cstdint>
#include <map>
#include <string>

#include "brain/commands.h"

namespace gui {
    using brain::Command;

	enum class Key : uint32_t {
        NONE,
        // Letters
        A,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        W,
        X,
        Y,
        Z,
        // Numbers
        ZERO,
        ONE,
        TWO,
        THREE,
        FOUR,
        FIVE,
        SIX,
        SEVEN,
        EIGHT,
        NINE,
        // Numpad
        NUMPAD_ZERO,
        NUMPAD_ONE,
        NUMPAD_TWO,
        NUMPAD_THREE,
        NUMPAD_FOUR,
        NUMPAD_FIVE,
        NUMPAD_SIX,
        NUMPAD_SEVEN,
        NUMPAD_EIGHT,
        NUMPAD_NINE,
        NUM_LOCK,
        NUMPAD_ADD,
        NUMPAD_DIVIDE,
        NUMPAD_ENTER,
        NUMPAD_MULTIPLY,
        NUMPAD_PERIOD,
        NUMPAD_SUBTRACT,
        // Symbols
        APOSTROPHE,
        BACK_SLASH,
        COMMA,
        EQUALS,
        FORWARD_SLASH,
        GRAVE,
        LEFT_BRACKET,
        MINUS,
        PERIOD,
        RIGHT_BRACKET,
        SEMICOLON,
        // Special keys
        ARROW_DOWN,
        ARROW_LEFT,
        ARROW_RIGHT,
        ARROW_UP,
        BACKSPACE,
        DELETE,
        END,
        ENTER,
        ESCAPE,
        HOME,
        INSERT,
        MENU,
        PAGE_DOWN,
        PAGE_UP,
        SPACE,
        SUPER,
        TAB,
        // Function keys
        F1,
        F2,
        F3,
        F4,
        F5,
        F6,
        F7,
        F8,
        F9,
        F10,
        F11,
        F12,
        // Gamepad
        GAMEPAD_BACK,
        GAMEPAD_DPAD_DOWN,
        GAMEPAD_DPAD_LEFT,
        GAMEPAD_DPAD_RIGHT,
        GAMEPAD_DPAD_UP,
        GAMEPAD_FACE_DOWN,
        GAMEPAD_FACE_LEFT,
        GAMEPAD_FACE_RIGHT,
        GAMEPAD_FACE_UP,
        GAMEPAD_L1,
        GAMEPAD_L2,
        GAMEPAD_L3,
        GAMEPAD_LSTICK_BUTTON,
        GAMEPAD_LSTICK_DOWN,
        GAMEPAD_LSTICK_LEFT,
        GAMEPAD_LSTICK_RIGHT,
        GAMEPAD_LSTICK_UP,
        GAMEPAD_R1,
        GAMEPAD_R2,
        GAMEPAD_R3,
        GAMEPAD_RSTICK_BUTTON,
        GAMEPAD_RSTICK_DOWN,
        GAMEPAD_RSTICK_LEFT,
        GAMEPAD_RSTICK_RIGHT,
        GAMEPAD_RSTICK_UP,
        GAMEPAD_SELECT,
        GAMEPAD_START,
        _count,
    };

    enum class KeyMod : uint32_t {
        NONE,
        SHIFT,
        CTRL,
        ALT,
        _count,
    };

	struct KeyBinding {
        KeyMod mod;
        Key key;

        uint64_t to_map_key() const;
	};

    /// <summary>
    /// Mapping of command back to the key binding. Key bindings to commands
    /// are one-to-one mappings. This map should not be modified manually.
    /// </summary>
    extern std::map<Command, KeyBinding> command_bindings;
    /// <summary>
    /// Mapping of key bindings to commands. Key bindings to commands are 
    /// one-to-one mappings. This map should not be modified manually.
    /// </summary>
    extern std::map<uint64_t, Command> key_bindings;

    const char* to_string(const Key key);
    Key key_from_string(const char* text, const size_t length);
    const char* to_string(const KeyMod mod);
    KeyMod mod_from_string(const char* text, const size_t length);
    const char* to_string(const KeyBinding binding);

    /// <summary>
    /// Convert from a string to key binding. Invalid bindings will have values
    /// of NONE.
    /// </summary>
    /// <param name="binding_string">The string to convert from.</param>
    /// <returns>The key binding that is written as the provided string.</returns>
    KeyBinding binding_from_string(const std::string binding_string);

    /// <summary>
    /// Map a key to a command. These bindings are one-to-one, so if 
    /// a key or command already have mappings they will be unbound first.
    /// </summary>
    /// <param name="key">The key.</param>
    /// <param name="command">The command.</param>
    void map_key(const KeyBinding key, const Command command);
    void unmap_key(const KeyBinding key);
    void unmap_command(const Command command);
    
    /// <summary>
    /// Check if a command has a key bound to it.
    /// </summary>
    /// <param name="command">The command.</param>
    /// <returns>Whether we have a key binding.</returns>
    bool has_binding(const Command command);
    
    /// <summary>
    /// Check if a key has a command bound to it.
    /// </summary>
    /// <param name="key">The key.</param>
    /// <returns>Whether we have a key binding.</returns>
    bool has_binding(const KeyBinding key);

    /// <summary>
    /// Fetch the binding, assuming the command has one.
    /// </summary>
    /// <param name="command">The command to find a key binding for.</param>
    /// <returns>The key binding, falls back to None+None if not mapped.</returns>
    KeyBinding get_binding(const Command command);

    /// <summary>
    /// Fetch the binding string, or nullptr if there is not one.
    /// </summary>
    /// <param name="command">The command to find a key binding for.</param>
    /// <returns>The key binding, falls back to nullptr if not mapped.</returns>
    const char* get_binding_text(const Command command);
    
    /// <summary>
    /// Fetch the binding, assuming the key has one.
    /// </summary>
    /// <param name="key">The key to find a binding for.</param>
    /// <returns>The command, or _count as a fallback if not mapped.</returns>
    Command get_binding(const KeyBinding key);

    /// <summary>
    /// Clear out all key bindings.
    /// </summary>
    void clear_all_bindings();

    /// <summary>
    /// Clear out all bindings and set up the default bindings.
    /// </summary>
    void set_default_bindings();

    /// <summary>
    /// Attempt to load key bindings from file. If we fail to 
    /// load bindings, they might not be in a valid state and should probably
    /// be reset to the defaults.
    /// </summary>
    /// <returns>Whether we successfully loaded bindings.</returns>
    bool load_key_bindings();

    /// <summary>
    /// Save all key bindings to file.
    /// </summary>
    void save_key_bindings();
}