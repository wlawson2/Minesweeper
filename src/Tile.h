#ifndef TILE_H
#define TILE_H
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include <vector>
#include <string>
#include <iostream>

struct Tile {

    sf::Sprite revealed, hidden, flag, digit, mine;
    float xPos, yPos;
    Tile* top;
    Tile* bottom;
    Tile* left;
    Tile* right;
    Tile* bottomLeft;
    Tile* bottomRight;
    Tile* topLeft;
    Tile* topRight;


    bool isMine, isFlag, isRevealed;
    int neighborMines;

    Tile();
    void RevealTile();
    void FlagTile();
    void SetMine();
    void ResetTile();
    std::vector<sf::Sprite> GetSprites(bool);
    void SetDigit();
    void SetPos(float, float);

};
#endif