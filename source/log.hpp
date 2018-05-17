/**
* Copyright (C) 2014 Patrick Mours. All rights reserved.
* License: https://github.com/crosire/reshade#license
*/

#pragma once

#include <fstream>
#include <iomanip>
#include <sstream>
#include "unicode.hpp"
#include "filesystem.hpp"
#include <mutex>

#define LOG(LEVEL) LOG_##LEVEL()
#define LOG_INFO() reshade::log::message(reshade::log::level::info)
#define LOG_ERROR() reshade::log::message(reshade::log::level::error)
#define LOG_WARNING() reshade::log::message(reshade::log::level::warning)
#define LOG_DEBUG() reshade::log::message(reshade::log::level::debug)


namespace reshade::log
{
	enum class level
	{
		info = 4,
		error = 1,
		warning = 2,
		debug = 3,
	};

	extern std::ofstream stream;
	extern level last_level;
	extern std::ostringstream memstream;
	extern int log_level;
	extern std::mutex _mutex;

	struct message
	{
		message(level level);
		~message();

		template <typename T>
		inline message &operator<<(const T &value)
		{
			stream << value;
			if (static_cast<int>(last_level) <= log_level) {
				memstream << value;
			}

			return *this;
		}
		inline message &operator<<(const char *message)
		{
			stream << message;
			if (static_cast<int>(last_level) <= log_level) {
				memstream << message;
			}

			return *this;
		}
		template <>
		inline message &operator<<(const std::wstring &message)
		{
			return operator<<(utf16_to_utf8(message));
		}
		inline message &operator<<(const wchar_t *message)
		{
			return operator<<(utf16_to_utf8(message));
		}
	};

	/// <summary>
	/// Open a log file for writing.
	/// </summary>
	/// <param name="path">The path to the log file.</param>
	bool open(const filesystem::path &path);
}
