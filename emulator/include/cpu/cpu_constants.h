#pragma once

#include "memory/memory_types.h"

/// <summary>
/// 0=Not Signed,
/// 1=Signed
/// </summary>
constexpr Word SIGN_FLAG_BITS = 0b1000'0000'0000'0000'0000'0000'0000'0000;

/// <summary>
/// 0=Not Zero,
/// 1=Zero
/// </summary>
constexpr Word ZERO_FLAG_BITS = 0b0100'0000'0000'0000'0000'0000'0000'0000;

/// <summary>
/// 0=Borrow/No Carry,
/// 1=Carry/No Borrow
/// </summary>
constexpr Word CARRY_FLAG_BITS = 0b0010'0000'0000'0000'0000'0000'0000'0000;

/// <summary>
/// 0=No Overflow,
/// 1=Overflow
/// </summary>
constexpr Word OVERFLOW_FLAG_BITS = 0b0001'0000'0000'0000'0000'0000'0000'0000;

/// <summary>
/// 1=Sticky Overflow, ARMv5TE and up only.
/// 
/// Used by QADD, QSUB, QDADD, QDSUB, SMLAxy, and SMLAWy only.
/// These opcodes set the Q-flag in case of overflows, but otherwise leave it
/// unchanged. The Q-flag can be tested or reset by MSR/MRS opcodes only.
/// </summary>
constexpr Word STICKY_OVERFLOW_FLAG_BITS = 0b0000'1000'0000'0000'0000'0000'0000'0000;

/// <summary>
/// 1=Jazelle Bytecode instructions (if supported)
/// </summary>
constexpr Word JAZELLE_MODE_FLAG_BITS = 0b0000'0000'1000'0000'0000'0000'0000'0000;

constexpr Word ENDIAN_FLAG_BITS = 0b0000'0000'0000'0000'0000'0001'0000'0000;

/// <summary>
/// 1=Disable Imprecise Data Aborts (ARM11 only)
/// </summary>
constexpr Word ABORT_DISABLE_FLAG_BITS = 0b0000'0000'0000'0000'0000'0000'1000'0000;

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
/// 0b0xx00 (0) - Old User       \ 26bit Backward Compatibility modes
/// 0b0xx01 (1) - Old FIQ        | (supported only on ARMv3, except ARMv3g,
/// 0b0xx10 (2) - Old IRQ        | and some non-T variants of ARMv4)
/// 0b0xx11 (3) - Old Supervisor /
/// 0b10000 (16) - User (non-privileged)
/// 0b10001 (17) - FIQ
/// 0b10010 (18) - IRQ
/// 0b10011 (19) - Supervisor (SWI)
/// 0b10111 (23) - Abort
/// 0b11011 (27) - Undefined
/// 0b11111 (31) - System (privileged 'User' mode) (ARMv4 and up)
/// </summary>
constexpr Word MODE_FLAG_BITS = 0b0000'0000'0000'0000'0000'0000'0000'1111;

constexpr Byte MODE_OLD_USER       = 0b0'0000;
constexpr Byte MODE_OLD_FIQ        = 0b0'0001;
constexpr Byte MODE_OLD_IRQ        = 0b0'0010;
constexpr Byte MODE_OLD_SUPERVISOR = 0b0'0011;
constexpr Byte MODE_USER           = 0b1'0000;
constexpr Byte MODE_FIQ            = 0b1'0001;
constexpr Byte MODE_IRQ            = 0b1'0010;
constexpr Byte MODE_SUPERVISOR     = 0b1'0011;
constexpr Byte MODE_ABORT          = 0b1'0111;
constexpr Byte MODE_UNDEFINED      = 0b1'1011;
constexpr Byte MODE_SYSTEM         = 0b1'1111;
