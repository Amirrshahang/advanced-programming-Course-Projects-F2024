#pragma once

#include "global.hpp"
#include "Configs.hpp"

class PlayerBase {
protected:
    Vector2f pos;
    float speedX;
    const SheepConfigs& sheepConfig;
    bool isAlignedFlag = false; 
    Texture texture;
    Sprite sprite;
    vector<ConvexShape*> lines;
    int currentLine = 0; 
    bool isFirstSpawn = true; 
    virtual int& getCurrentLine() = 0; 

public:
    PlayerBase(int x, int y, const SheepConfigs& config);
    virtual ~PlayerBase(); 

    void stop();
    int getSpeed() const;
    bool isAligned() const;
    bool isStopped() const;
    virtual int getDamage();
    void setAligned(bool value);
    const Texture& getTexture();
    virtual void reverseDirection();
    virtual int getStrength() const;
    virtual bool move(float boundaryX);
    void speedHandling(int updateSpeed);
    virtual void render(RenderWindow& window);
    virtual FloatRect getGlobalBounds() const = 0;
    virtual bool isOutOfSelfBoundary() const = 0;
    const Texture& getTexture() const {return texture;}  
    virtual bool isOutOfBoundary(float boundaryX) const = 0;
 
};
