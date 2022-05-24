#include <iostream>
#include <vector>
#include <cstring>
#include <iomanip>
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
        adjList.resize(n);
 
        // add edges to the directed graph
        for (Edge edge: edges)
        {
            int src = edge.src;
            int dest = edge.dest;
 
            adjList[src].push_back(dest);
        }
    }
};
 
// `C` is a connectivity matrix and stores transitive closure of a graph
// `root` is the topmost node in DFS tree (it is the starting vertex of DFS)
// `descendant` is current vertex to be explored in DFS.
// Invariant: A path already exists in the graph from `root` to `descendant`
void DFS(Graph const &graph, vector<vector<bool>> &C, int root, int descendant)
{
    for (int child: graph.adjList[descendant])
    {
        // if `child` is an adjacent vertex of descendant, we have
        // found a path from root->child
        if (!C[root][child])
        {
            C[root][child] = true;
            DFS(graph, C, root, child);
        }
    }
}
 
int main()
{
    // an array of graph edges as per the above diagram
    vector<Edge> edges = {
        {0, 2}, {1, 0}, {3, 1}
    };
 
    // total number of nodes in the graph (labelled from 0 to 3)
    int n = 4;
 
    // build a graph from the given edges
    Graph graph(edges, n);
 
    // `C` is a connectivity matrix and stores the transitive closure
    // of the graph. The value of `C[i][j]` is 1 only if a directed
    // path exists from vertex `i` to vertex `j`.
    vector<vector<bool>> C(n, vector<bool>(n, false));
 
    // consider each vertex and start DFS from it
    for (int v = 0; v < n; v++)
    {
        C[v][v] = true;
        DFS(graph, C, v, v);
 
        // print path info for vertex `v`
        for (int u = 0; u < n; u++) {
            cout << left << setw(4) << C[v][u];
        }
        cout << endl;
    }
 
    return 0;
}


// Output:

// 1   0   1   0
// 1   1   1   0
// 0   0   1   0
// 1   1   1   1

// Transitive closure is used to answer reachability queries (can we get to x from y?) efficiently in constant time after preprocessing of constructing the transitive closure.