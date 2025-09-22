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
  int width;
  int height;
};

struct PipePair {
  Rectangle top;
  Rectangle bot;
  bool scored = false;
};

class MainGameState : public GameState {
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
  int puntos = 0;
  static constexpr float gravedad = 900.0f;
  static constexpr int radio = 17;

  std::deque<PipePair> pipes;
  float spawnTimer = 0.0f;
  float spawnEvery = 1.75f;
  float PIPE_W = 0.0f;
  float PIPE_H = 0.0f;
  float PIPE_SPEED = 120.0f;
  float GAP_ALTURA = 4.5f;
  
  Texture2D birdSprite{};
  Texture2D pipeSprite{};
};