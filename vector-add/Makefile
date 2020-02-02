# this assumes that the IBM XL compiler is used

CXX = xlc++
CXXOFFLOAD = -qoffload
CXXFLAGS = -O2 -qsmp=omp
EXE = vector_add_cpu vector_add_gpu

all : $(EXE)

vector_add_cpu : vector_add_cpu.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

% : %.cpp
	$(CXX) $(CXXFLAGS) $(CXXOFFLOAD) $< -o $@

clean:
	rm -f $(EXE)
