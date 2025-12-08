#include "gtest/gtest.h"

#include "gui/key_binding.h"

TEST(KeyBindingTest, SerializationRoundTrip)
{
	for (uint32_t key_int = 0; key_int < static_cast<uint32_t>(gui::Key::_count); key_int++) {
		const gui::Key key = static_cast<gui::Key>(key_int);
		gui::KeyBinding binding = { gui::KeyMod::NONE, key };

		std::string string_form = std::string(gui::to_string(binding));
		gui::KeyBinding mapped = gui::binding_from_string(string_form);

		ASSERT_EQ(gui::KeyMod::NONE, mapped.mod) 
			<< "Expected to see a mod of NONE but got " 
			<< (mapped.mod == gui::KeyMod::_count ? "_count" : gui::to_string(mapped.mod))
			<< " when trying test case None+" << gui::to_string(key);
		ASSERT_EQ(key, mapped.key) << "Expected to see a key of " 
			<< gui::to_string(key) << " but got " 
			<< (mapped.key == gui::Key::_count ? "_count" : gui::to_string(mapped.key))
			<< " when trying test case None+" << gui::to_string(key);
	}

	for (uint32_t mod_int = 1; mod_int < static_cast<uint32_t>(gui::KeyMod::_count); mod_int++) {
		const gui::KeyMod mod = static_cast<gui::KeyMod>(mod_int);
		for (uint32_t key_int = 1; key_int < static_cast<uint32_t>(gui::Key::GAMEPAD_BACK); key_int++) {
			const gui::Key key = static_cast<gui::Key>(key_int);
			gui::KeyBinding binding = { mod, key };

			std::string string_form = std::string(gui::to_string(binding));
			gui::KeyBinding mapped = gui::binding_from_string(string_form);

			ASSERT_EQ(mod, mapped.mod) << "Expected to see a mod of "
				<< gui::to_string(mod) << " but got "
				<< (mapped.mod == gui::KeyMod::_count ? "_count" : gui::to_string(mapped.mod))
				<< " when trying test case " << gui::to_string(mod) << "+" << gui::to_string(key);
			ASSERT_EQ(key, mapped.key) << "Expected to see a key of "
				<< gui::to_string(key) << " but got "
				<< (mapped.key == gui::Key::_count ? "_count" : gui::to_string(mapped.key))
				<< " when trying test case " << gui::to_string(mod) << "+" << gui::to_string(key);
		}
	}

	for (uint32_t mod_int = 1; mod_int < static_cast<uint32_t>(gui::KeyMod::_count); mod_int++) {
		const gui::KeyMod mod = static_cast<gui::KeyMod>(mod_int);
		for (uint32_t key_int = static_cast<uint32_t>(gui::Key::GAMEPAD_BACK); key_int < static_cast<uint32_t>(gui::Key::_count); key_int++) {
			const gui::Key key = static_cast<gui::Key>(key_int);
			gui::KeyBinding binding = { mod, key };

			std::string string_form = std::string(gui::to_string(binding));
			gui::KeyBinding mapped = gui::binding_from_string(string_form);

			ASSERT_EQ("", string_form) << "Expected an empty string but got " 
				<< string_form;
			ASSERT_EQ(gui::KeyMod::NONE, mapped.mod)
				<< "Expected to see a mod of NONE but got "
				<< (mapped.mod == gui::KeyMod::_count ? "_count" : gui::to_string(mapped.mod))
				<< " when trying test case " << gui::to_string(mod) << "+" << gui::to_string(key);
			ASSERT_EQ(gui::Key::NONE, mapped.key)
				<< "Expected to see a key of NONE but got "
				<< (mapped.key == gui::Key::_count ? "_count" : gui::to_string(mapped.key))
				<< " when trying test case " << gui::to_string(mod) << "+" << gui::to_string(key);
		}
	}

}
