#define DOCTEST_CONFIG_IMPLEMENT
#include <iostream>
#include "DLList.h"
#include "DLList.cpp"
#include "doctest.h"

TEST_CASE("operator ++")
{
	DLList<int> list;
	DLList<int>::Iterator it = list.begin();

	try
	{
		++it;
	}
	catch (const std::out_of_range& str)
	{
		//std::cout << "molq";
		//CHECK(true);
	}
	catch (...)
	{
		CHECK(false);
	}
}

TEST_CASE("deleteAt")
{
	DLList<int> list;

	list.pushFront(1);
	list.pushFront(2);
	list.pushFront(3);
	list.pushFront(4); //4 3 [2] 1

	DLList<int>::Iterator it = list.begin();
	++(++it);
	list.removeAt(it);

	it = list.begin();
	++it;
	CHECK(*it == 3);
	++it;
	CHECK(*it == 1);

	it = list.begin();
	list.removeAt(it); //[4] 3 [2] 1

	it = list.begin();
	CHECK(*it == 3);

	++it;
	list.removeAt(it); //[4] 3 [2] [1]

	it = list.begin();
	CHECK(*it == 3);

}

TEST_CASE("Reverse")
{
	DLList<int> list;

	list.pushBack(1);
	//list.pushBack(2);
	//list.pushBack(3);
	list.pushBack(4);
	list.reverse();

	typename DLList<int>::Iterator it = list.begin();
	CHECK(*it == 4);
	//++(++(++it));
	++it;
	CHECK(*it == 1);

}

TEST_CASE("del_x")
{
	DLList<int> list;

	list.pushBack(1);
	list.pushBack(2);
	list.pushBack(1);
	list.pushBack(1);
	list.pushBack(3);

	list.removeAll(1); // [1] 2 [1] [1] 3
	typename DLList<int>::Iterator it = list.begin();
	CHECK(*it == 2);
	++it;
	CHECK(*it == 3);

	DLList<int> list2;
	list2.pushBack(1);
	list2.pushBack(2);

	list2.removeAll(2);
	typename DLList<int>::Iterator it2 = list2.begin();
	CHECK(*it2 == 1);
}

TEST_CASE("append")
{
	DLList<int> list, list1, list2;

	list1.pushBack(1);
	list1.pushBack(2);
	//list1.pushBack(3);

	list2.pushBack(3);
	list2.pushBack(4);

	list.append(list1, list2);
	
	typename DLList<int>::Iterator it = list.begin();
	CHECK(*it == 1);
	++it;
	CHECK(*it == 2);
	++it;
	CHECK(*it == 3);
	++it;
	CHECK(*it == 4);
	//++it;
	//CHECK(*it == 5);
}

TEST_CASE("removeDup")
{
	DLList<int> list;
	list.pushBack(1);
	list.pushBack(2);
	list.pushBack(1);
	list.pushBack(2);

	list.removeDuplicates();

	typename DLList<int>::Iterator it = list.begin();
	CHECK(*it == 1);
	++it;
	CHECK(*it == 2);
	//++it;
	//CHECK(*it == 3);

}

int main()
{
	/*
	DLList<int> hello;
	DLList<int> bye;

	bye.range(5, 7);
	hello.range(3, 7);

	//hello += bye;

	std::cout << std::endl;

	hello.print();
	*/

	doctest::Context().run();
	return 0;
}
