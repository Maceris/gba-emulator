#pragma once

#include <cstdint>

namespace emulator {

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

		constexpr AddressRange(Address32 min, Address32 max);
		constexpr AddressRange(const AddressRange&);
		constexpr AddressRange& operator=(const AddressRange&);
		constexpr AddressRange(AddressRange&&);
		constexpr AddressRange& operator=(AddressRange&&);
		constexpr ~AddressRange();

		constexpr bool contains(const Address32& address) const;
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
		/// <summary>
		/// During this cycle, the core is performing an internal transfer and
		/// no useful prefetching can be performed at the same time, 
		/// so it does not require a transfer.
		/// </summary>
		INTERNAL,
		/// <summary>
		/// During this cycle, the core requests a transfer to or from an address
		/// which is unrelated to the address used in the preceding cycle.
		/// </summary>
		NON_SEQUENTIAL,
		/// <summary>
		/// During this cycle, the core requests a transfer to or from an address
		/// that is either one word or one halfword greater than the address used
		/// in the preceding cycle.
		/// </summary>
		SEQUENTIAL,
		/// <summary>
		/// During this cycle, the core uses the data bus to communicate with a
		/// coprocessor, but does not require any action by the memory system.
		/// </summary>
		COPROCESSOR_REGISTER_TRANSFER
	};
}
