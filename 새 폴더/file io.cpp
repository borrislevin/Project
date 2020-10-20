#define _CRT_SECURE_NO_WARNINGS
// 파일 입출력
//	- 버퍼링 정책

#include <stdio.h>

// 프로세스가 시작되면 3개의 파일이 접근 가능합니다.
// stdin - 표준 입력 장치(키보드) 파일 - 라인 버퍼링
// stdout - 표준 출력 장치(터미널) 파일 - 라인 버퍼링 수행
// stderr - 표준 에러 장치(터미널) 파일 - 버퍼링 X

// 일반 파일
//		정책 - 풀 버퍼링
//		버퍼의 크기가 찰 때까지 화면에 내용을 추가하지 않는다.

int main() {
	char buf[32] = "Hello, World!";
	FILE *fp = fopen("c.txt", "w");

	if (fp == NULL) {
		fprintf(stderr, "file open error...\n");
		return 1;
	}

	fprintf(fp,"%s",buf);
	fflush(fp);
	getchar();
}


// 키보드로 EOF를 전달할 수 있다.
// Unix(Linux): Ctrl + D
// Windows : Ctrl + Z


#if 0
int main() {
	char buf[32];

	FILE *fp = fopen("a.txt", "r");
	FILE *fp2 = fopen("b.txt", "a");
	while (fscanf(fp,"%s", buf) == 1) {
		//printf("out : %s\n", buf);
		fprintf(fp2,"out : %s\n", buf);
	}
}




int main() {
	char buf[32];


	while (scanf("%s", buf) == 1) {
		printf("out : %s\n", buf);
	}

}

#endif


#if 0
int main() {
	//printf("hello");
	//fprintf(stdout,"hello\n");
	fprintf(stderr, "hello\n");
	

	while (1)
		;
}

#endif