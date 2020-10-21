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


int GetFileSize(std::string s) {			// 파일크기 측정 함수
	std::ifstream in_file(s, std::ios::binary);
	in_file.seekg(0, std::ios::end);
	return in_file.tellg();
}

class Logger {

	SYSTEMTIME time;
	std::vector<std::string> vs1;			// 파일명
	std::vector<std::string> vs2;			// 함수명
	std::vector<int> vl;					// 라인넘버
	int cnt = 0;							// 로그 갯수 cnt
	std::string fn;							// 파일 이름

public:

	void log(std::string file, std::string func, int line) {
		vs1.push_back(file);
		vs2.push_back(func);
		vl.push_back(line);
		GetLocalTime(&time);
		fn = std::to_string(year) + '.' + std::to_string(mon) + '.' + std::to_string(day) + "_v0.4_.log";
		cnt += 1;
	}

	void send() {
		std::ofstream out;
		int i = 1;
		while (1) {								// 사이즈 1kb 이상이면 뒤에 (i)를 붙여서 txt를 새로 만든다.
			int sz = GetFileSize(fn);
			if (sz < 1000) break;
			else {
				fn.replace(15, 10, "");
				fn += +"(" + std::to_string(i) + ").txt";
				++i;
			}
		}
		out.open(fn, std::ios::app);			// 파일에 출력하는 함수
		for (int i = 0; i < cnt; i++) {
			out << vs1[i] << "\t" << vs2[i] << "\t" << vl[i] << std::endl;
		}
		out.close();
	}

	void clear() { // 로그 txt 파일을 초기화 한다
		std::ofstream out;
		out.open(fn, std::ios::out);
		out.close();
	}
};

Logger info;
Logger warn;
Logger err;
Logger fatal;


int main() {
	LOG(info);
	LOG(info);
	LOG(info);
	LOG(info);
	LOG(info);
	OUT(info);
}

