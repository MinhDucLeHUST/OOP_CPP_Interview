CXX = g++
# CXXFLAGS = -std=c++17 -IC:/Users/duc5.le/Downloads/OOP_CPP/Practise/Library -IC:/Users/duc5.le/Downloads/OOP_CPP/json/include

# CXXFLAGS = -std=c++17 -I../Library -I../../json/include

CXXFLAGS = -std=c++17 -I../Library -I../../json-develop/include

all: main run

main: main.o handleJson.o signUp.o
	@$(CXX) $(CXXFLAGS) main.o handleJson.o signUp.o -o main

main.o: main.cpp ../Library/handleJson.hpp
	@$(CXX) $(CXXFLAGS) -c main.cpp

handleJson.o: ../Library/handleJson.cpp ../Library/handleJson.hpp
	@$(CXX) $(CXXFLAGS) -c ../Library/handleJson.cpp

signUp.o: ../Library/signUp.cpp ../Library/signUp.hpp
	@$(CXX) $(CXXFLAGS) -c ../Library/signUp.cpp

run:
	@./main.exe
clean:
	rm -f *.o
	rm -f *.exe
