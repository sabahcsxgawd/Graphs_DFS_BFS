// When we do a Depth–first search (DFS) from any vertex v in an undirected graph, we may encounter a back-edge that points to one of the ancestors of the current vertex v in the DFS tree. Each “back edge” defines a cycle in an undirected graph. If the back edge is x —> y, then since y is the ancestor of node x, we have a path from y to x. So, we can say that we have a path y ~~ x ~ y that forms a cycle. (Here, ~~ represents one more edge in the path, and ~ represents a direct edge).

// Following is the implementation in C++, Java, and Python based on the above idea:


#include <iostream>
#include <vector>
#include <queue>
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
        // resize the vector to hold `n` elements of type `vector<int>`
        adjList.resize(n);
 
        // add edges to the undirected graph
        for (auto &edge: edges)
        {
            adjList[edge.src].push_back(edge.dest);
            adjList[edge.dest].push_back(edge.src);
        }
    }
};
 
// Perform DFS on the graph and returns true if any back-edge is found in the graph
bool DFS(Graph const &graph, int v, vector<bool> &discovered, int parent)
{
    // mark the current node as discovered
    discovered[v] = true;
 
    // do for every edge (v, w)
    for (int w: graph.adjList[v])
    {
        // if `w` is not discovered
        if (!discovered[w])
        {
            if (DFS(graph, w, discovered, v)) {
                return true;
            }
        }
 
        // if `w` is discovered, and `w` is not a parent
        else if (w != parent)
        {
            // we found a back-edge (cycle)
            return true;
        }
    }
 
    // No back-edges were found in the graph
    return false;
}
 
int main()
{
    // initialize edges
    vector<Edge> edges =
    {
        {0, 1}, {0, 6}, {0, 7}, {1, 2}, {1, 5}, {2, 3},
        {2, 4}, {7, 8}, {7, 11}, {8, 9}, {8, 10}, {10, 11}
        // edge (10, 11) introduces a cycle in the graph
    };
 
    // total number of nodes in the graph (0 to 11)
    int n = 12;
 
    // build a graph from the given edges
    Graph graph(edges, n);
 
    // to keep track of whether a vertex is discovered or not
    vector<bool> discovered(n);
 
    // Perform DFS traversal from the first vertex
    if (DFS(graph, 0, discovered, -1)) {
        cout << "The graph contains a cycle";
    }
    else {
        cout << "The graph doesn't contain any cycle";
    }
 
    return 0;
}


// Output:

// The graph contains a cycle

// The time complexity of the above solutions is O(V + E), 
// where V and E are the total number of vertices and edges in the graph, respectively.