#pragma once
#include "GameState.hpp"
#include <deque>

extern "C" {
  #include <raylib.h>
}

struct Bird {
    float x;
    float y;
    float vy;
};

struct PipePair {
    Rectangle top;
    Rectangle bot;
    bool scored = false;
};

class MainGameState : public GameState
{
    public:
        MainGameState();
        ~MainGameState() = default;

        void init() override;
        void handleInput() override;
        void update(float deltaTime) override;
        void render() override;

        void pause() override;
        void resume() override;

    
    private:
        char entered_key;
        Bird jugador;
        static constexpr float gravedad = 900.0f;
        static constexpr int radio = 17;

        std::deque<PipePair> pipes;
        float spawnTimer = 0.0f;
        static constexpr float spawnEvery = 1.75f;
        static constexpr int PIPE_W = 32;
        static constexpr int PIPE_H = 320;
        static constexpr float PIPE_SPEED = 120.0f;
};