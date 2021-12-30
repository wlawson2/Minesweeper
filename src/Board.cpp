#include "Board.h"

// Creates a board from the information given in the file passed in as a parameter.
Board::Board(string FileName) {
    debugMode = false, gameLost = false, gameWon = false;
    ifstream inFile(FileName);
    string token;
    getline(inFile, token);
    col = stoi(token);
    origCol = col;
    getline(inFile, token);
    row = stoi(token);
    origRow = row;
    getline(inFile, token);
    numMine = stoi(token);
    for (int i = 0; i < row * col; i++)
        board.push_back(Tile());
    ConnectTiles();
    GenerateMines(numMine);
    for (unsigned int i = 0; i < board.size(); i++)
        board[i].SetDigit();
    debug.setTexture(TextureManager::GetTexture("debug"));
    debug.setPosition(col * 32 - 256, row * 32);
    test1.setTexture(TextureManager::GetTexture("test_1"));
    test1.setPosition(col * 32 - 192, row * 32);
    test2.setTexture(TextureManager::GetTexture("test_2"));
    test2.setPosition(col * 32 - 128, row * 32);
    test3.setTexture(TextureManager::GetTexture("test_3"));
    test3.setPosition(col * 32 - 64, row * 32);
    int loc = 0;
    if ((col - 2) * 16 < col * 32 - 320)
        loc = (col - 2) * 16;
    else
        loc = col * 32 - 320;
    win.setTexture(TextureManager::GetTexture("face_win"));
    win.setPosition(loc, row * 32);
    lose.setTexture(TextureManager::GetTexture("face_lose"));
    lose.setPosition(loc, row * 32);
    happy.setTexture(TextureManager::GetTexture("face_happy"));
    happy.setPosition(loc, row * 32);
    digits.setTexture(TextureManager::GetTexture("digits"));
    mineCounter = numMine;
    ResetBoard();
}

// Resets the board to the original conditions
// Removes old mines and generates new mines
void Board::ResetBoard() {
    row = origRow;
    col = origCol;
    board.clear();
    for (int i = 0; i < row * col; i++)
        board.push_back(Tile());
    ConnectTiles();
    SetTilePos();
    GenerateMines(numMine);
    for (unsigned int i = 0; i < board.size(); i++)
        board[i].SetDigit();
    mineCounter = numMine;
    debugMode = false;
    gameWon = false;
    gameLost = false;
}

// Sets the tiles to point to each other in order for ineraction between tiles
void Board::ConnectTiles() {
    for (int i = 0; i < row * col; i++) {
        // Uses if statements to ensure the correct tiles are pointed to and edges of board do not cause issues
        if (i >= col) {
            board[i].top = &board[i - col];
        }
        if (i < (row - 1) * col) {
            board[i].bottom = &board[i + col];
        }
        if (i % col != 0) {
            board[i].left = &board[i - 1];
        }
        if (i % col != col - 1) {
            board[i].right = &board[i + 1];
        }
        if ((board[i].top != nullptr) && (board[i].left != nullptr)) {
            board[i].topLeft = &board[i - col - 1];
        }
        if ((board[i].top != nullptr) && (board[i].right != nullptr)) {
            board[i].topRight = &board[i - col + 1];
        }
        if ((board[i].bottom != nullptr) && (board[i].left != nullptr)) {
            board[i].bottomLeft = &board[i + col - 1];
        }
        if ((board[i].bottom != nullptr) && (board[i].right != nullptr)) {
            board[i].bottomRight = &board[i + col + 1];
        }
    }
}

// Draws the board along with each tile in its current state
void Board::Draw(sf::RenderWindow& window) {
    vector<sf::Sprite> sprites;
    // Iterates each tile to get the sprites of each tile and display them
    for (int i = 0; i < col * row; i++) {
        sprites = board[i].GetSprites(debugMode);
        for (unsigned int j = 0; j < sprites.size(); j++) {
            window.draw(sprites[j]);
        }
        sprites.clear();
    }
    // Draws the accessories such as the buttons, mine counter, and win/lose face
    window.draw(debug);
    window.draw(test1);
    window.draw(test2);
    window.draw(test3);
    DisplayMineCount(window);
    if (gameLost)
        window.draw(lose);
    else if (gameWon)
        window.draw(win);
    else
        window.draw(happy);

}

void Board::SetTilePos() {
    //Sets the position that each tile should be drawn
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            board[j + (col * i)].SetPos(32 * j, 32 * i);
        }
    }
}

// Randomly generates the number of mines given as target onto the tiles mines 
void Board::GenerateMines(int target) {
    int numMines = 0;
    int rand;
    // Iterates to add a mine to the board each time until the number of mines equals the target number of mines
    while (numMines != target) {
        rand = Random::Int(0, row * col);
        if (board[rand].isMine) {
            continue;
        }
        else {
            board[rand].SetMine();
            numMines++;
        }

    }
}

// Causes the user to lose the game and display all mines
void Board::LoseGame() {
    if (!debugMode)
        DisplayMines();
    gameLost = true;

}

// 
void Board::DisplayMines() {
    if (!gameLost && !gameWon)
        debugMode = !debugMode;
}

