/*
        FT.H
*/

#ifndef FT__H
#define FT__H

#define _USE_MATH_DEFINES
#include <math.h>

#include "TempArray.h"
#include "Complex.h"
#include "err.h"
#include "utils.h"


class ft {

public:
virtual ~ft() {};
virtual status_t transform(Array<Complex> &, Array<Complex> &) = 0;
};

class dft:public ft {
public:

virtual ~dft() {};

virtual status_t transform (Array<Complex> &, Array<Complex> &) = 0;

status_t dft_transform(Array<Complex> & input_vector, Array<Complex> & output_vector) {
        status_t st = OK;
        unsigned int i,j;
        unsigned int size;
        Complex acum;

        if(output_vector.getSize() != 0)
            return ERROR_INVALID_OUTPUT_VECTOR;
        
        size = input_vector.getSize();        
        if(size != 0){
            if(!is_pow_2(size))
                return ERROR_INVALID_INPUT_VECTOR;
            for(i = 0 ; i < size ; i++)
            {
                acum.SetImag(0);
                acum.SetReal(0);
                for( j = 0; j < size ; j++)
                {
                    acum+=input_vector[j]*exp_imag(-2*M_PI*i*j/size);
                }
                if(output_vector.load_vector(acum)!=OK)
                    st = ERROR_OUT_OF_MEMORY;
            }
        }

        return st;
}
};



class direct_dft:public dft{
public:

virtual ~direct_dft() {};

virtual status_t transform(Array<Complex> & input_vector, Array<Complex> & output_vector)
{ 
    if(output_vector.getSize() != 0)
        return ERROR_INVALID_OUTPUT_VECTOR;
    if(!is_pow_2(input_vector.getSize()))
        return ERROR_INVALID_INPUT_VECTOR;
    return dft_transform(input_vector, output_vector);
} 

};

class inverse_dft:public dft{
public:

virtual ~inverse_dft() {};

virtual status_t transform(Array<Complex> & input_vector, Array<Complex> & output_vector) 
{
        status_t st = OK;
        unsigned int i;
        unsigned int size;

        if(output_vector.getSize() != 0)
            return ERROR_INVALID_OUTPUT_VECTOR;
        
        size = input_vector.getSize();

        if(size != 0) {
            if(!is_pow_2(size))
                return ERROR_INVALID_INPUT_VECTOR;

            for(i = 0; i < size; i++)
                conjugate(input_vector[i]);

            st = dft_transform(input_vector, output_vector);
                if(st != OK) {
					return st;
				}

            for(i = 0; i < size; i++){
                conjugate(output_vector[i]);
                output_vector[i] = output_vector[i] / size;
            }

        }

        return st;
}

};


class fft:public ft {
public:

virtual ~fft() {};

virtual status_t transform (Array<Complex> &, Array<Complex> &) = 0;

status_t fft_transform(Array<Complex> & input_vector, Array<Complex> & output_vector) {
    status_t st = OK;
    unsigned int size;
    unsigned int i, j;

    if(output_vector.getSize() != 0)
        return ERROR_INVALID_OUTPUT_VECTOR;
    
    size = input_vector.getSize();

    if(size != 0){

        if(!is_pow_2(size))
            return ERROR_INVALID_INPUT_VECTOR;

        if(size == 1){
            st = output_vector.load_vector(input_vector);
                if(st != OK)
                    return st;
            return OK;
        }
        else{
            Array<Complex> EvenArray;
            Array<Complex> OddArray;
            Array<Complex> EvenArrayDFT;
            Array<Complex> OddArrayDFT;

            for(i = 0; i < size/2; i++){
                EvenArray.load_vector(input_vector[2*i]);
                OddArray.load_vector(input_vector[2*i + 1]);
            }

            st = fft_transform(EvenArray, EvenArrayDFT);
                if(st != OK)
                    return st;
            st = fft_transform(OddArray, OddArrayDFT);
                if(st != OK)
                    return st;

            for(i = 0; i < size/2; i++){
                st = output_vector.load_vector(EvenArrayDFT[i] + (OddArrayDFT[i]*exp_imag(-2*M_PI*i/size)));
                if(st != OK)
                    return st;
            }
            for(j = 0 ; i < size; i++, j++){
                st = output_vector.load_vector(EvenArrayDFT[j] - (OddArrayDFT[j]*exp_imag(-2*M_PI*j/size)));     
                if(st != OK)
                    return st;
            }
        }
    } 
    return st;
}

};


class direct_fft:public fft{
public:

virtual ~direct_fft() {};

virtual status_t transform(Array<Complex> & input_vector, Array<Complex> & output_vector) 
{
    if(output_vector.getSize() != 0)
        return ERROR_INVALID_OUTPUT_VECTOR;
    if(!is_pow_2(input_vector.getSize()))
        return ERROR_INVALID_INPUT_VECTOR;
    
    return fft_transform(input_vector, output_vector);
}

};

class inverse_fft:public fft{
public:

virtual ~inverse_fft() {};

virtual status_t transform(Array<Complex> & input_vector, Array<Complex> & output_vector) 
{
    status_t  st = OK;
    unsigned int size;
    unsigned int i;

    if(output_vector.getSize() != 0)
        return ERROR_INVALID_OUTPUT_VECTOR;
    
    size = input_vector.getSize();

    if(size != 0){
        
        if(!is_pow_2(size))
            return ERROR_INVALID_INPUT_VECTOR;


        for(i = 0; i < size; i++)
            conjugate(input_vector[i]);

        st = fft_transform(input_vector, output_vector);
            if(st != OK){
				return st;
			}

        for(i = 0; i < size; i++){
            conjugate(output_vector[i]);
            output_vector[i] = output_vector[i] / size;
        }

    }
    return st;
} 

};


#endif