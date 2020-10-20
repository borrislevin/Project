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

#define LOG(lvl) lvl::call(__func__,__LINE__)

class Msg {	
	virtual void call() = 0;	
};

class INFO :public Msg {
	vector<string> v;
public:
	static void call(const char* func, int line) {
		printf("%s:%d] INFO LOG", func, line);
	}	
};

int main() {
	LOG(INFO);
}