#pragma once

#include <cstdint>
#include <stdexcept>

using Byte = uint8_t;
using Halfword = uint16_t;
using Word = uint32_t;

using Address32 = uint32_t;
using Address16 = uint16_t;

using Register = Word;

struct AddressRange
{
	Address32 min;
	Address32 max;

	constexpr AddressRange(Address32 min, Address32 max)
		: min{ min }
		, max{ max }
	{
		if (max < min)
		{
			throw std::invalid_argument("Max address is less than min");
		}
	}
	constexpr AddressRange(const AddressRange&) = default;
	constexpr AddressRange& operator=(const AddressRange&) = default;
	constexpr AddressRange(AddressRange&&) = default;
	constexpr AddressRange& operator=(AddressRange&&) = default;
	constexpr ~AddressRange() = default;

	constexpr bool contains(const Address32& address)
	{
		return address >= min && address <= max;
	}
};

struct MemoryAccessInfo
{
	uint8_t bus_width;
	bool supports_8_bit_read;
	bool supports_8_bit_write;
	uint8_t cycles_for_8_bit_access;

	bool supports_16_bit_read;
	bool supports_16_bit_write;
	uint8_t cycles_for_16_bit_access;

	bool supports_32_bit_read;
	bool supports_32_bit_write;
	uint8_t cycles_for_32_bit_access;
};
