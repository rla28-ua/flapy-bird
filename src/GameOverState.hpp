#pragma once
#include "GameState.hpp"

class GameOverState : public GameState {
public:
    GameOverState() = default;
    ~GameOverState() override = default;

    void init() override;
    void handleInput() override;
    void update(float) override;
    void render() override;

    void pause() override;
    void resume() override;
};
