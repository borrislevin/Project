#include <stdio.h>


// 매크로
#define PI 3

// 매크로 이름 규칙
// - 대문자 와 _ 를 사용

//매크로 함수
#define POW(x) x*x

//
//void log(const char* message) {
//	printf("%s:%d] %s", __func__,__LINE__,message);
//}

void log(const char* func, int line, const char* message) {
	printf("%s:%d] %s\n", func, line, message);
}

#define LOG(message) log(__func__,__LINE__,message)

int main() {

	LOG("Hello World!");
	LOG("Program end!");
	LOG("Hello World!");
	//log(__func__, __LINE__, "Hello world");
	//log(__func__, __LINE__, "program end");
	/*printf("%lf\n", 3.14);
	printf("%d\n", POW(2));
	log("Hello, World!\n");
	log("Program Exit\n");*/
}