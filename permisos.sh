#!/bin/bash

chmod 700 ./Tests/boundaries/test_boundaries 
chmod 700 ./Tests/dft/test_dft
chmod 700 ./Tests/invalid_input/test_invalid_input 
chmod 700 ./Tests/memory_leak/test_memory_leak.sh
chmod 700 ./Tests/regression/test_regression
chmod 700 ./Tests/time/test_timeFT.sh
make -C ./Compare
make -C ./Random_vector
make -C ./Tests/invalid_input/binary_file