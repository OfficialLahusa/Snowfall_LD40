#pragma once
#include <string>
#include <sstream>

#if __has_include(<Windows.h>)
#include <Windows.h>
#define setConsoleTextColor(color) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
#else
#define setConsoleTextColor(color) 
#endif


#if __has_include(<intrin.h>)
#include <intrin.h>
#define DEBUG_BREAK __debugbreak();
#else
#define DEBUG_BREAK
#endif

namespace sse
{
	namespace logger
	{
		typedef unsigned char byte;

		enum class logLevel : unsigned short
		{
			error = 0,
			warning = 1,
			info = 2
		};
		static logLevel m_logLevel = logLevel::info;

		inline void setLogLevel(logLevel logLevel)
		{
			m_logLevel = logLevel;
		}

		template<typename T>
		void logError(T str)
		{
			setConsoleTextColor(12);
			std::stringstream ss;
			if (m_logLevel >= logLevel::error)
			{
				ss << "[ERROR] " << str;
			}
			std::puts(ss.str().c_str());
			setConsoleTextColor(15);
		}

		template<typename T>
		void logWarning(T str)
		{
			setConsoleTextColor(11);
			std::stringstream ss;
			if (m_logLevel >= logLevel::error)
			{
				ss << "[WARNING] " << str;
			}
			std::puts(ss.str().c_str());
			setConsoleTextColor(15);
			/*
			setConsoleTextColor(11);
			if (m_logLevel >= logLevel::warning)
			{
				std::cout << "[WARNING] " << str << std::endl;
			}
			setConsoleTextColor(15);*/
		}

		template<typename T>
		void logInfo(T str)
		{
			setConsoleTextColor(14);
			std::stringstream ss;
			if (m_logLevel >= logLevel::error)
			{
				ss << str;
			}
			std::puts(ss.str().c_str());
			setConsoleTextColor(15);
			/*setConsoleTextColor(14);
			if (m_logLevel >= logLevel::info)
			{
				std::cout << str << std::endl;
			}
			setConsoleTextColor(15);*/
		}
	}
}