void Board::LeftClick(sf::Vector2i mousePos) {
    bool gameOver = gameWon || gameLost;
    auto debugBounds = debug.getGlobalBounds();
    if (debugBounds.contains(mousePos.x, mousePos.y))
        DisplayMines();
    auto resetBounds = happy.getGlobalBounds();
    if (resetBounds.contains(mousePos.x, mousePos.y)) {
        ResetBoard();
        ResetBoard();
    }
    auto test1Bounds = test1.getGlobalBounds();
    if (test1Bounds.contains(mousePos.x, mousePos.y))
        ResetBoard("boards/testboard1.brd");
    auto test2Bounds = test2.getGlobalBounds();
    if (test2Bounds.contains(mousePos.x, mousePos.y))
        ResetBoard("boards/testboard2.brd");
    auto test3Bounds = test3.getGlobalBounds();
    if (test3Bounds.contains(mousePos.x, mousePos.y))
        ResetBoard("boards/testboard3.brd");
    for (unsigned int i = 0; i < board.size(); i++) {
        auto tileBounds = board[i].hidden.getGlobalBounds();
        if ((tileBounds.contains(mousePos.x, mousePos.y)) && (!gameOver)) {
            if ((board[i].isMine) && (!board[i].isFlag))
                LoseGame();
            else if ((!board[i].isRevealed) && (!board[i].isFlag))
                board[i].RevealTile();
        }
    }
}

void Board::RightClick(sf::Vector2i mousePos) {
    for (unsigned int i = 0; i < board.size(); i++) {
        auto bounds = board[i].hidden.getGlobalBounds();
        if (!board[i].isRevealed) {
            if (bounds.contains(mousePos.x, mousePos.y)) {
                board[i].FlagTile();
                if (board[i].isFlag)
                    mineCounter--;
                else
                    mineCounter++;
            }
        }
    }
}

void Board::CheckWin() {
    gameWon = true;
    for (unsigned int i = 0; i < board.size(); i++) {
        if ((board[i].isMine) || (board[i].isRevealed))
            continue;
        else {
            gameWon = false;
            break;
        }
    }
    if (gameWon) {
        for (unsigned int i = 0; i < board.size(); i++) {
            if (board[i].isMine) {
                board[i].isFlag = true;
            }
        }
        mineCounter = 0;
    }
}

void Board::DisplayMineCount(sf::RenderWindow& window) {
    vector <int> nums;
    int temp = mineCounter;
    bool pos = true;
    if (temp < 0) {
        pos = false;
        temp /= -1;
    }
    while (temp != 0) {
        nums.push_back(temp % 10);
        temp /= 10;
    }
    if (mineCounter == 0)
        nums.push_back(0);
    DrawDigit(nums, window, pos);
}

void Board::DrawDigit(vector<int> nums, sf::RenderWindow& window, bool pos) {
    int x = 0;
    if (!pos) {
        digits.setTextureRect(sf::IntRect(210, 0, 21, 32));
        digits.setPosition(x, row * 32);
        x += 21;
        window.draw(digits);
    }
    for (int i = nums.size() - 1; i >= 0; i--) {
        if (nums[i] == 0) {
            digits.setTextureRect(sf::IntRect(0, 0, 21, 32));
            digits.setPosition(x, row * 32);
            x += 21;
            window.draw(digits);
        }
        if (nums[i] == 1) {
            digits.setTextureRect(sf::IntRect(21, 0, 21, 32));
            digits.setPosition(x, row * 32);
            x += 21;
            window.draw(digits);
        }
        if (nums[i] == 2) {
            digits.setTextureRect(sf::IntRect(42, 0, 21, 32));
            digits.setPosition(x, row * 32);
            x += 21;
            window.draw(digits);
        }
        if (nums[i] == 3) {
            digits.setTextureRect(sf::IntRect(63, 0, 21, 32));
            digits.setPosition(x, row * 32);
            x += 21;
            window.draw(digits);
        }
        if (nums[i] == 4) {
            digits.setTextureRect(sf::IntRect(84, 0, 21, 32));
            digits.setPosition(x, row * 32);
            x += 21;
            window.draw(digits);
        }
        if (nums[i] == 5) {
            digits.setTextureRect(sf::IntRect(105, 0, 21, 32));
            digits.setPosition(x, row * 32);
            x += 21;
            window.draw(digits);
        }
        if (nums[i] == 6) {
            digits.setTextureRect(sf::IntRect(126, 0, 21, 32));
            digits.setPosition(x, row * 32);
            x += 21;
            window.draw(digits);
        }
        if (nums[i] == 7) {
            digits.setTextureRect(sf::IntRect(147, 0, 21, 32));
            digits.setPosition(x, row * 32);
            x += 21;
            window.draw(digits);
        }
        if (nums[i] == 8) {
            digits.setTextureRect(sf::IntRect(168, 0, 21, 32));
            digits.setPosition(x, row * 32);
            x += 21;
            window.draw(digits);
        }
        if (nums[i] == 9) {
            digits.setTextureRect(sf::IntRect(189, 0, 21, 32));
            digits.setPosition(x, row * 32);
            x += 21;
            window.draw(digits);
        }
    }
}


void Board::ResetBoard(string fileName) {
    board.clear();
    ifstream inFile(fileName);
    string strings;
    string token;
    row = 0;
    col = 0;
    mineCounter = 0;
    while (getline(inFile, token)) {
        for (unsigned int i = 0; i < token.size(); i++) {
            if ((token[i] != '0') && (token[i] != '1'))
                token = token.substr(0, i) + token.substr(i + 1);
        }
        strings += token;
        row++;
    }
    col = strings.size() / (row);

    for (int i = 0; i < row * col; i++)
        board.push_back(Tile());

    ConnectTiles();
    for (int i = 0; i < row * col; i++) {
        if (strings[i] == '1') {
            board[i].SetMine();
            mineCounter++;
        }
    }
    SetTilePos();
    for (unsigned int i = 0; i < board.size(); i++)
        board[i].SetDigit();

    debugMode = false;
    gameWon = false;
    gameLost = false;
}
