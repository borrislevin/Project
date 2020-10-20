#include <iostream>
#include <vector>
#include <string>

class Logger {
public:
	std::vector<std::string> v_file;
	std::vector<std::string> v_func;
	std::vector<int> v_line;
};

class Info : public Logger{
	static Info infologger;
public:
	static Info& getInstance(std::string file, std::string func, int line) {
		v_file.push_back(file);
		v_func.push_back(func);
		v_line.push_back(line);
		return infologger;
	}
};

#define LOG(severity) severity::getInstance(__FILE__,__func__,__LINE__)


int main() {
	LOG(Info);
}