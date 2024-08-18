#include "debugging/logger.h"

#include <list>
#include <map>
#include <mutex>
#if defined(WIN32)
#include <Windows.h>
#elif defined(UNIX)
#endif
#include <iostream>

static const char* ERROR_LOG_FILENAME = "log.txt";

#ifdef DEBUG
const LogFlag DEFAULT_FLAG_ERROR = FLAG_WRITE_TO_DEBUGGER;
const LogFlag DEFAULT_FLAG_WARNING = FLAG_WRITE_TO_DEBUGGER;
const LogFlag DEFAULT_FLAG_INFO = FLAG_WRITE_TO_DEBUGGER;
#else
const LogFlag DEFAULT_FLAG_ERROR = FLAG_WRITE_NOWHERE;
const LogFlag DEFAULT_FLAG_WARNING = FLAG_WRITE_NOWHERE;
const LogFlag DEFAULT_FLAG_INFO = FLAG_WRITE_NOWHERE;
#endif

#pragma region LogManager declaration
/// <summary>
/// Manages logging, tracking where logs go, and cleaning up log resources.
/// </summary>
class LogManager
{
public:
	/// <summary>
	/// The possible results from an error dialog.
	/// </summary>
	enum ErrorDialogResult
	{
		LOG_MANAGER_ERROR_ABORT,
		LOG_MANAGER_ERROR_RETRY,
		LOG_MANAGER_ERROR_IGNORE
	};

	using Tags = std::map<std::string, LogFlag, std::less<>>;
	using ErrorLoggerList = std::list<Logger::ErrorLogger*>;

	/// <summary>
	/// A set of log flags for various tags, determining if and where they
	/// get logged.
	/// </summary>
	Tags tags;

	/// <summary>
	/// All the erorr loggers that got allocated by macros.
	/// </summary>
	ErrorLoggerList error_loggers;

	/// <summary>
	/// Used to ensure thread safety when adding or reading tags.
	/// </summary>
	std::mutex tag_mutex;

	/// <summary>
	/// Used to ensure thread safety when adding or reading the list of 
	/// error loggers.
	/// </summary>
	std::mutex error_mutex;

	/// <summary>
	/// Set up the log manager.
	/// </summary>
	LogManager();

	/// <summary>
	/// Clean up the log manager.
	/// </summary>
	~LogManager();

	/// <summary>
	/// Builds up a log string and outputs it to various places depending on 
	/// the log flags, for logs without a location.
	/// </summary>
	/// <param name="tag">The tag we are logging.</param>
	/// <param name="message">The message to log.</param>
	/// <param name="location">The location of the log line.</param>
	void log(std::string_view tag, std::string_view message);

	/// <summary>
	/// Builds up a log string and outputs it to various places depending on 
	/// the log flags.
	/// </summary>
	/// <param name="tag">The tag we are logging.</param>
	/// <param name="message">The message to log.</param>
	/// <param name="location">The location of the log line.</param>
	void log(std::string_view tag, std::string_view message,
		std::source_location location);

	/// <summary>
	/// Set the log flags for a tag. Passing a flag of FLAG_WRITE_NOWHERE
	/// will remove any flags for that tag.
	/// </summary>
	/// <param name="tag">The tag to set.</param>
	/// <param name="flags">Flags specifying where that tag gets logged.
	/// </param>
	void set_display_flags(std::string_view tag, unsigned char flags);

	/// <summary>
	/// Track a new error logger.
	/// </summary>
	/// <param name="logger">The logger to track.</param>
	void add_error_logger(Logger::ErrorLogger* logger);

