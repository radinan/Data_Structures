#ifndef _BINTREE_H
#define _BINTREE_H
#include <string>
#include <vector>

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
	void clear(Node* root);
	bool isEqual(Node* root1, Node* root2);
	bool isMemberHelp(Node* root, const T& element);
	T sumHelper(Node* root);
	size_t countHelper(Node* root);
	size_t countEvensHelper(Node* root);
	int searchCountHelper(Node* root, bool (*pred)(const T&));
	int heightHelper(Node* root);
	int countLeavesHelper(Node* root);
	const T& maxLeafHelper(Node* root);

	int getNodeLevelHelper(Node* root, const T& element, int level);
	void serializeTreeHelperScheme(Node* root, std::ostream& out); //const & ???
	Node* parseTreeHelperScheme(std::istream& in);
	void serializeTreeHelperHaskell(Node* root, std::ostream& out); //const & ???
	Node* parseTreeHelperHaskell(std::istream& in);
	void listLeavesHelper(Node* root, std::vector<T>& vec);
	bool findTraceHelper(Node* root, const T& element, std::string& path);

public:
	BinTree();
	bool operator == (const BinTree& other);
	void insert(const T& element, const char* path); //adds element to the tree
	Node* locate(const char* path) const; //returns a node by given path 
	T get(const char* path) const; //returns node's data by given path
	T& operator[](const char* path); //[path] for modifications
	bool isMember(const T& element); //checks whether an element is a member
	T sum(); //sum of all elements 
	size_t count(); //count of all nodes
	size_t countEvens(); //count of even nodes
	int searchCount(bool (*pred)(const T&));
	int height();
	int countLeaves();
	const T& maxLeaf();
	//19-2
	//void prettyPrint(); //do it later
	void serializeTreeScheme(std::ostream& out);
	void parseTreeScheme(std::istream& in);
	void serializeTreeHaskell(std::ostream& out);
	void parseTreeHaskell(std::istream& in);
	int getNodeLevel(const T& element);
	std::vector<T> listLeaves();
	std::string findTrace(const T& element);
};

#endif