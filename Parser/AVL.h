#pragma once
#include <iostream>


//--AVL Tree-- 
// self-balancing BST;  |B(n)| <= 1;
// Time complexity:
//		-> insert:		O(logn) best/worst case
//		-> delete:		O(logn) best/worst case
//		-> search:		O(logn) best/worst case

template <class T>
class AVL
{
private:
	struct Node
	{
		T data;
		Node* left = nullptr, * right = nullptr;
		size_t height = 0; //by default node is a leaf

		Node(const T& _data) : data(_data) {}
	};
	Node* root;
private:
	Node* copy(Node* other_root)
	{
		//empty tree
		if (other_root == nullptr)
			return nullptr;
		//else
		Node* new_Node = new Node(other_root->data); //copying node
		new_Node->left = copy(other_root->left);	 //copying children
		new_Node->right = copy(other_root->right);

		return root; //returning pointer to copied tree
	}
	void del(Node* root)
	{
		//empty tree
		if (root == nullptr)
			return;
		//else
		del(root->left);	//recursively calling all children
		del(root->right);

		delete root;	    //deleting every node
	}

	//setters and getters
	Node* get_min_node(Node* root) const
	{
		// (left subtree) < root < (right subtree)
		Node* curr = root;
		while (curr != nullptr && curr->left != nullptr)
		{
			curr = curr->left;
		}
		return curr;
	}
	int get_height(Node* node) const
	{
		if (node == nullptr)
			return -1; //no node
		else
			return node->height;
	}
	void set_height(Node* node)
	{
		node->height = 1 + std::max(get_height(node->left),
			get_height(node->right));
		//if node has no children -> h = 1 + (-1) = 0
	}
	int get_balance(Node* node) const
	{
		if (node == nullptr)
			return 0;
		else
			return get_height(node->left) - get_height(node->right);
		// B(node) = h(left) - h(right)
		// B > 0 -> left heavy
		// B < 0 -> right heavy
	}

	//rotations 
	Node* left_rotate(Node* node)
	{
		Node* temp = node->right;
		node->right = temp->left;
		temp->left = node;

		//set new heights
		set_height(node);
		set_height(temp);

		return temp;
	}
	Node* right_rotate(Node* node)
	{
		Node* temp = node->left;
		node->left = temp->right;
		temp->right = node;

		//set new heights
		set_height(node);
		set_height(temp);

		return temp;
	}
	Node* left_right_rotate(Node* node)
	{
		node->left = left_rotate(node->left);
		return right_rotate(node);
	}
	Node* right_left_rotate(Node* node)
	{
		node->right = right_rotate(node->right);
		return left_rotate(node);
	}

