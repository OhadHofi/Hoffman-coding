#include "binTree.h"

BinTree::BinTree() :root(nullptr), countNode(0)
{
}

BinTree::~BinTree()
{
	delete root;
}

void BinTree::insertNode(char c)
{
	if (findNode(c) == nullptr)
	{
		BinTreeNode* newNode = new BinTreeNode(c);
		if (root == nullptr)
		{
			root = newNode;
			countNode = 1;
		}
		else
		{
			BinTreeNode* temp = root;
			BinTreeNode* tempParent = root;

			while (temp != nullptr)
			{
				tempParent = temp;
				if (temp->c > newNode->c)
				{
					temp = temp->left;
				}
				else
				{
					temp = temp->right;
				}
			}
			if (tempParent->c > newNode->c)
			{
				tempParent->left = newNode;
			}
			else
			{
				tempParent->right = newNode;
			}
			newNode->parent = tempParent;

			countNode++;
		}
	}
	else
	{
		findNode(c)->countPriority++;
	}
}

BinTree::BinTreeNode* BinTree::findNode(char c)const
{
	BinTreeNode* temp = root;
	while (temp != nullptr)
	{
		if (temp->c == c)
		{
			return temp;
		}
		if (temp->c < c)
		{
			temp = temp->right;
		}
		else
		{
			temp = temp->left;
		}
	}
	return temp;//if we finish the while its mean we dont have any node like it
}

bool BinTree::deleteNode(char c)
{
	BinTreeNode* deleteNode = findNode(c);
	if (deleteNode == nullptr)//this case we try delete node that dont exists
	{
		return false;
	}
	else
	{
		if (deleteNode->right == nullptr && deleteNode->left == nullptr)//deleteNode is leave
		{
			deleteLeave(deleteNode);
		}
		else
		{
			if (deleteNode->right != nullptr && deleteNode->left == nullptr)//deleteNode has only right child
			{
				caseOnlyRightChild(deleteNode);
			}
			else
			{
				if (deleteNode->right == nullptr && deleteNode->left != nullptr)//deleteNode has only left child
				{
					caseOnlyLeftChild(deleteNode);
				}
				else//deleteNode has tow children
				{
					caseHasTowChildren(deleteNode);
				}
			}
		}
	}
	countNode--;
}

void BinTree::caseHasTowChildren(BinTreeNode* deleteNode)
{
	BinTreeNode* minSubRightTree;
	minSubRightTree = findMinValueOfSubRightTree(deleteNode->right);

	if (minSubRightTree == deleteNode->right)
	{
		deleteNode->left->parent = minSubRightTree;

		if (deleteNode->parent != nullptr)
		{
			if (deleteNode->parent->left == deleteNode)//if i left child to my parent
			{
				deleteNode->parent->left = minSubRightTree; 
			}
			if (deleteNode->parent->right == deleteNode)//if i right child to my parent
			{
				deleteNode->parent->right = minSubRightTree;
			}
		}
		minSubRightTree->parent = deleteNode->parent;
		minSubRightTree->left = deleteNode->left;
		delete deleteNode;
	}
	else
	{
		if (deleteNode->parent != nullptr)
		{
			if (deleteNode->parent->left == deleteNode)
			{
				deleteNode->parent->left = minSubRightTree;
			}
			else
			{
				deleteNode->parent->right = minSubRightTree;
			}
		}
		deleteNode->left->parent = minSubRightTree;
		deleteNode->right->parent = minSubRightTree;

		minSubRightTree->parent->left = minSubRightTree->right;
		if (minSubRightTree->right != nullptr)
		{
			minSubRightTree->right->parent = minSubRightTree->parent;
		}
		minSubRightTree->left = deleteNode->left;
		minSubRightTree->right = deleteNode->right;
		minSubRightTree->parent = deleteNode->parent;
	}

	if (minSubRightTree->parent == nullptr)//its mean that we delete the old root and replace it with min
	{
		root = minSubRightTree;
	}
}

BinTree::BinTreeNode* BinTree::findMinValueOfSubRightTree(BinTreeNode* node)
{
	BinTreeNode* temp = node;
	while (temp->left != nullptr)
	{
		temp = temp->left;
	}
	return temp;
}

void BinTree::caseOnlyLeftChild(BinTreeNode* deleteNode)
{
	if (deleteNode->parent == nullptr)//its mean we try delete the root
	{
		root = deleteNode->left;
		root->parent = nullptr;
	}
	else
	{
		if (deleteNode->parent->left == deleteNode)//if i left child to my parent
		{
			deleteNode->parent->left = deleteNode->left;
		}
		if (deleteNode->parent->right == deleteNode)//if i right child to my parent
		{
			deleteNode->parent->right = deleteNode->left;
		}
		deleteNode->left->parent = deleteNode->parent;
	}
	delete deleteNode;
}

void BinTree::caseOnlyRightChild(BinTreeNode* deleteNode)
{
	if (deleteNode->parent == nullptr)//its mean we try delete the root
	{
		root = deleteNode->right;
		root->parent = nullptr;
	}
	else
	{
		if (deleteNode->parent->left == deleteNode)//if i left child to my parent
		{
			deleteNode->parent->left = deleteNode->right;
		}
		if (deleteNode->parent->right == deleteNode)//if i right child to my parent
		{
			deleteNode->parent->right = deleteNode->right;
		}
		deleteNode->right->parent = deleteNode->parent;
	}
	delete deleteNode;
}

void BinTree::deleteLeave(BinTreeNode* deleteNode)
{
	if (deleteNode->parent == nullptr)//its mean we try delete the root
	{
		root = nullptr;
	}
	else //its mean we try delete leave that isnt root
	{
		if (deleteNode->parent->left == deleteNode)//if i left child to my parent
		{
			deleteNode->parent->left = nullptr;
		}
		if (deleteNode->parent->right == deleteNode)//if i right child to my parent
		{
			deleteNode->parent->right = nullptr;
		}
	}

	delete deleteNode;

}

bool BinTree::isEmpty()
{
	if (root == nullptr)
	{
		return true;
	}
	return false;
}

int BinTree::getsize()const
{
	return countNode;
}

BinTree::BinTreeNode* BinTree::getRoot()
{
	return root;
}

BinTree::BinTreeNode::~BinTreeNode()
{
	if (left != nullptr)
	{
		delete left;
	}
	if (right != nullptr)
	{
		delete right;
	}
}
