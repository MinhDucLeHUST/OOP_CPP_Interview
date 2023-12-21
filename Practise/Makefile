.PHONY := all build clean

CXXFLAGS = -std=c++11 -IC:/Users/duc5.le/Downloads/json/include

all: main run

main:
	@g++ $(CXXFLAGS) -o main main.cpp

run:
	@./main.exe

test:
	@g++ $(CXXFLAGS) -o test test.cpp
	@./test.exe

clean:
	rm -f *.exe
