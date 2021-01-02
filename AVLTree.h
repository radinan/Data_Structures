#pragma once
#include <iostream>
#include <algorithm>

//the tree won't "own" the class T elements; it's only going to store them to let us use data faster

template <class T> //either overload class' funcs or add more template typenames
class AVLTree
{
private:
	struct Node
	{
		T data;
		int height; //by default node is leaf => h=0
		Node* left, * right;
		Node(T& data, int height = 0, Node* left = nullptr, Node* right = nullptr)
			: data(data), height(height), left(left), right(right){}
	};
	
	Node* root;

private:
	//--help functions for the constructors--//
	Node* copy(Node* other_root)
	{
		if (other_root == nullptr) //empty tree
			return nullptr;
		//else
		Node* new_node = new Node(other_root->data); //copying Node
		new_node->left = copy(other_root->left);	 //setting children
		new_node->right = copy(other_root->right);
		return root;
	}
	void del(Node* root) //&?
	{
		if (root == nullptr) //empty tree
			return;
		del(root->left); //recursive call
		del(root->right);
		delete root;	 //delete leaves->..->root
	}

	//--private setters and getters--//
	int getBalance(Node* node) const
	{
		if (node == nullptr) //no children
			return 0;
		return getHeight(node->left) - getHeight(node->right); 
		// B(node) = h(left subtree) - h(right subtree)
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
						  (getHeight(node->left),   //left subtree
						   getHeight(node->right)); //right subtree
		//if node has no children -> h = 1 + (-1) = 0
	}
	Node* getMinNode(Node* root) const
	{
		Node* curr = root;
		while (curr->left != nullptr && curr != nullptr)
		{
			curr = curr->left;
		}
		return curr;
		// (left subtree) < root < (right subtree)
	} 
	Node* getMaxNode(Node* root) const
	{
		Node* curr = root;
		while (curr->right != nullptr && curr != nullptr)
		{
			curr = curr->right;
		}
		return curr;
		// (left subtree) < root < (right subtree)
	}
	size_t sizeHelp(Node* root) const
	{
		if (root == nullptr)
			return 0;
		return 1 + sizeHelp(root->left) + sizeHelp(root->right); //number of all nodes
	}

	//--self-balance function (possible improvements)--//
	void selfBalance(Node* root)
	{
		setHeight(root);				//update h of the node
		int balance = getBalance(root); //get    B of the node

		if (balance > 1) //left heavy
		{
			if (getBalance(root->left) >= 0)
				root = rotateRight(root); 
			else
				root = rotateLeftRight(root); 
		}
		else if (balance < -1) //right heavy
		{
			if (getBalance(root->right) <= 0)
				root = rotateLeft(root);
			else
				root = rotateRightLeft(root);
		}
	}

	//--help functions--//
	Node* searchHelp(Node* root, T value) const //overload >==< for class T
	{
		if (root == nullptr || value == root->data) //end of tree or found element
			return root;
		if (value < root->data)
			return searchHelp(root->left, value);
		if (value > root->data)
			return searchHelp(root->right, value);
	}
	Node* insertHelp(Node* root, T value)  //overload  >==<
	{
		//BST insertion:
		if (root == nullptr)
		{
			return new Node(value); 
		}
		if (value < root->data) //smaller than node
			root->left = insertHelp(root->left, value);
		if (value > root->data) //bigger than node
			root->right = insertHelp(root->right, value);

		selfBalance(root); //AVLT mark
		return root;
	}
	Node* removeHelp(Node* root, T value) 
	{
		if (root == nullptr) //empty tree
			return root;

		//search
		if (value < root->data) //smaller than node
		{
			root->left = removeHelp(root->left, value);
		}
		else if (value > root->data) //bigger than node
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
	bool isElement(Ò& value) const
	{
		return searchHelp(root, value) != nullptr;
	}
	size_t size() const
	{
		return sizeHelp(root);
	}

	//--search, insertion, deletion--//
	Node* search(Ò& value) const
	{
		return searchHelp(root, value);
	}
	void insert(Ò& value)
	{
		root = insertHelp(root, value);
	}
	void remove(Ò& value)
	{
		removeHelp(root, value);
	}
};

