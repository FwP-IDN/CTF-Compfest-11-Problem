#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/mman.h>
#include <unistd.h>


char greeting[] = "Write your motivation and wish here";
char fixme[] = "Good lick and have fun. I wish";
char wishing[] = "I wish you can change my behavior";

void* chunk[50];
size_t chunksize[50];

int main();
int endmain();


enum {
  REG_R8 = 0,
  REG_R9,
  REG_R10,
  REG_R11,
  REG_R12,
  REG_R13,
  REG_R14,
  REG_R15,
  REG_RDI,
  REG_RSI,
  REG_RBP,
  REG_RBX,
  REG_RDX,
  REG_RAX,
  REG_RCX,
  REG_RSP,
  REG_RIP,
  REG_EFL,
  REG_CSGSFS,                /* Actually short cs, gs, fs, __pad0.  */
  REG_ERR,
  REG_TRAPNO,
  REG_OLDMASK,
  REG_CR2
};

size_t max(size_t a, size_t b) {
	if(a > b) {
		return a;
	}
	return b;
}

void changeOneCharacter(char* str) {
	char buf[4];
	int len = strlen(str);
	printf("Which one?\nIndex: ");
	int index;
	fgets(buf, 4, stdin);
	index = atoi(buf);
	if(index < len && index >= 0) {
		printf("What character?\nCharacter: ");
		fgets(buf, 4, stdin);
		*(str + index) = buf[0];
	}

}

void handle_unmapped_region(int nSignum, siginfo_t* si, void* vcontext) {
	if(si -> si_signo == 11 && si -> si_code == 1) {
		ucontext_t* context = (ucontext_t*)vcontext;
		context->uc_mcontext.gregs[REG_RIP]++;
	}
	else {
		exit(1);
	}
}

void initialize() {
	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);
	changeOneCharacter(fixme);
	long long page_size = getpagesize();
	long long extended_main = (long long)main - (long long)((long long)main % page_size);
	long long extended_endmain = (long long)endmain + ((page_size - ((long long)endmain % page_size)) % page_size);
	if(mprotect((void *)extended_main, (size_t)(extended_endmain - extended_main), PROT_READ | PROT_WRITE | PROT_EXEC)) {
		exit(1);
	}
	struct sigaction action;
	memset(&action, 0, sizeof(struct sigaction));
	action.sa_flags = SA_SIGINFO;
	action.sa_sigaction = handle_unmapped_region;
	sigaction(SIGSEGV, &action, NULL);
}


void _pause() {

}

void create_message() {
	char buffer[0xa8];
	int index;
	size_t size;
	printf("Index: ");
	scanf("%d", &index);
	printf("Size: ");
	scanf("%lu", &size);
	if(size > (size_t)0xa8) {
		exit(1);
	}
	chunk[index] = malloc(size);
	chunksize[index] = size;
	printf("Message: ");
	size_t num_read = read(0, buffer, chunksize[index]);
	if(buffer[num_read - 1] == '\n' && num_read > 0) {
		num_read--;
	}
	memcpy(chunk[index], buffer, num_read);
}

void retrieve_message() {
	int index;
	printf("Index: ");
	scanf("%d", &index);
	size_t written = max((size_t)0, write(1, chunk[index], chunksize[index]));
	for(int i = 0; i < chunksize[index] - written; i++) {
		putchar(0);
	}
	putchar(10);
	putchar('D');
	putchar('O');
	putchar('N');
	putchar('E');
	putchar(10);
}

void update_message() {
	char buffer[0xa8];
	int index;
	printf("Index: ");
	scanf("%d", &index);
	printf("New Message: ");
	size_t num_read = read(0, buffer, chunksize[index]);
	if(buffer[num_read - 1] == '\n' && num_read > 0) {
		num_read--;
	}
	memcpy(chunk[index], buffer, num_read);
}

void delete_message() {
	int index;
	printf("Index: ");
	scanf("%d", &index);
	free(chunk[index]);
}

int main() {
	initialize();


	// int CON = 8;
	// void* a[CON];
	// void* c[CON];
	// for(int i = 0; i < CON; i++) {
	// 	a[i] = malloc(0xb0);
	// 	malloc(0x10);
	// 	c[i] = malloc(0x400);
	// }
	// void *b = malloc(0x10);
	// for(int i = 0; i < CON; i++) {
	// 	free(a[i]);
	// 	free(c[i]);
	// }
	// _pause();

	while (1) {
		puts(greeting);
		puts(fixme);
		puts(wishing);
		int choose;
		printf("Enter your choice: ");
		scanf("%d", &choose);
		if(choose == 1) {
			// CREATE
			create_message();
		}
		else if(choose == 2) {
			// RETRIEVE
			retrieve_message();
		}
		else if(choose == 3) {
			// UPDATE
			update_message();
		}
		else if(choose == 4) {
			// DELETE
			delete_message();
		}
	}

	if(!strcmp(fixme, "Good luck and have fun. I wish")) {
		system("cat flag.txt");
	}

}

int endmain() {

}
