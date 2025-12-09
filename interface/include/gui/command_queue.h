#pragma once

#include <cstdint>

#include "gui/commands.h"

namespace gui {
	constexpr size_t COMMAND_QUEUE_CAPACITY = 32;

	/// <summary>
	/// A circular queue. You can add more commands than will fit, 
	/// and older ones will be overwritten, but this will error out
	/// in debug builds since we only expect a couple commands per frame.
	/// </summary>
	struct CommandQueue {
		CommandQueue();
		CommandQueue(const CommandQueue&) = delete;
		CommandQueue(CommandQueue&&) = delete;
		~CommandQueue();
		CommandQueue& operator=(const CommandQueue&) = delete;
		CommandQueue& operator=(CommandQueue&&) = delete;

		void add(Command command);
		Command remove();
		void clear();
		size_t size() const;
		bool is_empty() const;
		bool is_full() const;

	private:
		Command data[COMMAND_QUEUE_CAPACITY];
		size_t head;
		size_t tail;
		bool full;
	};

}