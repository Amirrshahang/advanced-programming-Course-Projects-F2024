#include "MainMenu.hpp"

MainMenu::MainMenu(int width, int height, RenderWindow& window){

    if (!backgroundTexture.loadFromFile(PICS_PATH + "menu.png")){
        throw runtime_error("Failed to load background image!");
    }
    
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(
        float(window.getSize().x) / backgroundTexture.getSize().x,
        float(window.getSize().y) / backgroundTexture.getSize().y
    );

    button.setSize(Vector2f(350, 70)); 
    button.setFillColor(Color::Transparent); 
    button.setOutlineThickness(2);
    button.setOutlineColor(Color::Transparent);
    button.setPosition((width / 2) - 180,(height / 2) + 230);
}

void MainMenu::render(RenderWindow& window){
    window.clear(Color::Black);
    window.draw(backgroundSprite);
    window.draw(button);
    window.display();
}

void MainMenu::handleEvents(RenderWindow& window, bool& startGame){
    Event event;
    while (window.pollEvent(event)){
        if (event.type == Event::Closed){
            window.close();
        }
        if (event.type == Event::MouseButtonPressed){
            Vector2i mousePos = Mouse::getPosition(window);
            if (button.getGlobalBounds().contains(static_cast<Vector2f>(mousePos))){
                startGame = true; 
            }
        }
    }
}

bool MainMenu::run(RenderWindow& window){
    bool startGame = false;
    while (window.isOpen() && !startGame){
        handleEvents(window, startGame);
        render(window);
    }

    if (startGame){
        window.clear(); 
        window.display();
    }

    return startGame;
}
