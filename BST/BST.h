#pragma once
#include <iostream>

template <class T>
class BST
{
private:
	struct Node
	{
		T data;
		Node* left = nullptr, *right = nullptr;
		size_t height = 0; //by default node is a leaf

		Node(T _data) : data(_data) {}
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

	Node* get_min_node(Node* root)
	{
		// (left subtree) < root < (right subtree)
		Node* curr = root;
		while (curr != nullptr && curr->left != nullptr)
		{
			curr = curr->left;
		}
		return curr;
	}
	
	//helpers
	Node* insert_help(Node* root, T element)
	{
		//empty/end of tree
		if (root == nullptr)
			return new Node(element);  //creating leaf
		else if (element < root->data) //go in left subtree
			root->left = insert_help(root->left, element);
		else if (element > root->data) //go in right subtree
			root->right = insert_help(root->right, element);

		return root; //returning the root node at the end
	}
	Node* search_help(Node* root, T element) //returns either the element, or nullptr
	{
		//empty/end of tree or found 
		if (root == nullptr || root->data == element)
			return root;
		else if (element < root->data) //go in left subtree
			search_help(root->left, element);
		else if (element > root->data) //go in right subtree
			search_help(root->right, element);
	}
	Node* remove_help(Node* root, T element)
	{
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

		return root;
	}
	void inorder_help(Node* root)
	{
		if (root != nullptr)
		{
			inorder_help(root->left);
			std::cout << root->data << " ";
			inorder_help(root->right);
		}
	}
public:
	BST() : root(nullptr) {}
	BST(const BST& other)
	{
		root = copy(other.root);
	}
	BST& operator=(const BST& other)
	{
		if (this != other)
		{
			del();
			root = copy(other.root);
		}
		return *this;
	}
	~BST()
	{
		del(root);
	}

	//main functions
	void insert(T element)
	{
		root = insert_help(root, element);
	}
	Node* search(T element) //possible overload for searching by "criterium"
	{
		return search_help(root, element);
	}
	void remove(T element)
	{
		root = remove_help(root, element);
	}
	//sort() {}  //overload for sort ;(

	//print
	void inorder()
	{
		inorder_help(root);
	}

};
