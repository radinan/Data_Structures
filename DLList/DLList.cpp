#ifndef __DLLLIST_CPP
#define __DLLLIST_CPP

#include "DLList.h"

template<class T>
DLList<T>::Iterator::Iterator(Node* _curr, DLList* _list) : curr(_curr), list(_list) {}

template <class T>
typename DLList<T>::Iterator& DLList<T>::Iterator::operator++()
{
	if (curr == nullptr)
	{
		throw std::out_of_range("No more elements");
	}
	else
		curr = curr->next;
	return *this;
}

template <class T>
typename DLList<T>::Iterator& DLList<T>::Iterator::operator--()
{
	if (curr == nullptr)
	{
		if (list->first == nullptr) //ako e prazen spisyk
		{
			throw std::out_of_range("Empty list");
		}
		else
		{
			curr = list->last; // vryshtame edno nazad
		}
	}
	else
		curr = curr->prev; //vyzmojno prevyrtane, no ne igrae rolq

	return *this;
}

template <class T>
T& DLList<T>::Iterator::operator*()
{
	if (curr != nullptr)
		return curr->data;
	else //ako iteratora sluchaino e preskochil spisyka
		throw std::out_of_range("No data available");
}

template <class T>
bool DLList<T>::Iterator::operator!=(const Iterator& other)
{
	return (curr != other.curr); //tuk ne sym sig dali ne tr da e curr.data ???
}

template <class T>
bool DLList<T>::Iterator::operator==(const Iterator& other)
{
	return (curr == other.curr); //tuk ne sym sig dali ne tr da e curr.data ???
}

template <class T>
typename DLList<T>::Iterator DLList<T>::begin()
{
	return typename DLList<T>::Iterator(first, this);
}
template <class T>
typename DLList<T>::Iterator DLList<T>::end()
{
	return typename DLList<T>::Iterator(last, this); //last ili nullptr????
}



template <class T>
DLList<T>::DLList()
{
	first = nullptr;
	last = nullptr;
}

template <class T>
DLList<T>::DLList(const DLList<T>& other)
{
	copy(other);
}

template <class T>
DLList<T>::~DLList()
{
	del();
}


template <class T>
DLList<T>& DLList<T>::operator =(const DLList<T>& other)
{
	if (this != &other)
	{
		del();
		copy(other);
	}
	return *this;
}


template <class T>
void DLList<T>::copy(const DLList<T>& other) // 1 2
{
	if (other.first == nullptr) //prazen spisyk
		return;

	typename DLList<T>::Node* other_curr = other.first; //1
	while (other_curr != nullptr) //1
	{
		pushBack(other_curr->data);
		other_curr = other_curr->next; //2
	}
}

template <class T>
void DLList<T>::del()
{
	if (first == nullptr)
		return;

	Node* save = first;

	while (first != nullptr)
	{
		first = first->next;
		delete save;
		save = first;
	}
	last = nullptr;
}


template <class T>
void DLList<T>::pushBack(int value)
{
	Node* new_Node = new Node(value);

	if (first == nullptr) //prazen
	{
		first = new_Node;
		last = new_Node;
	}
	else
	{
		last->next = new_Node;
		new_Node->prev = last;
		last = new_Node;
	}
}

template <class T>
void DLList<T>::pushFront(const T& value)
{
	Node* new_Node = new Node(value);

	if (first == nullptr)
	{
		first = new_Node;
		last = new_Node;
	}
	else
	{
		first->prev = new_Node;
		new_Node->next = first;
		first = new_Node;
	}
}

/*
template <class T>
void DLList<T>::pushIndex(int index, T value)
{
	Node* new_Node = new Node(value);
	Node* current = first;

	for (int i = 1; i < index; ++i) //da proverq dali ne e do sledvashtiq el
	{
		if (current == nullptr)
			break;
		current = current->next;
	}
	if (current == nullptr)
	{
		pushBack(value);
		return;
	}
	new_Node->next = current->next;
	current->next->prev = new_Node;
	current->next = new_Node;
	new_Node->prev = current;
}
*/
template <class T>
void DLList<T>::popFront()
{
	if (first == nullptr)
	{
		return;
	}
	else if (first == last)
	{
		delete first;
		first = nullptr;
		last = nullptr;
	}
	else
	{
		Node* save = first;
		first = first->next;
		delete save;
	}
}

