#define _CRT_SECURE_NO_WARNINGS
// ���� �����
//	- ���۸� ��å

#include <stdio.h>

// ���μ����� ���۵Ǹ� 3���� ������ ���� �����մϴ�.
// stdin - ǥ�� �Է� ��ġ(Ű����) ���� - ���� ���۸�
// stdout - ǥ�� ��� ��ġ(�͹̳�) ���� - ���� ���۸� ����
// stderr - ǥ�� ���� ��ġ(�͹̳�) ���� - ���۸� X

// �Ϲ� ����
//		��å - Ǯ ���۸�
//		������ ũ�Ⱑ �� ������ ȭ�鿡 ������ �߰����� �ʴ´�.

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


// Ű����� EOF�� ������ �� �ִ�.
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