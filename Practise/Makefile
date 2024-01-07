.PHONY := all build clean

# CXXFLAGS = -std=c++17 -IC:/Users/duc5.le/Downloads/json/include
# JSON_LISTER = -IC:/Users/duc5.le/Downloads/Object-Oriented Programming/Practise
CXXFLAGS = -std=c++17 -IC:/Users/KCCSHOP.VN/Downloads/json/include
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

## at company

# clean:
# rm -f *.exe
# cleanJson:	
# rm -f *.json

## at home

clean:
	del *.exe
	del *.json
