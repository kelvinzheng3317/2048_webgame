let grid = [];
for (let i=0; i<4; ++i) {
    grid.push([]);
    for (let j=0; j<4; ++j) {
        grid[i][j] = 0;
    }
}

console.log(grid);

function hasEmptySpaces(grid) {
    /* Determines if there is still an empty square on the board */
    let hasEmpty = false;
    for (let i=0; i<4; ++i) {
        for (let j=0; j<4; ++j) {
            if (grid[i][j] == 0) {
                hasEmpty = true;
            }
        }
    }
    return hasEmpty;
}

function getEmptySpaces(grid) {
    let emptySpaces = [];
    for (let i=0; i<4; ++i) {
        for (let j=0; j<4; ++j) {
            if (grid[i][j] == 0) {
                emptySpaces.push(4*i + j);
            }
        }
    }
    return emptySpaces;
}

function generateNewSquare(grid) {
    /* Adds a new square(with 2 or 4) to the board */
    let emptySpaces = getEmptySpaces(grid);  // possible optimization here by taking the getEmptySpaces  out of this function so that it doesn't have to be generated everytime
    // randomly chooses index values 
    let index = emptySpaces[Math.floor(Math.random() * emptySpaces.length)];
    let colIndex = index % 4;
    let rowIndex = Math.floor(index / 4);
    // randomly chooses 2 or 4 to be the value of the new square
    let newEven = 2;
    if (Math.random() < 0.1) {
        newEven = 4;
    }
    grid[rowIndex][colIndex] = newEven;
}

function updateBoard(grid) {
    let gridHTML = `
    <div class="square num${grid[0][0]}">${grid[0][0]}</div>
    <div class="square num${grid[0][1]}">${grid[0][1]}</div>
    <div class="square num${grid[0][2]}">${grid[0][2]}</div>
    <div class="square num${grid[0][3]}">${grid[0][3]}</div>
    <div class="square num${grid[1][0]}">${grid[1][0]}</div>
    <div class="square num${grid[1][1]}">${grid[1][1]}</div>
    <div class="square num${grid[1][2]}">${grid[1][2]}</div>
    <div class="square num${grid[1][3]}">${grid[1][3]}</div>
    <div class="square num${grid[2][0]}">${grid[2][0]}</div>
    <div class="square num${grid[2][1]}">${grid[2][1]}</div>
    <div class="square num${grid[2][2]}">${grid[2][2]}</div>
    <div class="square num${grid[2][3]}">${grid[2][3]}</div>
    <div class="square num${grid[3][0]}">${grid[3][0]}</div>
    <div class="square num${grid[3][1]}">${grid[3][1]}</div>
    <div class="square num${grid[3][2]}">${grid[3][2]}</div>
    <div class="square num${grid[3][3]}">${grid[3][3]}</div>`;

    let gameBoard = document.querySelector(".grid");
    gameBoard.innerHTML = gridHTML;
}

function shiftLeft(grid) {
    /* will return true/false depending on wheter the move is doable, i.e. at least one block has to move positions */
    let aSquareMoved = false;  // determines if at least one change was made on the board
    for (let i=0; i<4; ++i) {  // iterates through rows
        let curr = 0;
        let toMerge = 0;
        let curNum = 0;
        for (let j=0; j<4; ++j) {
            // find next non-empty square for curr
            while (curr < 4 && grid[i][curr] == 0) {
                curr++;
            }
            // if curr < 4 a number was found, no number was found elsewise
            if (curr < 4) {
                curNum = grid[i][curr];
                toMerge = curr + 1;
                // first check for whether a square moved for this position
                if (curr != j) {
                    aSquareMoved = true;
                }
                // find next non-empty space to see if currNum can double from the move
                while (grid[i][toMerge] == 0 && toMerge < 4) {
                    toMerge++;
                }
                // if the next found number is a match, double the value in the curr position and delete the other number
                // this is also the second check for if a number moved for this position
                if (toMerge < 4 && curNum == grid[i][toMerge]) {
                    curNum *= 2;
                    grid[i][toMerge] = 0;
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

function shiftRight(grid) {
    /* will return true/false depending on wheter the move is doable, i.e. at least one block has to move positions */
    let aSquareMoved = false;  // determines if at least one change was made on the board
    for (let i=0; i<4; ++i) {  // iterates through rows
        let curr = 3;
        let toMerge = 3;
        let curNum = 0;
        for (let j=3; j>-1; --j) {
            // find next non-empty square for curr
            while (curr > -1 && grid[i][curr] == 0) {
                curr--;
            }
            // if curr > -1 a number was found, no number was found elsewise
            if (curr > -1) {
                curNum = grid[i][curr];
                toMerge = curr - 1;
                // find next non-empty space to see if currNum can double from the move
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

function shiftUp(grid) {
    /* will return true/false depending on wheter the move is doable, i.e. at least one block has to move positions */
    let aSquareMoved = false;  // determines if at least one change was made on the board
    for (let j=0; j<4; ++j) {  // iterates through rows
        let curr = 0;
        let toMerge = 0;
        let curNum = 0;
        for (let i=0; i<4; ++i) {
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

function shiftDown(grid) {
    /* will return true/false depending on wheter the move is doable, i.e. at least one block has to move positions */
    let aSquareMoved = false;  // determines if at least one change was made on the board
    for (let j=0; j<4; ++j) {  // iterates through rows
        let curr = 3;
        let toMerge = 3;
        let curNum = 0;
        for (let i=3; i>-1; --i) {
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


function playGame(key) {
    console.log(key);
    if (key === 'a' || key === 'ArrowLeft') {
        shiftLeft(grid);
    } else if (key === 'd' || key === 'ArrowRight') {
        shiftRight(grid);
    } else if (key === 'w' || key === 'ArrowUp') {
        shiftUp(grid);
    } else if (key === 's' || key === 'ArrowDown') {
        shiftDown(grid);
    }
    generateNewSquare(grid);
    updateBoard(grid);
}

generateNewSquare(grid);
generateNewSquare(grid);
updateBoard(grid);

document.addEventListener('keydown', (event) => {
    playGame(event.key);
})
