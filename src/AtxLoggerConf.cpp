#include "..\include\AtxLoggerConf.h"
#include <fstream>
#include <sstream>

ATXLOGGER_API AtxLoggerConf AtxLoggerConf::configuration_;

AtxLoggerConf::AtxLoggerConf(std::string conf_file) {

	if (!conf_file.empty()) {

		std::ifstream file(conf_file.c_str());
		std::string line;

		if (file.is_open()) {

			std::string name;
			int value;

			while (std::getline(file, line)) {

				if (line.empty() || line[0] == '#' || line[0] == '/' || line[0] == '\\') {
					continue;
				}

				std::istringstream iss(line);
				std::string name;
				int value;

				if (iss >> name >> value) {

					if (name == "LEVEL") {
						level = value;
					}
					else if (name == "MAX_NUM_ROTATED_FILES") {
						num_max_rotated_files = value;
					}
					else if (name == "ASYNC") {
						async = value;
					}
				}
			}

			file.close();
		}
	}
}

AtxLoggerConf AtxLoggerConf::getConfiguration(std::string config_file) {

	if (config_file != AtxLoggerConf::configuration_.config_file_) {

		configuration_ = AtxLoggerConf(config_file);
	}

	return configuration_;
}

bool AtxLoggerConf::operator==(const AtxLoggerConf& other) const {

	return (this->level == other.level)
		&& (this->num_max_rotated_files == other.num_max_rotated_files)
		&& (this->async == other.async);
}