	/// <summary>
	/// Log an error, and show an error dialog to the user.
	/// </summary>
	/// <param name="error_message">The error message to show.</param>
	/// <param name="fatal">Whether the error is fatal.</param>
	/// <param name="location">The location of the log line.</param>
	/// <returns>The result of the user's choice on the dialog.</returns>
	LogManager::ErrorDialogResult error(std::string_view error_message,
		bool fatal, std::source_location location);

private:
	/// <summary>
	/// Outputs the supplied buffer to the appropriate place(s), based on the
	/// supplied flags.
	/// </summary>
	/// <param name="final_buffer">The final log outputting.</param>
	/// <param name="flags">The flags indicating where to log.</param>
	void output_buffer_to_logs(std::string_view final_buffer,
		unsigned char flags);

	/// <summary>
	/// Write to a log file.
	/// </summary>
	/// <param name="data">The data to write.</param>
	void write_to_log_file(std::string_view data);

	/// <summary>
	/// Format a message and return it back out in the first parameter.
	/// </summary>
	/// <param name="tag">The tag we are logging.</param>
	/// <param name="message">The message to log, pre-formatting.</param>
	/// <param name="function_name">The function that log was called from.
	/// </param>
	/// <param name="source_file">The file that log was called from.</param>
	/// <param name="line_number">The line number that log was called from.
	/// </param>
	/// <returns>The resulting message.</returns>
	std::string format_message(
		std::string_view tag, std::string_view message,
		const char* function_name, const char* source_file,
		unsigned int line_number);
};

static LogManager* log_manager = nullptr;

#pragma endregion

#pragma region LogManager definition

LogManager::LogManager()
{
	set_display_flags("ERROR", DEFAULT_FLAG_ERROR);
	set_display_flags("WARNING", DEFAULT_FLAG_WARNING);
	set_display_flags("INFO", DEFAULT_FLAG_INFO);
}

LogManager::~LogManager()
{
	std::scoped_lock lock{ error_mutex };
	for (auto it = error_loggers.begin(); it != error_loggers.end(); ++it)
	{
		Logger::ErrorLogger* logger = *it;
		safe_delete(logger);
	}
	error_loggers.clear();
}

void LogManager::log(std::string_view tag, std::string_view message)
{
	LogFlag flags;
	{
		std::scoped_lock lock{ tag_mutex };

		Tags::iterator result = tags.find(tag);
		if (result == tags.end()) {
			return;
		}
		flags = result->second;
	}

	std::string buffer =
		format_message(tag, message, nullptr, nullptr, 0);
	output_buffer_to_logs(buffer, flags);
}

void LogManager::log(std::string_view tag, std::string_view message,
	std::source_location location)
{
	LogFlag flags;
	{
		std::scoped_lock lock{ tag_mutex };

		Tags::iterator result = tags.find(tag);
		if (result == tags.end()) {
			return;
		}
		flags = result->second;
	}

	std::string buffer =
		format_message(tag, message, location.function_name(),
			location.file_name(), location.line());
	output_buffer_to_logs(buffer, flags);
}

void LogManager::set_display_flags(std::string_view tag, unsigned char flags)
{
	std::scoped_lock lock{ tag_mutex };

	Tags::iterator result = tags.find(tag);

	if (result != tags.end())
	{
		if (flags == FLAG_WRITE_NOWHERE)
		{
			tags.erase(result);
		}
		else {
			result->second = flags;
		}
	}
	else if (flags != FLAG_WRITE_NOWHERE)
	{
		tags.insert(std::make_pair(tag, flags));
	}
}

void LogManager::add_error_logger(Logger::ErrorLogger* logger)
{
	std::scoped_lock lock{ error_mutex };
	error_loggers.push_back(logger);
}

