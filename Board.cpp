
#include "Board.hpp"

struct Location {
	int row;
	int col;
};


Board::Board() {
	srand(1);
	max = 0;
	target = 2048;
	numRows = 3;
    numCols = 3;
	panel = new int*[numRows];
	for (int i = 0; i < numRows;i++) {
		panel[i] = new int[numRows];
	}
	for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            panel[i][j] = 0;
        }
    }
}

Board::Board(int m) {
	srand(1);
	if (m >=1) {
		numRows = m;
		numCols = m;
	} 
	else {
	    numRows = 3;
	    numCols = 3;
	}
	max = 0;
	target = 2048;
	panel = new int*[numRows];
	for (int i = 0; i < numRows;i++) {
		panel[i] = new int[numRows];
	}
	for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            panel[i][j] = 0;
        }
    }
}

Board::Board(int m , int n) {
		srand(1);
	if (m >=1 && n >=1) {
		numRows = m;
		numCols = n;
	}
	else {
	    numRows = 3;
	    numCols = 3;
	}
	max = 0;
	target = 1024;
	panel = new int*[numRows];
	for (int i = 0; i < numRows;i++) {
		panel[i] = new int[numRows];
	}
	for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            panel[i][j] = 0;
        }
    }
}

Board::~Board() {
	for (int i = 0; i < numRows; i++) {
		delete[] panel[i];
		panel[i] = nullptr;
	}
	delete[] panel;
	panel = nullptr;
	
}



int Board::getNumRows() const {
	return numRows;
}

int Board::getNumCols() const {
	return numCols;
}

int Board::getTarget() const {
	return target;
}

int Board::getMax() const {
	return max;
}





void Board::selectRandomCell(int& row, int& col)
{
    std::vector<Location> zeros;
    Location cell;

    for (int i = 0; i < numRows; ++i)
    {
        for (int j = 0; j < numCols; ++j)
        {
            if (panel[i][j] == 0)
            {
                cell.row = i;
                cell.col = j;
                zeros.push_back(cell);
            }
        }
    }

    if (zeros.size() > 0)
    {
        int index = rand() % zeros.size();
        row = zeros[index].row;
        col = zeros[index].col;
        panel[row][col] = 1;
        print();
    }

    if (zeros.size() <= 1)
    {
        if (noAdjacentSameValue())
        {
            if (max < target)
            {
                std::cout << "Game over. Try again." << std::endl;
            }
            else
            {
                std::cout << "Congratulations!" << std::endl;
            }
            exit(0);
        }
        else
        {
            return;
        }
    }
}


bool Board::noAdjacentSameValue() const {
	for (int i=0; i<numRows;i++) {
		for(int j=0;j<numCols-1;j++){
			if (panel[i][j] == panel[i][j+1]) {
				return false;
			}

		}
	}
	for (int j = 0; j <numCols;j++) {
		for (int i = 0; i < numRows - 1; i++) {
			if (panel[i][j] == panel[i+1][j]) {
				return false;
			}
		}
	}
	return max < target;
}



void Board::print() const {
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            cout << "+----";
        }
        cout << "+" << endl;

        for (int x = 0; x < numCols; x++) {
            if (panel[i][x] == 0) {
                cout << "|" << setw(4) << " ";
            } else {
                cout << "|" << setw(4) << panel[i][x]; 
            }
        }
        cout << "|" << endl;
    }

    for (int j = 0; j < numCols; j++) {
        cout << "+----";
    }
    cout << "+" << endl;
}

void Board::pressUp() {
    for (int col = 0; col < numCols; col++) {
        vector<int> nonZeros;

        for (int row = 0; row < numRows; row++) {
            if (panel[row][col] != 0) {
                nonZeros.push_back(panel[row][col]);
            }
        }


        int curr = 0;
        int row = 0;

        while (curr < nonZeros.size()) {
            if (curr + 1 < nonZeros.size() && nonZeros[curr] == nonZeros[curr + 1]) {

                nonZeros[curr] += nonZeros[curr + 1];
                nonZeros[curr + 1] = 0;

                if (nonZeros[curr] > max) {
                    max = nonZeros[curr];
                }


                panel[row][col] = nonZeros[curr];
                curr += 2;
            } else {

                panel[row][col] = nonZeros[curr];


                curr += 1;
            }

            row++;
        }


        for (int i = row; i < numRows; i++) {
            panel[i][col] = 0;
        }
    }

    int g, h;
    selectRandomCell(g, h);
}

