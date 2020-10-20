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

#define LOG(severity) COMPACT_GOOGLE_LOG_ ## severity
#define COMPACT_GOOGLE_LOG_INFO google::LogMessage( \
		 __FILE__, __LINE__)

class google {
public:
	static google& LogMessage(const char* file, int line) {
		printf("%s:%d] INFO LOG", file, line);
		return *this; // static �Ⱦ��� ȣ���� �ȵǰ� static ���� this ��� �Ұ�
	}
	void operator<<(int value) {		printf("%d", value);		
	}
};

int main() {
	LOG(INFO);
	LOG(INFO) << 5;
}