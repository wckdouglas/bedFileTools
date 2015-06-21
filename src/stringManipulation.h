#include <string>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

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
	for (string line; getline(cin, line);)
	{
		processBedpe(line);
	}
	return 0;
}
