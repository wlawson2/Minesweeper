#include "Tile.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include "Random.h"
#include "TextureManager.h"
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

struct Board {
    vector<Tile> board;
    int mineCounter, col, row, numMine, numDisplay, origCol, origRow;
    sf::Sprite debug, test1, test2, test3, win, lose, happy;
    sf::Sprite digit0, digit1, digit2, digit3, digit4, digit5, digit6, digit7, digit8, digit9, digitn, digits;
    bool debugMode, gameLost, gameWon;
    Board(string fileName);
    void ConnectTiles();
    void ResetBoard(string);
    void ResetBoard();
    void Draw(sf::RenderWindow&);
    void GenerateMines(int numMines);
    void SetTilePos();
    void LeftClick(sf::Vector2i mousePos);
    void RightClick(sf::Vector2i mousePos);
    void CheckWin();
    void MineViewClick();
    void LoseGame();
    void DisplayMines();
    void DisplayMineCount(sf::RenderWindow& window);
    void DrawDigit(vector<int>, sf::RenderWindow&, bool);
};