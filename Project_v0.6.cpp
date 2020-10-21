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
	INITIALIZE_LOGGERS();
	LOG(INFO).write("1");
	LOG(INFO).write("1");
	LOG(INFO).write("1");
	LOG(INFO).write("1");
	LOG(WARNING).write("2");
	LOG(ERROR).write("3");
	LOG(FATAL).write("4");
	LOG(INFO).showAll();
	LOG(FATAL).showAll();
}