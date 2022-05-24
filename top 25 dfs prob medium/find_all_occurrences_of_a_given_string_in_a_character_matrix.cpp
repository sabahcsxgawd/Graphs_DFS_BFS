#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
 
template <typename T>
void printVectorOfPairs(vector<pair<T,T>> const &input)
{
    cout << "[";
    int n = input.size();
    for (int i = 0; i < n; i++) {
        cout << '(' << input[i].first << ", " << input[i].second << ')';
        if (i < n - 1) {
            cout << ", ";
        }
    }
    cout << "]\n";
}
 
// Function to check if it is possible to go to position next
// from the current position. The function returns false if next is
// not in a valid position, or it is already visited
bool isValid(pair<int,int> const &next, vector<pair<int,int>> const &path,
    vector<vector<char>> const &mat)
{
    return (next.first >= 0 && next.first < mat.size()) &&
            (next.second >= 0 && next.second < mat[0].size()) &&
            find(path.begin(), path.end(), next) == path.end();
}
 
// Notice that the path vector is not passed by the reference (Why?).
// Use backtracking if the vector is passed by reference
void DFS(vector<vector<char>> const &mat, string word, pair<int,int> const &next,
        vector<pair<int,int>> path, int index)
{
    int i = next.first;
    int j = next.second;
 
    // return if characters don't match
    if (mat[i][j] != word[index]) {
        return;
    }
 
    // include the current cell in the path
    path.push_back({i, j});
 
    // if all words are matched, print the result and return
    if (index == word.size() - 1)    {
        printVectorOfPairs(path);
        return;
    }
 
    // Below arrays detail all eight possible movements from a cell
    // (top, right, bottom, left, and four diagonal moves)
    int row[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
    int col[] = { -1, 0, 1, -1, 1, -1, 0, 1 };
 
    // check all eight possible movements from the current cell
    // and recur for each valid movement
    for (int k = 0; k < 8; k++)
    {
        // calculate the next position
        pair<int,int> next = {i + row[k], j + col[k]};
 
        // check if it is possible to go to the next position
        // from the current position
        if (isValid(next, path, mat)) {
            DFS(mat, word, next, path, index + 1);
        }
    }
}
 
void findAllOccurences(vector<vector<char>> const &mat, string word)
{
    for (int i = 0; i < mat.size(); i++)
    {
        for (int j = 0; j < mat[0].size(); j++) {
            DFS(mat, word, make_pair(i, j), {}, 0);
        }
    }
}
 
int main()
{
    vector<vector<char>> mat =
    {
        { 'D', 'E', 'M', 'X', 'B' },
        { 'A', 'O', 'E', 'P', 'E' },
        { 'D', 'D', 'C', 'O', 'D' },
        { 'E', 'B', 'E', 'D', 'S' },
        { 'C', 'P', 'Y', 'E', 'N' }
    };
 
    string word = "CODE";
 
    findAllOccurences(mat, word);
 
    return 0;
}


// Output:

// [(2, 2), (1, 1), (0, 0), (0, 1)]
// [(2, 2), (1, 1), (2, 0), (3, 0)]
// [(2, 2), (1, 1), (2, 1), (1, 2)]
// [(2, 2), (1, 1), (2, 1), (3, 0)]
// [(2, 2), (1, 1), (2, 1), (3, 2)]
// [(2, 2), (2, 3), (2, 4), (1, 4)]
// [(2, 2), (2, 3), (3, 3), (3, 2)]
// [(2, 2), (2, 3), (3, 3), (4, 3)]

// The time complexity of the proposed solution is exponential
//  and requires additional space for the recursion (call stack).