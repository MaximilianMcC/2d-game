#include "logger.h"
#include <iostream>

Logger::LogLevel Logger::currentLogLevel = Logger::WARNING;
const std::string Logger::RESET = "\033[0m";
const std::string Logger::LIGHT_GRAY = "\033[37m";
const std::string Logger::BLUE = "\033[34m";
const std::string Logger::RED = "\033[31m";
const std::string Logger::YELLOW = "\033[33m";
const std::string Logger::WHITE = "\033[97m";
const std::string Logger::BROWN = "\033[38;5;94m";

void Logger::SetLogLevel(LogLevel level)
{
	currentLogLevel = level;
}

void Logger::Log(std::string text, LogLevel level)
{
	// Check for if we're permitted to show the log
	if (level > currentLogLevel) return;
	std::string log;

	// Make the level prefix
	log += LIGHT_GRAY + "[";
	switch (level)
	{
	case WARNING:
		log += YELLOW + "^";
		break;

	case INFO:
		log += BLUE + "?";
		break;

	case ERROR:
		log += RED + "!";
		break;
	
	case DEBUG:
		log += BROWN + "D";
		break;
	}
	log += LIGHT_GRAY + "]" + RESET + WHITE;

	// Log the info
	log += " " + text;
	std::cout << log << std::endl;
}