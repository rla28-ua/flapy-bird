#include "MainGameState.hpp"
#include "GameOverState.hpp"
#include "StateMachine.hpp"
#include <iostream>

extern "C" {
#include <raylib.h>
}

MainGameState::MainGameState() {}

void MainGameState::init() {
  birdSprite = LoadTexture("assets/sprites/yellowbird-midflap.png");
  pipeSprite = LoadTexture("assets/sprites/pipe-green.png");

  jugador.width = birdSprite.width;
  jugador.height = birdSprite.height;

  PIPE_W = (float)pipeSprite.width;
  PIPE_H = (float)pipeSprite.height;

  jugador.x = 200.0f;
  jugador.y = 200.0f;
  jugador.vy = 0.0f;

  pipes.clear();
  spawnTimer = 0.0f;
}

void MainGameState::handleInput() {
  if (IsKeyPressed(KEY_SPACE)) {
    jugador.vy += -300.0f;
  }
}

void MainGameState::update(float deltaTime) {
  jugador.vy += gravedad * deltaTime;
  jugador.y += jugador.vy * deltaTime;
  jugador.vy = 0.0f;

  spawnTimer += deltaTime;

  Rectangle playerBB{jugador.x - jugador.width * 0.5f,
                     jugador.y - jugador.height * 0.5f, (float)jugador.width,
                     (float)jugador.height};

  if (spawnTimer >= spawnEvery) {
    spawnTimer = 0.0f;

    const int minOffset = PIPE_H / 2;
    const int maxOffset = GetScreenHeight() / 2;
    const int pipe_y_offset_top = GetRandomValue(minOffset, maxOffset);

    const float startX = (float)GetScreenWidth();

    PipePair pair;

    pair.top = Rectangle{
        startX,
        (float)(-pipe_y_offset_top),
        (float)PIPE_W,
        (float)PIPE_H,
    };

    pair.bot = Rectangle{
        startX,
        (float)((PIPE_H - pipe_y_offset_top) + (GetScreenHeight() / 2)),
        (float)PIPE_W,
        (float)PIPE_H,
    };

    pair.scored = false;
    pipes.push_back(pair);
  }

  for (auto &p : pipes) {
    p.top.x -= PIPE_SPEED * deltaTime;
    p.bot.x -= PIPE_SPEED * deltaTime;

    if (!p.scored && (p.top.x + PIPE_W) < jugador.x) {
      puntos++;
      p.scored = true;
    }
  }

  while (!pipes.empty()) {
    const PipePair &front = pipes.front();

    if (front.top.x + PIPE_W < 0.0f) {
      pipes.pop_front();
    } else {
      break;
    }

    if (jugador.y - jugador.height * 0.5f < 0.0f ||
        jugador.y + jugador.height * 0.5f > GetScreenHeight()) {
      this->state_machine->add_state(std::make_unique<GameOverState>(puntos),
                                     true);
      return;
    }

    for (const auto &p : pipes) {
      if (CheckCollisionRecs(playerBB, p.top) ||
          CheckCollisionRecs(playerBB, p.bot)) {
        this->state_machine->add_state(std::make_unique<GameOverState>(puntos),
                                       true);
        return;
      }
    }
  }
}

void MainGameState::render() {
  BeginDrawing();
  ClearBackground(RAYWHITE);

  DrawTexture(birdSprite, (int)(jugador.x - jugador.width * 0.5f),
              (int)(jugador.y - jugador.height * 0.5f), WHITE);

  for (const auto &p : pipes) {
    DrawTextureEx(pipeSprite, {p.top.x + PIPE_W, p.top.y + PIPE_H}, 180.0f,
                  1.0f, WHITE);
    DrawTextureEx(pipeSprite, {p.bot.x, p.bot.y}, 0.0f, 1.0f, WHITE);

    std::string scoreText = std::to_string(puntos);
    DrawText(scoreText.c_str(), 10, 10, 30, BLACK);
  }
  EndDrawing();
}

void MainGameState::pause(){};
void MainGameState::resume(){};