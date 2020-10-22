#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <iostream>
#include <time.h>
#include <map>
#include <stdarg.h>
#include <fstream>
#include <vector>
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;



enum Level {
	INFO,
	WARNING,
	ERROR,
	FATAL
};

class Logger {
public:
	virtual ~Logger() {}
	Logger(const std::string& f) : filename(f) {	}
	void write(const char* fmt, ...);
	void write_each(const char* fmt, ...);
	virtual std::string getLogLevel() const = 0;
	virtual std::string getFilename() const = 0;
	static Logger& getLogger(Level level);
	Logger& setCurrentContext(const std::string&, const std::string&, int);
	int getFileSize(std::string);
	void show(const std::string&);
	void showLogToday();
	void showLogOneday();
	
protected:
	std::string getDay() const;
	std::string getTime() const;
	std::string getTimestamp() const;
	static void registLogger(Level, Logger*);

private:
	std::string filename;
	std::string location;	
	int limit = 2000;
	std::vector<std::string> information;
	static std::map<Level, Logger*> loggers;
	int cnt = 0;
};

//Children
//---------------------------------------------------------------------------------------
class InfoLogger : public Logger {
public:
	InfoLogger() : Logger(getFilename()) {
		Logger::registLogger(INFO, this);
	}
	std::string getLogLevel() const override;
	std::string getFilename() const override;
	static InfoLogger& getInstance();
private:
	InfoLogger(const InfoLogger&) = delete;
	void operator=(const InfoLogger&) = delete;
};

class WarningLogger : public Logger {
public:
	WarningLogger() : Logger(getFilename()) {
		Logger::registLogger(WARNING, this);
	}
	std::string getLogLevel() const override;
	std::string getFilename() const override;
	static WarningLogger& getInstance();
private:
	WarningLogger(const WarningLogger&) = delete;
	void operator=(const WarningLogger&) = delete;
};

class ErrorLogger : public Logger {
public:
	ErrorLogger() : Logger(getFilename()) {
		Logger::registLogger(ERROR, this);
	}
	std::string getLogLevel() const override;
	std::string getFilename() const override;
	static ErrorLogger& getInstance();
private:
	ErrorLogger(const ErrorLogger&) = delete;
	void operator=(const ErrorLogger&) = delete;
};

class FatalLogger : public Logger {
public:
	FatalLogger() : Logger(getFilename()) {
		Logger::registLogger(FATAL, this);
	}
	std::string getLogLevel() const override;
	std::string getFilename() const override;
	static FatalLogger& getInstance();
private:
	FatalLogger(const FatalLogger&) = delete;
	void operator=(const FatalLogger&) = delete;
};
