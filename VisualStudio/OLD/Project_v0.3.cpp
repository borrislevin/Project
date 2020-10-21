#include <iostream>
#include <string>
#include <vector>
using namespace std;

// 내가 하고 싶은것
// 로그 호출하면서 시간과 라인을 전달
// 함수 호출

enum Level {INFO, WAR, ERR, FAT};

#define LOG(severity) Logger::getInstance(severity,__func__,__LINE__)

class Logger {
	static Logger infoLogger;
	static Logger warLogger;
	static Logger errLogger;
	static Logger fatLogger;
	vector<string> v;
public:
	static Logger& getInstance(const char* func, int line){
		cout << func << line;
		
		return infoLogger;
	}

	Logger& operator<<(const string& s) {
		cout << s;
		return *this;
	}
};

Logger Logger::infoLogger;
Logger Logger::warLogger;
Logger Logger::errLogger;
Logger Logger::fatLogger;

int main() {
	cout << FAT;
}
