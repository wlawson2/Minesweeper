#include "Tile.h"

//Default constructor to set tile with no neighbors or mines
Tile::Tile() {
    neighborMines = 0;
    top = nullptr;
    bottom = nullptr;
    left = nullptr;
    right = nullptr;
    bottomLeft = nullptr;
    bottomRight = nullptr;
    topLeft = nullptr;
    topRight = nullptr;
    ResetTile();
    flag.setTexture(TextureManager::GetTexture("flag"));
    mine.setTexture(TextureManager::GetTexture("mine"));
    revealed.setTexture(TextureManager::GetTexture("tile_revealed"));
    hidden.setTexture(TextureManager::GetTexture("tile_hidden"));
}

// The tile is revealed when clicked
// Recursvely called on neighboring tiles to reveal large sections of empty board
void Tile::RevealTile() {
    if (!isFlag) {
        isRevealed = true;
        if (neighborMines == 0) {
            if ((top != nullptr) && (!top->isRevealed))
                top->RevealTile();
            if ((bottom != nullptr) && (!bottom->isRevealed))
                bottom->RevealTile();
            if ((right != nullptr) && (!right->isRevealed))
                right->RevealTile();
            if ((left != nullptr) && (!left->isRevealed))
                left->RevealTile();
            if ((topRight != nullptr) && (!topRight->isRevealed))
                topRight->RevealTile();
            if ((bottomRight != nullptr) && (!bottomRight->isRevealed))
                bottomRight->RevealTile();
            if ((topLeft != nullptr) && (!topLeft->isRevealed))
                topLeft->RevealTile();
            if ((bottomLeft != nullptr) && (!bottomLeft->isRevealed))
                bottomLeft->RevealTile();
        }
    }
}

// Used to set a flag on a tile
void Tile::FlagTile() {
    isFlag = !isFlag;
}

//Sets a tile to hold a mine and increments the number of mines touched by neighboring tiles
void Tile::SetMine() {
    isMine = true;
    if (top != nullptr)
        top->neighborMines++;
    if (bottom != nullptr)
        bottom->neighborMines++;
    if (right != nullptr)
        right->neighborMines++;
    if (left != nullptr)
        left->neighborMines++;
    if (topLeft != nullptr)
        topLeft->neighborMines++;
    if (topRight != nullptr)
        topRight->neighborMines++;
    if (bottomLeft != nullptr)
        bottomLeft->neighborMines++;
    if (bottomRight != nullptr)
        bottomRight->neighborMines++;
}

// Resets tile back to default form
void Tile::ResetTile() {
    isMine = false;
    isFlag = false;
    isRevealed = false;
    neighborMines = 0;
}

// Function to determine which sprites should be used to represent each tile
std::vector<sf::Sprite> Tile::GetSprites(bool mineView) {
    std::vector<sf::Sprite> sprites;
    // Checks whether the tile has been revealed by the user yet
    if (isRevealed) {
        // Adds sprites to the vector of sprites that will be displayed
        sprites.push_back(revealed);
        if (isMine)
            sprites.push_back(mine);
        else if (neighborMines > 0)
            sprites.push_back(digit);
    }
    else {
        // displays the tile as hidden and adds flags or mines on top of the hidden tile if necessary
        sprites.push_back(hidden);
        if (isFlag)
            sprites.push_back(flag);
        if ((isMine) && (mineView))
            sprites.push_back(mine);
    }
    return sprites;

}

// Sets the sprite digit displayed based on the number of neighboring mines
void Tile::SetDigit() {
    string fileName;
    if (neighborMines == 1)
        fileName = "number_1";
    else if (neighborMines == 2)
        fileName = "number_2";
    else if (neighborMines == 3)
        fileName = "number_3";
    else if (neighborMines == 4)
        fileName = "number_4";
    else if (neighborMines == 5)
        fileName = "number_5";
    else if (neighborMines == 6)
        fileName = "number_6";
    else if (neighborMines == 7)
        fileName = "number_7";
    else if (neighborMines == 8)
        fileName = "number_8";

    if (neighborMines > 0)
        digit.setTexture(TextureManager::GetTexture(fileName));
}

// Used to set the position of the tile on the board based on the given parameters
void Tile::SetPos(float x, float y) {
    yPos = y;
    xPos = x;
    revealed.setPosition(x, y);
    hidden.setPosition(x, y);
    mine.setPosition(x, y);
    flag.setPosition(x, y);
    digit.setPosition(x, y);
}

