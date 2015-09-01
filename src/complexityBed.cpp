#include <string>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <unordered_set>
#include <cstring>
#include "stringManipulation.hpp"

using namespace std;
typedef unordered_set<string> transcriptIndex;


void processBed(string line, transcriptIndex &tIdx){
	string start;
	string end;
	string strand;
	stringList column = split(line,'\t');
	start = column[1];
	end = column[2];
	strand = column[5];
	tIdx.insert(start + "-" + end + "_"+strand);
}

// reading from files
int readFile(string filename, transcriptIndex &tIdx, int &reads)
{
	ifstream bedFile(filename.c_str());
	for (string line; getline(bedFile, line);)
	{
		processBed(line,tIdx);
		reads ++;
	}
	return 0;
}

// reading from standard input
int standardIn(transcriptIndex &tIdx, int &reads)
{
	for (string line; getline(cin, line);)
	{
		processBed(line, tIdx);
		reads ++;
	}
	return 0;
}

// print usage
int usage(char* program)
{
	cerr << "usage: " << program;
	cerr << " <bedfile>" ;
	cerr << endl;
	return 0;
}

int main(int argc, char **argv)
{
	ios::sync_with_stdio(false);
	char *program = argv[0];
	string filename;
	
	if (argc != 2)
	{
		usage(program);
		return 1;
	}
	filename = argv[1];

	//define output
	transcriptIndex tIdx;
	int reads = 0;

	if (strcmp(filename.c_str(),"-")==0)
	{
		standardIn(tIdx,reads);
	}
	else 
	{
		readFile(filename,tIdx,reads);
	}
	cout << reads << '\t' << tIdx.size() << endl;
	return 0;
}

