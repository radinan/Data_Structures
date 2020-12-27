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
		int height; //by default node is leaf => h=0
		Node* left, * right;
		Node(int data, int height = 0, Node* left = nullptr, Node* right = nullptr)
			: data(data), height(height), left(left), right(right){}
	};
	
	Node* root;

private:
	//--help functions for the constructors--//
	Node* copy(Node* other_root)
	{
		if (other_root == nullptr)
			return nullptr;
		Node* new_node = new Node(other_root->data);
		new_node->left = copy(other_root->left);
		new_node->right = copy(other_root->right);
		return root;
	}
	void del(Node* &root)
	{
		if (root == nullptr)
			return;
		del(root->left);
		del(root->right);
		delete root;
	}

	//--private setters and getters--//
	int getBalance(Node* node) const
	{
		if (node == nullptr)
			return 0;
		return getHeight(node->left) - getHeight(node->right);
	}
	int getHeight(Node* node) const
	{
		if (node == nullptr)
			return -1; //no node
		return node->height;
	}
	void setHeight(Node* node)
	{
		node->height = 1 + std::max
		(getHeight(node->left),
			getHeight(node->right));
	}
	Node* getMinNode(Node* root) const
	{
		Node* curr = root;
		while (curr->left != nullptr && curr != nullptr)
		{
			curr = curr->left;
		}
		return curr;
	} 
	Node* getMaxNode(Node* root) const
	{
		Node* curr = root;
		while (curr->right != nullptr && curr != nullptr)
		{
			curr = curr->right;
		}
		return curr;
	}
	size_t sizeHelp(Node* root) const
	{
		if (root == nullptr)
			return 0;
		return 1 + sizeHelp(root->left) + sizeHelp(root->right);
	}

	//--self-balance function (possible improvements)--//
	void selfBalance(Node*& root)
	{
		setHeight(root); //update-ing height
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
	}

	//--help functions--//
	Node* searchHelp(Node* root, int value) const //&? //returns ptr to element
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
		//BST insertion:
		if (root == nullptr)
		{
			return new Node(value); 
		}
		if (value < root->data)
			root->left = insertHelp(root->left, value);
		if (value > root->data)
			root->right = insertHelp(root->right, value);

		selfBalance(root);
		return root;
	}
	Node* removeHelp(Node* root, int value)
	{
		if (root == nullptr)
			return root;

		//search
		if (root->data > value)
		{
			root->left = removeHelp(root->left, value);
		}
		else if (root->data < value)
		{
			root->right = removeHelp(root->right, value);
		}
		else //found
		{
			//leaf or 1 child node
			if (root->left == nullptr) //only right child (or leaf)
			{
				Node* temp = root->right; //(or nullptr)
				delete root;
				return temp;
			}
			else if (root->right == nullptr) //only left child
			{
				Node* temp = root->left;
				delete root;
				return temp;
			}
			//2 child nodes
			Node* temp = getMinNode(root->right); //min el in the right subtree
			root->data = temp->data;
			root->right = removeHelp(root->right, temp->data); //find min el and del
		}

		//selfBalance(root);
		return root;
	}

	//--rotation functions--//
	Node* rotateRight(Node* node)
	{
		Node* left_temp = node->left;
		node->left = left_temp->right;
		left_temp->right = node;

		setHeight(node);
		setHeight(left_temp);

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

		setHeight(node);
		setHeight(right_temp);

		return right_temp;
	}
	Node* rotateRightLeft(Node* node)
	{
		node->right = rotateRight(node->right);
		return rotateLeft(node);
	}

public:
	//--Constructors--//
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

	//--informative methods--//
	bool isElement(int value) const
	{
		return searchHelp(root, value) != nullptr;
	}
	size_t size() const
	{
		return sizeHelp(root);
	}

	//--search, insertion, deletion--//
	Node* search(int value) const
	{
		return searchHelp(root, value);
	}
	void insert(int value)
	{
		root = insertHelp(root, value);
	}
	void remove(int value)
	{
		removeHelp(root, value);
	}
};

