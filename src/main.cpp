#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>
#include "TextureManager.h"
#include "Tile.h"
#include "Board.h"
#include "Random.h"
#include <iostream>
using namespace std;

int main()
{
    // creates the board to play on
    Board board("boards/config.cfg");

    // Specifies the width and height of the window generated by sfml based on the number of tiles in the board
    int height = (board.row * 32) + 88;
    int width = board.col * 32;
    
    //Generates new window to play game
    sf::RenderWindow window(sf::VideoMode(width, height), "Minesweeper");
    board.SetTilePos();

    // Loop to allow gameplay until the window is closed
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            // Gets the details of each mouse click and gives the information to the board 
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    board.LeftClick(mousePos);

                }

                else if (event.mouseButton.button == sf::Mouse::Right) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    board.RightClick(mousePos);
                }

            }
        }
        // Constantly checks for a win and clears and draws the new board each loop to ensure smooth gameplay
        board.CheckWin();
        window.clear();
        board.Draw(window);
        window.display();
    }
    TextureManager::Clear();
    return 0;
}
