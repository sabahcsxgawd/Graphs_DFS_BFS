#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
using namespace std;
 
// A Queue Node
struct Node
{
    int x;          // stores x–coordinate of a matrix cell
    int y;          // stores y–coordinate of a matrix cell
    int distance;   // stores the distance of (x, y) from mine
};
 
// check if specified row and column are valid matrix index
bool isValid(int i, int j, int M, int N) {
    return (i >= 0 && i < M) && (j >= 0 && j < N);
}
 
// check if the current cell is an open area, and its
// distance from the mine is not yet calculated
bool isSafe(int i, int j, vector<vector<char>> const &mat,
        vector<vector<int>> const &result) {
    return mat[i][j] == 'O' && result[i][j] == -1;
}
 
// Replace all O's in a matrix with their shortest distance
// from the nearest mine
vector<vector<int>> updateShortestDistance(vector<vector<char>> const &mat)
{
    // base case
    if (mat.size() == 0) {
        return {};
    }
 
    // `M × N` matrix
    int M = mat.size();
    int N = mat[0].size();
 
    vector<vector<int>> result(M, vector<int>(N));
 
    // initialize an empty queue
    queue<Node> q;
 
    // find all mines location and add them to the queue
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            // if the current cell represents a mine
            if (mat[i][j] == 'M')
            {
                q.push({i, j, 0});
 
                // update mine distance as 0
                result[i][j] = 0;
            }
            // otherwise, initialize the mine distance by -1
            else {
                result[i][j] = -1;
            }
        }
    }
 
    // arrays to get indices of four adjacent cells of a given cell
    int row[] = { 0, -1, 0, 1 };
    int col[] = { -1, 0, 1, 0 };
 
    // do for each node in the queue
    while (!q.empty())
    {
        // process front cell in the queue
        int x = q.front().x;
        int y = q.front().y;
        int distance = q.front().distance;
 
        // dequeue front cell
        q.pop();
 
        // update the four adjacent cells of the front node in the queue
        for (int i = 0; i < 4; i++)
        {
            // enqueue adjacent cell if it is valid, unvisited,
            // and has a path through it
            if (isValid(x + row[i], y + col[i], M, N) &&
                isSafe(x + row[i], y + col[i], mat, result))
            {
                result[x + row[i]][y + col[i]] = distance + 1;
                q.push({x + row[i], y + col[i], distance + 1});
            }
        }
    }
 
    return result;
}
 
// Utility function to print a matrix
void printMatrix(vector<vector<int>> const &mat)
{
    for (int i = 0; i < mat.size(); i++)
    {
        for (int j = 0; j < mat[0].size(); j++) {
            cout << setw(3) << mat[i][j];
        }
        cout << endl;
    }
}
 
int main()
{
    vector<vector<char>> mat =
    {
        {'O', 'M', 'O', 'O', 'X'},
        {'O', 'X', 'X', 'O', 'M'},
        {'O', 'O', 'O', 'O', 'O'},
        {'O', 'X', 'X', 'X', 'O'},
        {'O', 'O', 'M', 'O', 'O'},
        {'O', 'X', 'X', 'M', 'O'}
    };
 
    vector<vector<int>> output = updateShortestDistance(mat);
    printMatrix(output);
 
    return 0;
}


// Output:

// 1   0   1   2  -1
// 2  -1  -1   1   0
// 3   4   3   2   1
// 3  -1  -1  -1   2
// 2   1   0   1   2
// 3  -1  -1   0   1

// The time complexity of the proposed solution is O(M × N) and 
// requires O(M × N) extra space, where M and N are dimensions of the matrix.