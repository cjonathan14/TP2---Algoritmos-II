CXXARGS  = -g -Wall -pedantic -ansi
CXXFLAGS = -I. $(CXXARGS)

all: compare_vector.exe
	
	
compare_vector.exe: main.o Complex.o process_signal.o err.o utils.o
	$(CXX) $(CXXFLAGS) -o compare_vector.exe main.o Complex.o process_signal.o err.o utils.o
main.o: main.cc ../TempArray.h ../Complex.h ../err.h
	$(CXX) $(CXXFLAGS) -c main.cc
Complex.o: ../Complex.cc ../Complex.h
	$(CXX) $(CXXFLAGS) -c ../Complex.cc
process_signal.o: ../process_signal.cc ../process_signal.h  ../TempArray.h ../err.h ../types.h ../Complex.h ../ft.h ../utils.h
	$(CXX) $(CXXFLAGS) -c ../process_signal.cc
err.o: ../err.cc ../err.h 
	$(CXX) $(CXXFLAGS) -c ../err.cc 
utils.o: ../utils.cc ../utils.h 
	$(CXX) $(CXXFLAGS) -c ../utils.cc 
clean:
	$(RM) -vf *.o *.exe *.t *.out *.err