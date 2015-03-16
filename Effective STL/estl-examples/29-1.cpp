//
// Example from ESTL Item 29 (MSVC version)
//
// Fails under MSVC/native lib, STLPort (lacks member templates)
// Fails under G++ (library missing stuff)
//

#include <string>
#include <iostream>
#include <fstream>
#include <streambuf>
#include "ESTLUtil.h"

int main()
{
	using namespace std;
	using namespace ESTLUtils;


	{
		ifstream inputFile("interestingData.txt");

		string fileData(istream_iterator<char>(inputFile),	// read inputFile into
						 istream_iterator<char>());			// fileData; see below
															// for why this isn't
															// quite right, and see
															// Item 6 for a warning
															// about this syntax
		cout << "After initializing, fileData = " << endl << fileData << endl;
	}

	{
		ifstream inputFile("interestingData.txt");

		inputFile.unsetf(ios::skipws);						// disable the skipping of
															// whitespace in inputFile

		string fileData(istream_iterator<char>(inputFile),
						istream_iterator<char>());

		cout << "After initializing, fileData = " << endl << fileData << endl;
	}

	{
		ifstream inputFile("interestingData.txt");

		string fileData(istreambuf_iterator<char>(inputFile),
					istreambuf_iterator<char>());
		cout << "After initializing using istreambuf_iter, fileData = " << endl <<
					fileData << endl;
	}

	return 0;
}
