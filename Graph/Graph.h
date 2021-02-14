#ifndef _GRAPH_H
#define _GRAPH_H

#include <unordered_map>
#include <map>
#include <iostream>

template <class VertexType, class WeightType>
class Graph
{
private:
	std::unordered_map<VertexType, std::map<VertexType, WeightType>> graph;
public:
	void addVertex(const VertexType&);
	bool hasVertex(const VertexType&) const;

	void addEdge(const VertexType&, const VertexType&, const WeightType&);
	bool hasEdge(const VertexType&, const VertexType&) const;

	WeightType getWeight(const VertexType&, const VertexType&) const;

	const std::map<VertexType, WeightType>& neighbors(const VertexType&) const;

private:
	using IteratorType = typename std::unordered_map<VertexType, std::map<VertexType, WeightType>>::const_iterator;
public:
	class VertexIterator
	{
	private:
		IteratorType it;
	public:
		VertexIterator(const IteratorType& _it);

		VertexIterator& operator ++();
		VertexType operator *();
		bool operator !=(const VertexIterator& other) const;
	};
	VertexIterator begin() const;
	VertexIterator end() const;
};


#endif