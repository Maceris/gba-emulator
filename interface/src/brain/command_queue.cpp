#include "brain/command_queue.h"

#include "debugging/logger.h"

namespace brain {
	CommandQueue::CommandQueue()
		: data{}
		, head{ 0 }
		, tail{ 0 }
		, full{ false }
	{}
	CommandQueue::~CommandQueue() = default;

	void CommandQueue::add(Command command) {
		data[head] = command;

		if (full) {
			if (++tail == COMMAND_QUEUE_CAPACITY) {
				tail = 0;
			}
		}
		
		if (++head == COMMAND_QUEUE_CAPACITY) {
			head = 0;
		}
		full = (head == tail);
		LOG_ASSERT(!full && "We should probably not have filled this queue up");
	}

	Command CommandQueue::remove() {
		if (head == tail) {
			LOG_ERROR("Reading from an empty queue, check is_empty() or size() first");
			return Command::_count;
		}

		Command command = data[tail];

		full = false;
		if (++tail == COMMAND_QUEUE_CAPACITY) {
			tail = 0;
		}
		return command;
	}

	void CommandQueue::clear() {
		head = 0;
		tail = 0;
		full = false;
	}

	size_t CommandQueue::size() const {
		if (head == tail) {
			return full ? COMMAND_QUEUE_CAPACITY : 0;
		}
		if (head > tail) {
			return head - tail;
		}
		return head + COMMAND_QUEUE_CAPACITY - tail;
	}

	bool CommandQueue::is_empty() const {
		return (head == tail) && !full;
	}

	bool CommandQueue::is_full() const {
		return full;
	}
}