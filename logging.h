#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <iostream>
#include <time.h>
#include <map>
#include <stdarg.h>
#include <fstream>

enum Level {
	INFO,
	WARNING,
	ERROR,
	FATAL
};

class Logger {
public:
	virtual ~Logger() {}
	Logger(const std::string& f) : filename(f) {
	}

	void write(const std::string& message) {
		std::ofstream out;
		out.open(filename, std::ios::app);
		std::string header = this->getLogLevel() + " " + getTimestamp() + "] ";
		out << header << message << std::endl;
		out.close();
	}

	virtual std::string getLogLevel() const = 0;
	virtual std::string getFilename() const = 0;

	static Logger& getLogger(Level level) {
		return *loggers[level];
	}

	Logger& setCurrentContext(const std::string& f, int l) {
		funcname = f;
		line = l;
		return *this;
	}

protected:
	std::string getDay() const {
		time_t current = time(nullptr);
		struct tm* t = localtime(&current);
		std::string day = std::to_string(t->tm_year + 1900) + "." +
			std::to_string(t->tm_mon + 1) + "." +
			std::to_string(t->tm_mday);
		return day;
	}
	std::string getTimestamp() const {
		time_t current = time(nullptr);
		struct tm* t = localtime(&current);
		std::string time = std::to_string(t->tm_year + 1900) + "." +
			std::to_string(t->tm_mon + 1) + "." +
			std::to_string(t->tm_mday) + " " +
			std::to_string(t->tm_hour) + "." +
			std::to_string(t->tm_min) + "." +
			std::to_string(t->tm_sec);
		return time;
	}

	static void registLogger(Level level, Logger* logger) {
		loggers[level] = logger;
	}
private:
	std::string filename;
	std::string funcname;
	int line;
	static std::map<Level, Logger*> loggers;
};


class InfoLogger : public Logger {
public:
	InfoLogger() : Logger(getFilename()) {
		Logger::registLogger(INFO, this);
	}

	std::string getLogLevel() const override {
		return "INFO";
	}

	std::string getFilename() const override {
		std::string name;
		name = "INFO_" + getDay() + ".log";
		return name;
	}

	static InfoLogger& getInstance() {
		static InfoLogger instance;
		return instance;
	}

private:
	std::string name = "INFO";
};



class WarningLogger : public Logger {
public:
	WarningLogger() : Logger(getFilename()) {
		Logger::registLogger(WARNING, this);
	}

	std::string getLogLevel() const override {
		return "WARNING";
	}

	std::string getFilename() const override {
		std::string name;
		name = "WARNING_" + getDay() + ".log";
		return name;
	}

	static WarningLogger& getInstance() {
		static WarningLogger instance;
		return instance;
	}

private:
	std::string name = "WARNING";
};

class ErrorLogger : public Logger {
public:
	ErrorLogger() : Logger(getFilename()) {
		Logger::registLogger(ERROR, this);
	}

	std::string getLogLevel() const override {
		return "ERROR";
	}

	std::string getFilename() const override {
		std::string name;
		name = "ERROR_" + getDay() + ".log";
		return name;
	}

	static ErrorLogger& getInstance() {
		static ErrorLogger instance;
		return instance;
	}

private:
	std::string name = "ERROR";
};



class FatalLogger : public Logger {
public:
	FatalLogger() : Logger(getFilename()) {
		Logger::registLogger(FATAL, this);
	}

	std::string getLogLevel() const override {
		return "FATAL";
	}

	std::string getFilename() const override {
		std::string fname;
		fname = "FATAL_" + getDay() + ".log";
		return fname;
	}

	static FatalLogger& getInstance() {
		static FatalLogger instance;
		return instance;
	}

private:
	std::string name = "FATAL";
};

#define LOG(level) (Logger::getLogger(level).setCurrentContext(__func__, __LINE__))

#define INITIALIZE_LOGGERS()				\
  do {										\
        InfoLogger::getInstance();			\
		WarningLogger::getInstance();		\
		ErrorLogger::getInstance();			\
		FatalLogger::getInstance();			\
  } while (0)  


std::map<Level, Logger*> Logger::loggers;
