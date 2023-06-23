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