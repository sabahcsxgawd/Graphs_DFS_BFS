// Recommended Read:

// Types of edges involved in DFS and relation between them

// Arrival and departure time of vertices in DFS

 
// We can use Depth–first search (DFS) to solve this problem. The idea is to find if any back-edge is present in the graph or not. A digraph is a DAG if there is no back-edge present in the graph. Recall that a back-edge is an edge from a vertex to one of its ancestors in the DFS tree.

 
// Fact: For an edge u —> v in a directed graph, an edge is a back edge if departure[u] < departure[v].

// Proof: We have already discussed the relationship between all four types of edges involved in the DFS in the previous post. Following are the relationships we have seen between the departure time for different types of edges involved in a DFS of a directed graph:

// Tree edge (u, v): departure[u] > departure[v]
// Back edge (u, v): departure[u] < departure[v]
// Forward edge (u, v): departure[u] > departure[v]
// Cross edge (u, v): departure[u] > departure[v]
// Note that for tree edge, forward edge and cross edge, departure[u] > departure[v]. But only for the back edge, the relationship departure[u] < departure[v] holds true. So, it is guaranteed that an edge (u, v) is a back-edge, not some other edge if departure[u] < departure[v].

#include <iostream>
#include <vector>
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
 
        // add edges to the directed graph
        for (auto &edge: edges) {
            adjList[edge.src].push_back(edge.dest);
        }
    }
};
 
// Perform DFS on the graph and set the departure time of all vertices of the graph
int DFS(Graph const &graph, int v, vector<bool>
    &discovered, vector<int> &departure, int &time)
{
    // mark the current node as discovered
    discovered[v] = true;
 
    // do for every edge (v, u)
    for (int u: graph.adjList[v])
    {
        // if `u` is not yet discovered
        if (!discovered[u]) {
            DFS(graph, u, discovered, departure, time);
        }
    }
 
    // ready to backtrack
    // set departure time of vertex `v`
    departure[v] = time++;
}
 
// Returns true if given directed graph is DAG
bool isDAG(Graph const &graph, int n)
{
    // keep track of whether a vertex is discovered or not
    vector<bool> discovered(n);
 
    // keep track of the departure time of a vertex in DFS
    vector<int> departure(n);
 
    int time = 0;
 
    // Perform DFS traversal from all undiscovered vertices
    // to visit all connected components of a graph
    for (int i = 0; i < n; i++)
    {
        if (!discovered[i]) {
            DFS(graph, i, discovered, departure, time);
        }
    }
 
    // check if the given directed graph is DAG or not
    for (int u = 0; u < n; u++)
    {
        // check if (u, v) forms a back-edge.
        for (int v: graph.adjList[u])
        {
            // If the departure time of vertex `v` is greater than equal
            // to the departure time of `u`, they form a back edge.
 
            // Note that departure[u] will be equal to
            // departure[v] only if `u = v`, i.e., vertex
            // contain an edge to itself
            if (departure[u] <= departure[v]) {
                return false;
            }
        }
    }
 
    // no back edges
    return true;
}
 
int main()
{
    // vector of graph edges as per the above diagram
    vector<Edge> edges = {
        {0, 1}, {0, 3}, {1, 2}, {1, 3}, {3, 2}, {3, 4}, {3, 0}, {5, 6}, {6, 3}
    };
 
    // total number of nodes in the graph (labelled from 0 to 6)
    int n = 7;
 
    // build a graph from the given edges
    Graph graph(edges, n);
 
    // check if the given directed graph is DAG or not
    if (isDAG(graph, n)) {
        cout << "The graph is a DAG";
    }
    else {
        cout << "The graph is not a DAG";
    }
 
    return 0;
}


// Output:

// The graph is not a DAG

// The time complexity of the above solutions is O(V + E), 
// where V and E are the total number of vertices and edges in the graph, respectively.