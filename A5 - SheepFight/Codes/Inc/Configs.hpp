#ifndef CONFIGS_HPP_INCLUDE
#define CONFIGS_HPP_INCLUDE

#include <vector>
#include <string>
#include "global.hpp"


struct SheepConfigs {
    string name;
    int damage;
    int strength;
    float displayProb;
    string texturePath;
    bool aligned = false;
};

const vector<SheepConfigs> SHEEP_CONFIGS1 = {
    {"Timmy", 50, 50, 0.5f, PICS_PATH + "timmy.png"},
    {"Shaun", 30, 150, 0.3f, PICS_PATH + "shaun.png"},
    {"Meow", 10, 250, 0.2f, PICS_PATH + "meow.png"}
};
const vector<SheepConfigs> SHEEP_CONFIGS2 = {
    {"Timmyblack", 50, -50, 0.5f, PICS_PATH + "timmyblack.png"},
    {"Shaunblack", 30, -150, 0.3f, PICS_PATH + "shaunblack.png"},
    {"Meowblack", 10, -250, 0.2f, PICS_PATH + "meowblack.png"}
};

constexpr int COOLDOWN_MS = 1000;       
constexpr int INITIAL_HEALTH = 400;    
constexpr int CONSTANT_SPEED = 1.0f;    

#endif 