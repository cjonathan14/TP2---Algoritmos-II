#   MAKEFILE

ifeq ($(TARGET),clang)
	CXX := clang++
	CXXARGS  = -g -Wall -pedantic
	CXXFLAGS = -I. $(CXXARGS)
else
	CXX := g++
	CXXARGS  = -g -Wall -pedantic -ansi
	CXXFLAGS = -I. $(CXXARGS)
endif

all: rename fourier_transform.exe
	
fourier_transform.exe: main.o cmdline.o process_signal.o  Complex.o err.o utils.o
	$(CXX) $(CXXFLAGS) -o fourier_transform.exe cmdline.o main.o process_signal.o Complex.o err.o utils.o
main.o: main.cc main.h types.h process_signal.h err.h cmdline.h ft.h
	$(CXX) $(CXXFLAGS) -c main.cc
cmdline.o: cmdline.cc cmdline.h err.h
	$(CXX) $(CXXFLAGS) -c cmdline.cc
process_signal.o: process_signal.cc process_signal.h  TempArray.h err.h types.h Complex.h ft.h utils.h
	$(CXX) $(CXXFLAGS) -c process_signal.cc
Complex.o: Complex.cc Complex.h 
	$(CXX) $(CXXFLAGS) -c Complex.cc
err.o: err.cc err.h 
	$(CXX) $(CXXFLAGS) -c err.cc 
utils.o: utils.cc utils.h
	$(CXX) $(CXXFLAGS) -c utils.cc


rename:
ifneq ( ,$(wildcard fourier_transform.exe))	
	@test -f "fourier_transform.exe" && mv fourier_transform.exe old_fourier_transform.exe || echo "No .exe found"
endif

tests: test_regression test_dft test_boundaries test_invalid_input test_memory_leak test_timeFT 

test_regression:
	./Tests/regression/test_regression

test_dft:
	./Tests/dft/test_dft

test_boundaries:
	./Tests/boundaries/test_boundaries

test_invalid_input:
	./Tests/invalid_input/test_invalid_input

test_memory_leak:
	./Tests/memory_leak/test_memory_leak.sh

test_timeFT:
	./Tests/time/test_timeFT.sh

clean:
	$(RM) -vf *.o *.exe *.t *.out *.err