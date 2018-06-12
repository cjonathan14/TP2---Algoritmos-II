#include <fstream>
#include <iostream>
#include "../process_signal.h"
#include "../TempArray.h"
#include "../Complex.h"
#include "../err.h"

using namespace std;

int main(int argc, char * const argv[])
{
	fstream ifs1(argv[1], ios::in);
	fstream ifs2(argv[2], ios::in);
	Array<Complex> vi1;
	Array<Complex> vi2;
	bool equals;
	double err_res;

	read_line(vi1, ifs1);
	read_line(vi2, ifs2);

	compare_signals (vi1, vi2, 1e-3, equals, err_res);
	if (equals == false)
		return 1;

	return 0;
}
