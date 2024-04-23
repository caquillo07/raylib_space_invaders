#include <string>
#include <fmt/core.h>
#include <raylib.h>

#include "src/utils/common.h"
#include "src/game.h"

static void init() {
    initLogger();
}

int main() {
    init();

    std::string title = "Space Invaders";
    #ifdef DEBUG
    title = "Space Invaders - Debug";
    #endif

    InitWindow(ScreenWidth + Offset, ScreenHeight + 2 * Offset, title.c_str());
    SetTargetFPS(FPS);

    InitAudioDevice();

    Game game;

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        f32 deltaTime = GetFrameTime();
        game.HandleInput();
        game.Update(deltaTime);

        SetWindowTitle(fmt::format("{} - FPS: {}", title, GetFPS()).c_str());
        BeginDrawing();
        {
            game.Draw();
        }
        EndDrawing();
    }

    game.Close();
    CloseWindow();
    CloseAudioDevice();

    return 0;
}
