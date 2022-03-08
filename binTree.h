#pragma once
#include <iostream>
//#include "MinHeap.h"
using namespace std;



class BinTree
{
public:

	class BinTreeNode
	{
	public:
		char c;
		int countPriority;
		BinTreeNode* left;
		BinTreeNode* right;
		BinTreeNode* parent;
		BinTreeNode(char tav) :c(tav), countPriority(1), left(nullptr), right(nullptr), parent(nullptr) {}
		BinTreeNode() = default;
		~BinTreeNode();
	};


	~BinTree();
	BinTree();
	void insertNode(char c);
	bool deleteNode(char c);
	BinTreeNode* findNode(char c)const;
	bool isEmpty();
	int getsize()const;
	BinTreeNode* getRoot();


private:

	BinTreeNode* root;
	int countNode;

	void deleteLeave(BinTreeNode* deleteNode);
	void caseOnlyRightChild(BinTreeNode* deleteNode);
	void caseOnlyLeftChild(BinTreeNode* deleteNode);
	void caseHasTowChildren(BinTreeNode* deleteNode);
	BinTreeNode* findMinValueOfSubRightTree(BinTreeNode* deleteNode);

};

