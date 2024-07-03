#include "raylib.h"
#include "lua_wrapper.h"

#include <stdio.h>

int main(int argc, char **argv) {
    // SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 450, "raylib [core] example - basic window");

    script_state *silly = script_new();
    script_run_file(silly, "assets/test.lua");

    lua_Integer value = 1;

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
        
        value++;
        if (value > 32) {
            value = 32;
        }

        for (int i = 0; i < 1024; i++) {
            script_push_arg(silly, (script_arg) {INT, &value});
            script_call_args_void(silly, "bacon", call_dumb, 1);
        }

        DrawFPS(4, 4);
        EndDrawing();
    }

    script_call_empty_void(silly, "madre");
    script_dispose(silly);
    CloseWindow();

    return 0;
}
