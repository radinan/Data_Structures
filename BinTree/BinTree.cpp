#ifndef _BINTREE_CPP
#define _BINTREE_CPP

#include "BinTree.h"
#include <stdexcept>
#include <cassert>
#include <cmath>
#include <fstream>

template <class T>
void BinTree<T>::clear(Node* root)
{
	if (root == nullptr)
		return;
	clear(root->left);
	clear(root->right);
	delete root;
}
template<class T>
BinTree<T>::BinTree() : root(nullptr) {}
template <class T>
bool BinTree<T>::isEqual(Node* root1, Node* root2)
{
	if (root1 == nullptr || root2 == nullptr)
		return root1 == nullptr && root2 == nullptr;
	return root1->data == root2->data &&
		isEqual(root1->left, root1->left) &&
		isEqual(root2->right, root2->right);
}
template <class T>
bool BinTree<T>::operator == (const BinTree& other)
{
	return isEqual(root, other.root);
}

template <class T>
void BinTree<T>::insert(const T& element, const char* path)
{
	Node* curr = root;
	if (curr == nullptr)
	{
		assert(path[0] == 0);
		root = new Node{ element, nullptr, nullptr };
		return;
	}

	assert(path[0] != 0);
	assert(path[0] == 'L' || path[0] == 'R');
	while (path[1] != 0) 
	{
		assert(curr != nullptr);
		assert(path[0] == 'L' || path[0] == 'R');

		if (path[0] == 'L')
			curr = curr->left;
		else 
			curr = curr->right;

		++path;
	}

	assert(path[0] == 'L' || path[0] == 'R');
	if (path[0] == 'L')
	{
		assert(curr->left == nullptr);
		curr->left = new Node{ element, nullptr, nullptr };
	}
	else
	{
		assert(curr->right == nullptr);
		curr->right = new Node{ element, nullptr, nullptr };
	}

}
template <class T>
typename BinTree<T>::Node* BinTree<T>::locate(const char* path) const
{
	Node* curr = root;
	while (path[0] != 0)
	{
		assert(curr != nullptr);
		assert(path[0] == 'L' || path[0] == 'R');

		if (path[0] == 'L')
			curr = curr->left;
		else
			curr = curr->right;

		++path;
	}
	assert(curr != nullptr);
	return curr;
}
template <class T>
T BinTree<T>::get(const char* path) const
{
	return locate(path)->data;
}
template <class T>
T& BinTree<T>::operator[](const char* path)
{
	Node* node = locate(path);
	assert(node != nullptr);
	return node->data;
}

template <class T>
bool BinTree<T>::isMember(const T& element)
{
	return isMemberHelp(root, element);
}
template <class T>
bool BinTree<T>::isMemberHelp(Node* root, const T& element)
{
	//separating different cases
	if (root == nullptr)
		return false;

	return root->data == element
		|| isMemberHelp(root->left, element)
		|| isMemberHelp(root->right, element);
}
template <class T>
T BinTree<T>::sum()
{
	return sumHelper(root);
}
template <class T>
T BinTree<T>::sumHelper(Node* root)
{
	if (root == nullptr)
		return 0;

	return root->data 
		+ sumHelper(root->left) 
		+ sumHelper(root->right);
}
template <class T>
size_t BinTree<T>::count()
{
	return countHelper(root);
}
template <class T>
size_t BinTree<T>::countHelper(Node* root)
{
	if (root == nullptr)
		return 0;
	else
		return 1 + countHelper(root->left) + countHelper(root->right);
}
template <class T>
size_t BinTree<T>::countEvens()
{
	return countEvensHelper(root);
}
template <class T>
size_t BinTree<T>::countEvensHelper(Node* root)
{
	if (root == nullptr)
		return 0;
	else if (root->data % 2 == 0)
		return 1 + countEvensHelper(root->left) + countEvensHelper(root->right);
	else
		return countEvensHelper(root->left) + countEvensHelper(root->right);
}

template <class T>
int BinTree<T>::searchCount(bool (*pred)(const T& el))
{
	return searchCountHelper(root, pred);
}
template <class T>
int BinTree<T>::searchCountHelper(Node* root, bool (*pred)(const T& el))
{
	if (root == nullptr)
		return 0;
	if(pred(root->data))
		return 1 + searchCountHelper(root->left, pred) + searchCountHelper(root->right, pred);
	else
		return searchCountHelper(root->left, pred) + searchCountHelper(root->right, pred);
}
template <class T>
int BinTree<T>::height()
{
	return heightHelper(root);
}
template <class T>
int BinTree<T>::heightHelper(Node* root)
{
	if (root == nullptr)
		return -1;
	return 1 + std::max(heightHelper(root->left), heightHelper(root->right));
}
template <class T>
int BinTree<T>::countLeaves()
{
	return countLeavesHelper(root);
}
template <class T>
int BinTree<T>::countLeavesHelper(Node* root)
{
	if (root == nullptr)
		return 0;
	else if (root->left == nullptr && root->right == nullptr)
		return 1;
	else
		return countLeavesHelper(root->left) + countLeavesHelper(root->right);
}
template <class T>
const T& BinTree<T>::maxLeaf()
{
	return maxLeafHelper(root);
}
template <class T>
const T& BinTree<T>::maxLeafHelper(Node* root)
{
	if (root == nullptr)
		return 0;
	else if (root->left == nullptr && root->right == nullptr)
		return root->data;
	else
		return std::max(maxLeafHelper(root->left), maxLeafHelper(root->right));
}

