#include <iostream>
#include <climits>
#include <queue>
#include <cstring>
using namespace std;
 
// A queue node used in BFS
struct Node {
    // (x, y) represents a position inside the field
    // `dist` represents its minimum distance from the source
    int x, y, dist;
};
 
// Below arrays detail all four possible movements from a cell,
// i.e., (top, right, bottom, left)
int row[] = { -1, 0, 0, 1 };
int col[] = { 0, -1, 1, 0 };
 
// Function to check if it is safe to go to position (x, y)
// from the current position. The function returns false if (x, y)
// is unsafe or already visited.
bool isSafe(vector<vector<int>> const &field, vector<vector<bool>> const &visited,
                int x, int y) {
    return field[x][y] != 0 && !visited[x][y];
}
 
// Check if (x, y) is valid field coordinates.
// Note that we cannot go out of the field.
bool isValid(int x, int y, int M, int N) {
    return (x < M && y < N) && (x >= 0 && y >= 0);
}
 
// Find the minimum number of steps required to reach the last column
// from the first column using BFS
int BFS(vector<vector<int>> const &field)
{
    // `M × N` matrix
    int M = field.size();
    int N = field[0].size();
 
    // stores if a cell is visited or not
    vector<vector<bool>> visited;
    visited.resize(M, vector<bool>(N));
 
    // create an empty queue
    queue<Node> q;
 
    // process every cell of the first column
    for (int r = 0; r < M; r++)
    {
        // if the cell is safe, mark it as visited and
        // enqueue it by assigning it distance as 0
        if (field[r][0] == 1)
        {
            q.push({r, 0, 0});
            visited[r][0] = true;
        }
    }
 
    // loop till queue is empty
    while (!q.empty())
    {
        // dequeue front node and process it
        int i = q.front().x;
        int j = q.front().y;
        int dist = q.front().dist;
        q.pop();
 
        // if the destination is found, return minimum distance
        if (j == N - 1) {
            return dist;
        }
 
        // check for all four possible movements from the current cell
        // and enqueue each valid movement
        for (int k = 0; k < 4; k++)
        {
            // skip if the location is invalid or visited, or unsafe
            if (isValid(i + row[k], j + col[k], M, N) &&
                isSafe(field, visited, i + row[k], j + col[k]))
            {
                // mark it as visited and enqueue it with +1 distance
                visited[i + row[k]][j + col[k]] = true;
                q.push({i + row[k], j + col[k], dist + 1});
            }
        }
    }
 
    return INT_MAX;
}
 
// Find the shortest path from the first column to the last column in a given field
int findShortestDistance(vector<vector<int>> &mat)
{
    // base case
    if (mat.size() == 0) {
        return 0;
    }
 
    // `M × N` matrix
    int M = mat.size();
    int N = mat[0].size();
 
    // `r[]` and `c[]` detail all eight possible movements from a cell
    // (top, right, bottom, left, and four diagonal moves)
    int r[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
    int c[] = { -1, 0, 1, -1, 1, -1, 0, 1 };
 
    // mark adjacent cells of sensors as unsafe
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            for (int k = 0; k < 8; k++) {
                if (!mat[i][j] && isValid(i + r[k], j + c[k], M, N)
                        && mat[i + r[k]][j + c[k]]) {
                    mat[i + r[k]][j + c[k]] = INT_MAX;
                }
            }
        }
    }
 
    // update the mat
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (mat[i][j] == INT_MAX) {
                mat[i][j] = 0;
            }
        }
    }
 
    // call BFS and return the shortest distance found by it
    return BFS(mat);
}
 
int main()
{
    vector<vector<int>> field =
    {
        { 0, 1, 1, 1, 0, 1, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 0, 1 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 1, 0, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 1, 0, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
        { 1, 1, 1, 1, 1, 0, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
    };
 
    int dist = findShortestDistance(field);
 
    if (dist != INT_MAX) {
        cout << "The shortest safe path has a length of " << dist;
    }
    else {
        cout << "No route is safe to reach destination";
    }
 
    return 0;
}


// Output:

// The shortest safe path has a length of 11

// The time complexity of the proposed solution is O(M × N) and 
// requires O(M × N) extra space, where M and N are dimensions of the matrix.