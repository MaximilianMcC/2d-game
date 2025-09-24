#pragma once

#include <string>
#include <vector>

class Logger
{
public:

	enum LogLevel
	{
		NONE,
		TODO,
		DEBUG,
		WARNING,
		INFO,
		CRITICAL,
		EVERYTHING
	};

	static void SetLogLevel(LogLevel level);

	static void Log(std::string text, LogLevel level = DEBUG);
	static void Log(std::vector<std::string> vector, LogLevel level = DEBUG);

private:
	static LogLevel currentLogLevel;

    static const std::string RESET;
    static const std::string LIGHT_GRAY;
    static const std::string BLUE;
    static const std::string RED;
    static const std::string YELLOW;
    static const std::string WHITE;
    static const std::string BROWN;
    static const std::string ORANGE;
};
