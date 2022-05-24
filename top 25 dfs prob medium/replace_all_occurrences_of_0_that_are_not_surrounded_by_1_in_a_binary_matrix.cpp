#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;
 
// Below arrays detail all eight possible movements
int row[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
int col[] = { -1, 0, 1, -1, 1, -1, 0, 1 };
 
// check false if `(x, y)` is not a valid location
bool isValid(int x, int y, int M, int N) {
    return (x >= 0 && x < M && y >= 0 && y < N);
}
 
void DFS(vector<vector<int>> &mat, int x, int y)
{
    int M = mat.size();
    int N = mat[0].size();
 
    // replace 0 by 1
    mat[x][y] = 1;
 
    // process all eight adjacent locations of the current cell and
    // recur for each valid location
    for (int k = 0; k < 8; k++)
    {
        int i = x + row[k];
        int j = y + col[k];
 
        // if the adjacent location at position `(i, j)` is
        // valid and has a value 0
        if (isValid(i, j, M, N) && !mat[i][j]) {
            DFS(mat, i, j);
        }
    }
}
 
void replaceZeroes(vector<vector<int>> &mat)
{
    // base case
    if (mat.size() == 0) {
        return;
    }
 
    // `M × N` matrix
    int M = mat.size();
    int N = mat[0].size();
 
    // check every element on the first and last column of the matrix
    for (int i = 0; i < M; i++)
    {
        if (!mat[i][0]) {
            DFS(mat, i, 0);
        }
 
        if (!mat[i][N - 1]) {
            DFS(mat, i, N - 1);
        }
    }
 
    // check every element on the first and last row of the matrix
    for (int j = 0; j < N - 1; j++)
    {
        if (!mat[0][j]) {
            DFS(mat, 0, j);
        }
 
        if (!mat[M - 1][j]) {
            DFS(mat, M - 1, j);
        }
    }
}
 
// Function to print the matrix
void printMatrix(vector<vector<int>> const &mat)
{
    for (auto &row: mat) {
        for (auto &i: row) {
            cout << setw(3) << i;
        }
        cout << endl;
    }
    cout << endl;
}
 
int main()
{
    vector<vector<int>> mat =
    {
        { 1, 1, 1, 1, 0, 0, 1, 1, 0, 1 },
        { 1, 0, 0, 1, 1, 0, 1, 1, 1, 1 },
        { 1, 0, 0, 1, 1, 1, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 0, 0, 1, 1, 0, 1 },
        { 1, 1, 1, 1, 0, 0, 0, 1, 0, 1 },
        { 1, 1, 0, 1, 1, 0, 1, 1, 0, 0 },
        { 1, 1, 0, 1, 1, 1, 1, 1, 1, 1 },
        { 1, 1, 0, 1, 1, 0, 0, 1, 0, 1 },
        { 1, 1, 1, 0, 1, 0, 1, 0, 0, 1 },
        { 1, 1, 1, 0, 1, 1, 1, 1, 1, 1 }
    };
 
    replaceZeroes(mat);
    printMatrix(mat);
 
    return 0;
}


// Output:

// 1  1  1  1  1  1  1  1  1  1
// 1  0  0  1  1  1  1  1  1  1
// 1  0  0  1  1  1  1  1  1  1
// 1  1  1  1  0  0  1  1  1  1
// 1  1  1  1  0  0  0  1  1  1
// 1  1  1  1  1  0  1  1  1  1
// 1  1  1  1  1  1  1  1  1  1
// 1  1  1  1  1  0  0  1  0  1
// 1  1  1  1  1  0  1  0  0  1
// 1  1  1  1  1  1  1  1  1  1

// The time complexity of the proposed solution is O(M × N) for an M × N matrix. 
// The auxiliary space required by the program is O(M × N) for recursion (call stack).