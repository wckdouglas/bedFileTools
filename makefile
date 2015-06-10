CPP=g++
MKDIR_P = mkdir 

.PHONY: binary

all: binary bedpeTobed


binary:
	${MKDIR_P} ./bin

bedpeTobed:
	$(CPP) bedpeTobed.cpp -o ./bin/bedpeTobed
