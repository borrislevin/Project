#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <Windows.h>
#include <fstream>
#include <filesystem>
using namespace std;


class LOG {
	vector<string> v;
	vector<string> v2;
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
				<< Time.wHour << "." << Time.wMinute << "." << Time.wSecond << "\t" 
				<<__FILE__ <<"\t"<< __LINE__
				<< "\t" << e << endl;
		}
		
	}
	void clear() {
		ofstream out;
		out.open("log.txt");		
	}

	int GetFilesize()	{
		std::ifstream in_file("log.txt", std::ios::binary);
		in_file.seekg(0, std::ios::end);
		return in_file.tellg();
	}
};

int main() {
	LOG a;
	int b;
	a << "Hello, World!";
	a << "Hello, World!2";
	a << "Hello, World!3";
	a << "Hello, World!4";
	a.send();
	b = a.GetFilesize();
	cout << b;
}

/* 
>>현재 경로 구하는 함수
char path[128];
if (GetCurrentDirectoryA(128, path) > 0) {
		printf("Working Directory : %s\n", path);

>>파일 크기 구하는 함수
b = a.GetFilesize();
cout << b << endl;;
	}*/
