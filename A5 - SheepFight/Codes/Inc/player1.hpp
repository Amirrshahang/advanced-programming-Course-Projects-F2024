
#pragma once

#include "playerBase.hpp"

class Player1 : public PlayerBase {
public:
    Player1(int x, int y, float speed, const SheepConfigs& config);
    ~Player1() override = default;
    
    int getDamage();
    int& getCurrentLine() override;
    int getStrength() const override;
    bool move(float boundaryX) override;
    bool isOutOfSelfBoundary() const override;
    FloatRect getGlobalBounds() const override;
    bool isOutOfBoundary(float boundaryX) const override;
};
