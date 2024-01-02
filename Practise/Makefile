.PHONY := all build clean

# CXXFLAGS = -std=c++11 -IC:/Users/duc5.le/Downloads/json/include
CXXFLAGS = -std=c++11 -IC:/Users/KCCSHOP.VN/Downloads/json/include
all: main run

main:
	@g++ $(CXXFLAGS) -o main main.cpp

run:
	@./main.exe

test:
	@g++ $(CXXFLAGS) -o test test.cpp
	@./test.exe

runnn:
	@g++ $(CXXFLAGS) -o runnn runnn.cpp
	@./runnn.exe

## at company

# clean:
# rm -f *.exe
# cleanJson:	
# rm -f *.json

## at home

clean:
	del *.exe
	del *.json
