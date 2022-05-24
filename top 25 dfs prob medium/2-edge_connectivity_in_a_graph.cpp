// Given an undirected connected graph, check if the graph is 2–edge connected and return the bridges (if any).

// A connected graph is 2–edge connected if it remains connected whenever any edges are removed. A bridge (or cut arc) is an edge of a graph whose deletion increases its number of connected components, i.e., an edge whose removal disconnects the graph. So if any such bridge exists, the graph is not 2–edge connected.

// Prerequisite:

// Types of edges involved in DFS and relation between them

// Arrival and departure time of vertices in DFS

 
// A simple approach would be to remove each edge from the graph one by one and run Depth–first search (DFS) or Breadth–first search (BFS) starting from any vertex. If the DFS or BFS covers all nodes in the graph, then the removed edge cannot be a bridge. If not, that edge is a bridge. The time complexity of this solution is O(E × (V + E)), where V and E are the total number of vertices and edges in the graph, respectively.

 
// We can solve this problem efficiently in one pass of DFS. When we do a DFS from vertex v in an undirected graph, there could be edges going out of the subtree, i.e., back edges. We can say that the graph is 2–edge connected if and only if for every edge u —> v in the graph, there is at least one back-edge that is going out of a subtree rooted at v to some ancestor of u. When we say subtree rooted at v, we mean all of v's descendants, including the vertex itself.

// In other words, when we backtrack from a vertex v, we need to ensure that there is some back-edge from some descendant of v (including v) to some proper ancestor (parent or above) of v.

// How can we modify DFS so that we can check if there is a back-edge going out of every subtree?

// We can modify DFS such that DFS(v) returns the smallest arrival time to which there is a back edge from the subtree rooted at v. For example, let arrival(v) be the arrival time of vertex v in the DFS. If there is a back edge out of the subtree rooted at v, it is to something visited before v, and therefore with a smaller arrival value. Remember for a back edge u —> v in a graph, arrival[u] > arrival[v].

// Suppose four edges are going out of a subtree rooted at v to vertex a, b, c and d, with arrival time A(a), A(b), A(c) and A(d), respectively. We look at their four arrival times and consider the smallest among them, that will be the value returned by DFS(v), i.e., DFS(v) returns the minimum min of A(a), A(b), A(c), and A(d). But before returning, we have to check that min is less than the A(v). If min is less than the A(v), then that means that at least one back-edge is going out of the subtree rooted at v. If not, we can say that (parent[v], v) is a bridge.

// The algorithm can be implemented as follows in C++, Java, and Python:

#include <iostream>
#include <vector>
#include <set>
using namespace std;
 
typedef pair<int, int> Edge;
 
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
            adjList[edge.first].push_back(edge.second);
            adjList[edge.second].push_back(edge.first);
        }
    }
};
 
// Perform DFS on the graph starting from vertex `v` and find
// all bridges in the process
int DFS(Graph const &graph, int v, vector<bool> visited, vector<int> &arrival,
        int parent, int &time, auto &bridges)
{
    // set the arrival time of vertex `v`
    arrival[v] = ++time;
 
    // mark vertex as visited
    visited[v] = true;
 
    // initialize `t` with the arrival time of vertex `v`
    int t = arrival[v];
 
    // (v, w) forms an edge
    for (int w: graph.adjList[v])
    {
        // if `w` is not visited
        if (!visited[w]) {
            t = min(t, DFS(graph, w, visited, arrival, v, time, bridges));
        }
        // if `w` is visited, and `w` is not a parent of `v`
        else if (w != parent)
        {
            // If vertex `w` is already visited, there is a back edge starting
            // from `v`. Note that as visited[u] is already
            // true, arrival[u] is already defined
            t = min(t, arrival[w]);
        }
    }
 
    // if the value of `t` remains unchanged, i.e., it is equal
    // to the arrival time of vertex `v`, and if `v` is not the root node,
    // then (parent[v] —> v) forms a bridge
    if (t == arrival[v] && parent != -1) {
        bridges.insert({parent, v});
    }
 
    // return the minimum arrival time
    return t;
}
 
set<Edge> findBridges(Graph const &graph, int n)
{
    // to keep track of whether a vertex is visited or not
    vector<bool> visited(n);
 
    // stores arrival time of a node in DFS
    vector<int> arrival(n);
 
    int start = 0, parent = -1, time = 0;
 
    set<Edge> bridges;
 
    // As the given graph is connected, DFS will cover every node
    DFS(graph, start, visited, arrival, parent, time, bridges);
 
    return bridges;
}
 
void printEdges(auto const &edges)
{
    for (auto const &edge: edges) {
        cout << '(' << edge.first << ", " << edge.second << ") ";
    }
}
 
// 2–edge connectivity in a graph
int main()
{
    // vector of graph edges
    vector<Edge> edges = {
        {0, 2}, {1, 2}, {2, 3}, {2, 4}, {3, 4}, {3, 5}
    };
 
    // total number of nodes in the graph (0 to 6)
    int n = 10;
 
    // build a graph from the given edges
    Graph graph(edges, n);
 
    // find and print bridges
    auto bridges = findBridges(graph, n);
 
    if (bridges.size() != 0) {
        cout << "Bridges are "; printEdges(bridges);
    } else {
        cout << "Graph is 2– Connected";
    }
 
    return 0;
}


// Output:

// Bridges are (0, 2) (2, 1) (3, 5)

 
// The time complexity of the above solution is O(V + E), 
// where V and E are the total number of vertices and edges in the graph, respectively.