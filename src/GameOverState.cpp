#include "GameOverState.hpp"
#include "MainGameState.hpp"
#include "StateMachine.hpp"

extern "C" {
#include <raylib.h>
}

GameOverState::GameOverState(int puntosFinal) : puntosFinal(puntosFinal) {}

void GameOverState::init() { /* nada especial por ahora */
}

void GameOverState::handleInput() {
  // Si el jugador pulsa ESPACIO, iniciamos una nueva partida
  if (IsKeyPressed(KEY_SPACE)) {
    this->state_machine->add_state(std::make_unique<MainGameState>(), true);
  }
}

void GameOverState::update(float) {
  // Sin lógica de momento
}

void GameOverState::render() {
  BeginDrawing();
  ClearBackground(RAYWHITE);

  const char *msg = "Game Over";
  int fontSize = 32;
  int w = MeasureText(msg, fontSize);
  int x = (GetScreenWidth() - w) / 2;
  int y = (GetScreenHeight() - fontSize) / 2;

  DrawText(msg, x, y, fontSize, RED);

  std::string scoreMsg = "Puntuacion: " + std::to_string(puntosFinal);
  DrawText(scoreMsg.c_str(), 20, GetScreenHeight() - 80, 20, BLACK);

  DrawText("Pulsa ESPACIO para reiniciar", 20, GetScreenHeight() - 40, 20,
           DARKGRAY);

  EndDrawing();
}

void GameOverState::pause(){};
void GameOverState::resume(){};
