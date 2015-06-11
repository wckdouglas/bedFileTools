CPP=g++
MKDIR_P = mkdir 

.PHONY: binary

all: binary bedpeTobed filterPairToBed


binary:
	${MKDIR_P} ./bin

bedpeTobed:
	$(CPP) bedpeTobed.cpp -o ./bin/bedpeTobed

filterPairToBed:
	$(CPP) filterPairToBed.cpp -o ./bin/filterPairToBed

