#include "TextureManager.h"

// Unordered map used to store textures based on their names
unordered_map <string, sf::Texture> TextureManager::textures;

// Function used to load new textures into the map of textures
void TextureManager::LoadTexture(string fileName) {

    string path = "images/" + fileName + ".png";
    textures[fileName].loadFromFile(path);

}

// Function used to retrieve a texture from the map based on the texture name
sf::Texture& TextureManager::GetTexture(string name) {
    if (textures.find(name) == textures.end())
        LoadTexture(name);
    return textures[name];
}

// Function to clear all textures from the map of textures
void TextureManager::Clear() {
    textures.clear();
}
