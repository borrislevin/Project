// 1. �޼��� ������ ���ϰڴ�.
// 2. LOG(INFO), LOG(WARNING) �� ����ϰ� ������ ��� �������� - ok
// 3. ��¥ ����

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