#include "..\include\AtxLogger.h"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/async.h>

#include <direct.h> // For _mkdir
#include <stdarg.h> // For va_start e va_end


ATXLOGGER_API AtxLogger* AtxLogger::atx_logger_instance_ = nullptr;


class AtxLogger::AtxLoggerPrivate {
public:
	std::shared_ptr<spdlog::logger> spd_logger_;
};


AtxLogger::AtxLogger(AtxLoggerConf configuration) : configuration_(configuration), atx_logger_private_(new AtxLoggerPrivate()) {

	//std::shared_ptr<spdlog::logger> logger;
	
	/*std::time_t now = std::time(nullptr);
	std::tm timeInfo;
	localtime_s(&timeInfo, &now);*/

	//auto sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(std::string(LOGS_FOLDER) + "/log_" + formatString("%d-%d-%d", timeInfo.tm_mday, timeInfo.tm_mon + 1, timeInfo.tm_year + 1900) + ".txt", 1024 * 1024 * max_mb_sized_files, num_max_rotated_files);
	//auto sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(std::string(LOGS_FOLDER) + "/log.txt", 1024 * 1024 * max_mb_sized_files, num_max_rotated_files);
	
	auto sink = std::make_shared<spdlog::sinks::daily_file_sink_mt>(std::string(configuration_.LOGS_FOLDER) + "/log.txt", 0, 0, false, configuration_.num_max_rotated_files);

	if (configuration_.async) {

		spdlog::init_thread_pool(8192, 2);

		atx_logger_private_->spd_logger_ = std::make_shared<spdlog::async_logger>(configuration_.LOGGER_NAME, sink, spdlog::thread_pool());
	}
	else {

		atx_logger_private_->spd_logger_ = std::make_shared<spdlog::logger>(configuration_.LOGGER_NAME, sink);
	}

	//logger->sinks().push_back(std::make_shared<spdlog::sinks::daily_file_sink_mt>(std::string(LOGS_FOLDER) + "/log.txt", 0, 0));

	spdlog::register_logger(atx_logger_private_->spd_logger_);

	switch (configuration_.level) {
	case 0:
		atx_logger_private_->spd_logger_->set_level(spdlog::level::trace);
		break;
	case 1:
		atx_logger_private_->spd_logger_->set_level(spdlog::level::debug);
		break;
	case 2:
		atx_logger_private_->spd_logger_->set_level(spdlog::level::info);
		break;
	case 3:
		atx_logger_private_->spd_logger_->set_level(spdlog::level::warn);
		break;
	case 4:
		atx_logger_private_->spd_logger_->set_level(spdlog::level::err);
		break;
	case 5:
		atx_logger_private_->spd_logger_->set_level(spdlog::level::critical);
		break;
	default:
		atx_logger_private_->spd_logger_->set_level(spdlog::level::info);

	}

	spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [thread %t] [%l] %v");

	spdlog::flush_every(std::chrono::seconds(5));
}

AtxLogger::~AtxLogger() {

	delete atx_logger_private_;
	spdlog::shutdown();
}

AtxLogger* AtxLogger::getInstance() {

	if (AtxLogger::atx_logger_instance_ == nullptr) {

		//If does not exist, create it with default configuration
		AtxLoggerConf configuration = AtxLoggerConf::getConfiguration();

		_mkdir(configuration.LOGS_FOLDER);

		AtxLogger::atx_logger_instance_ = new AtxLogger(configuration);
	}

	return  AtxLogger::atx_logger_instance_;
}

AtxLogger* AtxLogger::getInstance(AtxLoggerConf configuration) {

	//If exist but the configuration are not igual -> delete the instance
	if ((AtxLogger::atx_logger_instance_ != nullptr) && !(AtxLogger::atx_logger_instance_->configuration_ == configuration)) {

		delete AtxLogger::atx_logger_instance_;
		AtxLogger::atx_logger_instance_ = nullptr;
	}

	if (AtxLogger::atx_logger_instance_ == nullptr) {

		_mkdir(configuration.LOGS_FOLDER);

		AtxLogger::atx_logger_instance_ = new AtxLogger(configuration);
	}

	return  AtxLogger::atx_logger_instance_;
}

void AtxLogger::log(Level level, std::string message) {

	//auto logger = spdlog::get(LOGGER_NAME);

	if (atx_logger_private_->spd_logger_) {
		switch (level) {
		case Level::trace:
			atx_logger_private_->spd_logger_->trace(message);
			break;
		case Level::debug:
			atx_logger_private_->spd_logger_->debug(message);
			break;
		case Level::info:
			atx_logger_private_->spd_logger_->info(message);
			break;
		case Level::warning:
			atx_logger_private_->spd_logger_->warn(message);
			break;
		case Level::error:
			atx_logger_private_->spd_logger_->error(message);
			break;
		case Level::critical:
			atx_logger_private_->spd_logger_->critical(message);
			break;
		default:
			atx_logger_private_->spd_logger_->info(message);
		}
		
	}
}

void AtxLogger::log(Level level, std::string category, std::string message) 
{
	log(level, formatString("[%s] %s", category.c_str(), message.c_str()));
}

void AtxLogger::flush() {

	//auto logger = spdlog::get(LOGGER_NAME);
	atx_logger_private_->spd_logger_->flush();
}

//To call before close the application
void AtxLogger::shutdown() {

	if (atx_logger_instance_) {
		delete atx_logger_instance_;
		atx_logger_instance_ = nullptr;
	}
	spdlog::shutdown();
}

std::string AtxLogger::formatString(std::string format, ...) {

	const int bufferSize = 512;
	char buffer[bufferSize];

	va_list args;
	va_start(args, format);

	vsnprintf(buffer, bufferSize, format.c_str(), args);

	va_end(args);

	return std::string(buffer);
}
