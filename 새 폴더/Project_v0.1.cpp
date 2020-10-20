// 1. 메세지 전달은 못하겠다.
// 2. LOG(INFO), LOG(WARNING) 만 사용하고 나머지 기능 구현하자 - ok
// 3. 날짜 구현

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <Windows.h>
#include <fstream>
#include <filesystem>
using namespace std;


#define LOG(sev) Logger::log.sev();

class Logger {	
public:
	void INFO() {
		printf("sss");
	}
};

static Logger log;

int main() {
	LOG(INFO);
}