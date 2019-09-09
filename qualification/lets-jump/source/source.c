#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void hmm(long long num, char* s) {
	FILE* fp;
	fp = fopen("flag.txt", "r");
	char* flag = malloc(40);
	fscanf(fp, "%s", flag);
	if(num == 1 && !strcmp(s, "Hewhewbrew")) {
		puts(flag);
		exit(0);
	}
}

void jump_on_me() {
	char inp[1];
	fgets(inp, 60, stdin);
}

int main() {
	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);
	puts("Enter input");
	jump_on_me();
}