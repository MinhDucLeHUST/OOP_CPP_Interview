.PHONY := all build clean

CXXFLAGS = -std=c++17 -IC:/Users/duc5.le/Downloads/json/include

all: main run

main:
	@g++ $(CXXFLAGS) -o main main.cpp

run:
	@./main.exe

test:
	@g++ $(CXXFLAGS) -o test test.cpp
	@./test.exe

dev:
	@g++ $(CXXFLAGS) -o dev dev.cpp
	@./dev.exe

clean:
	del *.exe
	del *.json
