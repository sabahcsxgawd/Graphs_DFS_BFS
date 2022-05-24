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
 
    // Constructor
    Graph(vector<Edge> const &edges, int n)
    {
        // resize the vector to hold `n` elements of type `vector<int>`
        adjList.resize(n);
 
        // add edges to the directed graph
        for (auto &edge: edges) {
            adjList[edge.src].push_back(edge.dest);
        }
    }
};
 
// Function to perform DFS traversal on the graph on a graph
void DFS(Graph const &graph, int v, vector<bool> &visited)
{
    // mark current node as visited
    visited[v] = true;
 
    // do for every edge (v, u)
    for (int u: graph.adjList[v])
    {
        // `u` is not visited
        if (!visited[u]) {
            DFS(graph, u, visited);
        }
    }
}
 
// Function to check if the graph is strongly connected or not
bool isStronglyConnected(Graph const &graph, int n)
{
    // to keep track of whether a vertex is visited or not
    vector<bool> visited(n);
 
    // choose a random starting point
    int v = 0;
 
    // run a DFS starting at `v`
    DFS(graph, v, visited);
 
    // If DFS traversal doesn't visit all vertices,
    // then the graph is not strongly connected
    if (find(visited.begin(), visited.end(), false) != visited.end()) {
        return false;
    }
 
    // reset visited vector
    fill(visited.begin(), visited.end(), false);
 
    // Reverse the direction of all edges in the directed graph
    vector<Edge> edges;
    for (int i = 0; i < n; i++)
    {
        for (int j: graph.adjList[i]) {
            edges.push_back({j, i});
        }
    }
 
    // Create a graph from reversed edges
    Graph gr(edges, n);
 
    // Again run a DFS starting at `v`
    DFS(gr, v, visited);
 
    // If DFS traversal doesn't visit all vertices,
    // then the graph is not strongly connected
    if (find(visited.begin(), visited.end(), false) != visited.end()) {
        return false;
    }
 
    // if a graph "passes" both DFSs, it is strongly connected
    return true;
}
 
int main()
{
    // vector of graph edges as per the above diagram
    vector<Edge> edges = {
        {0, 4}, {1, 0}, {1, 2}, {2, 1}, {2, 4}, {3, 1}, {3, 2}, {4, 3}
    };
 
    // total number of nodes in the graph
    int n = 5;
 
    // build a graph from the given edges
    Graph graph(edges, n);
 
    // check if the graph is not strongly connected or not
    if (isStronglyConnected(graph, n)) {
        cout << "The graph is strongly connected";
    }
    else {
        cout << "The graph is not strongly connected";
    }
 
    return 0;
}


// Output:

// The graph is strongly connected

// The time complexity of the above solution is O(V + E), 
// where V and E are the total number of vertices and edges in the graph, respectively.
// Please note that O(E) may vary between O(1) and O(V2), depending on how dense the graph is.