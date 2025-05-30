
#include "player2.hpp"

Player2::Player2(int x, int y ,float speed,const SheepConfigs& config)
    : PlayerBase(x, y, config) {
        speedX = -speed;
    }

int& Player2::getCurrentLine(){
    return currentLine; 
}
int Player2::getDamage(){
    return sheepConfig.damage; 
}
int Player2::getStrength() const{
    return sheepConfig.strength;
}
FloatRect Player2::getGlobalBounds() const{
    return sprite.getGlobalBounds();
}
bool Player2::isOutOfBoundary(float boundaryX) const{
    return pos.x < boundaryX;
}
bool Player2::isOutOfSelfBoundary() const{
    return  pos.x > 1030;
}
bool Player2::move(float boundaryX){
        return PlayerBase::move(boundaryX); 
}

