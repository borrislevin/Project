#include "logging_v0.7.h"

class Logger {
public:
	virtual ~Logger() {}
	Logger(const std::string& f) : filename(f) {	}

	void write(const char* fmt, ...) {
	}
	virtual std::string getLogLevel() const = 0;
	virtual std::string getFilename() const = 0;

	static Logger& getLogger(Level level) {
	}

	Logger& setCurrentContext(const std::string& file, const std::string& func, int l) {
	}

	int GetFileSize(std::string s) {
	}

	void show(const std::string& message) {
	}

	void showAll() {
	}

protected:
	std::string getDay() const {
	}

	std::string getTime() const {
	}
	std::string getTimestamp() const {
	}

	static void registLogger(Level level, Logger* logger) {
	}
};

//Children
//---------------------------------------------------------------------------------------

class InfoLogger : public Logger {
public:
	InfoLogger() : Logger(getFilename()) {
	}

	std::string getLogLevel() const override {
	}

	std::string getFilename() const override {
	}

	static InfoLogger& getInstance() {
	}
};



class WarningLogger : public Logger {
public:
	WarningLogger() : Logger(getFilename()) {
	}

	std::string getLogLevel() const override {
	}

	std::string getFilename() const override {
	}

	static WarningLogger& getInstance() {
	}
};


class ErrorLogger : public Logger {
public:
	ErrorLogger() : Logger(getFilename()) {
		Logger::registLogger(ERROR, this);
	}

	std::string getLogLevel() const override {
	}

	std::string getFilename() const override {
	}

	static ErrorLogger& getInstance() {
		static ErrorLogger instance;
		return instance;
	}
};



class FatalLogger : public Logger {
public:
	FatalLogger() : Logger(getFilename()) {
		Logger::registLogger(FATAL, this);
	}

	std::string getLogLevel() const override {
	}

	std::string getFilename() const override {
	}

	static FatalLogger& getInstance() {
	}
};

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
