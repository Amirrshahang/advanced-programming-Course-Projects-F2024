#pragma once
#include "Configs.hpp"
#include "global.hpp"

class Player {
protected:
    Vector2f pos;
    float speedX;
    const SheepConfigs& sheepConfig;
    Texture texture;
    Sprite sprite;

public:
    Player(int x, int y, float speed, const SheepConfigs& config);
    virtual ~Player();

    virtual bool move(float boundaryX) = 0; // متد مجازی برای حرکت بازیکن
    virtual int getDamage();
    void render(RenderWindow& window);
    void update();
};
