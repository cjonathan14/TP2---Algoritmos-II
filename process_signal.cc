/*
		PROCESS_SIGNAL.CC
*/

#include <iostream>
#include <fstream>
#include <limits>
#include <cstdlib>
#include <string>
#include <math.h>
#include "TempArray.h"
#include "err.h"
#include "types.h"
#include "Complex.h"
#include "ft.h"
#include "utils.h"

#include "process_signal.h"

using namespace std;

status_t process_signal(istream &is, ostream &os, istream &regr_is, ft * transformer, bool regression, double regr_error, bool & regr_equals)
{
	status_t st=OK;
	bool vector_equals;
	double error_result;
	Array<Complex> vi;
	Array<Complex> vo;
	Array<Complex> vr;

	if (!is.good()) {
		st = ERROR_INPUT_FILE;
		return st;
	}
	if (!os.good()) {
		st = ERROR_OUTPUT_FILE;
		return st;
	}
	if (regression && !regr_is.good()) {
		st = ERROR_REGRESSION_FILE;
		return st;
	}

	while(!is.eof()) {
		vi.clean_vector();
		vo.clean_vector();
		vr.clean_vector();
		st = read_line(vi, is);
		if(st != OK && st != ERROR_CORRUPT_LINE)
			return st;
		if(st ==  ERROR_CORRUPT_LINE) {
			handle_err(st);
			if (regression == true) {
				regr_is.ignore(numeric_limits<streamsize>::max(),'\n');
			}
		} 
		else {
			if (vi.getSize() == 0) {
				continue;
			}
			st = transformer->transform(vi,vo);
			if (st != OK) {
				return st;
			}
			if (regression == false) {
				st = print_line(vo, os);
				if (st != OK) {
					return st;
				}
			}
			else {
				if (regr_is.eof()) {
					st = ERROR_REGRESSION_FILE;
					return st;
				}
				st = read_line(vr, regr_is);
				if (st != OK && st != ERROR_CORRUPT_LINE) {
					return st;
				}
				if (st == ERROR_CORRUPT_LINE) {
					handle_err(st);
					vector_equals = false;
					error_result = -1;
				} else {
					st = compare_signals (vo, vr, regr_error, vector_equals, error_result);
					if (st != OK) {
						return st;
					}
				}
				if (!vector_equals)
					regr_equals = false;
				print_regression (os, vector_equals, vo.getSize(), error_result);
			}
		}

	} /*WHILE*/

	return OK;
}


status_t read_line (Array<Complex> & v, istream & is)
{
	status_t st;
	Complex c;

	if (is.fail())
		return ERROR_INPUT_FILE;
	if (v.getSize() != 0)
		return ERROR_INVALID_INPUT_VECTOR;

	while(is.peek() == ' ')
		is.ignore();
	if (is.peek() == '\n') {
		is.ignore();
		return OK;
	}

	while (is.peek() != '\n' && !is.eof()) {
		if (!(is >> c)) {
			is.clear();
			is.ignore(numeric_limits<streamsize>::max(),'\n');
			return ERROR_CORRUPT_LINE;
		}

		st = v.load_vector(c);
		if(st != OK)
			return st;

		while(is.peek() == ' ')
			is.ignore();
	}
	if (is.peek() == '\n')
		is.ignore();

	if(v.getSize() == 0)
		return OK;
	while(!is_pow_2(v.getSize())){
		v.load_vector(0);
	}

	return OK;
}

status_t print_line (Array<Complex> & v, ostream & os)
{
	size_t size = v.getSize();

	if (os.fail())
		return ERROR_OUTPUT_FILE;

	for (size_t i = 0; i < size; i++) {
		os << v[i];
		if (i < size-1)
			os << ' ';
	}
	os << '\n';
	if (os.fail())
		return ERROR_OUTPUT_FILE;

	return OK;
}

status_t compare_signals (Array<Complex> & v, Array<Complex> & vr, double error_limit, bool & equals, double & error_res)
{
	double norm_diff=0, norm_reff=0;

	if (v.getSize() != vr.getSize()) {
		equals = false;
		error_res = -1;
		return OK;
	}

	norm_diff = (v-vr).euclidean_norm();
	norm_reff = vr.euclidean_norm();

	if (norm_reff == 0) {
		if (norm_diff == 0) {
			equals = true;
			error_res = 0;
		} else {
			equals = false;
			error_res = -1;
		}
	} else {
		error_res = norm_diff/norm_reff;
		equals = (error_res < error_limit)? true : false;
	}
	return OK;
}

status_t print_regression (ostream & os, bool equals, size_t size, double error) 
{
	static size_t regression_counter = 1;
	string result;

	if (equals)
		result = "ok";
	else
		result = "error";
	os << "test " << regression_counter << ": " << result << " " << size << " " << error << endl;
	regression_counter++;
	return OK;
}
