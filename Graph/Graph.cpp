#ifndef _GRAPH_CPP
#define _GRAPH_CPP

#include "Graph.h"
#include <cassert>

template <class VertexType, class WeightType>
void Graph<VertexType, WeightType>::addVertex(const VertexType& v)
{
	graph[v];
}

template <class VertexType, class WeightType>
bool Graph<VertexType, WeightType>::hasVertex(const VertexType& v) const
{
	return graph.count(v) > 0;
}

template <class VertexType, class WeightType>
void Graph<VertexType, WeightType>::addEdge(const VertexType& v1, const VertexType& v2, const WeightType w)
{
	assert(hasVertex(v1));
	assert(hasVertex(v2));
	graph[v1][v2] = w;
}

template <class VertexType, class WeightType>
bool Graph<VertexType, WeightType>::hasEdge(const VertexType& v1, const VertexType& v2) const
{
	return hasVertex(v1) && hasVertex(v2) && graph.at(v1).count(v2) > 0;
}

template <class VertexType, class WeightType>
WeightType Graph<VertexType, WeightType>::getWeight(const VertexType& v1, const VertexType& v2) const
{
	assert(hasEdge(v1, v2));

	return graph.at(v1).at(v2)
}

template <class VertexType, class WeightType>
const std::map<VertexType, WeightType>& Graph<VertexType, WeightType>::neighbors(const VertexType& v) const
{
	assert(hasVertex(v));
	return graph.at(v);
}

#endif