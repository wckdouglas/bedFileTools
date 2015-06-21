#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cstring>
#include <unistd.h>

using namespace std;

typedef vector<string> stringList;

//split function to split line with desired deliminator
stringList split(const string &s, char delim) 
{
	stringList result;
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) 
    {
        result.push_back(item);
    }
    return result;
}


// split every line tab, 
// and assign chrom/start/end/strand to each columns
int processBedpe(string line, double fraction)
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
		chrom1.compare(geneChrom) == 0 && strand1.compare(geneStrand) == 0 &&
		min(end1,geneEnd) - max(start1,geneStart) > fraction * readLength1 &&
		min(end2,geneEnd) - max(start2,geneStart) > fraction * readLength2 )
	{	
		cout << line << '\n';
	}

	return 0;
}

// reading from files
int readFile(string filename, double fraction)
{
	ifstream bedFile(filename);
	for (string line; getline(bedFile, line);)
	{
		processBedpe(line, fraction);
	}
	return 0;
}

// reading from standard input
int standardIn(double fraction)
{
	for (string line; getline(cin, line);)
	{
		processBedpe(line,fraction);
	}
	return 0;
}

// print usage
int usage(char* program)
{
	cerr << "usage: " << program << " -i <pairtobed File> | <stdin> [-f <fraction>]" << endl;
	cerr << endl;
	return 0;
}

// main function for parsing arguments
int main(int argc, char **argv)
{
	ios::sync_with_stdio(false);
	char *program = argv[0];
	int c;
	double fraction = 0.5;
	string filename;
	
	if (argc == 1)
	{
		usage(program);
		return 1;
	}

	while ((c = getopt (argc, argv, "i:f:")) != -1)
	{
		switch(c)
		{
			case 'i':
				filename = optarg;
				break;
			case 'f':
				fraction = atof(optarg);
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
		standardIn(fraction);
	}
	else 
	{
		readFile(filename,fraction);
	}

	return 0;
}
