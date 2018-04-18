#ifndef SUDOKU
#define SUDOKU

#include <vector>
using namespace std;

class SUDOKU{
public:
    SUDOKU();
    vector<vector<int>> puzzle;
private:
    vector<vector<int>>&& gen_whole_puzzle();
    void filter_puzzle(vector<vector<int>>&& whole_puzzle);
    void regenarate();
};

#endif // SUDOKU

