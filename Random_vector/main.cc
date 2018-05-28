#include <fstream>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "../process_signal.h"
#include "../TempArray.h"
#include "../Complex.h"
#include "../err.h"

#define MAX_COMPONENT_VALUE 100

using namespace std;

int main(int argc, char * const argv[])
{
	Array<Complex> vo;
	fstream ofs(argv[2], ios::out);
	unsigned long int size;
	char * aux;
	Complex c;
	double random;

	size = strtoul(argv[1], &aux, 10);

	srand ( time(NULL) );

	for (size_t i=0; i < size; i++) {
		random = ( (double)rand()/RAND_MAX*2 - 1 ) * MAX_COMPONENT_VALUE;
		c.SetReal(random);
		random = (double)rand()/RAND_MAX*MAX_COMPONENT_VALUE - MAX_COMPONENT_VALUE;
		c.SetImag(random);
		vo.load_vector(c);
	}
	print_line(vo, ofs);

	ofs.close();
	return 0;
}