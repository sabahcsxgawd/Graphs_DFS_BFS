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
    // A vector of vectors to represent an adjacency list
    vector<vector<int>> adjList;
 
    // Total number of nodes in the graph
    int n;
 
    // Graph Constructor
    Graph(vector<Edge> const &edges, int n)
    {
        // resize the vector to hold `n` elements of type `vector<int>`
        this->n = n;
        adjList.resize(n);
 
        // add edges to the undirected graph
        for (auto &edge: edges)
        {
            adjList[edge.src].push_back(edge.dest);
            adjList[edge.dest].push_back(edge.src);
        }
    }
};
 
// Perform BFS on the graph starting from vertex `v`
bool isBipartite(Graph const &graph)
{
    // get total number of nodes in the graph
    int n = graph.n;
 
    // start from any node as the graph is connected and undirected
    int v = 0;
 
    // to keep track of whether a vertex is discovered or not
    vector<bool> discovered(n);
 
    // stores the level of each vertex in BFS
    vector<int> level(n);
 
    // mark the source vertex as discovered and set its level to 0
    discovered[v] = true, level[v] = 0;
 
    // create a queue to do BFS and enqueue source vertex in it
    queue<int> q;
    q.push(v);
 
    // loop till queue is empty
    while (!q.empty())
    {
        // dequeue front node
        v = q.front();
        q.pop();
 
        // do for every edge (v, u)
        for (int u: graph.adjList[v])
        {
            // if vertex `u` is explored for the first time
            if (!discovered[u])
            {
                // mark it as discovered
                discovered[u] = true;
 
                // set level one more than the level of the parent node
                level[u] = level[v] + 1;
 
                // enqueue vertex
                q.push(u);
            }
            // if the vertex has already been discovered and the
            // level of vertex `u` and `v` are the same, then the
            // graph contains an odd-cycle and is not bipartite
            else if (level[v] == level[u]) {
                return false;
            }
        }
    }
 
    return true;
}
 
int main()
{
    // vector of graph edges
    vector<Edge> edges = {
        {0, 1}, {1, 2}, {1, 7}, {2, 3}, {3, 5}, {4, 6}, {4, 8}, {7, 8}
        // if we add edge (1, 3), the graph becomes non-bipartite
    };
 
    // total number of nodes in the graph (0 to 8)
    int n = 9;
 
    // build a graph from the given edges
    Graph graph(edges, n);
 
    if (isBipartite(graph)) {
        cout << "Graph is bipartite";
    }
    else {
        cout << "Graph is not bipartite";
    }
 
    return 0;
}


// Output:

// Graph is bipartite

// The time complexity of the above solution is O(V + E), 
// where V and E are the total number of vertices and edges in the graph, respectively. 
// Please note that O(E) may vary between O(1) and O(V2), depending on how dense the graph is.