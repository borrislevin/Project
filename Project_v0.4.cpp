#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include <Windows.h>

#include "time.h"

using namespace std;

class logger {
	SYSTEMTIME time;
	vector<string> vs1;
	vector<string> vs2;
	vector<int> vl;
	int cnt = 0;

public:
	void log(string s,const char* func, int line) {
		vs1.push_back(s);
		vs2.push_back(func);
		vl.push_back(line);
		cnt += 1;
	}
	void send() {
		GetLocalTime(&time);
		string fn = to_string(year) + '.' + to_string(mon) + '.' + to_string(day) + "_v0.4_log.txt";
		ofstream out;
		out.open(fn, ios::app);
		for (int i = 0; i < cnt; i++) {
			out << vs1[i] << "\t" << vs2[i] << "\t" << vl[0] << endl;
		}
		cout << cnt;
	}
};

logger INFO;
logger WARN;
logger ERR;
logger FATAL;

#define LOG(severity) severity.log(__FILE__,__func__,__LINE__)
#define OUT(severity) severity.send();
#define CLEAR(severity) severity.clear();
#define PRINT(severity) severity.print();

int main() {
	LOG(INFO);
	OUT(INFO);
	LOG(INFO);
	LOG(INFO);
	LOG(INFO);
	LOG(INFO);
	OUT(INFO);
}