#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cstring>
#include <unistd.h>
#include "stringManipulation.h"

using namespace std;

// split every line tab, 
// and assign chrom/start/end/strand to each columns
int processBedpe(string line, double fraction, int strandeness)
{
	string chrom1, chrom2;
	int start1, end1, start2, end2;
	string id, strand1, strand2;
	string geneChrom, geneName;
	int geneStart, geneEnd;
	int readLength1, readLength2;
	string geneStrand, geneType, geneID;
	stringList columns = split(line, '\t');
	//pairReads
	chrom1 = columns[0];
	chrom2 = columns[3];
	start1 = atol(columns[1].c_str());
	start2 = atol(columns[4].c_str());
	end1 = atol(columns[2].c_str());
	end2 = atol(columns[5].c_str());
	id = columns[6];
	strand1 = columns[8];
	strand2 = columns[9];

	// gene infomation
	geneChrom = columns[10];
	geneStart = atol(columns[11].c_str());
	geneEnd = atol(columns[12].c_str());
	geneName = columns[13];
	geneStrand = columns[15];
	geneType = columns[16];
	geneID = columns[17];
	
	//computer read lengths
	readLength1 = end2 - start1;
	readLength2 = end2 - start2;

	if (strand1.compare(strand2) != 0 && chrom1.compare(chrom2) == 0 &&
		chrom1.compare(geneChrom) == 0 && 
		min(end1,geneEnd) - max(start1,geneStart) > fraction * readLength1 &&
		min(end2,geneEnd) - max(start2,geneStart) > fraction * readLength2 )
	{	
		if ( strandeness == 1)
		{
			if (strand1.compare(geneStrand) == 0 )
			{
				cout << line << '\n';
			}
		}
		else
		{
			cout << line << '\n';
		}
	}

	return 0;
}

// reading from files
int readFile(string filename, double fraction, int strandeness)
{
	ifstream bedFile(filename.c_str());
	for (string line; getline(bedFile, line);)
	{
		processBedpe(line, fraction, strandeness);
	}
	return 0;
}

// reading from standard input
int standardIn(double fraction, int strandeness)
{
	for (string line; getline(cin, line);)
	{
		processBedpe(line,fraction, strandeness);
	}
	return 0;
}

// print usage
int usage(char* program)
{
	cerr << "usage: " << program;
	cerr << " -i <pairtobed File> | <stdin> [-f <fraction>] [-s]" << endl;
	cerr << "\n" ;
	cerr << "-f         fraction of overlap [default = 0.001]" << endl;
	cerr << "-i         can be file name or - for stdin" << endl;
	cerr << "-s         optional, for stradeness check"<<endl;
	cerr << endl;
	return 0;
}

// main function for parsing arguments
int main(int argc, char **argv)
{
	ios::sync_with_stdio(false);
	char *program = argv[0];
	int c;
	double fraction = 0.001;
    int	strandeness = 0;
	string filename;
	
	if (argc == 1)
	{
		usage(program);
		return 1;
	}

	while ((c = getopt (argc, argv, "i:f:s")) != -1)
	{
		switch(c)
		{
			case 'i':
				filename = optarg;
				break;
			case 'f':
				fraction = atof(optarg);
				break;
			case 's':
				strandeness = 1;
				break;
			case '?':
				if (optopt == 'f')
				{
					usage(program);
					cerr << "option f requires a fraction!" << endl;
				}
				else if (optopt == 'i')
				{
					cerr << "option i requires a file!" << endl;
				}
			default:
				abort();
		}
	}
	if (strcmp(filename.c_str(),"-")==0)
	{
		standardIn(fraction,strandeness);
	}
	else 
	{
		readFile(filename,fraction,strandeness);
	}

	return 0;
}
