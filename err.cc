/*
		ERR.CC
*/

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "err.h"

using namespace std;

void handle_err(status_t st)
	{
	bool screen = true; //establishes if the error message is printed on stdout.
	string msg; 
	string msg_time;
	ofstream outfile;
	time_t rawtime;
	struct tm * timeinfo;


	if(st!=OK)
	{	
		outfile.open(ERROR_LOG_FILE_NAME,ios::app);

		if(st==ERROR_OUT_OF_MEMORY)
			msg = MSG_ERROR_OUT_OF_MEMORY;
		else if(st==ERROR_INPUT_FILE)
			msg = MSG_ERROR_INPUT_FILE;
		else if(st==ERROR_OUTPUT_FILE)
			msg = MSG_ERROR_OUTPUT_FILE;
		else if(st==ERROR_INVALID_INPUT_VECTOR)
			{msg = MSG_ERROR_INVALID_INPUT_VECTOR;screen=false;}
		else if(st==ERROR_INVALID_OUTPUT_VECTOR)
			{msg = MSG_ERROR_INVALID_OUTPUT_VECTOR;screen=false;}
		else if(st==ERROR_PROGRAM_INVOCATION)
			msg = MSG_ERROR_PROGRAM_INVOCATION;
		else if(st==ERROR_CORRUPT_LINE)
			msg = MSG_ERROR_CORRUPT_LINE;
		else if (st == ERROR_REGRESSION_FILE)
			msg = MSG_ERROR_REGRESSION_FILE;

		time(&rawtime);
		timeinfo=localtime(&rawtime);
		msg_time=asctime(timeinfo);

		if(screen)
			cerr << msg << endl;

		outfile << msg << " - " << msg_time << endl;
	}
	outfile.close();

}