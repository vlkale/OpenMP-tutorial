# this assumes that the IBM XL compiler is used

CXX = xlc++
CXXOFFLOAD = -qoffload
CXXFLAGS = -O2 -qsmp=omp
EXE = 01_target_construct 02_target_teams_parallel 03_map \
      03_map_function 03_map_unstructured_function

all : $(EXE)

% : %.cpp
	$(CXX) $(CXXFLAGS) $(CXXOFFLOAD) $< -o $@

clean:
	rm -f $(EXE)
