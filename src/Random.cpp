#include "Random.h"

std::mt19937 Random::random(time(0));

// Generates a random integer between the two given integers
int Random::Int(int min, int max) {
    std::uniform_int_distribution<int> dist(min, max);
    return dist(random);
}

// Generates a random float between the two given floats
float Random::Float(float min, float max) {
    std::uniform_real_distribution<float> dist(min, max);
    return dist(random);
}
