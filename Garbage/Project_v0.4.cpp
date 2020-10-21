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


int GetFileSize(std::string s) {			// ����ũ�� ���� �Լ�
	std::ifstream in_file(s, std::ios::binary);
	in_file.seekg(0, std::ios::end);
	return in_file.tellg();
}

class Logger {

	SYSTEMTIME time;
	std::vector<std::string> vs1;			// ���ϸ�
	std::vector<std::string> vs2;			// �Լ���
	std::vector<int> vl;					// ���γѹ�
	int cnt = 0;							// �α� ���� cnt
	std::string fn;							// ���� �̸�

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
		while (1) {								// ������ 1kb �̻��̸� �ڿ� (i)�� �ٿ��� txt�� ���� �����.
			int sz = GetFileSize(fn);
			if (sz < 1000) break;
			else {
				fn.replace(15, 10, "");
				fn += +"(" + std::to_string(i) + ").txt";
				++i;
			}
		}
		out.open(fn, std::ios::app);			// ���Ͽ� ����ϴ� �Լ�
		for (int i = 0; i < cnt; i++) {
			out << vs1[i] << "\t" << vs2[i] << "\t" << vl[i] << std::endl;
		}
		out.close();
	}

	void clear() { // �α� txt ������ �ʱ�ȭ �Ѵ�
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

