//LOG(INFO) SEVERITY, MSG 호출까지 구현

#include <iostream>
using namespace std;]

#define LOG(severity) severity::call()

class INFO {
public:
	static void call() {
		cout << "test";
	}
	void operator<<(string s) {
		printf("test");
	}
};

//#define LOG(lvl) log_##(__func__,__LINE__,message)
//#define LOGG(severity) google::logg(severity)

int main() {

	LOG(INFO);
	LOG(INFO) << "testtt";
}