#include <iostream>
#include <fstream>
//#include <random>
#include <stdlib.h>
//#include <time.h> //i used this class to create algorithem that check the delete from bin tree with random chars
#include "HofmanTree.h"
#include "binTree.h"
#include "MinHeap.h"

using namespace std;


int main()
{
	char c;
	BinTree tree;
	char* filaeName = new char[128];
	cout << "Please enter file name: " << endl;
	cin >> filaeName;
	ifstream infile(filaeName);
	if (!infile)
	{
		cout << "input invalid";
		exit(1);
	}

	infile.get(c);

	while (!infile.eof())
	{
		if (!infile.good())
		{
			cout << "input invalid";
			exit(1);
		}
		tree.insertNode(c);
		infile.get(c);

	}

	if (tree.isEmpty())
	{
		cout << "the file is empty. No data to code";
	}
	else
	{
		cout << endl;
		PriorityQueue priorityQ(tree.getRoot(), tree.getsize());
		HofmanTree hofmaiTree(priorityQ, tree.getsize());
		hofmaiTree.printData();

		hofmaiTree.deleteData();
	}
	infile.close();
	delete[] filaeName;
}