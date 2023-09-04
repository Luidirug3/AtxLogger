#pragma once

//#ifdef ATXLOGGER_EXPORTS
//#define ATXLOGGER_API __declspec(dllexport)
//#else
//#define ATXLOGGER_API __declspec(dllimport)
//#endif

#define ATXLOGGER_API __declspec(dllexport)

#include <string>


struct ATXLOGGER_API AtxLoggerConf
{
	static AtxLoggerConf getConfiguration(std::string config_file = "");

	bool operator==(const AtxLoggerConf& other) const;

	static constexpr const char* LOGS_FOLDER = "../Logger/Logs";
	static constexpr const char* LOGGER_NAME = "Logger";

	
	int level = 1;
	int num_max_rotated_files = 15;
	int async = 0;

private:

	AtxLoggerConf(std::string conf_file = "");

	std::string config_file_ = "";
	static AtxLoggerConf configuration_;
};

