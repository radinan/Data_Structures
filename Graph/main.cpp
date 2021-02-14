#define DOCTEST_CONFIG_IMPLEMENT
#include <iostream>
#include "Graph.cpp"
#include "doctest.h"
#include <string>


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

int main()
{
	doctest::Context().run();
}

