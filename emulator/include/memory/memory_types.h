#pragma once

#include <cstdint>
#include <stdexcept>

using Byte = uint8_t;
using Halfword = uint16_t;
using Word = uint32_t;

using Address32 = uint32_t;
using Address16 = uint16_t;

using Register = Word;

using ArmInstruction = uint32_t;
/// <summary>
/// Technically, Thumb instructions can be either 16-bit or 32-bit. In order
/// to suppor both, we consider them always 16-bit with the 32-bit instructions
/// being encoded as a pair of 16-bit instructions. This means that not
/// everything encoded as a ThumbInstruction will be valid by itself.
/// </summary>
using ThumbInstruction = uint16_t;

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

	constexpr bool contains(const Address32& address) const
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

enum class MemoryCycleType
{
	IDLE,
	NON_SEQUENTIAL,
	SEQUENTIAL,
	COPROCESSOR_REGISTER_TRANSFER
};