template <class T>
void BinTree<T>::serializeTreeScheme(std::ostream& out) //const & ???
{
	serializeTreeHelperScheme(root, out);
}
template <class T>
void BinTree<T>::serializeTreeHelperScheme(Node* root , std::ostream& out) //const & ??? or return copy?
{
	if (root == nullptr)
	{
		out << "()";
		return;
	}

	out << '(' 
		<< root->data 
		<< " ";
	serializeTreeHelperScheme(root->left, out);
	out << " ";
	serializeTreeHelperScheme(root->right, out);
	out << ")";
}
template <class T>
void BinTree<T>::parseTreeScheme(std::istream& in)
{
	clear(root);
	root = parseTreeHelperScheme(in);
}
template <class T>
typename BinTree<T>::Node* BinTree<T>::parseTreeHelperScheme(std::istream& in) //change return type to Node*
{
	char c;
	in >> c;
	assert(c == '(');
	if(in.peek() == ')') //()
	{ 
		in.get(); //get ')'
		return nullptr;
	}

	T data;
	in >> data;

	Node* left = parseTreeHelperScheme(in);
	Node* right = parseTreeHelperScheme(in);
	
	assert(in.peek() == ')'); //is not  wrong 
	in.get(); // get ')'

	return new Node{ data, left, right };
}

template <class T>
int BinTree<T>::getNodeLevelHelper(Node* root, const T& element, int level)
{
	if (root == nullptr)
		return -1;
	if (root->data == element)
		return level;

	int save = getNodeLevelHelper(root->left, element, level + 1);
	if (save != -1)
		return save;
	save = getNodeLevelHelper(root->right, element, level + 1);

	return save;
}


template <class T>
int BinTree<T>::getNodeLevel(const T& element)
{
	return getNodeLevelHelper(root, element, 0);
}
template <class T>
void BinTree<T>::serializeTreeHaskell(std::ostream& out) //const & ???
{
	serializeTreeHelperHaskell(root, out);
}
template <class T>
void BinTree<T>::serializeTreeHelperHaskell(Node* root, std::ostream& out) //const & ??? or return copy?
{
	if (root == nullptr)
	{
		out << "Empty";
		return;
	}
	if (root != this->root)
		out << "\n";
	int spaces = getNodeLevel(root->data);
	for (int i = 0; i < spaces; ++i)
	{
		out << "     ";
	}
	out << "Node "
		<< root->data
		<< " ";
	serializeTreeHelperHaskell(root->left, out);
	out << " ";
	serializeTreeHelperHaskell(root->right, out);
}
template <class T>
void BinTree<T>::parseTreeHaskell(std::istream& in)
{
	clear(root);
	root = parseTreeHelperHaskell(in);
}
template <class T>
typename BinTree<T>::Node* BinTree<T>::parseTreeHelperHaskell(std::istream& in) //change return type to Node*
{
	while (in.peek() == 32) //get whitespaces
	{
		in.get();
	}
	std::string str;
	in >> str;
	assert(str == "Node" || str == "Empty");
	if (str == "Empty") //()
	{
		return nullptr;
	}

	T data;
	in >> data;
	in.get(); // "\n" or " "
	Node* left = parseTreeHelperHaskell(in);
	Node* right = parseTreeHelperHaskell(in);

	return new Node{ data, left, right };
}

template <class T>
std::vector<T> BinTree<T>::listLeaves()
{
	std::vector<T> vec;
	listLeavesHelper(root, vec);
	return vec;
}
template <class T>
void BinTree<T>::listLeavesHelper(Node* root, std::vector<T>& vec)
{
	if (root == nullptr)
		return;
	if (root->left == nullptr && root->right == nullptr)
		vec.push_back(root->data);

	listLeavesHelper(root->left, vec);
	listLeavesHelper(root->right, vec);
}

template <class T>
std::string BinTree<T>::findTrace(const T& element)
{
	std::string path;
	
	if (!findTraceHelper(root, element, path))
		path = "_";

	return path;
}
template <class T>
bool BinTree<T>::findTraceHelper(Node* root, const T& element, std::string& path)
{
	if (root == nullptr)
	{
		return 0;
	}
	if (root->data == element)
		return 1;

	path.push_back('L');
	if (!findTraceHelper(root->left, element, path))
		path.pop_back();
	else
		return 1;

	path.push_back('R');
	if (!findTraceHelper(root->right, element, path))
	{
		path.pop_back();
		return 0;
	}
	else
		return 1;

}

#endif