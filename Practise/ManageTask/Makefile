CXX = g++
CXXFLAGS = -std=c++17 -IC:/Users/duc5.le/Downloads/OOP_CPP/Practise/Library -IC:/Users/duc5.le/Downloads/OOP_CPP/json/include
LIBS = -L../Library -L../Library -l../Library/handleJson -l../Library/handleJson2

all: test run

test: test.o handleJson.o
	@$(CXX) $(CXXFLAGS) test.o handleJson.o -o test

test.o: test.cpp ../Library/handleJson.hpp
	@$(CXX) $(CXXFLAGS) -c test.cpp

handleJson.o: ../Library/handleJson.cpp ../Library/handleJson.hpp
	@$(CXX) $(CXXFLAGS) -c ../Library/handleJson.cpp
run:
	@./test.exe
clean:
	rm -f *.o
	rm -f *.exe
