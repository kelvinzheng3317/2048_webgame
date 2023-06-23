#include <iostream>
#include <limits>
#include <vector>
#include <cstdlib>
using namespace std;


void printGrid(int** grid) {
    for (int i=0; i<4; ++i) {
        cout << "-----------------------------" << endl;
        cout << "| ";
        for (int j=0; j<4; ++j) {
            if (grid[i][j] < 10) {
                cout << "_";
            }
            if (grid[i][j] < 100) {
                cout << "_";
            }
            if (grid[i][j] < 1000) {
                cout << "_";
            }
            if (grid[i][j] == 0) {
                cout << '_';
            } else {
                cout << grid[i][j];
            }
            cout << " | ";
        }
        cout << endl;
    }
    cout << "-----------------------------" << endl;
}


bool hasEmptySpaces(int** grid) {
    /* Determines if there is still an empty square on the board */
    bool hasEmpty = false;
    for (int i=0; i<4; ++i) {
        for (int j=0; j<4; ++j) {
            if (grid[i][j] == 0) {
                hasEmpty = true;
            }
        }
    }
    return hasEmpty;
}

vector<int> getEmptySpaces(int** grid) {
    vector<int> emptySpaces;
    for (int i=0; i<4; ++i) {
        for (int j=0; j<4; ++j) {
            if (grid[i][j] == 0) {
                emptySpaces.push_back(4*i + j);
            }
        }
    }
    return emptySpaces;
}


bool shiftLeft(int** grid) {
    /* will return true/false depending on wheter the move is doable, i.e. at least one block has to move positions */
    bool aSquareMoved = false;  // determines if at least one change was made on the board
    for (int i=0; i<4; ++i) {  // iterates through rows
        int curr = 0;
        int toMerge = 0;
        int curNum = 0;
        for (int j=0; j<4; ++j) {
            // find next non-empty square for curr
            while (curr < 4 && grid[i][curr] == 0) {
                curr++;
            }
            // if curr < 4 a number was found, no number was found elsewise
            if (curr < 4) {
                curNum = grid[i][curr];
                toMerge = curr + 1;
                // find next non-empty space
                while (grid[i][toMerge] == 0 && toMerge < 4) {
                    toMerge++;
                }
                // if the next found number is a match, double the value in the curr position and delete the other number
                if (toMerge < 4 && curNum == grid[i][toMerge]) {
                    curNum *= 2;
                    grid[i][toMerge] = 0;
                    aSquareMoved = true;
                }
                if (curr != j) {
                    aSquareMoved = true;
                }
                // shift the numbers
                grid[i][curr] = 0;
                grid[i][j] = curNum;
                curr++;
            } else {
                grid[i][j] = 0;
            }
        }
    }
    return aSquareMoved;
}


bool shiftRight(int** grid) {
    /* will return true/false depending on wheter the move is doable, i.e. at least one block has to move positions */
    bool aSquareMoved = false;  // determines if at least one change was made on the board
    for (int i=0; i<4; ++i) {  // iterates through rows
        int curr = 3;
        int toMerge = 3;
        int curNum = 0;
        for (int j=3; j>-1; --j) {
            // find next non-empty square for curr
            while (curr > -1 && grid[i][curr] == 0) {
                curr--;
            }
            // if curr > - 1 a number was found, no number was found elsewise
            if (curr > -1) {
                curNum = grid[i][curr];
                toMerge = curr - 1;
                // find next non-empty space
                while (grid[i][toMerge] == 0 && toMerge > -1) {
                    toMerge--;
                }
                // if the next found number is a match, double the value in the curr position and delete the other number
                if (toMerge > -1 && curNum == grid[i][toMerge]) {
                    curNum *= 2;
                    grid[i][toMerge] = 0;
                    aSquareMoved = true;
                }
                if (curr != j) {
                    aSquareMoved = true;
                }
                // shift the numbers
                grid[i][curr] = 0;
                grid[i][j] = curNum;
                curr--;
            } else {
                grid[i][j] = 0;
            }
        }
    }
    return aSquareMoved;
}


bool shiftUp(int** grid) {
    /* will return true/false depending on wheter the move is doable, i.e. at least one block has to move positions */
    bool aSquareMoved = false;  // determines if at least one change was made on the board
    for (int j=0; j<4; ++j) {  // iterates through rows
        int curr = 0;
        int toMerge = 0;
        int curNum = 0;
        for (int i=0; i<4; ++i) {
            // find next non-empty square for curr
            while (curr < 4 && grid[curr][j] == 0) {
                curr++;
            }
            // if curr < 4 a number was found, no number was found elsewise
            if (curr < 4) {
                curNum = grid[curr][j];
                toMerge = curr + 1;
                // find next non-empty space
                while (toMerge < 4 && grid[toMerge][j] == 0) {
                    toMerge++;
                }
                // if the next found number is a match, double the value in the curr position and delete the other number
                if (toMerge < 4 && curNum == grid[toMerge][j]) {
                    curNum *= 2;
                    grid[toMerge][j] = 0;
                    aSquareMoved = true;
                }
                if (curr != i) {
                    aSquareMoved = true;
                }
                // shift the numbers
                grid[curr][j] = 0;
                grid[i][j] = curNum;
                curr++;
            } else {
                grid[i][j] = 0;
            }
        }
    }
    return aSquareMoved;
}

