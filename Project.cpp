#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <Windows.h>
#include <fstream>
using namespace std;

class LOG {
	vector<string> v;
public:
	LOG& operator<<(const string& s) {
		v.push_back(s);
		
		return *this;
	}
	void send() {
		SYSTEMTIME Time;
		GetLocalTime(&Time);


		ofstream out;
		out.open("log.txt", ios::app);

		for (auto e : v) {
			out << Time.wYear << "." << Time.wMonth << "." << Time.wDay << "\t"
				<< Time.wHour << "." << Time.wMinute << "." << Time.wSecond << "\t" << "\t" << e << endl;
		}
	}
	void clear() {
		ofstream out;
		out.open("log.txt");

	}
};


int main() {
	LOG a;
	a << "Hello, World!";
	a.clear();
	a.send();
}