#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <Windows.h>
#include <fstream>
#include <filesystem>
using namespace std;

/*
 10.20 목표 : 기능구현 (1,4,5,6)
1.모듈 또는 소스 파일의 어떤 함수, 어떤 위치에서 발생한 정보인지 알수 있어야 한다.
	=> __FILE__, __LINE__ check
2.로깅 정보가 다양한 목적지로 저장 / 전송 될 수 있어야 한다.
	=> ..??
3.로깅의 출력 레벨을 조정할 수 있어야 한다.
	=> LOG(INFO)등 정의 필요
4.로깅의 정확한 날짜와 시간을 기록할 수 있어야 한다.
	=> 가능
5.로깅을 날짜별 시간별로 다른 파일로 기록할 것.
	=> TRY
6.로그 파일이 지정된 크기를 넘어설 경우, 자동으로 다른 파일에 기록할 수 있어야 한다.
	=> TRY
*/


class LOG {
	vector<string> v;
	vector<string> v2;
public:
	LOG& operator<<(const string& s) {
		v.push_back(s);		
		return *this;
	}
	void TimetoString() {
		SYSTEMTIME Time;
		GetLocalTime(&Time);
		cout << Time.wYear+Time.wDay;
		
	}
	void send() {
		SYSTEMTIME Time;
		GetLocalTime(&Time);
		ofstream out;
		out.open("log.txt", ios::app);

		for (auto e : v) {	// string으로 만들면 어떨까
			cout << Time.wYear << "." << Time.wMonth << "." << Time.wDay << "\t"
				<< Time.wHour << "." << Time.wMinute << "." << Time.wSecond << "\t" 
				<<__FILE__ <<"\t"<< __LINE__
				<< "\t" << e << endl; 
		}
		
	}
	void clear() {
		ofstream out;
		out.open("log.txt");		
	}

	int GetFilesize()	{	//파일 크기 얻는 함수
		std::ifstream in_file("log.txt", std::ios::binary);
		in_file.seekg(0, std::ios::end);
		return in_file.tellg();
	}
};

int main() {
	LOG a;

	a << "Hello, World!";
	a << "Hello, World!2";
	a << "Hello, World!3";
	a << "Hello, World!4";
	a.send();
	a.TimetoString();
	/*
	int b;
	b = a.GetFilesize();
	cout << b;*/
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
