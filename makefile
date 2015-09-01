CPP=g++
MKDIR_P=mkdir -p

all: binary bedpeTobed filterPairToBed complexityBed

binary:
	$(MKDIR_P) bin

bedpeTobed:
	$(CPP) src/bedpeTobed.cpp -o bin/bedpeTobed

filterPairToBed:
	$(CPP) src/filterPairToBed.cpp -o bin/filterPairToBed

complexityBed:
	$(CPP) src/complexityBed.cpp -o bin/complexityBed

