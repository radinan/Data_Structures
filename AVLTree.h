#pragma once
#include <iostream>
#include <algorithm>
//first - BST ; then - AVL 

class AVLTree
{
private:
	struct Node
	{
		int data;
		int height;
		Node* left, * right;
		Node(int data, int height = 0, Node* left = nullptr, Node* right = nullptr)
			: data(data), height(height), left(left), right(right){}
	};

	Node* root;
private:
	Node* copy(Node* other_root)
	{
		if (other_root == nullptr)
			return;
		Node* new_node = new Node(other_root->data);
		new_node->left = copy(other_root->left);
		new_node->right = copy(other_root->right);
	}
	void del(Node* &root)
	{
		if (root == nullptr)
			return;
		del(root->left);
		del(root->right);
		delete root;
	}

	Node* getMinNode(Node* root)
	{
		Node* curr = root;
		while (curr->left != nullptr && curr != nullptr)
		{
			curr = curr->left;
		}
		return curr;
	}
	Node* getMaxNode(Node* root)
	{
		Node* curr = root;
		while (curr->right != nullptr && curr != nullptr)
		{
			curr = curr->right;
		}
		return curr;
	}
	

	int getBalance(Node* node)
	{
		if (node == nullptr)
			return 0;
		return getHeight(node->left) - getHeight(node->right);
	}
	int getHeight(Node* node)
	{
		if (node == nullptr)
			return -1; //no node
		return node->height;
	}


	Node* searchHelp(Node* root, int value) //&? //returns ptr to element
	{
		if (root == nullptr)
			return nullptr;
		if (value == root->data) //can be merged with the upper one
			return root;
		if (value < root->data)
			return searchHelp(root->left, value);
		if (value > root->data)
			return searchHelp(root->right, value);
	}
	Node* insertHelp(Node* root, int value) //or bool
	{
		if (root == nullptr)
		{
			return new Node(value); 
		}
		if (value < root->data)
			root->left = insertHelp(root->left, value);
		if (value > root->data)
			root->right = insertHelp(root->right, value);

		root->height = 1 + std::max
							(getHeight(root->left), 
							 getHeight(root->right));
		int balance = getBalance(root);
		
		if (balance > 1)
		{
			if (getBalance(root->left) >= 0)
				root = rotateRight(root);
			else
				root = rotateLeftRight(root);
		}
		else if (balance < -1)
		{
			if (getBalance(root->right) <= 0)
				root = rotateLeft(root);
			else
				root = rotateRightLeft(root);
		}

		return root;
	}

	Node* rotateRight(Node* node)
	{
		Node* left_temp = node->left;
		node->left = left_temp->right;
		left_temp->right = node;

		node->height = 1 + std::max
			(getHeight(node->left),
			 getHeight(node->right));
		left_temp->height = 1 + std::max
			(getHeight(left_temp->left),
			 getHeight(left_temp->right));

		return left_temp;
	}
	Node* rotateLeftRight(Node* node)
	{
		node->left = rotateLeft(node->left);
		return rotateRight(node);
	}
	Node* rotateLeft(Node* node)
	{
		Node* right_temp = node->right;
		node->right = right_temp->left;
		right_temp->left = node;

		node->height = 1 + std::max
			(getHeight(node->left),
			 getHeight(node->right));
		right_temp->height = 1 + std::max
			(getHeight(right_temp->left),
			 getHeight(right_temp->right));

		return right_temp;
	}
	Node* rotateRightLeft(Node* node)
	{
		node->right = rotateRight(node->right);
		return rotateLeft(node);
	}


	Node* removeHelp(Node* root, int value)
	{
		if (root == nullptr)
			return root;
		//case 1 -> leaf
		if (root->data < value)
		{
			root->left = removeHelp(root->left, value);
		}
		else if (root->data > value)
		{
			root->right = removeHelp(root->right, value);
		}
		else //root->data == value
		{
			//leaf
			/*if (root->left == nullptr && root->right == nullptr) //sluchai?
			{
				delete root;
				return nullptr; //???
			}*/
			//1 child node
			if (root->left == nullptr)
			{
				Node* temp = root->left;
				delete root;
				return temp;
			}
			else if (root->right == nullptr)
			{
				Node* temp = root->right;
				delete root;
				return temp;
			}
			//2 child nodes
			Node* temp = getMinNode(root->right); //min el in the right subtree
			root->data = temp->data;
			root->right = removeHelp(root->right, temp->data); //find min el and del
		}
		return root;
	}
	size_t sizeHelp(Node* root)
	{
		if (root == nullptr)
			return 0;
		return 1 + sizeHelp(root->left) + sizeHelp(root->right);
	}
public:
	//BST
	AVLTree() :root(nullptr) {}
	AVLTree(const AVLTree& other)
	{
		root = copy(other.root);
	}
	AVLTree& operator= (const AVLTree& other)
	{
		if (this != &other)
		{
			del(root);
			root = copy(other.root);
		}
		return *this;
	}
	~AVLTree()
	{
		del(root);
	}

	bool isElement(int value)
	{
		return searchHelp(root, value) != nullptr;
	}
	Node* search(int value)
	{
		return searchHelp(root, value);
	}
	void insert(int value)
	{
		insertHelp(root, value);
	}
	void remove(int value)
	{
		removeHelp(root, value);
	}
	size_t size()
	{
		return sizeHelp(root);
	}
};

