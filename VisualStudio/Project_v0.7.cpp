#include"logging_v0.7.h"

#define LOG(level) (Logger::getLogger(level).setCurrentContext(__FILE__,__func__, __LINE__))


#define INITIALIZE_LOGGERS()				\
  do {										\
        InfoLogger::getInstance();			\
		WarningLogger::getInstance();		\
		ErrorLogger::getInstance();			\
		FatalLogger::getInstance();			\
  } while (0)								\


std::map<Level, Logger*> Logger::loggers;

int Logger::GetFileSize(std::string s) {					
	std::ifstream in_file(s, std::ios::binary);
	in_file.seekg(0, std::ios::end);
	return in_file.tellg();
}

int main() {
	int n = 10;	char c = 'A';
	INITIALIZE_LOGGERS();
	LOG(INFO).write("tetntn");
	LOG(WARNING).write("tetntn");
	LOG(ERROR).write("tetntn");
	LOG(FATAL).write("tetntn");
	LOG(INFO).write("hello - %d %c", n, c);
}
