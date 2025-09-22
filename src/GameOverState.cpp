#include "GameOverState.hpp"
#include "MainGameState.hpp"
#include "StateMachine.hpp"

extern "C" {
  #include <raylib.h>
}

void GameOverState::init() { /* nada especial por ahora */ }

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

    const char* msg = "Game Over";
    int fontSize = 32;
    int w = MeasureText(msg, fontSize);
    int x = (GetScreenWidth()  - w) / 2;
    int y = (GetScreenHeight() - fontSize) / 2;

    DrawText(msg, x, y, fontSize, RED);
    DrawText("Pulsa ESPACIO para reiniciar", 20, GetScreenHeight() - 40, 20, DARKGRAY);

    EndDrawing();
}

void GameOverState::pause() {};
void GameOverState::resume() {};
