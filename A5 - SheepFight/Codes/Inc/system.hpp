
#pragma once
#include "global.hpp"
#include "player1.hpp"
#include "player2.hpp"



enum State {
    IN_GAME,
    WHITE_SHEEP_VICTORY_SCREEN,
    BLACK_SHEEP_VICTORY_SCREEN,
    EXIT
};


class System {
public:
    System(int width, int height);
    ~System();

    void run();
    void render();
    
private:
    Font font;
    Clock clock; 
    State state;
    Text healthText;
    Text healthText1;
    Text healthText2;
    RenderWindow window;
    Music backgroundMusic;
    Sprite backgroundSprite;
    CircleShape healthCircle;
    Texture backgroundTexture;
    CircleShape healthCircle1;
    CircleShape healthCircle2;
    

    int currentLine1;
    int currentLine2;
    int playerHealth1;
    int playerHealth2;
    bool isFirstSpawn1;
    bool isFirstSpawn2;

    vector<PlayerBase*> linePlayers1[LINECOUNT]; 
    vector<PlayerBase*> linePlayers2[LINECOUNT];

    vector<ConvexShape*> lines1;
    vector<ConvexShape*> lines2;
    vector<CircleShape> sheepCircles1;
    vector<CircleShape> sheepCircles2;
   
    deque<SheepConfigs> sheepQueue1;
    deque<SheepConfigs> sheepQueue2;
    chrono::steady_clock::time_point lastSpawnTime1;
    chrono::steady_clock::time_point lastSpawnTime2;


    void handle_events();
    void highlightLine1();
    void highlightLine2();
    void initializeMusic();
    void reverseDirection();
    void initializeLines1();
    void initializeLines2();
    void updateSheepCircles1();
    void updateSheepCircles2();
    void updateHealthDisplay1(); 
    void updateHealthDisplay2();
    void handle_key(Keyboard::Key key);
    void checkCollisions(int lineIndex);
    void handleTeamCollisions(vector<PlayerBase*>& linePlayers);
    bool allPlayersAligned(const vector<PlayerBase*>& linePlayers) const;
    int calculateLineStrength(const vector<PlayerBase*>& linePlayers);
    void updatePlayers(vector<PlayerBase*> linePlayers[], int& playerHealth, float boundaryX, bool isPlayer1);


};
