#pragma once

//първо го правя BST после го upgrade-вам :)

class AVLTree
{
private:
	struct Node
	{
		int data;
		//int BF;
		//int height;
		Node* left, * right;
		//Node(int data, int BF = 0, int height = -1, Node* left = nullptr, Node* right = nullptr)
		//	:data(data), BF(BF), height(height), left(left), right(right){}
		Node(int data, Node* left = nullptr, Node* right = nullptr)
			: data(data), left(left), right(right){}
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

	Node* searchHelp(Node* root, int value) //&? //връща указател към елемента
	{
		if (root == nullptr)
			return nullptr;
		if (value == root->data) //може да се обедини с горното
			return root;
		if (value < root->data)
			return searchHelp(root->left, value);
		if (value > root->data)
			return searchHelp(root->right, value);
	}
	void insertHelp(Node* root, int value) //може да е bool
	{
		if (root == nullptr)
		{
			new Node(value);
			return;
		}
		if (value < root->data)
			insertHelp(root->left, value);
		if (value > root->data)
			insertHelp(root->right, value);
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
			Node* temp = getMinNode(root->right); //най-малкия ел в дясното поддърво
			root->data = temp->data;
			root->right = removeHelp(root->right, temp->data); //намираме мин елемента и го изтриваме
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

