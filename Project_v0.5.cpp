#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <iostream>
#include <time.h>
#include <map>
#include <stdarg.h>
using namespace std;

enum Level {
	INFO,
};

class Logger {
public:
	virtual ~Logger() {}

	Logger(const std::string& f) : filename(f) {

	}

	void write(const char* fmt, ...) {
		FILE* fp = fopen(filename.c_str(), "a");
		if (fp == nullptr) {
			std::cout<<"파일없음";
		}

		char header[64];
		sprintf(header, "%s %s %s:%d] ",
			getLogLevel().c_str(), getTimestamp().c_str(), funcname.c_str(), line);

		va_list start;
		va_start(start, fmt);

		char message[128];
		//vsprintf(message, fmt, start);

		fprintf(fp, "%s %s\n", header, message);

		fclose(fp);
	}

	void write(const std::string& message) {
		FILE* fp = fopen(filename.c_str(), "a");
		if (fp == nullptr) {
		}

		char header[64];
		sprintf(header, "%s %s %s:%d] ",
			getLogLevel().c_str(), getTimestamp().c_str(), funcname.c_str(), line);

		fprintf(fp, "%s %s\n", header, message.c_str());
		fclose(fp);
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
	std::string getTimestamp() const {
		time_t current = time(nullptr);
		struct tm* t = localtime(&current);

		char buf[64];
		sprintf(buf, "%d.%d.%d %d:%d:%d",
			t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);

		return std::string(buf);
	}

	static void registLogger(Level level, Logger* logger) {
		loggers[INFO] = logger;
	}
private:
	std::string filename;

	std::string funcname;
	int line;

	static std::map<Level, Logger*> loggers;
};


std::map<Level, Logger*> Logger::loggers;


class InfoLogger : public Logger {
public:
	InfoLogger() : Logger(getFilename()) {
		Logger::registLogger(INFO, this);
	}

	std::string getLogLevel() const override {
		return "INFO";
	}

	std::string getFilename() const override {
		char buf[64];
		sprintf(buf, "INFO_%s.log", getTimestamp().c_str());
		return buf;
	}

	static InfoLogger& getInstance() {
		static InfoLogger instance;
		return instance;
	}

private:

};

#define LOG(level) (Logger::getLogger(level).setCurrentContext(__func__, __LINE__))
#define INITIALIZE_LOGGERS()        \
  do {                              \
        InfoLogger::getInstance();  \
                                    \
  } while (0)  


int main() {
	// InfoLogger l;
	// l.setCurrentContext(__func__, __LINE__); l.write("hello");

	INITIALIZE_LOGGERS();

	LOG(INFO).write("hello world");
	//LOG(INFO).write("%d %d %d", 42, 32, 10);


}