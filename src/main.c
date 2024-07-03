#include "raylib.h"
#include "lua_wrapper.h"

#include <stdio.h>

int fart = 0;
int tart = 0;
lua_Number poopy = 0.0;
lua_Number myBalls = 1.0;

int helloMario(lua_State *state) {
    int arg_count = lua_gettop(state);
    if (!lua_isnumber(state, 1)) {
        return 0;
    }

    myBalls = lua_tonumber(state, 1);
    return 0;
}

int yoMamaSoUgly(lua_State *state) {
    int arg_count = lua_gettop(state);
    if (!lua_isnumber(state, 1)) {
        return 0;
    }

    poopy = lua_tonumber(state, 1);
    return 0;
}

int yoMamaSoHairy(lua_State *state) {
    int arg_count = lua_gettop(state);
    if (!lua_isnumber(state, 1) || !lua_isnumber(state, 2)) {
        return 0;
    }

    fart = lua_tonumber(state, 1);
    tart = lua_tonumber(state, 2);
    return 0;
}

int main(int argc, char **argv) {
    // SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 450, "raylib [core] example - basic window");

    script_state *silly = script_new();
    script_bind_func(silly, "setScale", helloMario, 1);
    script_bind_func(silly, "setAngle", yoMamaSoUgly, 1);
    script_bind_func(silly, "setPosition", yoMamaSoHairy, 2);
    script_run_file(silly, "assets/test.lua");

    Texture2D phighting = LoadTexture("assets/peak.png");

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        lua_Number delta = GetFrameTime();
        script_init_args(silly, "update");
        script_push_arg(silly, (script_arg) {NUMBER, &delta});
        script_call_args_void(silly, 1);

        DrawTexturePro(phighting, (Rectangle) {0, 0, phighting.width, phighting.height},
                (Rectangle) {fart, tart, phighting.width * myBalls, phighting.height * myBalls},
                (Vector2) {phighting.width * myBalls / 2.0, phighting.height * myBalls / 2.0}, poopy, WHITE);

        DrawFPS(4, 4);
        EndDrawing();
    }

    script_call_empty_void(silly, "madre");
    script_dispose(silly);
    UnloadTexture(phighting);
    CloseWindow();

    return 0;
}
