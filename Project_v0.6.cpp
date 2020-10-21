#include"logging.h"

#define LOG(level) (Logger::getLogger(level).setCurrentContext(__FILE__,__func__, __LINE__))

#define INITIALIZE_LOGGERS()				\
  do {										\
        InfoLogger::getInstance();			\
		WarningLogger::getInstance();		\
		ErrorLogger::getInstance();			\
		FatalLogger::getInstance();			\
  } while (0)								\


std::map<Level, Logger*> Logger::loggers;


int main() {
	int n = 10;	char c = 'A';
	INITIALIZE_LOGGERS();
	LOG(INFO).write("tetntn");
	LOG(WARNING).write("tetntn");
	LOG(ERROR).write("tetntn");
	LOG(FATAL).write("tetntn");
	LOG(INFO).write("hello - %d %c", n, c);
}
