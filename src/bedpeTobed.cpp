#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <sstream>
#include <cstring>
#include <stdio.h>
#include <unistd.h>
#include "stringManipulation.hpp"


// put leftmost start site and 
// rightmost end site to new bed file
// output read length as 5th columns
int printBed(string chrom, int start1, int start2 ,
		int end1, int end2, string strand, string id, int maximumDist, int minDist)
{
	int start = min(start1,start2);
	int end = max(end1,end2);
	int innerDist = end - start;
	if (innerDist < maximumDist && innerDist > minDist)
	{
		cout << chrom << '\t' << start << '\t' << end << '\t';
		cout << id << '\t' << innerDist << '\t' << strand << '\n';
	}
	return 0;
}

// split every line tab, 
// and assign chrom/start/end/strand to each columns
int processBedpe(string line, int maximumDist, int minDist)
{
	string chrom1, chrom2;
	int start1, end1, start2, end2;
	string id, strand1, strand2;
	stringList columns = split(line, '\t');
	if (columns.size() < 10)
	{
		cerr << "Input is not bedpe!!" << endl;
		return 1;
	}
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
		printBed(chrom1,start1,start2,end1,end2,strand1, id , maximumDist, minDist);
	}
	return 0;
}


// reading from files
int readFile(string filename, int maximumDist, int minDist)
{
	ifstream bedFile(filename.c_str());
	int fail;
	for (string line; getline(bedFile, line);)
	{
		fail = processBedpe(line, maximumDist, minDist);
		if (fail == 1)
		{
			return 1;
		}
	}
	return 0;
}

// reading from standard input
int standardIn(int maximumDist, int minDist)
{
	int fail;
	for (string line; getline(cin, line);)
	{
		processBedpe(line, maximumDist, minDist);
		if (fail == 1)
		{
			return 1;
		}
	}
	return 0;
}

// print usage
int usage(char* program)
{
	cerr << "usage: " << program << " -i <bedpeFile> | <stdin>" << endl;
	cerr << "-i          bedpe file or standard input[-]" << endl;
	cerr << "-m          maximum inner span distance of the pair [default: 10000]"<<endl;
	cerr << "-l          minimum inner span distance of the pair [default: 10]"<<endl;
	cerr << endl;
	return 0;
}

// main function for parsing arguments
int main(int argc, char **argv)
{
	ios::sync_with_stdio(false);
	char *program = argv[0];
	int maximumDist = 10000;
	int minDist = 10;
	int c;
	string Filename = " ";
	
	while ((c = getopt (argc, argv, "i:m:")) != -1)
	{
		switch(c)
		{
			case 'i':
				Filename = optarg;
				break;
			case 'm':
				maximumDist = atoi(optarg);
				break;
			case 'l':
				minDist = atoi(optarg);
				break;
			case '?':
				if (optopt == 'i')
				{
					cerr << "option i requires a file!" << endl;
					usage(program);
				}
			default:
				abort();
		}
	}
	cerr << "Maximum inner distance filterd at: " << maximumDist << endl;
	if (strcmp(Filename.c_str()," ")==0)
	{
		cerr << "option i requires a file!" << endl;
		usage(program);
	}
	else if (strcmp(Filename.c_str(),"-")==0)
	{
		cerr << "Using stdin" << endl;
		standardIn(maximumDist, minDist);
	}
	else
	{
		readFile(Filename, maximumDist, minDist);
	}
	return 0;
}
