/*
		MAIN.H
*/

#ifndef MAIN__H
#define MAIN__H

#include "types.h"
#include "process_signal.h"
#include "err.h"
#include "cmdline.h"
#include "ft.h"

#define CMD_ARG_METHOD_DFT "DFT"
#define CMD_ARG_METHOD_IDFT "IDFT"
#define CMD_ARG_METHOD_FFT "FFT"
#define CMD_ARG_METHOD_IFFT "IFFT"
#define ERROR_REGRESSION_DEFAULT 1e-3

ft* construct_transformer (method_t method);

#endif
