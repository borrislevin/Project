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

#define LOG(severity) COMPACT_GOOGLE_LOG_ ## severity
#define COMPACT_GOOGLE_LOG_INFO google::LogMessage( \
		 __FILE__, __LINE__)

class google {
public:
	static google& LogMessage(const char* file, int line) {
		printf("%s:%d] INFO LOG", file, line);
		return *this; // static 안쓰면 호출이 안되고 static 빼면 this 사용 불가
	}
	void operator<<(int value) {		printf("%d", value);		
	}
};

int main() {
	LOG(INFO);
	LOG(INFO) << 5;
}