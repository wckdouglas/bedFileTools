#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <sstream>
#include <cstring>
#include <stdio.h>
#include "stringManipulation.h"


// put leftmost start site and 
// rightmost end site to new bed file
// output read length as 5th columns
int printBed(string chrom, int start1, int start2 ,
		int end1, int end2, string strand, string id)
{
	int start = min(start1,start2);
	int end = max(end1,end2);
	cout << chrom << '\t' << start << '\t' << end << '\t';
	cout << id << '\t' << end-start << '\t' << strand << '\n';
	return 0;
}

// split every line tab, 
// and assign chrom/start/end/strand to each columns
int processBedpe(string line)
{
	string chrom1, chrom2;
	int start1, end1, start2, end2;
	string id, strand1, strand2;
	stringList columns = split(line, '\t');
	chrom1 = columns[0];
	chrom2 = columns[3];
	start1 = atol(columns[1].c_str());
	start2 = atol(columns[4].c_str());
	end1 = atol(columns[2].c_str());
	end2 = atol(columns[5].c_str());
	id = columns[6];
	strand1 = columns[8];
	strand2 = columns[9];
	if (strand1.compare(strand2) != 0 && chrom1.compare(chrom2) == 0)
	{	
		printBed(chrom1,start1,start2,end1,end2,strand1, id);
	}
	return 0;
}

// reading from files
int readFile(string filename)
{
	ifstream bedFile(filename);
	for (string line; getline(bedFile, line);)
	{
		processBedpe(line);
	}
	return 0;
}

// reading from standard input
int standardIn()
{
	ios::sync_with_stdio(false);
	for (string line; getline(cin, line);)
	{
		processBedpe(line);
	}
	return 0;
}

// print usage
int usage(char* program)
{
	cerr << "usage: " << program << " <bedpeFile> | <stdin>" << endl;
	cerr << endl;
	return 0;
}

// main function for parsing arguments
int main(int argc, char **argv)
{
	ios::sync_with_stdio(false);
	char *program = argv[0];
	if (argc != 2)
	{
		usage(program);
	}
	else 
	{
		string Filename = argv[1];
		if (strcmp(Filename.c_str(),"-")==0)
		{
			standardIn();
		}
		else
		{
			readFile(Filename);
		}
	}
	return 0;
}
