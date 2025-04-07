# email: dvirbto@gmail.com

CXX = g++ # compiler
CXXFLAGS = -Wall -Wextra -std=c++11 -Idoctest # flags

SRC = Main.cpp Graph.cpp Algorithms.cpp Queue.cpp UnionFind.cpp # source files
OBJ = $(SRC:.cpp=.o) # create o files from the cpp files
TEST_SRC = Tests.cpp # for test
TEST_OBJ = $(TEST_SRC:.cpp=.o) # create test object file
EXEC = Main
TEST_EXEC = Tests

Main: $(OBJ) # rule Main
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJ)

test: Graph.o Algorithms.o Queue.o UnionFind.o Tests.o # rule test
	$(CXX) $(CXXFLAGS) -o $(TEST_EXEC) Graph.o Algorithms.o Queue.o UnionFind.o Tests.o

%.o: %.cpp # rule to compile cpp files into object files
	$(CXX) $(CXXFLAGS) -c $< -o $@

valgrind: Main # rule using valgrind to check memory leak in Tests
	valgrind --leak-check=full --show-leak-kinds=all ./$(EXEC)

clean: # rule to clean the object files
	rm -f $(OBJ) $(TEST_OBJ) $(EXEC) $(TEST_EXEC)