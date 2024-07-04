#include "raylib.h"
#include "lua_wrapper.h"

#include <stdio.h>

int lua_DrawFPS(lua_State *state) {
    DrawFPS(luaL_optnumber(state, 1, 0.0), luaL_optnumber(state, 2, 0.0));
    return 0;
}

int lua_ClearBackground(lua_State *state) {
    Color color = RAYWHITE;
    if (lua_istable(state, 1) && lua_rawlen(state, 1) >= 3) {
        color = (Color) {script_table_get_number(state, 1, 1), script_table_get_number(state, 1, 2), script_table_get_number(state, 1, 3), 255};
    }

    ClearBackground(color);
    return 0;
}

int lua_DrawText(lua_State *state) {
    const char *text = luaL_optstring(state, 1, "Text");
    int x = luaL_optnumber(state, 2, 0.0);
    int y = luaL_optnumber(state, 3, 0.0);
    int size = luaL_optnumber(state, 4, 20.0);

    Color color = BLACK;
    if (lua_istable(state, 5) && lua_rawlen(state, 5) >= 3) {
        color = (Color) {script_table_get_number(state, 5, 1), script_table_get_number(state, 5, 2), script_table_get_number(state, 5, 3), 255};
    }

    DrawText(text, x, y, size, color);
    return 0;
}

int lua_LoadTexture(lua_State *state) {
    if (!lua_isstring(state, 1)) {
        lua_pushnil(state);
        return 1;
    }

    Texture2D texture = LoadTexture(lua_tostring(state, 1));
    script_table_new(state, 5);
    script_table_set_field_int(state, "id", texture.id, 2);
    script_table_set_field_int(state, "width", texture.width, 2);
    script_table_set_field_int(state, "height", texture.height, 2);
    script_table_set_field_int(state, "mipmaps", texture.mipmaps, 2);
    script_table_set_field_int(state, "format", texture.format, 2);
    return 1;
}

int lua_UnloadTexture(lua_State *state) {
    if (!lua_istable(state, 1)) {
        return 0;
    }

    UnloadTexture((Texture2D) {
        script_table_get_field_int(state, -1, "id"),
        script_table_get_field_int(state, -1, "width"), script_table_get_field_int(state, -1, "height"),
        script_table_get_field_int(state, -1, "mipmaps"), script_table_get_field_int(state, -1, "format")
    });
    return 0;
}

int lua_DrawTexture(lua_State *state) {
    if (!lua_istable(state, 1)) {
        return 0;
    }

    // texture info //
    Texture2D texture = {
        script_table_get_field_int(state, 1, "id"),
        script_table_get_field_int(state, 1, "width"), script_table_get_field_int(state, 1, "height"),
        script_table_get_field_int(state, 1, "mipmaps"), script_table_get_field_int(state, 1, "format")
    };

    // other shit (optional technically) //
    lua_Number x = luaL_optnumber(state, 2, 0.0);
    lua_Number y = luaL_optnumber(state, 3, 0.0);
    lua_Number scale = luaL_optnumber(state, 4, 1.0);
    lua_Number angle = luaL_optnumber(state, 5, 0.0);

    DrawTexturePro(texture, (Rectangle) {0, 0, texture.width, texture.height}, (Rectangle) {x, y, texture.width * scale, texture.height * scale},
            (Vector2) {texture.width / 2.0, texture.height / 2.0}, angle, WHITE);
    return 0;
}

void bind_functions(SCRIPT_STATE *state) {
    script_bind_func(state, "loadTexture", lua_LoadTexture, 1);
    script_bind_func(state, "unloadTexture", lua_UnloadTexture, 1);
    script_bind_func(state, "clear", lua_ClearBackground, 3);
    script_bind_func(state, "drawTexture", lua_DrawTexture, 5);
    script_bind_func(state, "drawText", lua_DrawText, 4);
    script_bind_func(state, "drawFPS", lua_DrawFPS, 2);
}

int main(int argc, char **argv) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1280, 720, "Friday Night Funkin'");

    SCRIPT_STATE *script = script_new();
    bind_functions(script);
    script_run_file(script, "assets/script.lua");

    while (!WindowShouldClose()) {
        BeginDrawing();

        lua_Number delta = GetFrameTime();
        script_init_args(script, "update");
        script_push_arg(script, (script_arg) {NUMBER, &delta});
        script_call_args_void(script, 1);

        script_call_empty_void(script, "draw");

        EndDrawing();
    }

    script_call_empty_void(script, "dispose");
    script_dispose(script);
    CloseWindow();

    return 0;
}
