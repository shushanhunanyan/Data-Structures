#include <list>
#include <unordered_map>
#include <cstddef>
#include <vector>

template <typename T>
class Graph
{
public:
	Graph();
 /* 	Graph(const Graph&);
  	Graph(Graph&&);
  	Graph& operator=(const Graph&);
  	Graph& operator=(Graph&&);
  	~Graph();
*/
public:
	void AddVertex(const T&);
	void AddEdge(const T&, const T&);
	void BFS(const T&);
	void BFSExtra();
	void BFSRec(const T&);
	void DFS(const T&);
	void DFSExtra();
	void DFSRec(const T&);
	void traverse();
	void Transpose();
	std::list<T> UndirectedShortestPath(const T&, const T&);
	std::vector<std::list<T>> AllUndirectedPaths(const T& v, const T& u);

private:
	void _HelperDFS(const T&, std::vector<bool>&);
	std::list<T> _HelperShortestPath(std::vector<int>&, const T&, const T&);
	void _Helper(const T&, const T&, std::vector<bool>&, std::vector<std::list<T>>&, std::list<T>&);
	
private:
	std::unordered_map<T, std::list<T>> adjacency_list;
	std::size_t size_;
};

#include "Graph.tpp"
