#!/bin/bash

path="./Tests/memory_leak"


inputfile=""$path"/input.txt"
outputfile1=""$path"/outputfile1.txt"
outputfile2=""$path"/outputfile2.txt"



valgrind --show-leak-kinds=all --leak-check=yes --log-file="$path/RESULT_DFT.txt"  ./fourier_transform.exe -i $inputfile -o $outputfile1 -m DFT


valgrind --show-leak-kinds=all --leak-check=yes --log-file="$path/RESULT_IDFT.txt"  ./fourier_transform.exe -i $inputfile -o $outputfile2 -m IDFT


valgrind --show-leak-kinds=all --leak-check=yes --log-file="$path/RESULT_FFT.txt"  ./fourier_transform.exe -i $inputfile -o $outputfile1 -m FFT

valgrind --show-leak-kinds=all --leak-check=yes --log-file="$path/RESULT_IFFT.txt"  ./fourier_transform.exe -i $inputfile -o $outputfile2 -m IFFT


