#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <Windows.h>
using namespace std;

class LOG {
	vector<string> v;
public:
	LOG& operator<<(const string& s) {
		v.push_back(s);
		time_t result = time(nullptr);
		SYSTEMTIME curTime;	
		GetLocalTime(&curTime);
		cout << curTime.wHour << ":"
			<< curTime.wMinute << ":"
			<< curTime.wSecond << "     " << s << endl;
		for (auto e : v) {
			cout << e << endl;
		}
		return *this;
	}
};


int main() {
	LOG a;
	a << "Hello, World!";
	a << "Hello, World!";
	a << "Hello, World!";
	
}