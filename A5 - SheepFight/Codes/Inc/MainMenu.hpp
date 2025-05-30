#pragma once

#include "global.hpp"

class MainMenu {
private:
    Font font;
    Text startText;
    RectangleShape button;
    Sprite backgroundSprite;
    Texture backgroundTexture;


public:
    MainMenu(int width, int height, RenderWindow& window);

    bool run(RenderWindow& window);
    void render(RenderWindow& window);
    void handleEvents(RenderWindow& window, bool& startGame);
};
