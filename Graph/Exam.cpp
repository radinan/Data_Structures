// Exam.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <unordered_map>
#include <map>
#include <vector>
#include <queue>
//verteces
//edges
//неориентиран
//нетегловен
//има ли цикъл?

template <class VertexType>
class Graph
{
private:
    std::unordered_map<VertexType, std::vector<VertexType>> verteces;
public:
    void addVertex(const VertexType& v)
    {
        verteces[v];
    }
    void addEdge(const VertexType& v1, const VertexType& v2)
    {
        //if v1 and v2 exist
        verteces[v1].push_back(v2);
        verteces[v2].push_back(v1);
    }

    void DFSHelper(const VertexType& v1, std::vector<VertexType>& visited)
    {
        //std::cout << v1 << " ";
        if (std::find(visited.begin(), visited.end(), v1) == visited.end())
        {
            std::cout << v1 << " ";
            visited.push_back(v1);
        }
        for (auto i : verteces[v1])
        {
            if (std::find(visited.begin(), visited.end(), i) == visited.end())
            {
                std::cout << i << " ";
                visited.push_back(i);
                DFSHelper(i, visited);
            }
        }

    }

    void BFSHelper(const VertexType& v1, std::vector<VertexType>& visited)
    {
        std::queue<VertexType> q;

        q.push(v1);
        visited.push_back(v1);
        std::cout << v1 << " ";
        while (!q.empty())
        {
            VertexType curr = q.front(); 
            q.pop();

            for (auto i : verteces[curr])
            {
                if (std::find(visited.begin(), visited.end(), i) == visited.end()) //if vertex is not visited
                {
                    std::cout << i << " ";
                    visited.push_back(i);
                    q.push(i);

                }
            }
        }
    }

    bool hasCycle(const VertexType& v1, std::vector<VertexType>& visited)
    {
        std::queue<std::pair<VertexType, bool>> q;
        std::unordered_map<VertexType, VertexType> child_parent;
        int lvl = 0;

        q.push(std::make_pair(v1, true));
        visited.push_back(v1);
        q.push(std::make_pair(VertexType(), false));
        while (!q.empty())
        {
            std::pair<VertexType, bool> curr = q.front();
            q.pop();
            if (curr.second == false)
            {
                if (!q.empty())
                {
                    q.push(std::make_pair(VertexType(), false));
                    ++lvl;
                }
            }

            for (auto i : verteces[curr.first])
            {
                if (std::find(visited.begin(), visited.end(), i) == visited.end()) //if vertex is not visited
                {
                    child_parent[i] = curr.first;
                    visited.push_back(i);
                    q.push(std::make_pair(i, true));

                }
                else
                {
                    if (lvl >= 1 && i != child_parent[curr.first])
                        return true;
                }
            }
        }
        return false;
    }

};

int main()
{
    Graph<int> g;
    g.addVertex(1);
    g.addVertex(2);
    g.addVertex(3);
    g.addVertex(0);
    g.addVertex(4);
    g.addVertex(5);
    g.addVertex(6);
    g.addVertex(7);
    g.addVertex(8);
    g.addVertex(9);





    g.addEdge(2, 1);
    g.addEdge(2, 3);
    g.addEdge(1, 3);
    g.addEdge(2, 4);
    g.addEdge(2, 5);
    g.addEdge(4, 6);
    g.addEdge(5, 7);
    g.addEdge(7, 8);
    g.addEdge(8, 9);
    g.addEdge(7, 9);

    std::vector<int> visited;
    g.DFSHelper(2, visited);
    std::cout << std::endl;
    std::vector<int> visited1;
    g.BFSHelper(2, visited1);

    std::cout << std::endl;

    std::vector<int> visited2;
    std::cout << g.hasCycle(2, visited2);
    std::cout << std::endl;
 
}
