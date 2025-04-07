CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

all: toycc

toycc: main.o lexer.o
	$(CXX) $(CXXFLAGS) -o toycc main.o lexer.o

main.o: main.cpp lexer.hpp token.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

lexer.o: lexer.cpp lexer.hpp token.hpp
	$(CXX) $(CXXFLAGS) -c lexer.cpp

clean:
	rm -f *.o toycc