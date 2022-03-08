#pragma once
#include "MinHeap.h"



class HofmanTree
{
private:

	Data *root;
	int high;
	int numOfLeaves;

	void Hofman(PriorityQueue& queue, int size);
	void findHigh();
	int findHighHelper(Data* node);
	bool isLeaf(Data* node);
	int max(int first, int sec);
	void printChar(char c) const;
	void deleteDataHelper(Data* node);

public:
	HofmanTree(PriorityQueue& q, int size);
	~HofmanTree();
	void printDataHelper(Data* node, int i, char* string, int* pSizeOfHofmanCode);

	void printData();
	void deleteData();

};
