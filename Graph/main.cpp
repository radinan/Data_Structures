#define DOCTEST_CONFIG_IMPLEMENT
#include <iostream>
#include "Graph.cpp"
#include "doctest.h"
#include <string>
#include <vector>
#include <queue>
#include <set>


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
bool isWayDFS(const Graph<VertexType, WeightType>& g, const VertexType& v1, const VertexType& v2, std::vector<VertexType>& path)
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
			if (isWayDFS(g, i.first, v2, path))
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
bool isWayBFS(const Graph<VertexType, WeightType>& g, const VertexType& v1, const VertexType& v2)
{
	std::queue<VertexType> q;
	std::set<VertexType> visited;

	q.push(v1);
	visited.insert(v1); //?
	while (!q.empty() && q.front() != v2)
	{
		VertexType curr = q.front(); q.pop();

		for (auto i : g.neighbors(curr))
		{
			if (visited.count(i.first) == 0)
			{
				q.push(i.first);
				visited.insert(i.first);
			}
		}
	}

	return !q.empty();
}

template <class VertexType, class WeightType>
bool stepsWayBFS(const Graph<VertexType, WeightType>& g, const VertexType& v1, const VertexType& v2)
{
	std::queue<std::pair<VertexType, bool>> q;
	std::set<VertexType> visited;
	unsigned int lvl = 0;

	q.push(std::make_pair(v1, true));
	visited.insert(v1);
	q.push(std::make_pair(VertexType(), false));

	while (!q.empty() && q.front().first != v2)
	{
		std::pair<VertexType, bool> curr = q.front();
		q.pop();

		if (curr.second == false)
		{
			if (!q.empty())
			{
				++lvl;
				q.push(std::make_pair(VertexType(), false));
			}
		}
		else
		{
			std::cout << "lvl: " << lvl << " City: " << curr.first << std::endl;

			for (auto i : g.neighbors(curr.first))
			{
				if (visited.count(i.first) == 0)
				{
					q.push(std::make_pair(i.first, true));
					visited.insert(i.first);
				}
			}
		}
	}

	return !q.empty();

}

template <class VertexType, class WeightType>
void reverseBestWayBFS(const Graph<VertexType, WeightType>& g, const VertexType& v1, const VertexType& v2)
{
	std::queue<std::pair<VertexType, bool>> q;
	std::set<VertexType> visited;
	std::unordered_map<VertexType, VertexType> way;

	q.push(std::make_pair(v1, true));
	visited.insert(v1);
	q.push(std::make_pair(VertexType(), false));

	while (!q.empty() && q.front().first != v2)
	{
		std::pair<VertexType, bool> curr = q.front();
		q.pop();

		if (curr.second == false)
		{
			if (!q.empty())
			{
				q.push(std::make_pair(VertexType(), false));
			}
		}
		else
		{
			for (auto i : g.neighbors(curr.first))
			{
				if (visited.count(i.first) == 0)
				{
					visited.insert(i.first);
					q.push(std::make_pair(i.first, true));
					way[i.first] = curr.first;

				}
			}
		}
	}

	if (!q.empty())
	{
		VertexType curr = v2; 
		std::cout << v2 ;
		while (v1 != curr )
		{
			std::cout << ", " << way[curr];
			curr = way[curr];
		}
	}

}













int main()
{
	std::vector<std::string> path, path1;
	std::vector<std::vector<std::string>>allPaths;
	//std::cout << isWayDFS<std::string, double>(testGraph(), "Sofia", "Naples", path) << std::endl;
	/*std::cout<< isWayDFS<std::string, double>(testGraph(), "Sofia", "Los Angelis", path)<< std::endl;
	for (auto i : path)
	{
		std::cout << i << " ";
	}
	std::cout << std::endl;*/

	//allWaysDFS<std::string, double>(testGraph(), "New York", "Los Angelis", path, allPaths);
	/*bestWayDFS<std::string, double>(testGraph(), "New York", "Los Angelis", path, path1);
	for (auto i : path1)
	{
		std::cout << i << " ";
	}
	std::cout << std::endl;*/

	//std::cout << isWayBFS<std::string, double>(testGraph(), "Sofia", "Los Angelis") << std::endl;
	//std::cout << isWayBFS<std::string, double>(testGraph(), "Naples", "Sofia") << std::endl;

	reverseBestWayBFS<std::string, double>(testGraph(), "New York", "Los Angelis");

	doctest::Context().run();
}

