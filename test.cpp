// LOG(INFO) 부터 구현하기
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <Windows.h>
#include <fstream>
#include <filesystem>
using namespace std;

#define INFO 0
#define WARNING 1
#define ERROR 2
#define FATAL 3

#define LOG(severity) Logging::LogMsg(severity)

class Msg {
	vector<string> v;
public:
	Msg& operator<<(const string& s) {
		v.push_back(s);
		return *this;
	}
};

class Logging {
public:
	static void LogMsg(int a) { printf("%d test\n",a); };
};

int main() {
	LOG(INFO);
}