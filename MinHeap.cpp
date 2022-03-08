#include "MinHeap.h"

Data::Data():left(nullptr),right(nullptr),numOfPerformances(0)
{
}

Data::~Data()
{

}

PriorityQueue::PriorityQueue(int max)
{
	arrMinHeap = new Data[max];
	maxSize = max;
	heapSize = 0;
	allocated = 1;
}

PriorityQueue::PriorityQueue(BinTree::BinTreeNode* root, int n)
{
	arrMinHeap = new Data[n];
	insertDataToArray(root);

	heapSize = maxSize = n;
	allocated = 1;

	for (int i = n / 2 - 1; i >= 0; i--)
	{
		FixHeap(i);
	}
}

PriorityQueue::~PriorityQueue()
{
	if (allocated)
	{
		delete[] arrMinHeap;
	}
	arrMinHeap = nullptr;
}

void PriorityQueue::insertDataToArray(BinTree::BinTreeNode* node)
{
	int i = 0;
	int *idx = &i;
	insertDataToArrayHelper(node, idx);
}

void PriorityQueue::insertDataToArrayHelper(BinTree::BinTreeNode* node, int* idx)
{
	if (node == nullptr)
	{
		return;
	}
	else
	{
		insertDataToArrayHelper(node->left, idx);
		insertDataToArrayHelper(node->right, idx);
		arrMinHeap[*idx].c = node->c;
		arrMinHeap[*idx].numOfPerformances = node->countPriority;
		*idx = *idx + 1;
	}
}

int PriorityQueue::Left(int node)
{
	return (2 * node + 1);
}

int PriorityQueue::Right(int node)
{
	return (2 * node + 2);
}

int PriorityQueue::Parent(int node)
{
	return(node - 1) / 2;
}

void PriorityQueue::FixHeap(int node)
{
	int min;
	int left = Left(node);
	int right = Right(node);

	if ((left < heapSize) && (arrMinHeap[left].numOfPerformances < arrMinHeap[node].numOfPerformances))
	{
		min = left;
	}
	else
	{
		min = node;
	}

	if ((right < heapSize) && (arrMinHeap[right].numOfPerformances < arrMinHeap[min].numOfPerformances))
	{
		min = right;
	}

	if (min != node)
	{
		Swap(arrMinHeap[node], arrMinHeap[min]);
		FixHeap(min);
	}
}

void PriorityQueue::Swap(Data& one, Data& sec)
{
	Data temp;
	temp = one;
	one = sec;
	sec = temp;
}

bool PriorityQueue::isEmpty()
{
	if (heapSize == 0)
	{
		return true;
	}
	return false;
}

void PriorityQueue::makeEmpty()
{
	if (arrMinHeap != nullptr)
	{
		delete[] arrMinHeap;
	}
	arrMinHeap = new Data[maxSize];
}

Data PriorityQueue::Front()
{
	return arrMinHeap[0];
}

void PriorityQueue::EnQueue(Data& item)
{
	if (heapSize == maxSize)
	{
		cout << "The Queue is full. Cant insert more items." << endl;
	}
	int i = heapSize;
	heapSize++;

	while ((i > 0) && (arrMinHeap[Parent(i)].numOfPerformances > item.numOfPerformances))
	{
		arrMinHeap[i] = arrMinHeap[Parent(i)];
		i = Parent(i);
	}
	arrMinHeap[i] = item;

}

Data PriorityQueue::DeQueue()
{
	if (heapSize < 1)
	{
		cout << "error. the heap is empty." << endl;
	}
	Data min = arrMinHeap[0];
	heapSize--;
	arrMinHeap[0] = arrMinHeap[heapSize];
	FixHeap(0);
	return min;
}

