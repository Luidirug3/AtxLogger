#pragma once

#include <string>
#include "AtxLoggerConf.h"


// should be an interface, and spdlog implementation in another
class ATXLOGGER_API AtxLogger {
	
public:
	enum struct Level {
		trace,
		debug,
		info,
		warning,
		error,
		critical,
		off
	};

	~AtxLogger();

	static AtxLogger* getInstance(AtxLoggerConf configuration);
	static AtxLogger* getInstance();

	void log(Level level, std::string message);
	void log(Level level, std::string category, std::string message);

	void flush();
	static void shutdown();

	static std::string formatString(std::string format, ...);

private:

	AtxLogger(AtxLoggerConf configuration);
	static AtxLogger* atx_logger_instance_;

	AtxLoggerConf configuration_;
	 
	//Private implementation of the class to hide spdlog outside
	class AtxLoggerPrivate; 
	AtxLoggerPrivate* atx_logger_private_;
};