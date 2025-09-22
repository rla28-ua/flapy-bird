#include "MainGameState.hpp"
#include "GameOverState.hpp"
#include "StateMachine.hpp"
#include <iostream>

extern "C" {
#include <raylib.h>
}

MainGameState::MainGameState() {}

void MainGameState::init() {
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

  Rectangle playerBB{jugador.x - (float)radio, jugador.y - (float)radio,
                     (float)radio * 2.0f, (float)radio * 2.0f};

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

    if (jugador.y - radio < 0.0f || jugador.y + radio > GetScreenHeight()) {
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

  Rectangle playerBB{jugador.x - (float)radio, jugador.y - (float)radio,
                     (float)radio * 2.0f, (float)radio * 2.0f};
  DrawRectangleLinesEx(playerBB, 1.0f, BLACK);

  for (const auto &p : pipes) {
    DrawRectangleRec(p.top, DARKGREEN);
    DrawRectangleRec(p.bot, DARKGREEN);

    std::string scoreText = std::to_string(puntos);
    DrawText(scoreText.c_str(), 10, 10, 30, BLACK);
  }
  EndDrawing();
}

void MainGameState::pause(){};
void MainGameState::resume(){};