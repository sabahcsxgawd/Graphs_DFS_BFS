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
 
// Node to store vertex and its parent info in BFS
struct Node {
    int v, parent;
};
 
// Perform BFS on the graph starting from vertex `src` and
// return true if a cycle is found in the graph
bool BFS(Graph const &graph, int src, int n)
{
    // to keep track of whether a vertex is discovered or not
    vector<bool> discovered(n);
 
    // mark the source vertex as discovered
    discovered[src] = true;
 
    // create a queue for doing BFS and
    // enqueue source vertex
    queue<Node> q;
    q.push({src, -1});
 
    // loop till queue is empty
    while (!q.empty())
    {
        // dequeue front node and print it
        Node node = q.front();
        q.pop();
 
        // do for every edge (v, u)
        for (int u: graph.adjList[node.v])
        {
            if (!discovered[u])
            {
                // mark it as discovered
                discovered[u] = true;
 
                // construct the queue node containing info
                // about vertex and enqueue it
                q.push({ u, node.v });
            }
 
            // `u` is discovered, and `u` is not a parent
            else if (u != node.parent)
            {
                // we found a cross-edge, i.e., the cycle is found
                return true;
            }
        }
    }
 
    // no cross-edges were found in the graph
    return false;
}
 
int main()
{
    // initialize edges
    vector<Edge> edges =
    {
        {0, 1}, {0, 2}, {0, 3}, {1, 4}, {1, 5}, {4, 8},
        {4, 9}, {3, 6}, {3, 7}, {6, 10}, {6, 11}, {5, 9}
        // edge {5, 9} introduces a cycle in the graph
    };
 
    // total number of nodes in the graph (0 to 11)
    int n = 12;
 
    // build a graph from the given edges
    Graph graph(edges, n);
 
    // Perform BFS traversal in connected components of a graph
    if (BFS(graph, 0, n)) {
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