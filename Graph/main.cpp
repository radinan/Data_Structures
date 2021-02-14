#define DOCTEST_CONFIG_IMPLEMENT
#include <iostream>
#include "Graph.cpp"
#include "doctest.h"
#include <string>
#include <vector>


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
	if (v1 == v2)
		return true;

	for (auto i : g.neighbors(v1))
	{
		if (std::find(path.begin(), path.end(), i.first) == path.end())
		{
			path.push_back(i.first);
			if (isWay(g, i.first, v2, path))
				return true;
			path.pop_back();
		}
	}

	return false;
}
void wayDFS()
{

}

int main()
{
	std::vector<std::string> path;
	std::cout << isWay<std::string, double>(testGraph(), "Sofia", "Naples", path) << std::endl;
	doctest::Context().run();
}

