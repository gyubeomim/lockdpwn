#include <stdio.h>

int main(int argc, char *argv[]) {
	char buffer[100];
	fgets(buffer, 128, stdin);
	return 0;
}
