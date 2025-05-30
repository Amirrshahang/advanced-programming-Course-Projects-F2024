
#include "player1.hpp"
#include "playerBase.hpp"

Player1::Player1(int x, int y, float speed,const SheepConfigs& config)
    : PlayerBase(x, y,config) {
        speedX = speed;
    }

int& Player1::getCurrentLine(){
    return currentLine; 
}
int Player1::getDamage(){
    return sheepConfig.damage; 
}
int Player1::getStrength() const{
    return sheepConfig.strength; 
}
FloatRect Player1::getGlobalBounds() const{
    return sprite.getGlobalBounds(); 
}
bool Player1::isOutOfBoundary(float boundaryX) const{
    return pos.x > boundaryX; 
}
bool Player1::isOutOfSelfBoundary()const{
    return  pos.x < 130;
}
bool Player1::move(float boundaryX){
    return PlayerBase::move(boundaryX);
}


