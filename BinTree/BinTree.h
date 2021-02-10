#ifndef _BINTREE_H
#define _BINTREE_H

template <class T>
class BinTree
{
private:
	struct Node
	{
		T data;
		Node* left, * right;

		//Node()
		Node(const T& _data, Node* _left, Node* _right) : data(_data), left(_left), right(_right) {}
	};

	Node* root;
private:
	bool isMemberHelp(Node* root, const T& element);
	T sumHelper(Node* root);
	size_t countHelper(Node* root);

public:
	BinTree();
	void insert(const T& element, const char* path);
	Node* locate(const char* path) const;
	T get(const char* path) const;
	T& operator[](const char* path);
	bool isMember(const T& element);
	T sum();
	size_t count();
};

#endif