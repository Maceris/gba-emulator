#pragma once

#include <cstdint>

#include "board/wire.h"

namespace emulator {

	struct ARM7TDMI_Bus
	{
		//TODO(ches) do we need this? Shouldn't they plug into the board?

#pragma region Clock signals
		/// <summary>
		/// Memory clock input. Clock used for all memory accesses and processor 
		/// operations, can be reduced where required for slow peripherals or memory.
		/// Also, nWAIT can be used to achieve the same effect.
		/// </summary>
		Wire1 MCLK;

		/// <summary>
		/// Allows stretching a bus cycle longer, separate from clock cycles. Must
		/// only change during the low phase of MCLK.
		/// 
		/// When nWAIT is high on teh falling edge of MCLK, a bus cycle completes.
		/// When nWAIT is low, the bus cycle is extended by stretching the low phase
		/// of the internal clock.
		/// </summary>
		Wire1 nWAIT;

		/// <summary>
		/// Not reset.
		/// 
		/// Used to reset the core, must be held at 0 for a minimum of 2 MCLK cycles to 
		/// fully reset.
		/// </summary>
		Wire1 nRESET;
#pragma endregion

#pragma region Address signals
		/// <summary>
		/// 32-bit address bus.
		/// </summary>
		Wire32 A32;

		/// <summary>
		/// Not read, write.
		/// Specifies the direction of the transfer.
		/// 
		/// 0 - read cycle
		/// 1 - write cycle
		/// </summary>
		Wire1 nRW;

		/// <summary>
		/// Encodes the size of a transfer.
		/// 
		/// 00 - Byte, significant address bits are A[31:0]
		/// 01 - Halfword, significant address bits are A[31:1]
		/// 10 - Word, significant address bits are A[31:2]
		/// 11 - Reserved
		/// </summary>
		Wire2 MAS2;

		/// <summary>
		/// Not op-code fetch.
		/// Specifies info about a transfer. Can be used by an MMU to determine if
		/// access is an opcode fetch or data transfer. Can also be used with nTRANS 
		/// to implement an access permission scheme.
		/// 
		/// 0 - Opcode
		/// 1 - Data
		/// </summary>
		Wire1 nOPC;

		/// <summary>
		/// Specifies info about a transfer. Can be used by an MMU to determine if
		/// access is from a privileged mode or use mode. Can also be used with nOPC
		/// to implement an access permission scheme.
		/// 
		/// 0 - User
		/// 1 - Privileged
		/// </summary>
		Wire1 nTRANS;

		/// <summary>
		/// Indicates an atomic operation is being performed on the bus. Normally low,
		/// but high when SWP or SWPB is happening.
		/// </summary>
		Wire1 LOCK;

		/// <summary>
		/// Indicates the operating state.
		/// 
		/// 0 - ARM
		/// 1 - Thumb
		/// </summary>
		Wire1 TBIT;
#pragma endregion

#pragma region Memory request signals

		/// <summary>
		/// Not memory request, 0 when the processor needs memory access during
		/// the following cycle.
		/// </summary>
		Wire1 nMREQ;

		/// <summary>
		/// Sequential address. 1 when the address of the next memory cycle is 
		/// closely related to the last one. In ARM this means the same word or
		/// next, and in THUMB this means the same halfword or next.
		/// </summary>
		Wire1 SEQ;
#pragma endregion

#pragma region Data timed signals

		/// <summary>
		/// Bidirectional data bus.
		/// </summary>
		Wire32 D32;

		/// <summary>
		/// Unidirecitonal data input bus.
		/// </summary>
		Wire32 DIN32;

		/// <summary>
		/// Unidirectional data output bus.
		/// </summary>
		Wire32 DOUT32;

		/// <summary>
		/// Indicates a memory transaction failed to complete successfully. If
		/// asserted on data access, the processor takes the Data Abort trap. If
		/// asserted on an opcode fetch, the abort is tracked down the pipeline and
		/// if the instruction is executed then the Prefetch Abort trap is taken.
		/// </summary>
		Wire1 ABORT;

		//TODO(ches) is this literally 4 wires wide? Where did I even find this?

		/// <summary>
		/// Byte latch enables.
		/// 
		/// BL[3] controls latching of data on D[31:24]
		/// BL[2] controls latching of data on D[23:16]
		/// BL[1] controls latching of data on D[15:8]
		/// BL[0] controls latching of data on D[7:0]
		/// </summary>
		uint8_t BL4;
#pragma endregion
	};

}