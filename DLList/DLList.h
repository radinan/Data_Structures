#ifndef __DLLLIST_H
#define __DLLLIST_H

#include <iostream>

template <class T>
class DLList
{
private:
	struct Node
	{
		T data;
		Node* next;
		Node* prev;

		Node(T _data, Node* _next = nullptr, Node* _prev = nullptr)
			: data(_data), next(_next), prev(_prev) {}
	};
	Node* first;
	Node* last;

public:
	class Iterator
	{
	private:
		Node* curr;
		DLList* list; //bez <T> zashtoto e vlojen class
	public:
		Iterator(Node*, DLList*);
		Iterator& operator++();
		Iterator& operator--();
		T& operator*();
		bool operator!=(const Iterator& other);
		bool operator==(const Iterator& other);

		friend class DLList;
	};
public:

	Iterator begin();
	Iterator end();


	DLList();
	DLList(const DLList<T>& other);
	~DLList();

	DLList<T>& operator =(const DLList<T>& other);
	//DLList<T> operator +(const DLList& other) const;
	//DLList<T>& operator +=(const DLList& other);

	void copy(const DLList<T>& other);
	void del();

	void pushBack(int value);
	void pushFront(const T& value);
	//void pushIndex(int index, T value);
	void popFront();
	void popBack();
	//void popIndex(int index);


	int count(int x); //kolko pyti x se sreshta v spisyka
	void range(int x, int y);


	bool removeAt(const Iterator&);
	void reverse();
	bool empty();


	//zad
	void removeAll(const T& x);
	void append(const DLList<T>& l1, const DLList<T>& l2);
	void removeDuplicates();

	void print();
};

#endif