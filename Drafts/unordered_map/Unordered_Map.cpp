#include <iostream>
#include <unordered_map> //includes also unordered_multimap


class Song
{
private:
	std::string name;
	std::string artist;
public:
	Song() {}
	Song(const std::string& n, const std::string& a)
	{
		name = n;
		artist = a;
	}
	~Song() {}

	std::string& get_name()
	{
		return name;
	}

	friend std::ostream& operator <<(std::ostream& out, Song& song);
};
std::ostream& operator <<(std::ostream& out, Song& song)
{
	out << song.name << " " << song.artist;
	return out;
}

int main()
{

	std::unordered_multimap<std::string, Song> unrd;
	Song song1("name of song", "this artist"), song2("name of song", "other artist"), song3("third name", "third artist");
  
  //works only for unordered_map:
	//unrd[song1.get_name()] = song1;
	//unrd[song2.get_name()] = song2;
	//unrd[song3.get_name()] = song3;
  
	unrd.insert(std::make_pair(song1.get_name(), song1));
	unrd.insert(std::make_pair(song3.get_name(), song3));
	unrd.insert(std::make_pair(song2.get_name(), song2));



	for (auto& it : unrd)
	{
		std::cout << it.first << ": " << it.second << '\n';
	}
	std::cout << std::endl;
  
  //for chained buckets in unordered_multimap:
	auto range = unrd.equal_range(song1.get_name());
	for (auto itr = range.first; itr != range.second; ++itr)
	{
		std::cout << itr->second << "  ";
	}
	std::cout << std::endl;


}

