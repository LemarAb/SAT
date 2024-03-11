# Compiler and flags
# g++ src/*.cpp  -o main -std=c++11 -Wall -Wno-sign-compare -Wno-format -g -O3 //--Manual run
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wno-sign-compare -Wno-format -g -O3

# Directories
SRCDIR = src
INCDIR = include
BINDIR = .
SOLVERDIR = cdcl

# Source files
SOURCES = $(wildcard $(SRCDIR)/$(SOLVERDIR)/*.cpp)
SELECTED_SOURCES =  $(wildcard $(SRCDIR)/main.cpp) $(wildcard $(SRCDIR)/parseDIMACS.cpp)
OBJ = $(SRC:.cpp=.o)
EXECUTABLE = main

TEST1 = test
TESTHEAP = heap2Test.cpp $(wildcard $(SRCDIR)/$(SOLVERDIR)/parseDimacs.cpp)

TEST2 = test2
TESTNIVER = niver.cpp $(wildcard $(SRCDIR)/$(SOLVERDIR)/parseDimacs.cpp) $(wildcard $(SRCDIR)/$(SOLVERDIR)/cdcl.cpp)
# Build target
all: $(EXECUTABLE)

# Rule to create executable
$(EXECUTABLE): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $@ $^

$(TEST1): $(TESTHEAP)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $@ $^

$(TEST2): $(TESTNIVER)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $@ $^
	
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean

clean:
	del main.exe
	del test.exe

run: $(EXECUTABLE) 
	$(EXECUTABLE) $(arg) $(heur=0)

buildheaptest: $(TEST)

test1run: $(TEST1)
	$(TEST1)

buildnivertest: $(TEST2)

test2run: $(TEST2)
	$(TEST2)	
