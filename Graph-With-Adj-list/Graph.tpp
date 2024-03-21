#include "Graph.h"


#include <iostream>
#include <queue>
#include <stack>
#include <algorithm>


template <typename T>
Graph<T>::Graph() : adjacency_list{}, size_{} 
{}


template <typename T>
void Graph<T>::traverse()
{
	for (const auto& v : adjacency_list) {
		std::cout << v.first << ": ";
		for (const auto& n : v.second) {
			std::cout << n << " ";
		}
		std::cout << std::endl;
	} 
}


template <typename T>
void Graph<T>::Transpose()
{
	std::unordered_map<T, std::list<T>> newList;

	for (const auto& v : adjacency_list) {
		T curr = v.first;
		for (const auto& n : v.second) {
			newList[n].push_back(curr);
		}
	}
	adjacency_list = newList;
}


template <typename T>
void Graph<T>::AddEdge(const T& v, const T& e)
{
	if (adjacency_list.find(v) == adjacency_list.end()) {
		++size_;
	}
	if (adjacency_list.find(e) == adjacency_list.end()) {
                ++size_;
        }
	
	adjacency_list[v].push_back(e);
        adjacency_list[e].push_back(v);
}


template <typename T>
void Graph<T>::AddVertex(const T& v)
{
        adjacency_list[v];
	++size_;
}


template <typename T>
void Graph<T>::BFS(const T& v)
{
	 std::queue<T> q;
	 std::vector<bool> visited(size_, false);

	 q.push(v);
	 visited[v] = true;
	 while (!q.empty()) {
	 	T curr = q.front();
		q.pop();

		std::cout << curr << " ";

		for (const auto& n : adjacency_list[curr]) {
			if (!visited[n]) {
				q.push(n);
				visited[n] = true;
			}
		}
	 } 
}


template <typename T>
void Graph<T>::BFSExtra()
{
	std::vector<bool> visited(size_, false);

	for (const auto& vertex : adjacency_list) {
		T currVertex = vertex.first;

	
		if (!visited[currVertex]) {
			std::queue<T> q;
	 		q.push(currVertex);
         		visited[currVertex] = true;

         		while (!q.empty()) {
                		T curr = q.front();
                		q.pop();

             	   		std::cout << curr << " ";

                		for (const auto& n : adjacency_list[curr]) {
                        		if (!visited[n]) {
                                		q.push(n);
                                		visited[n] = true;
                        		}
                		}
         		}
		}
	}
}



template <typename T>
void Graph<T>::DFS(const T& v)
{
	std::stack<T> s;
	std::vector<bool> visited(size_, false);

	s.push(v);
	visited[v] = true;
 
	while (!s.empty()) {
		T curr = s.top();
		s.pop();

		std::cout << curr << " ";

		for (const auto& n : adjacency_list[curr]) {
			if (!visited[n]) {
				s.push(n);
				visited[n] = true;
			}
		}
	}
	
}


template <typename T>
void Graph<T>::DFSRec(const T& v)
{
	std::vector<bool> visited(size_, false);
	_HelperDFS(v, visited);
}



template <typename T>
void Graph<T>::_HelperDFS(const T& v, std::vector<bool>& visited)
{
	visited[v] = true;
	std::cout << v << " ";

	for (const auto& n : adjacency_list[v]) {
		if (!visited[n]) {
			_HelperDFS(n, visited);
		}
	}
}



template <typename T>
void Graph<T>::DFSExtra()
{
       
        std::vector<bool> visited(size_, false);
	std::stack<T> s;


	for (const auto& v : adjacency_list) {
		T currVertex = v.first;

		if (!visited[currVertex]) {
        		s.push(currVertex);
        		visited[currVertex] = true;

        		while (!s.empty()) {
                		T curr = s.top();
                		s.pop();

                		std::cout << curr << " ";
                		for (const auto& n : adjacency_list[curr]) {
                        		if (!visited[n]) {
                                		s.push(n);
                                		visited[n] = true;
                        		}
                		}
        		}
		}
	}
}



template <typename T>
std::list<T> Graph<T>::UndirectedShortestPath(const T& v, const T& u)
{
	std::unordered_map<T, T> parent;
        std::queue<T> q;
        q.push(v);

        
        while (!q.empty()) {
            T curr = q.front();
            q.pop();

            for (const auto& n : adjacency_list[curr]) {
                if (parent.find(n) == parent.end()) {
                    parent[n] = curr;
                    q.push(n);

                    if (n == u) {
                        std::list<T> path;
                        for (T at = u; at != v; at = parent[at]) {
                            path.push_front(at);
                        }
                        path.push_front(v);
                        return path;
                    }
                }
            }
        }

        return {};
}


template <typename T>
std::vector<std::list<T>> Graph<T>::AllUndirectedPaths(const T& v, const T& u)
{
        std::vector<bool> visited(size_, false);
	std::vector<std::list<T>> result;
	std::list<T> path;
	_Helper(v, u, visited, result, path);

	return result;
}


template <typename T>
void Graph<T>::_Helper(const T& v, const T& u
		, std::vector<bool>& visited, std::vector<std::list<T>>& result, std::list<T>& path)
{
	path.push_back(v);
        visited[v] = true;
	
	if (v == u) {
		result.push_back(path);
	} else {
		for (const auto& n : adjacency_list[v]) {
			if (!visited[n]) {
				visited[n] = true;
                        	_Helper(n, u, visited, result, path);
                	}
		}
	}
	path.pop_back();
	visited[v] = false;
}

/*
int main()
{
	Graph<int> g;
	g.AddEdge(10, 11);
	g.AddEdge(10, 12);
	g.AddEdge(10, 13);
	g.AddEdge(11, 15);
	g.AddEdge(11, 14);
        g.AddEdge(12, 15);
        g.AddEdge(13, 16);
        g.AddEdge(14, 17);
        g.AddEdge(15, 16);
        g.AddEdge(15, 17);
        g.AddEdge(16, 17);
	g.AddVertex(8);
	g.traverse();

	std::vector<std::list<int>> paths = g.AllUndirectedPaths(10, 16);

	for (const auto& shortest : paths) {
		for (const auto& t : shortest) {
			std::cout << t << " ";
		}
		std::cout << std::endl;
	}	
}
*/
