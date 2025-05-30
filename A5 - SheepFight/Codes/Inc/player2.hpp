
#pragma once
#include "playerBase.hpp"

class Player2 : public PlayerBase {
public:
    Player2(int x, int y, float speed , const SheepConfigs& config);
    ~Player2() override = default;
    
    int getDamage();
    int& getCurrentLine() override;
    bool move(float boundaryX) override;
    int getStrength() const override;
    bool isOutOfSelfBoundary() const override;
    FloatRect getGlobalBounds() const override;
    bool isOutOfBoundary(float boundaryX) const override;
};
