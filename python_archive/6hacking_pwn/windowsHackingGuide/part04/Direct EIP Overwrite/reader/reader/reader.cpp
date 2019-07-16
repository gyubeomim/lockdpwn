#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char* argv[])
{
	char readbuf[2000] = {0,};
	char printbuf[500] = {0,};
	printf(" # text reader #\n");
	if(argc!=2) {
		printf(" Usage : reader.exe filename\n", argv[0]);
		exit(1);
	}
	FILE *f = fopen(argv[1], "r");
	fgets(readbuf,2000,f);
	strcpy(printbuf,readbuf);
	printf("File Contents : %s\n", printbuf); 
}