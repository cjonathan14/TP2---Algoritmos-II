#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main (int argc, char * argv[])
{
	size_t i, n;
	char random;
	char * aux;
	FILE * fp;

	srand ( time(NULL) );
	fp = fopen (argv[1], "wb");
	n = strtoul (argv[2], &aux, 10);

	for (i = 0; i < n; i++) {
		random = rand();
		fwrite (&random, sizeof(char), 1, fp);
	}

	fclose (fp);
	return 0;
}
