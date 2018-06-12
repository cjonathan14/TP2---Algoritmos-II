/*
		MAIN.CC	
*/

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include "types.h"
#include "process_signal.h"
#include "err.h"
#include "cmdline.h"
#include "ft.h"

#include "main.h"

using namespace std;


static void opt_input(string const &);
static void opt_output(string const &);
static void opt_method(string const &);
static void opt_regression(string const &);
static void opt_error(string const &);
static void opt_help(string const &);
void set_transformer (ft* & transformer, method_t method);


/**************** Elementos globales ******************/
static option_t options[] = {
	{1, "i", "input", "-", opt_input, OPT_DEFAULT},
	{1, "o", "output", "-", opt_output, OPT_DEFAULT},
	{1, "m", "method", "-", opt_method, OPT_DEFAULT},
	{1, "r", "regression", "-", opt_regression, OPT_DEFAULT},
	{1, "e", "error", "-", opt_error, OPT_DEFAULT},
	{0, "h", "help", NULL, opt_help, OPT_DEFAULT},
	{0, },
};
method_t method;
bool regression;
double regr_error;
static istream *iss = 0;
static ostream *oss = 0;
static istream *regr_iss = 0;
static fstream ifs;
static fstream ofs;
static fstream regr_ifs;


/******************* **********************************/

static void
opt_input(string const &arg)
{
	if (arg == "-") {
		iss = &cin;
	}
	else {
		ifs.open(arg.c_str(), ios::in);
		iss = &ifs;
	}
	if (!iss->good()) {
		handle_err (ERROR_INPUT_FILE);
		exit(EXIT_FAILURE);
	}
}

static void
opt_output(string const &arg)
{
	if (arg == "-") {
		oss = &cout;
	} else {
		ofs.open(arg.c_str(), ios::out);
		oss = &ofs;
	}
	if (!oss->good()) {
		handle_err (ERROR_OUTPUT_FILE);
		exit(EXIT_FAILURE);
	}
}

static void
opt_method(string const &arg)
{
	if (arg == "-" || arg == CMD_ARG_METHOD_FFT) {
		method = FFT;
	} else if (arg == CMD_ARG_METHOD_IDFT) {
		method = IDFT;
	}
	else if(arg == CMD_ARG_METHOD_DFT) {
		method = DFT;
	}
	else if(arg == CMD_ARG_METHOD_IFFT) {
		method = IFFT;
	}

	else {
	handle_err (ERROR_PROGRAM_INVOCATION);
	exit(EXIT_FAILURE);
	}
}

static void
opt_regression (string const &arg)
{
	if (arg == "-") {
		regression = false;
	}
	else {
		regr_ifs.open(arg.c_str(), ios::in);
		regr_iss = &regr_ifs;
		if (!regr_iss->good()) {
			handle_err (ERROR_REGRESSION_FILE);
			exit(EXIT_FAILURE);
		}
		regression = true;
	}
}

static void
opt_error (string const &arg)
{
	if (arg == "-") {
		regr_error = ERROR_REGRESSION_DEFAULT;
	}
	else {
		stringstream convert (arg);
		if (!(convert >> regr_error) || regr_error < 0) {
			handle_err (ERROR_PROGRAM_INVOCATION);
			exit(EXIT_FAILURE);
		}
	}
}

static void
opt_help(string const &arg)
{
	cout << "cmdline [-m method] [-i file] [-o file] [-r file] [-e error]"
	     << endl;
	exit(EXIT_SUCCESS);
}

ft* construct_transformer (method_t method)
{
	switch(method){
		case DFT:
			return new (std::nothrow) direct_dft;
			break;
		case IDFT:
			return new (std::nothrow) inverse_dft;
			break;
		case FFT:
			return new (std::nothrow) direct_fft;
			break;
		case IFFT:
			return new (std::nothrow) inverse_fft;
			break;
		default:
			return NULL;
			break;
	}
}


int main(int argc, char * const argv[])
{
	status_t st;
	ft * transformer;
	bool regr_equals = true;

	cmdline cmdl(options);
	cmdl.parse(argc, argv);
	transformer = construct_transformer (method);
	if (transformer == NULL) {
		st = ERROR_OUT_OF_MEMORY;
		handle_err(st);
		return st;
	}
	st = process_signal(*iss, *oss, *regr_iss, transformer, regression, regr_error, regr_equals);
    if(st != OK) {
		handle_err(st);
		delete transformer;
		return st;
	}
	delete transformer;
	ifs.close();
	regr_ifs.close();
	ofs.close();
	if (ofs.fail() && oss != &cout) {
		st = ERROR_OUTPUT_FILE;
		handle_err(st);
		return st;
	}
	if (regression)
		return regr_equals? 0 : 1 ;
	return EXIT_SUCCESS;
}