LogManager::ErrorDialogResult LogManager::error(
	std::string_view error_message, bool fatal, std::source_location location)
{
	std::string tag = fatal ? "FATAL" : "ERROR";

	std::string buffer = format_message(tag, error_message,
		location.function_name(), location.file_name(), location.line());

	{
		std::scoped_lock lock{ tag_mutex };
		// Log first, dialog later
		Tags::iterator result = tags.find(tag);
		if (result != tags.end())
		{
			output_buffer_to_logs(buffer, result->second);
		}
	}

#if defined(WIN32)
	// Show a dialog box, with an error icon, defaulting to abort
	int response = MessageBoxA(nullptr, buffer.c_str(), tag.c_str(),
		MB_ABORTRETRYIGNORE | MB_ICONERROR | MB_DEFBUTTON1);

	switch (response)
	{
	case IDABORT:
		__debugbreak();// breaks into the debugger
		return LogManager::LOG_MANAGER_ERROR_RETRY;
	case IDIGNORE:
		return LogManager::LOG_MANAGER_ERROR_IGNORE;
	case IDRETRY:
	default:
		return LogManager::LOG_MANAGER_ERROR_RETRY;
	}
#elif defined(UNIX)
	//TODO(ches) figure out how to ask the user what to do

	abort();//NOTE(ches) just hard crash I guess
#endif
}

void LogManager::output_buffer_to_logs(std::string_view final_buffer,
	unsigned char flags)
{
	if ((flags & FLAG_WRITE_TO_DEBUGGER) != FLAG_WRITE_NOWHERE)
	{
#if defined(WIN32)
		OutputDebugStringA(final_buffer.data());
#elif defined(UNIX)
		std::clog << final_buffer << std::endl;
#endif
	}
	if ((flags & FLAG_WRITE_TO_LOG_FILE) != FLAG_WRITE_NOWHERE)
	{
		write_to_log_file(final_buffer);
	}
}

void LogManager::write_to_log_file(std::string_view data)
{
	FILE* log_file = nullptr;
	// Opens for reading and appending. Creates the file if it doesn't exist.
	errno_t error = fopen_s(&log_file, ERROR_LOG_FILENAME, "a+");
	if (error != 0)
	{
		OutputDebugStringA("Failed to open log file");
		return;
	}
	fprintf(log_file, data.data());
	fclose(log_file);
}

std::string LogManager::format_message(
	std::string_view tag, std::string_view message,
	const char* function_name, const char* source_file,
	unsigned int line_number)
{
	std::string output;
	if (tag.empty())
	{
		output = message;
	}
	else
	{
		output = "[";
		output += tag;
		output += "] ";
		output += message;
	}

	if (function_name != nullptr)
	{
		output += "\n";
		output += "Function: ";
		output += function_name;
	}
	if (source_file != nullptr)
	{
		output += "\n";
		output += "Source File: ";
		output += source_file;
	}
	if (line_number != 0)
	{
		output += "\n";
		output += "Line: ";
		output += std::to_string(line_number);
	}

	output += "\n";

	return output;
}

#pragma endregion

#pragma region ErrorLogger definition

namespace Logger
{
	ErrorLogger::ErrorLogger()
		: enabled(true)
	{
		log_manager->add_error_logger(this);
	}

	void ErrorLogger::log_error(std::string_view error_message,
		bool fatal, std::source_location location)
	{
		if (enabled)
		{
			if (log_manager->error(error_message, fatal, location))
			{
				enabled = false;
			}
		}
	}
}

#pragma endregion

#pragma region Logger function definitions

namespace Logger
{
	void init()
	{
		if (!log_manager)
		{
			log_manager = ALLOC LogManager;
		}
	}

	void destroy()
	{
		if (log_manager)
		{
			safe_delete(log_manager);
			log_manager = nullptr;
		}
	}

	void log(std::string_view tag, std::string_view error_message)
	{
		LOG_ASSERT(log_manager);
		log_manager->log(tag, error_message);
	}
	void log(std::string_view tag, std::string_view error_message,
		std::source_location location)
	{
		LOG_ASSERT(log_manager);
		log_manager->log(tag, error_message, location);
	}

	void set_display_flags(std::string_view tag, unsigned char flags)
	{
		LOG_ASSERT(log_manager);
		log_manager->set_display_flags(tag, flags);
	}
}

#pragma endregion