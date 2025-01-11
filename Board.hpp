#ifndef Board_HPP
#define Board_HPP
#include <cstdlib>
#include <time.h>
#include <vector>
#include <iostream>
using namespace std;
#include <iomanip>

class Board {
    public:
        Board();
        Board(int m);
        Board(int m, int n);
        ~Board();


        int getNumRows() const;
        int getNumCols() const;
        int getTarget() const;
        int getMax() const;

        void pressUp();
        void pressDown();
        void pressLeft();
        void pressRight();
        void selectRandomCell(int& row, int& col);
        void print() const;
        void start();

        bool noAdjacentSameValue() const;
    private:
        int target;
        int max;
        int numRows;
        int numCols;
        int** panel;
};

#endif