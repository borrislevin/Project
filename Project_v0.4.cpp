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
	vector<string> vs;
	vector<int> vl;
public:
	void log(const char* func, int line) {
		vs.push_back(func);
		vl.push_back(line);
	}
	void send() {
		GetLocalTime(&time);
		string fn = to_string(year) + '.' + to_string(mon) + '.' + to_string(day) + "_v0.4_log.txt";
		ofstream out;
		out.open(fn, ios::app);
		out << vs[0] << "\t" << vl[0] << endl;
	}
};

logger INFO;
logger WARN;
logger ERR;
logger FATAL;

#define LOG(severity) severity.log(__func__,__LINE__)
#define OUT(severity) severity.send();
#define CLEAR(severity) severity.clear();

int main() {
	LOG(INFO);
	OUT(INFO);
}