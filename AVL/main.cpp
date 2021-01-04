#include <iostream>
#include "AVLTree.h"
#include <string>


enum class Property{name, artist, year};

class Song //test class for my project
{
private:
	std::string name;
	std::string artist;
	int year;
	Property property = Property::name; //by default

public:
	Song(const std::string& name, const std::string& artist, int year) : name(name), artist(artist), year(year) {}
	void set(const Property& _property) 
	{
		property = _property;
	}

	friend bool operator>(const Song& one, const Song& other) //without friend
	{
		switch (one.property)
		{
		case Property::artist:
			return one.artist > other.artist;
			break;
		case Property::name:
			return one.name > other.name;
			break;
		case Property::year:
			return one.year > other.year;
			break;
		}
	}
	friend bool operator<(const Song& one, const Song& other) //without friend
	{
		switch (one.property)
		{
		case Property::artist:
			return one.artist < other.artist;
			break;
		case Property::name:
			return one.name < other.name;
			break;
		case Property::year:
			return one.year < other.year;
			break;
		}
	}
	friend bool operator==(const Song& one, const Song& other) //without friend
	{
		switch (one.property)
		{
		case Property::artist:
			return one.artist == other.artist;
			break;
		case Property::name:
			return one.name == other.name;
			break;
		case Property::year:
			return one.year == other.year;
			break;
		}
	}
	friend std::ostream& operator<<(std::ostream& out, Song& one)
	{
		out << one.name << " " << one.year << " ";// << std::endl;
		return out;
	}
};


int main()
{
	Song s("i","c", 9), s1("h","b", 5), s2("g","a", 10), s3("f","b", 0), s4("e","f",6), s5("d", "c", 11),
		s6("c", "c", -1), s7("b", "c", 1), s8("a", "c", 2);
	s.set(Property::year);
	s1.set(Property::year);
	s2.set(Property::year);
	s3.set(Property::year);
	s4.set(Property::year);
	s5.set(Property::year);
	s6.set(Property::year);
	s7.set(Property::year);
	s8.set(Property::year);

	AVL<Song> rr;
	rr.insert(s);
	rr.insert(s1);
	rr.insert(s2);
	rr.insert(s3);
	rr.insert(s4);
	rr.insert(s5);
	rr.insert(s6);
	rr.insert(s7);
	rr.insert(s8);
	std::cout << "Preorder traversal of the given tree \n";
	rr.preorder();

	rr.remove(s2);
	std::cout << "Preorder traversal of the given tree \n";
	rr.preorder();
  
  return 0;
  }
