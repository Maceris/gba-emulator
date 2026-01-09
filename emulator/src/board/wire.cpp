#include "board/wire.h"

#include "debugging/logger.h"

namespace emulator {

	void set_bit(Wire1* wire, bool on) {
		LOG_ASSERT(wire != nullptr);

		if (on) {
			*wire = 1;
		}
		else {
			*wire = 0;
		}
	}

	void set_bit(Wire2* wire, int bit, bool on) {
		LOG_ASSERT(wire != nullptr);
		LOG_ASSERT(bit >= 0 && bit <= 1
			&& "Bit must be between 0 and 1, inclusive");

		if (on) {
			*wire |= 1 << bit;
		}
		else {
			*wire &= ~(1 << bit);
		}
	}

	void set_bit(Wire32* wire, int bit, bool on) {
		LOG_ASSERT(wire != nullptr);
		LOG_ASSERT(bit >= 0 && bit <= 31
			&& "Bit must be between 0 and 31, inclusive");

		if (on) {
			*wire |= 1 << bit;
		}
		else {
			*wire &= ~(1 << bit);
		}
	}

	bool get_bit(Wire1* wire) {
		LOG_ASSERT(wire != nullptr);
		return *wire != 0;
	}

	bool get_bit(Wire2* wire, int bit) {
		LOG_ASSERT(wire != nullptr);
		LOG_ASSERT(bit >= 0 && bit <= 1
			&& "Bit must be between 0 and 1, inclusive");
		return ((*wire >> bit) & 0b1) != 0;
	}

	bool get_bit(Wire32* wire, int bit) {
		LOG_ASSERT(wire != nullptr);
		LOG_ASSERT(bit >= 0 && bit <= 31
			&& "Bit must be between 0 and 31, inclusive");
		return ((*wire >> bit) & 0b1) != 0;
	}
}
