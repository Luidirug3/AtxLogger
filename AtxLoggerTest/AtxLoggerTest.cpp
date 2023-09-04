#include <iostream>
#include "AtxLogger.h"

int main()
{
    //std::cout << "Hello!" << std::endl;

	auto logger = AtxLogger::getInstance(AtxLoggerConf::getConfiguration());
	logger->log(AtxLogger::Level::info, "");
	logger->log(AtxLogger::Level::info, "**************************************************************************************");
	logger->log(AtxLogger::Level::info, "********************************** STARTING PROGRAM **********************************");
	logger->log(AtxLogger::Level::info, "**************************************************************************************");
	logger->log(AtxLogger::Level::info, "");

    system("pause");
}