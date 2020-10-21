#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <iostream>
#include <time.h>
#include <map>
#include <stdarg.h>
#include <fstream>
#include <vector>

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

	void write(const std::string& message) {
		std::ofstream out;
		std::string temp = filename + ".log";
		std::string temp2 = filename + "(1).log";
		int i = 1;
		while (1) {										// 사이즈 limit 이상이면 뒤에 (i)를 붙여서 txt를 새로 만든다.
			filesize = GetFileSize(temp);
			if (filesize < limit) {
				break;
			}
			else {
				std::string tem2 = "_(" + std::to_string(i) + ").log";
				temp.replace(temp.end() - 4, temp.end(), tem2);
				++i;
			}
		}
		out.open(temp, std::ios::app);
		std::string tempinfo = getLogLevel() + location + getTimestamp() + " " + message;
		out <<tempinfo << std::endl;
		this->information.push_back(tempinfo);
		out.close();
	}

	virtual std::string getLogLevel() const = 0;
	virtual std::string getFilename() const = 0;

	static Logger& getLogger(Level level) {
		return *loggers[level];
	}

	Logger& setCurrentContext(const std::string& file, const std::string& func, int l) {	// 위치 정보
		location = file + " " + func + "_" + "line:" + std::to_string(l) + " ";
		cnt++;
		return *this;
	}

	int GetFileSize(std::string s) {					// 파일 크기
		std::ifstream in_file(s, std::ios::binary);
		in_file.seekg(0, std::ios::end);
		return in_file.tellg();
	}

	void show(const std::string& message) {				
		std::cout << this->getLogLevel()<<location<<getTimestamp()<<"] "<<message<< std::endl;
	}

	void showAll() {		
		for (int i = 0; i < cnt-1; i++) {				
			std::cout << information[i] << std::endl;
		}
	}

protected:
	std::string getDay() const {
		time_t current = time(nullptr);
		struct tm* t = localtime(&current);
		std::string day = std::to_string(t->tm_year + 1900) + "." +
			std::to_string(t->tm_mon + 1) + "." +
			std::to_string(t->tm_mday) + "_" +
			std::to_string(t->tm_hour) + "_" + std::to_string(t->tm_min);
		return day;
	}
	std::string getTimestamp() const {
		time_t current = time(nullptr);
		struct tm* t = localtime(&current);
		std::string time = getDay() + "_" + std::to_string(t->tm_sec);
		return time;
	}

	static void registLogger(Level level, Logger* logger) {
		loggers[level] = logger;
	}

private:
	std::string filename;
	std::string location;
	int filesize;
	int limit=2000;
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

	std::string getLogLevel() const override {
		return "INFO_";
	}

	std::string getFilename() const override {
		std::string name;
		name = "INFO_" + getDay();
		return name;
	}

	static InfoLogger& getInstance() {
		static InfoLogger instance;
		return instance;
	}

private:
	InfoLogger(const InfoLogger&) = delete;
	void operator=(const InfoLogger&) = delete;
};



class WarningLogger : public Logger {
public:
	WarningLogger() : Logger(getFilename()) {
		Logger::registLogger(WARNING, this);
	}

	std::string getLogLevel() const override {
		return "WARNING_";
	}

	std::string getFilename() const override {
		std::string name;
		name = "WARNING_" + getDay();
		return name;
	}

	static WarningLogger& getInstance() {
		static WarningLogger instance;
		return instance;
	}

private:
	WarningLogger(const WarningLogger&) = delete;
	void operator=(const WarningLogger&) = delete;
};

class ErrorLogger : public Logger {
public:
	ErrorLogger() : Logger(getFilename()) {
		Logger::registLogger(ERROR, this);
	}

	std::string getLogLevel() const override {
		return "ERROR_";
	}

	std::string getFilename() const override {
		std::string name;
		name = "ERROR_" + getDay();
		return name;
	}

	static ErrorLogger& getInstance() {
		static ErrorLogger instance;
		return instance;
	}

private:
	ErrorLogger(const ErrorLogger&) = delete;
	void operator=(const ErrorLogger&) = delete;
};



class FatalLogger : public Logger {
public:
	FatalLogger() : Logger(getFilename()) {
		Logger::registLogger(FATAL, this);
	}

	std::string getLogLevel() const override {
		return "FATAL_";
	}

	std::string getFilename() const override {
		std::string fname;
		fname = "FATAL_" + getDay();
		return fname;
	}

	static FatalLogger& getInstance() {
		static FatalLogger instance;
		return instance;
	}

private:
	FatalLogger(const FatalLogger&) = delete;
	void operator=(const FatalLogger&) = delete;
};

