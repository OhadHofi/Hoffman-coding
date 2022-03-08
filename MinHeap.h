#pragma once
#include <stdio.h>
#include <iostream>
#include "binTree.h"

using namespace::std;

class hofmanTreeStruct;



class Data
{
public:
	char c;
	int numOfPerformances;
	Data* left;
	Data* right;

	Data();
	~Data();
};

class PriorityQueue
{
private:
	int maxSize;
	int heapSize;
	int allocated;
	Data* arrMinHeap;

	static int Left(int node);
	static int Right(int node);
	static int Parent(int node);
	void FixHeap(int node);
	void Swap(Data& one, Data& sec);

	void insertDataToArray(BinTree::BinTreeNode* node);
	void insertDataToArrayHelper(BinTree::BinTreeNode* node, int* idx);


public:
	PriorityQueue() = default;
	PriorityQueue(int max);
	PriorityQueue(BinTree::BinTreeNode* root, int n);
	~PriorityQueue();

	//this function insert new Pair to the heap and save the heap
	void EnQueue(Data& item);

	//This function takes out the first value in the queue and returns and with it
	Data DeQueue();
	bool isEmpty();
	void makeEmpty();
	Data Front();
	int getQSize() { return heapSize; }

};

