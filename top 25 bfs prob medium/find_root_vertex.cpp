// we can use topological sorting; need to be clever

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
 
// Data structure to store a graph edge
struct Edge {
    int src, dest;
};
 
// A class to represent a graph object
class Graph
{
public:
 
    // a vector of vectors to represent an adjacency list
    vector<vector<int>> adjList;
 
    // Graph Constructor
    Graph(vector<Edge> const &edges, int n)
    {
        // resize the vector to hold `n` elements
        adjList.resize(n);
 
        // add edges to the directed graph
        for (auto &edge: edges) {
            adjList[edge.src].push_back(edge.dest);
        }
    }
};
 
// Utility function to perform DFS traversal on the graph on a graph
void DFS(Graph const &graph, int u, vector<bool> &visited)
{
    // mark the current node as visited
    visited[u] = true;
 
    // do for every edge (u, v)
    for (int v: graph.adjList[u])
    {
        // if `v` is not visited
        if (!visited[v]) {
            DFS(graph, v, visited);
        }
    }
}
 
// Function to find the root vertex of a graph
int findRootVertex(Graph const &graph, int n)
{
    // to keep track of all previously visited vertices in DFS
    vector<bool> visited(n);
 
    // find the last starting vertex `v` in DFS
    int v = 0;
    for (int i = 0; i < n; i++)
    {
        if (!visited[i])
        {
            DFS(graph, i, visited);
            v = i;
        }
    }
 
    // reset the visited vertices
    fill(visited.begin(), visited.end(), false);
 
    // perform DFS on the graph from the last starting vertex `v`
    DFS(graph, v, visited);
 
    // return -1 if all vertices are not reachable from vertex `v`
    for (int i = 0; i < n; i++)
    {
        if (!visited[i]) {
            return -1;
        }
    }
 
    // we reach here only if `v` is a root vertex
    return v;
}
 
int main()
{
    // vector of graph edges as per the above diagram
    vector<Edge> edges = {
        {0, 1}, {1, 2}, {2, 3}, {3, 0}, {4, 3}, {4, 5}, {5, 0}
    };
 
    // total number of nodes in the graph (0 to 5)
    int n = 6;
 
    // build a directed graph from the given edges
    Graph graph(edges, n);
 
    // find the root vertex in the graph
    int root = findRootVertex(graph, n);
 
    if (root != -1) {
        cout << "The root vertex is " << root << endl;
    }
    else {
        cout << "The root vertex does not exist" << endl;
    }
 
    return 0;
}

// Output:

// The root vertex is 4