#pragma once

#include "memory/memory_types.h"

namespace emulator {

	/// <summary>
	/// 0=Not Signed,
	/// 1=Signed (Negative or less than)
	/// </summary>
	constexpr Word SIGN_FLAG_BITS = 0b1000'0000'0000'0000'0000'0000'0000'0000;

	/// <summary>
	/// 0=Not Zero,
	/// 1=Zero
	/// </summary>
	constexpr Word ZERO_FLAG_BITS = 0b0100'0000'0000'0000'0000'0000'0000'0000;

	/// <summary>
	/// 0=Borrow/No Carry,
	/// 1=Carry/No Borrow/extend
	/// </summary>
	constexpr Word CARRY_FLAG_BITS = 0b0010'0000'0000'0000'0000'0000'0000'0000;

	/// <summary>
	/// 0=No Overflow,
	/// 1=Overflow
	/// </summary>
	constexpr Word OVERFLOW_FLAG_BITS = 0b0001'0000'0000'0000'0000'0000'0000'0000;

	/// <summary>
	/// 0=Enable,
	/// 1=Disable
	/// </summary>
	constexpr Word IRQ_DISABLE_FLAG_BITS = 0b0000'0000'0000'0000'0000'0000'0100'0000;

	/// <summary>
	/// Set this to disable IRQ interrupts. Also, gets set whenever IRQ mode is
	/// entered.
	/// 
	/// 0=Enable,
	/// 1=Disable
	/// </summary>
	constexpr Word FIQ_DISABLE_FLAG_BITS = 0b0000'0000'0000'0000'0000'0000'0010'0000;

	/// <summary>
	/// 0=ARM,
	/// 1=THUMB
	/// Should not be changed manually, only by the BX instruction.
	/// </summary>
	constexpr Word STATE_FLAG_BITS = 0b0000'0000'0000'0000'0000'0000'0001'0000;

	/// <summary>
	/// 0b10000 (16) - User (non-privileged)           <para/>
	/// 0b10001 (17) - FIQ                             <para/>
	/// 0b10010 (18) - IRQ                             <para/>
	/// 0b10011 (19) - Supervisor (SWI)                <para/>
	/// 0b10111 (23) - Abort                           <para/>
	/// 0b11011 (27) - Undefined                       <para/>
	/// 0b11111 (31) - System (privileged 'User' mode) <para/>
	/// 
	/// Illegal values (anything else) puts the processor into an unrecoverable
	/// state.
	/// </summary>
	constexpr Word MODE_FLAG_BITS = 0b0000'0000'0000'0000'0000'0000'0001'1111;

	constexpr Byte MODE_USER           = 0b1'0000;
	constexpr Byte MODE_FIQ            = 0b1'0001;
	constexpr Byte MODE_IRQ            = 0b1'0010;
	constexpr Byte MODE_SUPERVISOR     = 0b1'0011;
	constexpr Byte MODE_ABORT          = 0b1'0111;
	constexpr Byte MODE_UNDEFINED      = 0b1'1011;
	constexpr Byte MODE_SYSTEM         = 0b1'1111;
}
