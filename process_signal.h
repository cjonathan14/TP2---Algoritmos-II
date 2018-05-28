/*
		PROCESS_SIGNAL.H
*/

#ifndef PROCESS_SIGNAL__H
#define PROCESS_SIGNAL__H

#include <iostream>
#include "TempArray.h"
#include "err.h"
#include "types.h"
#include "Complex.h"
#include "ft.h"
#include "utils.h"

using namespace std;

#define MAX_ZERO_VALUE 1e-6
#define TOLERANCE 0.01
#define MAX_ERRORS_PERCENTAGE 0.1

status_t process_signal(istream &is, ostream &os, istream &regr_is,  ft * transformer, bool regression, double error_regression, bool & regr_equals);
status_t read_line (Array<Complex> & v, istream & is);
status_t print_line (Array<Complex> & v, ostream & os);
status_t compare_signals (Array<Complex> & v, Array<Complex> & vr, double error_limit, bool & equals, double & error_res);
status_t print_regression (ostream & os, bool equals, size_t size, double error);


#endif
