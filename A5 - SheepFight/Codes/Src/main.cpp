#include "global.hpp"
#include "system.hpp"
#include "MainMenu.hpp"

int main() {
    srand(static_cast<unsigned>(time(nullptr)));
    RenderWindow window(VideoMode(WIDTH, HEIGHT), "Main Menu and Game", Style::Close);

    MainMenu menu(WIDTH, HEIGHT, window);

    if (menu.run(window)){
        System* game = new System(WIDTH, HEIGHT);
        game->run();
        delete game;
    }

    return 0;
}