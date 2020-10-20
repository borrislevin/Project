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

int GetFilesize(string s) {		// ����ũ�� ���� �Լ�
	std::ifstream in_file(s, std::ios::binary);
	in_file.seekg(0, std::ios::end);
	return in_file.tellg();
}

class Logger {
	SYSTEMTIME time;
	vector<string> vs1;			// ���ϸ�
	vector<string> vs2;			// �Լ���
	vector<int> vl;				// ���γѹ�
	int cnt = 0;				// �α� ���� cnt
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
		while (1) {				// ������ 1kb �̻��̸� �ڿ� (i)�� �ٿ��� txt�� ���� �����.
			int sz = GetFilesize(fn);
				if (sz < 1000) break; 
				else{
					fn.replace(19, 10, "");
					fn +=  +"(" + to_string(i) + ").txt";
					++i;
				}
			}
		out.open(fn, ios::app);			// ���Ͽ� ����ϴ� �Լ�
		for (int i = 0; i < cnt; i++) {
			out << vs1[i] << "\t" << vs2[i] << "\t" << vl[i] << endl;
		}	
	}
	void clear() { // �α� txt ������ �ʱ�ȭ �Ѵ�
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

