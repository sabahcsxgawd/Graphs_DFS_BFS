// We can use Depth–first search (DFS) to implement topological sort algorithm. The idea is to order the vertices in order of their decreasing departure time of vertices in DFS, and we will get our desired topological sort.

// How does it work?

// We have already discussed the relationship between all four types of edges involved in the DFS in the previous post. Following is the relationship we have seen between the departure time for different types of edges involved in a DFS of the directed graph:

// Tree edge (u, v): departure[u] > departure[v]
// Back edge (u, v): departure[u] < departure[v]
// Forward edge (u, v): departure[u] > departure[v]
// Cross edge (u, v): departure[u] > departure[v]
// As we can see that for a tree edge, forward edge, or cross edge (u, v), departure[u] is more than departure[v]. But only for the back edge, relationship departure[u] < departure[v] is true. So, it is guaranteed that if an edge (u, v) has departure[u] > departure[v], it’s not a back-edge.

 
// We know that in a DAG, no back-edge is present. So if we order the vertices in order of their decreasing departure time, we will get the topological order of the graph (every edge going from left to right).

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
 
// Perform DFS on the graph and set the departure time of all
// vertices of the graph
void DFS(Graph const &graph, int v, vector<bool>
    &discovered, vector<int> &departure, int &time)
{
    // mark the current node as discovered
    discovered[v] = true;
 
    // set the arrival time of vertex `v`
    time++;
 
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
    departure[time] = v;
    time++;
}
 
// Function to perform a topological sort on a given DAG
void doTopologicalSort(Graph const &graph, int n)
{
    // departure[] stores the vertex number using departure time as an index
    vector<int> departure(2*n, -1);
 
    /* If we had done it the other way around, i.e., fill the array
       with departure time using vertex number as an index, we would
       need to sort it later */
 
    // to keep track of whether a vertex is discovered or not
    vector<bool> discovered(n);
    int time = 0;
 
    // perform DFS on all undiscovered vertices
    for (int i = 0; i < n; i++)
    {
        if (!discovered[i]) {
            DFS(graph, i, discovered, departure, time);
        }
    }
 
    // Print the vertices in order of their decreasing
    // departure time in DFS, i.e., in topological order
    for (int i = 2*n - 1; i >= 0; i--)
    {
        if (departure[i] != -1) {
            cout << departure[i] << " ";
        }
    }
}
 
int main()
{
    // vector of graph edges as per the above diagram
    vector<Edge> edges =
    {
        {0, 6}, {1, 2}, {1, 4}, {1, 6}, {3, 0}, {3, 4}, {5, 1}, {7, 0}, {7, 1}
    };
 
    // total number of nodes in the graph (labelled from 0 to 7)
    int n = 8;
 
    // build a graph from the given edges
    Graph graph(edges, n);
 
    // perform topological sort
    doTopologicalSort(graph, n);
 
    return 0;
}


// Output:

// 7 5 3 1 4 2 0 6

// The time complexity of the above implementation is O(V + E), 
// where V and E are the total number of vertices and edges in the graph, respectively.