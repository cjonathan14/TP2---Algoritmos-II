/*
		COMPLEX.CC
*/

#include <iostream>
#include <cmath>
#include "Complex.h"

using namespace std;


/*--------------COSTRUCTORS--------------*/
Complex::Complex(void){
	_real = 0;
	_imag = 0;
}

Complex::Complex(double r){
	_real = r;
	_imag = 0;
}

Complex::Complex(double r, double i){
	_real = r;
	_imag = i;
}

Complex::Complex(const Complex &c){
	_real = c._real;
	_imag = c._imag;
}

/*--------------DESTROYER-----------------*/
Complex::~Complex(void){
}

/*----------------GETTERS-----------------*/
double Complex::real(void) const{
	return _real;
}

double Complex::imag(void) const{
	return _imag;
}

/*-----------------SETTERS--------------*/
void Complex::SetReal(double r){
	_real = r;
}

void Complex::SetImag(double i){
	_imag = i;
}

/*------------------OPERATORS-------------*/

//ASSIGN
const Complex & Complex::operator=(const Complex &c){
	_real = c._real;
	_imag = c._imag;
	return *this;
}

const Complex & Complex::operator=(const double &d){
	_real = d;
	_imag = 0;
	return *this;
}

//MULTIPLY AND ASSIGN
const Complex & Complex::operator*=(const Complex &c){
	_real = _real * c._real - _imag * c._imag;
	_imag = _real * c._imag + _imag * c._real;
	return *this;
}

const Complex & Complex::operator*=(const double &d){
	_real *= d;
	_imag *= d;
	return *this;
}

//ADD AND ASSIGN
const Complex & Complex::operator+=(const Complex &c){
	_real += c._real;
	_imag += c._imag;
	return *this;
}

const Complex & Complex::operator+=(const double &d){
	_real += d;
	return *this;
}

//SUBTRACT AND ASSIGN
const Complex & Complex::operator-=(const Complex &c){
	_real -= c._real;
	_imag -= c._imag;
	return *this;
}
const Complex & Complex::operator-=(const double &d){
	_real -= d;
	return *this;
}



//MULTIPLICATION
Complex Complex::operator*(const Complex &c){
	return Complex(_real * c._real - _imag * c._imag,
					_real * c._imag + _imag * c._real);
}

Complex Complex::operator*(const double &d){
	return Complex(_real * d, _imag * d);
}

Complex operator*(const double d, const Complex &c){
	return Complex(c.real() * d, c.imag() * d);
}


//SUM
Complex Complex::operator+(const Complex &c){
	return Complex(_real + c._real, _imag + c._imag);
}

Complex Complex::operator+(const double &d){
	return Complex(_real + d, _imag);
}

Complex operator+(const double d, const Complex &c){
	return Complex(c.real() + d, c.imag());
}


//SUBTRACTION
Complex Complex::operator-(const Complex &c){
	return Complex(_real - c._real, _imag - c._imag);
}

Complex Complex::operator-(const double &d){
	return Complex(_real - d, _imag);
}

Complex operator-(const double d, const Complex &c){
	return Complex(c.real() - d, c.imag());
}


//DIVISION
Complex Complex::operator/(const double &d){
	return Complex(_real / d, _imag / d);
}

Complex Complex::operator/(const unsigned int &d){
	return Complex(_real / d, _imag / d);
}


//COMPARATORS
bool Complex::operator==(const Complex &b){
	return (_real != b._real || _imag != b._imag) ? false : true;

}

bool Complex::operator==(const double &d){
	return (_real != d || _imag != 0) ? false : true;
}

bool operator==(const double d, const Complex &c){
	return (c.real() != d || c.imag() != 0 ) ? false : true;
}

bool Complex::operator!=(const Complex &b){
	return (_real != b._real || _imag != b._imag) ? true : false;
}

bool Complex::operator!=(const double &d){
	return (_real != d || _imag != 0) ? true : false;
}

bool operator!=(const double d, const Complex &c){
	return (c.real() != d || c.imag() != 0) ? true : false;
}



/*----------OPERATIONS / FUNCTIONS ---------*/

Complex exp_imag(double d){
	return Complex(cos(d), sin(d));
}

void conjugate(Complex &c){
	c.SetImag(-c.imag());
}

double abs (Complex & c) {
	return sqrt(c.real()*c.real() + c.imag()*c.imag());
}

istream &operator>>(istream &is, Complex &c){
	bool good = false;
	bool bad = false;
	double re = 0;
	double im = 0;
	char ch = 0;

	if(is >> ch && ch == '('){
		if(is >> re &&
			is >> ch &&
			ch == ',' &&
			is >> im &&
			is >> ch &&
			ch == ')')
			good = true;
		else
			bad = true;
	}else if (is.good()){
		is.putback(ch);
		if(is >> re)
			good = true;
		else
			bad = true;
	}

	if(good){
		c.SetReal(re);
		c.SetImag(im);
	}
	if(bad)
		is.clear(ios::badbit);

	return is;
}

ostream &operator<<(ostream &os, const Complex &c){
	os << '(' << c.real() << ',' << c.imag() << ')';
	return os;
}