bool shiftDown(int** grid) {
    /* will return true/false depending on wheter the move is doable, i.e. at least one block has to move positions */
    bool aSquareMoved = false;  // determines if at least one change was made on the board
    for (int j=0; j<4; ++j) {  // iterates through rows
        int curr = 3;
        int toMerge = 3;
        int curNum = 0;
        for (int i=3; i>-1; --i) {
            // find next non-empty square for curr
            while (curr > -1 && grid[curr][j] == 0) {
                curr--;
            }
            // if curr > -1 a number was found, no number was found elsewise
            if (curr > -1) {
                curNum = grid[curr][j];
                toMerge = curr - 1;
                // find next non-empty space
                while (toMerge > -1 && grid[toMerge][j] == 0) {
                    toMerge--;
                }
                // if the next found number is a match, double the value in the curr position and delete the other number
                if (toMerge > -1 && curNum == grid[toMerge][j]) {
                    curNum *= 2;
                    grid[toMerge][j] = 0;
                    aSquareMoved = true;
                }
                if (curr != i) {
                    aSquareMoved = true;
                }
                // shift the numbers
                grid[curr][j] = 0;
                grid[i][j] = curNum;
                curr--;
            } else {
                grid[i][j] = 0;
            }
        }
    }
    return aSquareMoved;
}


void generateNewSquare(int** grid) {
    /* Adds a new square(with 2 or 4) to the board */
    vector<int> emptySpaces = getEmptySpaces(grid);  // possible optimization here by taking the getEmptySpaces  out of this function so that it doesn't have to be generated everytime
    // randomly chooses index values 
    int randNum = rand();
    int index = emptySpaces[randNum % emptySpaces.size()];
    int colIndex = index % 4;
    int rowIndex = index / 4;
    // randomly chooses 2 or 4 to be the value of the new square
    int newEven = 2;
    randNum /= 10;
    if (randNum == 7) {
        newEven = 4;
    }
    grid[rowIndex][colIndex] = newEven;
}

int gameOver(int** grid) {
    /*  
        0 means game isn't over.
        1 means the player has lost
        2 means the player has won
    */
   bool winGame = false;
   bool validMoveAvailable = true;
   for (int i=0; i<4; ++i) {
        for (int j=0; j<4; ++j) {
            if (grid[i][j] == 2048) {
                winGame = true;
            }
            // check if valid move is available
        }
    }
    if (winGame) {
        return 2;
    } else if (!validMoveAvailable) {
        return 1;
    } else {
        return 0;
    }
}



int main() {
    // initialize values
    srand((unsigned) time(NULL));
    int** grid = new int*[4];
    for (int i=0; i<4; ++i) {
        grid[i] = new int[4];
    }
    for (int i=0; i<4; ++i) {
        for (int j=0; j<4; ++j) {
            grid[i][j] = 0;
        }
    }
    // board doesn't start empty, starts w 2 squares given
    generateNewSquare(grid);
    generateNewSquare(grid);
    char userInput;

    // tells user controls
    cout << "Use wasd to move the squares." << endl;
    cout << "Merge squares of the same numbers to double them." << endl;
    cout << "Reach 2048 to win!" << endl;

    /* The basic implementation will have it so that when there is no empty spaces, the game is over.
    Note, that in a more complex implementation, the game doesn't end when there is no empty spaces,
    but instead when there is no more legal moves. */
    int gameState = gameOver(grid);
    while (gameState == 0) {
        printGrid(grid);
        cout << "Give a direction: ";
        cin >> userInput;

        // handles bad user input
        if (cin.fail()) {
            cout << "Invalid response, please type w, a, s, or d" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        if (userInput!='w' && userInput!='a' && userInput!='s' && userInput!='d') {
            cout << "Invalid response, please type w, a, s, or d" << endl;
            continue;
        }

        // does move, if its an invalid move, outputs error message
        bool validMove = false;
        if (userInput == 'a') {
            validMove = shiftLeft(grid);
        } else if (userInput == 'd') {
            validMove = shiftRight(grid);
        } else if (userInput == 'w') {
            validMove = shiftUp(grid);
        } else {
            validMove = shiftDown(grid);
        }

        // doesn't generate a new square if not a valid move, i.e. no squares moved
        if (validMove) {
            generateNewSquare(grid);
        }
        
        // check the game state
        gameState = gameOver(grid);
    }
    
    
    if (gameState == 1) {
        cout << "You Lose :(" << endl;
    } else if (gameState == 2) {
        cout << "You Win!! :)" << endl;
    }

}