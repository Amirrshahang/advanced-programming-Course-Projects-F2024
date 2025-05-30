
#include "playerBase.hpp"

PlayerBase::PlayerBase(int x, int y, const SheepConfigs& config)
    : pos(x, y), speedX(CONSTANT_SPEED), sheepConfig(config) {
    if (!texture.loadFromFile(config.texturePath)) {
        throw runtime_error("Failed to load texture: " + config.texturePath);
    }
    sprite.setTexture(texture);
    sprite.setPosition(pos);
    sprite.setScale(0.35f, 0.35f);
}

 PlayerBase::~PlayerBase() {
     for (auto line : lines) {
         delete line;
     }
     lines.clear();
 }

int PlayerBase::getDamage(){
    return sheepConfig.damage;
}
void PlayerBase::setAligned(bool value){
    isAlignedFlag = value;
}
bool PlayerBase::isAligned() const{
    return isAlignedFlag;
}
int PlayerBase::getSpeed() const{
    return speedX; 
}
void PlayerBase::speedHandling(int updateSpeed) {
    speedX = updateSpeed;
}
bool PlayerBase::isStopped() const{
    return speedX == 0; 
}
void PlayerBase::reverseDirection(){
    speedX = -speedX;
}
void PlayerBase::stop() {
    speedX = 0; 
}
int PlayerBase::getStrength() const{
    return 0;
}
bool PlayerBase::move(float boundaryX){
    pos.x += speedX;
    sprite.setPosition(pos);

    if (isOutOfBoundary(boundaryX)) {
        return true;
    }
    return false;
}
void PlayerBase::render(RenderWindow& window){
    window.draw(sprite);
}
