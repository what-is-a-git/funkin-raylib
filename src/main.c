#include "raylib.h"
#include "lua_wrapper.h"

#include <stdio.h>

int main(int argc, char **argv) {
    // SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 450, "raylib [core] example - basic window");

    script_state *silly = script_new();
    script_run_file(silly, "assets/test.lua");

    lua_Integer value = 40;
    SCRIPT_ARGS call_dumb = script_args_init(script_arg_new(INT, &value));
    script_call_args_void(silly, "bacon", call_dumb);

    // script_args_dispose(call_dumb);

    while (!WindowShouldClose()) {
        BeginDrawing();
        
        ClearBackground(RAYWHITE);
        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
        
        script_call_args_void(silly, "bacon", call_dumb);
        EndDrawing();
    }

    script_call_empty_void(silly, "madre");
    script_dispose(silly);
    CloseWindow();

    return 0;
}