	//helpers
	Node* insert_help(Node* root, T& element)
	{
		//1. BST insert
		//empty/end of tree
		if (root == nullptr)
			return new Node(element);  //creating leaf
		else if (element < root->data) //go in left subtree
			root->left = insert_help(root->left, element);
		else if (element > root->data) //go in right subtree
			root->right = insert_help(root->right, element);

		//~~AVL~~:
		//2. update height and check balance
		set_height(root);
		int balance = get_balance(root);

		//3. rotate if it's unbalanced
		if (balance > 1) //left heavy
		{
			//LL
			if (element < root->left->data)
				return right_rotate(root);
			//LR
			else if (element > root->left->data)
				return left_right_rotate(root);
		}
		else if (balance < -1) //right heavy
		{
			//RR
			if (element > root->right->data)
				return left_rotate(root);
			//RL
			else if (element < root->right->data)
				return right_left_rotate(root);
		}

		return root; //returning the root node at the end
	}
	Node* search_help(Node* root, T& element) const //returns either the element, or nullptr
	{
		//BST search
		//empty/end of tree or found 
		if (root == nullptr || root->data == element)
			return root;
		else if (element < root->data) //go in left subtree
			search_help(root->left, element);
		else if (element > root->data) //go in right subtree
			search_help(root->right, element);
	}
	Node* remove_help(Node* root, T& element)
	{
		//1. BST remove
		//empty/end of tree 
		if (root == nullptr)
			return root;
		else if (element < root->data) //go in left subtree
			root->left = remove_help(root->left, element);
		else if (element > root->data) //go in right subtree
			root->right = remove_help(root->right, element);
		else //found
		{
			//no children or 1 child
			if (root->left == nullptr)
			{
				Node* save = root->right; //ptr to save the child node
				delete root;
				return save;			  //it will automatically connect with root's parent by the recursion
			}
			else if (root->right == nullptr) //analogical
			{
				Node* save = root->left;
				delete root;
				return save;
			}
			//2 children
			else
			{
				//we either get the max node from the left subtree  (could shrink the tree too much)
				//			 or the min node from the right subtree (my choice)
				//so we can save the BST property
				Node* min_right = get_min_node(root->right);			 //min node from the right subtree
				root->data = min_right->data;							 //copy its data
				root->right = remove_help(root->right, min_right->data); //find and remove the original
			}
		}

		//~~AVL~~: 
		//2. update height and check balance
		set_height(root);
		int balance = get_balance(root);
		int left_balance = get_balance(root->left);
		int right_balance = get_balance(root->right);

		//3. rotate if it's unbalanced
		if (balance > 1)
		{
			//LL
			if (left_balance >= 0)
				return right_rotate(root);
			//LR
			else // left_balance < 0
				return left_right_rotate(root);
		}
		else if (balance < -1)
		{
			//RR
			if (right_balance <= 0)
				return left_rotate(root);
			//RL
			else // right_balance > 0
				return right_left_rotate(root);
		}

		return root; //returning the root node at the end
	}
	Node* copy_insert_helper(Node* _root)
	{
		if (_root == nullptr)
			return nullptr;

		insert(_root->data);
		copy_insert_helper(_root->left);
		copy_insert_helper(_root->right);

		return root;
	}
	void inorder_help(Node* root) const
	{
		if (root != nullptr)
		{
			inorder_help(root->left);
			std::cout << root->data << " ";
			inorder_help(root->right);
		}
	}
	void preorder_help(Node* root) const
	{
		if (root != nullptr)
		{
			std::cout << root->data << " ";
			preorder_help(root->left);
			preorder_help(root->right);
		}
	}
	const size_t sizeHelp(Node* root) const
	{
		if (root == nullptr)
			return 0;
		return 1 + sizeHelp(root->left) + sizeHelp(root->right); //number of all nodes
	}
	//new function
	std::vector<T>& inorder_bigger_help(Node* root, std::vector<T>& vec, int value)
	{
		if (root != nullptr)
		{
			inorder_search_help(root->left, vec, value);
			if (root->data > value)
				vec.push_back(root->data);
			inorder_search_help(root->right, vec, value);

			return vec;
		}
	}
	std::vector<T>& inorder_equal_help(Node* root, std::vector<T>& vec, std::string str)
	{
		if (root != nullptr)
		{
			inorder_equal_help(root->left, vec, str);
			if (root->data == str)
				vec.push_back(root->data);
			inorder_equal_help(root->right, vec, str);

			return vec;
		}
	}

public:
	AVL() : root(nullptr) {}
	AVL(const AVL& other)
	{
		//root = copy(other.root);
		root = copy_insert_helper(other.root);
	}
	AVL& operator=(const AVL& other)
	{
		if (this != other)
		{
			del(root);
			root = copy(other.root);
		}
		return *this;
	}
	~AVL()
	{
		del(root);
	}

	bool empty()
	{
		return root == nullptr;
	}
	//main functions
	void insert(T& element)
	{
		root = insert_help(root, element);
	}
	Node* search(T& element) const
	{
		return search_help(root, element);
	}
	void remove(T& element)
	{
		root = remove_help(root, element);
	}
	//new function
	void bigger_than_search(std::vector<T>& vec, int value)
	{
		vec = inorder_bigger_help(root, vec, value);
	}
	void equal_to_search(std::vector<T>& vec, std::string str)
	{
		vec = inorder_equal_help(root, vec, str);
	}

	void inorder() const
	{
		inorder_help(root);
	}
	void preorder() const
	{
		preorder_help(root);
	}
	const size_t size() const
	{
		return sizeHelp(root);
	}
};