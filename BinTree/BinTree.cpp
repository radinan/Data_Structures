#ifndef _BINTREE_CPP
#define _BINTREE_CPP

#include "BinTree.h"
#include <stdexcept>
#include <cassert>

template<class T>
BinTree<T>::BinTree() : root(nullptr) {}

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

#endif