#include <iostream>
#include "AVL.h"
#include <string>


enum class Property { name, artist, year };

class Song
{
private:
	std::string name;
	std::string artist;
	size_t year;
public:
	static Property property; //one for all objects
public:
	Song(const std::string& name, const std::string& artist, int year) : name(name), artist(artist), year(year) {}

	Song& operator=(const Song& other)
	{
		if (this != &other)
		{
			name = other.name;
			artist = other.artist;
			year = other.year;
		}
		return *this;
	}
	//new overload for >, < and ==
	bool operator>(int right)
	{
		if (Song::property == Property::year)
			return year > right;
	}
	bool operator>(int right)
	{
		if (Song::property == Property::year)
			return year < right;
	}
	bool operator==(std::string str)
	{
		if (Song::property == Property::artist)
			return artist == str;
		if (Song::property == Property::name)
			return name == str;
	}

	friend bool operator>(const Song& left, const Song& right) //without friend
	{
		//name,artist,year
		switch (Song::property)
		{
		case Property::name:
			if (left.name == right.name)
			{
				if (left.artist == left.artist)
				{
					return left.year > right.year;
					break;
				}
				return left.artist > right.artist;
				break;
			}
			return left.name > right.name;
			break;
		case Property::artist:
			if (left.artist == right.artist)
			{
				if (left.name == left.name)
				{
					return left.year > right.year;
					break;
				}
				return left.name > right.name;
				break;
			}
			return left.artist > right.artist;
			break;

		case Property::year:
			if (left.year == right.year)
			{
				if (left.name == left.name)
				{
					return left.artist > right.artist;
					break;
				}
				return left.name > right.name;
				break;
			}
			return left.year > right.year;
			break;
		}
	}
	friend bool operator<(const Song& left, const Song& right)
	{
		switch (Song::property)
		{
		case Property::name:
			if (left.name == right.name)
			{
				if (left.artist == left.artist)
				{
					return left.year < right.year;
					break;
				}
				return left.artist < right.artist;
				break;
			}
			return left.name < right.name;
			break;
		case Property::artist:
			if (left.artist == right.artist)
			{
				if (left.name == left.name)
				{
					return left.year < right.year;
					break;
				}
				return left.name < right.name;
				break;
			}
			return left.artist < right.artist;
			break;

		case Property::year:
			if (left.year == right.year)
			{
				if (left.name == left.name)
				{
					return left.artist < right.artist;
					break;
				}
				return left.name < right.name;
				break;
			}
			return left.year < right.year;
			break;
		}
	}
	friend bool operator==(const Song& left, const Song& right) //not changed
	{
		switch (Song::property)
		{
		case Property::artist:
			return left.artist == right.artist;
			break;
		case Property::name:
			return left.name == right.name;
			break;
		case Property::year:
			return left.year == right.year;
			break;
		}
	}
	friend bool operator!=(const Song& left, const Song& right) //not changed
	{
		switch (Song::property)
		{
		case Property::artist:
			return left.artist != right.artist;
			break;
		case Property::name:
			return left.name != right.name;
			break;
		case Property::year:
			return left.year != right.year;
			break;
		}
	}
	friend std::ostream& operator<<(std::ostream& out, Song& one)
	{
		out << one.name << " " << one.artist << " " << one.year << " ";// << std::endl;
		return out;
	}

};
Property Song::property = Property::name; //by default

int main()
{
	Song s("a", "ff", 5), s1("b", "gg", 2), s2("a", "hh", 2), s3("d", "zz", 2), s4("e", "gg", 1), s5("f", "ss", 6);
	
	//--name--
	AVL<Song> name_sorted;
	name_sorted.insert(s);
	name_sorted.insert(s1);
	name_sorted.insert(s2);
	name_sorted.insert(s3);
	name_sorted.insert(s4);
	name_sorted.insert(s5);
	name_sorted.inorder();
	std::cout << std::endl;

	//--year--
	Song::property = Property::year;

	AVL<Song> year_sorted(name_sorted);
	std::vector<Song> veco;
	int a = 2;
	year_sorted.bigger_than_search(veco, a);
	year_sorted.inorder(); std::cout << std::endl;

	for (auto i : veco)
	{
		std::cout << i << " ";
	}
	std::cout << std::endl;

	//--artist--
	Song::property = Property::artist;

	AVL<Song> artist_sorted(name_sorted);
	std::vector<Song> vecco;
	std::string c = "gg";
	year_sorted.equal_to_search(vecco, c);
	artist_sorted.inorder(); std::cout << std::endl;
	for (auto i : vecco)
	{
		std::cout << i << " ";
	}
	
return 0;
}
	