void Board::pressDown() {
    for (int col = 0; col < numCols; col++) {
        vector<int> nonZeros;

        for (int row = numRows - 1 ; row >= 0; row--) {  
            if (panel[row][col] != 0) {
                nonZeros.push_back(panel[row][col]);
            }
        }

        int curr = 0;
        int row = numRows-1;
        while (curr < nonZeros.size()) {
            if (curr + 1 < nonZeros.size() && nonZeros[curr] == nonZeros[curr + 1]) {
                nonZeros[curr] += nonZeros[curr + 1];
                nonZeros[curr + 1] = 0;

                if (nonZeros[curr] > max) {
                    max = nonZeros[curr];
                }

                panel[row][col] = nonZeros[curr];

                curr += 2;
            } else {
                panel[row][col] = nonZeros[curr];
                curr += 1;
            }

            row--;
        }

        for (int i = row; i >= 0; i--) {  
            panel[i][col] = 0;
        }
    }

    int g, h;
    selectRandomCell(g, h);
}

void Board::pressLeft() {
    for (int row = 0; row < numRows; row++) {
        vector<int> nonZeros;

        for (int col = 0; col < numCols; col++) {
            if (panel[row][col] != 0) {
                nonZeros.push_back(panel[row][col]);
            }
        }


        int curr = 0;
        int col = 0;

        while (curr < nonZeros.size()) {
            if (curr + 1 < nonZeros.size() && nonZeros[curr] == nonZeros[curr + 1]) {

                nonZeros[curr] += nonZeros[curr + 1];
                nonZeros[curr + 1] = 0;

                if (nonZeros[curr] > max) {
                    max = nonZeros[curr];
                }


                panel[row][col] = nonZeros[curr];


                curr += 2;
            } else {

                panel[row][col] = nonZeros[curr];


                curr += 1;
            }

            col++;
        }


        for (int i = col; i < numCols; i++) {
            panel[row][i] = 0;
        }
    }

    int g, h;
    selectRandomCell(g, h);
}

void Board::pressRight() {
    for (int row = 0; row < numRows; row++) {
        vector<int> nonZeros;

        for (int col = numCols-1 ; col >= 0; col--) {
            if (panel[row][col] != 0) {
                nonZeros.push_back(panel[row][col]);
            }
        }


        int curr = 0;
        int col = numCols-1;

        while (curr < nonZeros.size()) {
            if (curr + 1 < nonZeros.size() && nonZeros[curr] == nonZeros[curr + 1]) {

                nonZeros[curr] += nonZeros[curr + 1];
                nonZeros[curr + 1] = 0;

                if (nonZeros[curr] > max) {
                    max = nonZeros[curr];
                }


                panel[row][col] = nonZeros[curr];


                curr += 2;
            } else {

                panel[row][col] = nonZeros[curr];


                curr += 1;
            }

            col--;
        }


        for (int i = col; i >= 0; i--) {
            panel[row][i] = 0;
        }
    }

    int g, h;
    selectRandomCell(g, h);
}




void Board::start() {
    int round = 1;
    int g, h;
    selectRandomCell(g, h);
    selectRandomCell(g, h);

    char ch;
    
    while (true) {

        if (max >= target) {
            cout << "Congratulation!" << endl;
            break;
        }
	ch = getchar(); 
        if (ch == 'S') {
            break;
        }

        if (ch == '\033') {
            getchar();  
            switch (getchar()) {
                case 'A':
                    cout << "Round " << setw(4) << round << ": ";
                    cout << "Press UP. "
                         << "Goal: " << target << endl;
                    pressUp();
                    round++;
                    break;
                case 'B':
                    cout << "Round " << setw(4) << round << ": ";
                    cout << "Press DOWN. "
                         << "Goal: " << target << endl;
                    pressDown();
                    round++;
                    break;
                case 'C':
                    cout << "Round " << setw(4) << round << ": ";
                    cout << "Press RIGHT. "
                         << "Goal: " << target << endl;
                    pressRight();
                    round++;
                    break;
                case 'D':
                    cout << "Round " << setw(4) << round << ": ";
                    cout << "Press LEFT. "  
                         << "Goal: " << target << endl;
                    pressLeft();
                    round++;
                    break;

            }
            while (getchar() != '\n'); 

        }

    }
}