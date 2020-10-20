#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include <Windows.h>
#include <filesystem>

#include "time.h"

#define LOG(severity) severity.log(__FILE__,__func__,__LINE__)
#define OUT(severity) severity.send();
#define CLEAR(severity) severity.clear();
#define PRINT(severity) severity.print();

using namespace std;

int GetFilesize(string s) {		// 파일크기 측정 함수
	std::ifstream in_file(s, std::ios::binary);
	in_file.seekg(0, std::ios::end);
	return in_file.tellg();
}

class Logger {
	SYSTEMTIME time;
	vector<string> vs1;			// 파일명
	vector<string> vs2;			// 함수명
	vector<int> vl;				// 라인넘버
	int cnt = 0;				// 로그 갯수 cnt
	string fn = to_string(year) + '.' + to_string(mon) + '.' + to_string(day) + "_v0.4_log.txt";
public:
	void log(string s,const char* func, int line) {
		vs1.push_back(s);
		vs2.push_back(func);
		vl.push_back(line);
		GetLocalTime(&time);
		fn = to_string(year) + '.' + to_string(mon) + '.' + to_string(day) + "_v0.4_log.txt";
		cnt += 1;
	}
	void send() {
		ofstream out;
		int i = 1;
		while (1) {				// 사이즈 1kb 이상이면 뒤에 (i)를 붙여서 txt를 새로 만든다.
			int sz = GetFilesize(fn);
				if (sz < 1000) break; 
				else{
					fn.replace(19, 10, "");
					fn +=  +"(" + to_string(i) + ").txt";
					++i;
				}
			}
		out.open(fn, ios::app);			// 파일에 출력하는 함수
		for (int i = 0; i < cnt; i++) {
			out << vs1[i] << "\t" << vs2[i] << "\t" << vl[i] << endl;
		}	
	}
	void clear() { // 로그 txt 파일을 초기화 한다
		ofstream out;
		out.open(fn, ios::out);
	}
};

Logger INFO;
Logger WARN;
Logger ERR;
Logger FATAL;


int main() {
	LOG(INFO);
	LOG(INFO);
	LOG(INFO);
	LOG(INFO);
	LOG(INFO);
	OUT(INFO);
}

