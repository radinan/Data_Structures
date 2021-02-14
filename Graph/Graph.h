#ifndef _GRAPH_H
#define _GRAPH_H

#include <unordered_map>
#include <map>
#include <iostream>

template <class VertexType, class WeightType>
class Graph
{
private:
	std::unordered_map <const VertexType, std::map<VertexType, WeightType>>& graph;
private:

public:
	void addVertex(const VertexType&);
	bool hasVertex(const VertexType&) const;

	void addEdge(const VertexType&, const VertexType&, const WeightType);
	bool hasEdge(const VertexType&, const VertexType&) const;

	WeightType getWeight(const VertexType&, const VertexType&) const;

	const std::map<VertexType, WeightType>& neighbors(const VertexType&) const;

};

#endif