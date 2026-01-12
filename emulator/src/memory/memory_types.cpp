#include "memory/memory_types.h"

#include <stdexcept>

namespace emulator {
	constexpr AddressRange::AddressRange(Address32 min, Address32 max)
		: min{ min }
		, max{ max }
	{
		if (max < min)
		{
			throw std::invalid_argument("Max address is less than min");
		}
	}

	constexpr AddressRange::AddressRange(const AddressRange&) = default;
	constexpr AddressRange& AddressRange::operator=(const AddressRange&) = default;
	constexpr AddressRange::AddressRange(AddressRange&&) = default;
	constexpr AddressRange& AddressRange::operator=(AddressRange&&) = default;
	constexpr AddressRange::~AddressRange() = default;

	constexpr bool AddressRange::contains(const Address32& address) const
	{
		return address >= min && address <= max;
	}
}