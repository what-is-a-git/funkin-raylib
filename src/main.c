#include <stdio.h>
#include "raylib.h"

#include "lua_wrapper.h"
#include "lua_frontend.h"

int main(int argc, char **argv) {   
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1280, 720, "Friday Night Funkin'");

    SCRIPT_STATE *script = script_new();
    frontend_bind(script);
    script_run_file(script, "assets/scenes/initial_testing.lua");
    script_call_empty_void(script, "init");
    script_call_empty_void(script, "ready");

    while (!WindowShouldClose()) {
        BeginDrawing();

        lua_Number delta = GetFrameTime();
        script_init_args(script, "update");
        script_push_arg(script, (script_arg) {NUMBER, &delta});
        script_call_args_void(script, 1);

        script_call_empty_void(script, "draw");

        EndDrawing();
    }

    script_call_empty_void(script, "free");
    script_dispose(script);
    CloseWindow();

    return 0;
}
