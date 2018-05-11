#include <stdio.h>

int main(int argc, char *argv[]) {
	int zero = 0;
	char buffer[10];

	printf("buffer address\t= %x\n", (int)buffer);
	printf("zero address\t= %x\n", (int)&zero);

	fgets(buffer, 64, stdin);
	printf("zero = %d\n", zero);
	return 0;
}
