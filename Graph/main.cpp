#define DOCTEST_CONFIG_IMPLEMENT
#include <iostream>
#include "Graph.cpp"
#include "doctest.h"
#include <string>
#include <vector>
#include <queue>


TEST_CASE("addVertex, addEdge, hasVertex, hasEdge, getWeight, neighbors")
{
	Graph <std::string, double> g;

	g.addVertex("Sofia");
	g.addVertex("Varna");
	g.addVertex("Berlin");
	
	g.addEdge("Sofia", "Varna", 100);
	g.addEdge("Varna", "Sofia", 90);
	g.addEdge("Sofia", "Berlin", 200);
	g.addEdge("Berlin", "Sofia", 150);

	CHECK(g.hasVertex("Sofia"));
	CHECK(!g.hasVertex("Paris"));
	CHECK(g.hasVertex("Berlin"));

	CHECK(g.hasEdge("Sofia", "Varna"));
	CHECK(!g.hasEdge("Varna", "Berlin"));

	CHECK(g.getWeight("Sofia", "Varna") == 100);
	CHECK(g.getWeight("Varna", "Sofia") == 90);
	CHECK(g.getWeight("Berlin", "Sofia") == 150);

	int count = 0;
	for (auto nbrs : g.neighbors("Sofia"))
	{
		CHECK((nbrs.first == "Varna" || nbrs.first == "Berlin"));
		++count;
	}
	CHECK(count == 2);

	count = 0;
	for (std::string s : g)
	{
		CHECK((s == "Berlin" || s == "Varna" || s == "Sofia"));
		++count;
	}
	CHECK(count == 3);

}

Graph<std::string, double> testGraph()
{
	Graph<std::string, double> airports;

	airports.addVertex("Sofia");
	airports.addVertex("New York");
	airports.addVertex("Milan");
	airports.addVertex("Naples");
	airports.addVertex("Los Angelis");
	airports.addVertex("Dan Francisko");
	airports.addVertex("Boston");

	airports.addEdge("Sofia", "Milan", 20);
	airports.addEdge("Milan", "Sofia", 25);

	airports.addEdge("Milan", "New York", 650);
	airports.addEdge("New York", "Milan", 800);

	airports.addEdge("Milan", "Naples", 100);
	airports.addEdge("Naples", "Naples", 15);

	airports.addEdge("New York", "Boston", 20);
	airports.addEdge("New York", "Los Angelis", 200);
	airports.addEdge("New York", "Dan Francisko", 120);
	airports.addEdge("Dan Francisko", "Los Angelis", 60);

	return airports;
}

template<class VertexType, class WeightType>
bool isWay(const Graph<VertexType, WeightType>& g, const VertexType& v1, const VertexType& v2, std::vector<VertexType>& path)
{
	path.push_back(v1);

	if (v1 == v2)
	{
		/*for (auto it : path)
		{
			std::cout << it << " ";
		}
		std::cout << std::endl;*/
		return true;
	}

	for (auto i : g.neighbors(v1))
	{
		if (std::find(path.begin(), path.end(), i.first) == path.end())
		{
			if (isWay(g, i.first, v2, path))
				return true;
		}
	}

	//std::cout << "Current path: ";
	//for (auto it : path)
	//{
	//	std::cout << it << " ";
	//}
	//std::cout << "Abandoning city: " << path.back() << std::endl;
	path.pop_back();
	return false;
}

template <class VertexType, class WeightType>
void allWaysDFS(const Graph<VertexType, WeightType>& g, const VertexType& v1, const VertexType& v2,
				std::vector<VertexType>& path, std::vector<std::vector<VertexType>>& allPaths)
{
	path.push_back(v1);

	if (v1 == v2)
	{
		std::cout << "Path found: ";
		for (std::string it : path)
		{
			std::cout << it << " ";
		}
		std::cout << std::endl;
		allPaths.push_back(path);
	}
	else
	{
		for (auto i : g.neighbors(v1))
		{
			if (std::find(path.begin(), path.end(), i.first) == path.end())
			{
				allWaysDFS(g, i.first, v2, path, allPaths);
			}
		}
	}
	path.pop_back();
}
template <class VertexType, class WeightType>
void bestWayDFS(const Graph<VertexType, WeightType>& g, const VertexType& v1, const VertexType& v2,
				std::vector<VertexType>& path, std::vector<VertexType>& bestPath)
{
	path.push_back(v1);
	if (v1 == v2)
	{
		if (bestPath.empty() || path.size() < bestPath.size()) //!!
			bestPath = path;
	}
	else
	{
		for (auto n : g.neighbors(v1))
		{
			if (std::find(path.begin(), path.end(), n.first) == path.end())
				bestWayDFS(g, n.first, v2, path, bestPath);
		}
	}
	path.pop_back();
}

//--------------------------------------------------------------------------------------------------------------------------
template <class VertexType, class WeightType>
bool iswayBFS(const Graph<VertexType, WeightType>& g, const VertexType& v1, const VertexType& v2, std::vector <VertexType>& path)
{
}

int main()
{
	std::vector<std::string> path, path1;
	std::vector<std::vector<std::string>>allPaths;
	//std::cout << isWay<std::string, double>(testGraph(), "Sofia", "Naples", path) << std::endl;
	/*std::cout<< isWay<std::string, double>(testGraph(), "Sofia", "Los Angelis", path)<< std::endl;
	for (auto i : path)
	{
		std::cout << i << " ";
	}
	std::cout << std::endl;*/

	//allWaysDFS<std::string, double>(testGraph(), "New York", "Los Angelis", path, allPaths);
	bestWayDFS<std::string, double>(testGraph(), "New York", "Los Angelis", path, path1);
	for (auto i : path1)
	{
		std::cout << i << " ";
	}
	std::cout << std::endl;
	doctest::Context().run();
}

