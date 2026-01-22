#pragma once

#include <cstdint>

namespace emulator {
	using Wire1 = uint8_t;
	using Wire2 = uint8_t;
	using Wire8 = uint8_t;
	using Wire16 = uint16_t;
	using Wire32 = uint32_t;

	void set_bit(Wire1* wire, bool on);
	void set_bit(Wire2* wire, int bit, bool on);
	void set_bit(Wire8* wire, int bit, bool on);
	void set_bit(Wire16* wire, int bit, bool on);
	void set_bit(Wire32* wire, int bit, bool on);

	bool get_bit(Wire1* wire);
	bool get_bit(Wire2* wire, int bit);
	bool get_bit(Wire8* wire, int bit);
	bool get_bit(Wire16* wire, int bit);
	bool get_bit(Wire32* wire, int bit);

// Annotation used to indicate signal coming into a component, does nothing.
#define WIRE_INCOMING
// Annotation used to indicate signal coming out of a component, does nothing.
#define WIRE_OUTGOING
// Annotation used to indicate signal internal to a component, does nothing.
#define WIRE_INTERNAL

}