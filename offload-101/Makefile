# this assumes that the IBM XL compiler is used

CXX = mpic++
CXXOFFLOAD = -qoffload
CXXFLAGS = -O2 -qsmp=omp
EXE = 01_target_construct 02_target_teams_parallel

all : $(EXE)

% : %.cpp
	$(CXX) $(CXXFLAGS) $(CXXOFFLOAD) $< -o $@

clean:
	rm -f $(EXE)
