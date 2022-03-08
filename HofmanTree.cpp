#include "HofmanTree.h"



HofmanTree::HofmanTree(PriorityQueue& q, int size)
{
	Hofman(q, size);
	findHigh();//inserrt high
}

HofmanTree::~HofmanTree()
{
}



void HofmanTree::Hofman(PriorityQueue& queue,int size)
{
	Data* node;
	Data sec;
	bool flag = true;

	for (int i = 1; i < size; i++)
	{
		node = new Data();
		node->left = new Data((queue.DeQueue()));
		node->right = new Data((queue.DeQueue()));

		node->numOfPerformances = node->left->numOfPerformances + node->right->numOfPerformances;
		queue.EnQueue(*node);
	}
	root = new Data((queue.DeQueue()));
}

void HofmanTree::printData()
{
	char* helpString = new char[high + 1];
	int sizeOfHofmanCode = 0;
	int* pSizeOfHofmanCode = &sizeOfHofmanCode;
	printDataHelper(root, 0, helpString, pSizeOfHofmanCode);
	delete[] helpString;
	cout << "The total weight of the code is: " << *pSizeOfHofmanCode;
}


void HofmanTree::printChar(char c) const
{
	if (c == 10)
	{
		cout << "\\n";
	}else if (c == 9)
	{
		cout<< "\\t";
	}
	else if (c == 32)
	{
		cout << "Space";
	}
	else
	{
		cout << c;
	}
}

void HofmanTree::printDataHelper(Data* node, int i,char* string,int* pSizeOfHofmanCode)
{
	if (isLeaf(node))
	{
		string[i] = '\0';
		cout << "the char is: ";
		printChar(node->c);
		cout << " times: " << node->numOfPerformances;

		cout << "  and the binar code is: " << string << endl;
		*pSizeOfHofmanCode = *pSizeOfHofmanCode + (i)*node->numOfPerformances;// i is equal to the current high
	}
	else
	{
		if (node->left != nullptr)
		{
			string[i] = '0';
		}
		printDataHelper(node->left, i + 1, string, pSizeOfHofmanCode);
		if (node->right != nullptr)
		{
			string[i] = '1';
		}
		printDataHelper(node->right, i + 1, string, pSizeOfHofmanCode);
	}
}



void HofmanTree::findHigh()
{
	high = findHighHelper(root);
}

int HofmanTree::findHighHelper(Data* node)
{
	if (node == nullptr)
	{
		return 0;
	}
	else
	{
		int hL, hR;
		hL = findHighHelper(node->left);
		hR = findHighHelper(node->right);
		return max(hL, hR) + 1;
	}
}

int HofmanTree::max(int first, int sec)
{
	if (first > sec)
	{
		return first;
	}
	return sec;
}

bool HofmanTree::isLeaf(Data* node)
{
	return(node->left == nullptr && node->right == nullptr);
}

void HofmanTree::deleteData()
{
	deleteDataHelper(root);
}

void HofmanTree::deleteDataHelper(Data* node)
{
	if (node == nullptr)
	{
		return;
	}
	else
	{
		deleteDataHelper(node->left);
		deleteDataHelper(node->right);
		delete node;
	}
}

