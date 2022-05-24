#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <string>
using namespace std;
 
// Below arrays detail all eight possible movements from a cell
// (top, right, bottom, left, and four diagonal moves)
int row[] = { -1, -1, -1, 0, 1, 0, 1, 1 };
int col[] = { -1, 1, 0, -1, -1, 1, 0, 1 };
 
// Function to check if it is safe to go to cell (x, y) from the current cell.
// The function returns false if (x, y) is not valid matrix coordinates
// or cell (x, y) is already processed.
bool isSafe(int x, int y, auto &processed) {
    return (x >= 0 && x < processed.size()) && (y >= 0 && y < processed[0].size()) &&
        !processed[x][y];
}
 
// A recursive function to generate all possible words in a boggle
void searchBoggle(auto const &board, auto const &words, auto &result, auto &processed,
                int i, int j, string path)
{
    // mark the current node as processed
    processed[i][j] = true;
 
    // update the path with the current character and insert it into the set
    path += board[i][j];
 
    // check whether the path is present in the input set
    if (words.find(path) != words.end()) {
        result.insert(path);
    }
 
    // check for all eight possible movements from the current cell
    for (int k = 0; k < 8; k++)
    {
        // skip if a cell is invalid, or it is already processed
        if (isSafe(i + row[k], j + col[k], processed)) {
            searchBoggle(board, words, result, processed, i + row[k], j + col[k], path);
        }
    }
 
    // backtrack: mark the current node as unprocessed
    processed[i][j] = false;
}
 
unordered_set<string> searchBoggle(auto const &board, auto const &words)
{
    // construct a set to store valid words constructed from the boggle
    unordered_set<string> result;
 
    // base case
    if (board.size() == 0) {
        return result;
    }
 
    // `M × N` board
    int M = board.size();
    int N = board[0].size();
 
    // construct a boolean matrix to store whether a cell is processed or not
     vector<vector<bool>> processed(M, vector<bool>(N));
 
    // generate all possible words in a boggle
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++) {
            // consider each character as a starting point and run DFS
            searchBoggle(board, words, result, processed, i, j, "");
        }
    }
 
    return result;
}
 
template <typename T>
void printSet(unordered_set<T> const &input)
{
    cout << "{";
    int n = input.size();
    for (auto const &i: input) {
        cout << i;
        if (--n) {
            cout << ", ";
        }
    }
    cout << "}";
}
 
int main()
{
    vector<vector<char>> board = {
                    {'M', 'S', 'E', 'F'},
                    {'R', 'A', 'T', 'D'},
                    {'L', 'O', 'N', 'E'}
                };
 
    unordered_set<string> words = { "START", "NOTE", "SAND", "STONED" };
 
    unordered_set<string> output = searchBoggle(board, words);
    printSet(output);
 
    return 0;
}


// Output:

// {NOTE, SAND, STONED}

// The time complexity of the proposed solution is exponential. 
// We can improve the time complexity by using a Trie data structure. 
// The idea is to build a Trie out of the given words and then perform preorder traversal (DFS) on it