CXXFLAGS=-std=c++20 -Wall -Wextra -Werror -O3 -march=native #-ggdb -fconcepts-diagnostics-depth=10
LDFLAGS=-ltbb

all: project.exe

clean:
	rm -rf *.exe *.o

run: project.exe
	./$<

project.o : project.cxx benchmark.hxx
	$(CXX) $(CXXFLAGS) -c $<

project.exe : project.o
	$(CXX) $(CXXFLAGS) -o $@ $+ $(LDFLAGS)