template <class T>
void DLList<T>::popBack()
{
	if (last == nullptr)
	{
		return;
	}
	else if (first == last)
	{
		delete last;
		first = nullptr;
		last = nullptr;
	}
	else
	{
		Node* save = last;
		last = last->prev;
		delete save;
	}
}
/*
template <class T>
void DLList<T>::popIndex(int index)
{
	if (index == 0)
	{
		return;
	}
	if (index == 1)
	{
		popFront();
		return;
	}

	Node* current = first;

	for (int i = 1; i < index; ++i)
	{
		if (current == nullptr)
			break;

		current = current->next;
	}
	if (current == nullptr)
	{
		return;
	}
	else
	{
		current->prev->next = current->next;
		current->next->prev = current->prev;
		delete current;
	}
}
*/

template <class T>
int DLList<T>::count(int x)
{
	if (first == nullptr)
	{
		return 0;
	}

	Node* current = first;
	int counter = 0;

	while (current != nullptr)
	{
		if (current->data == x)
			counter++;
		current = current->next;
	}
	return counter;
}


template <class T>
void DLList<T>::range(int x, int y)
{
	for (int i = x; i <= y; ++i)
	{
		pushBack(i);
	}
}

template <class T>
bool DLList<T>::removeAt(const DLList<T>::Iterator& it)
{
	typename DLList<T>::Node* crr = it.curr,
						   * save;

	if (crr == nullptr)
	{
		return false;
	}

	if (crr == first)
		//изтривамне първи елемент
	{
		save = first;
		first = first->next;
		delete save;

		if (first == nullptr)
		{
			last = nullptr;
		}
		return true;
	}

	save = crr;
	crr->prev->next = crr->next;

	if (crr->next != nullptr)
	{
		crr->next->prev = crr->prev;
	}
	else
	{
		last = crr->prev;
	}

	delete save;

	return true;
}

template <class T>
void DLList<T>::reverse()
{
	typename DLList<T>::Node* current = first, * save;
	//012340
	while (current != nullptr) //1 //2 //3 //4
	{
		save = current->next; //2 //3 //4 //0
		current->next = current->prev; //0 //1 //2 //3
		current->prev = save; //2 //3 //4 //0

		current = save; //2 //3 //4 //0
	}

	save = last; //4
	last = first; //1
	first = save; //4
}

template <class T>
bool DLList<T>::empty()
{
	return (this->first == nullptr);
}


//zad
template <class T>
void DLList<T>::removeAll(const T& x)
{
	typename DLList<T>::Iterator it = begin();
	T el;

	while (it != end()) //432/1
	{
		el = *it;
		if (el == x)
		{
			removeAt(it);
			it = begin();
		}
		++it;
	}
	if (*it == x) //posleden el;
		removeAt(it);
}

template <class T>
void DLList<T>::append(const DLList<T>& l1, const DLList<T>& l2)
{
	copy(l1);

	typename DLList<T>::Node *current_l2 = l2.first;
	//1 2 3 4 5 6 7 [8]<-current
	//current_l2->5 6 7 8 [nullptr]

	while (current_l2 != nullptr)
	{
		pushBack(current_l2->data);
		current_l2 = current_l2->next;
	}
}

template <class T>
void DLList<T>::removeDuplicates()
{
	if (first == nullptr) // first
		return;
	typename DLList<T>::Iterator it1 = begin(), it2 = begin();
	typename DLList<T>::Node* current, * data1, * data2;
	if (first->next == nullptr)
		return;

	while (it1.curr != nullptr) // pone 2 el
	{
		it2.curr = it1.curr;
		++it2;

		while (it2.curr != nullptr)
		{
			if (*it1 == *it2)
			{
				current = it2.curr;
				if (current->next != nullptr)
				{
					current = current->next;
				}
				else
					current = nullptr;

				removeAt(it2);
				it2.curr = current;
			}
			else
				++it2;
		}

		++it1;
	}
}


template <class T>
void DLList<T>::print()
{
	Node* current = first;
	while (current != nullptr)
	{
		std::cout << current->data << " ";
		current = current->next;
	}
	std::cout << std::endl;
}

#endif