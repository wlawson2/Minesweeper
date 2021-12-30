#pragma once
#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
using std::unordered_map;
using std::string;
class TextureManager {
    static unordered_map<string, sf::Texture> textures;
    static void LoadTexture(string name);

public:
    static sf::Texture& GetTexture(string name);
    static void Clear();
};
#endif