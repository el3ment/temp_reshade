/**
* Copyright (C) 2014 Patrick Mours. All rights reserved.
* License: https://github.com/crosire/reshade#license
*/

#include "log.hpp"
#include <Windows.h>


namespace reshade::log
{
	std::ofstream stream;
	std::ostringstream memstream;
	level last_level;
	int log_level = 3;
	std::mutex _mutex;

	message::message(level level)
	{
		SYSTEMTIME time;
		GetLocalTime(&time);
		last_level = level;

		std::ostringstream tmp;
		const char level_names[][6] = { "ERROR", "WARN", "DEBUG", "INFO" };

		// Lock the stream until the message is complete
		_mutex.lock();

		tmp << std::right << std::setfill('0')
			<< std::setw(4) << time.wYear << '-'
			<< std::setw(2) << time.wMonth << '-'
			<< std::setw(2) << time.wDay << 'T'
			<< std::setw(2) << time.wHour << ':'
			<< std::setw(2) << time.wMinute << ':'
			<< std::setw(2) << time.wSecond << ':'
			<< std::setw(3) << time.wMilliseconds << ' '
			<< '[' << std::setw(5) << GetCurrentThreadId() << ']' << std::setfill(' ')
			<< " | " << level_names[static_cast<unsigned int>(level) - 1] << " | " << std::left;

		stream << tmp.str();

		if (static_cast<int>(last_level) <= log_level) {
			memstream << tmp.str();
		}
	}
	message::~message()
	{
		stream << std::endl;
		if (static_cast<int>(last_level) <= log_level) {
			memstream << std::endl;
		}

		// The message is finished, we can unlock the stream
		_mutex.unlock();
	}

	bool open(const filesystem::path &path)
	{
		stream.open(path.wstring(), std::ios::out | std::ios::trunc);
		memstream.clear();

		if (!stream.is_open())
		{
			return false;
		}

		stream.setf(std::ios_base::showbase);

		stream.flush();

		return true;
	}
}
