#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define LOG(severity) Logger::getInstance(INFO)

enum Level {
	INFO,WARNING,ERROR,FATAL
};


class Logger {
	static Logger infoLogger;
	static Logger warnLogger;
	static Logger errLogger;
	static Logger fatalLogger;
public:

	static Logger& getInstance(Level severity) {
		if (severity == INFO)
			return infoLogger;
		else if (severity == FATAL)
			return fatalLogger;
	}

	Logger& operator<<(int value) {
		cout << value;
		return *this;
	}
	Logger& operator<<(const string& s) {
		cout << s;
		return *this;
	}
};


Logger Logger::infoLogger;
Logger Logger::fatalLogger;


int main() {
	LOG(INFO)<<"FUCK";
	LOG(FATAL) << "fuck";
}

