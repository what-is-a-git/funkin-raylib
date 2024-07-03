#include "raylib.h"
#include "lua_wrapper.h"

#include <stdio.h>

int iLoveEatingFlixel(lua_State *state) {
    if (!lua_isinteger(state, 1) || !lua_isinteger(state, 2)) {
        return 0;
    }

    DrawFPS(lua_tointeger(state, 1), lua_tointeger(state, 2));
    return 0;
}

int ohEmGeeGodotIsThatYou(lua_State *state) {
    if (!lua_isinteger(state, 1) || !lua_isinteger(state, 2) || !lua_isinteger(state, 3)) {
        return 0;
    }

    int r, g, b = 0;
    r = lua_tointeger(state, 1);
    g = lua_tointeger(state, 2);
    b = lua_tointeger(state, 3);
    ClearBackground((Color) {r, g, b, 255});
    return 0;
}

int heheILikeCheese(lua_State *state) {
    if (!lua_isstring(state, 1) || !lua_isinteger(state, 2) || !lua_isinteger(state, 3) || !lua_isinteger(state, 4)) {
        return 0;
    }

    const char *text = lua_tostring(state, 1);
    int x, y, s = 0;
    x = lua_tointeger(state, 2);
    y = lua_tointeger(state, 3);
    s = lua_tointeger(state, 4);

    Color color = BLACK;

    if (lua_istable(state, 5) && lua_rawlen(state, 5) >= 3) {
        lua_rawgeti(state, 5, 1);
        lua_Integer r = lua_tointeger(state, -1);
        lua_pop(state, 1);

        lua_rawgeti(state, 5, 2);
        lua_Integer g = lua_tointeger(state, -1);
        lua_pop(state, 1);

        lua_rawgeti(state, 5, 3);
        lua_Integer b = lua_tointeger(state, -1);
        lua_pop(state, 1);

        color = (Color) {r, g, b, 255};
    }

    DrawText(text, x, y, s, color);
    return 0;
}

int donaldJTrump(lua_State *state) {
    if (!lua_isstring(state, 1)) {
        lua_pushnil(state);
        return 1;
    }

    const char *path = lua_tostring(state, 1);
    Texture2D tex = LoadTexture(path);

    lua_createtable(state, 0, 5);

    lua_pushinteger(state, tex.id);
    lua_setfield(state, -2, "id");

    lua_pushinteger(state, tex.width);
    lua_setfield(state, -2, "width");

    lua_pushinteger(state, tex.height);
    lua_setfield(state, -2, "height");

    lua_pushinteger(state, tex.mipmaps);
    lua_setfield(state, -2, "mipmaps");

    lua_pushinteger(state, tex.format);
    lua_setfield(state, -2, "format");

    return 1;
}

int owoUwU(lua_State *state) {
    if (!lua_istable(state, 1)) {
        return 0;
    }

    lua_getfield(state, -1, "id");
    lua_Integer id = lua_tointeger(state, -1);
    lua_pop(state, 1);

    lua_getfield(state, -1, "width");
    lua_Integer width = lua_tointeger(state, -1);
    lua_pop(state, 1);

    lua_getfield(state, -1, "height");
    lua_Integer height = lua_tointeger(state, -1);
    lua_pop(state, 1);

    lua_getfield(state, -1, "mipmaps");
    lua_Integer mipmaps = lua_tointeger(state, -1);
    lua_pop(state, 1);

    lua_getfield(state, -1, "format");
    lua_Integer format = lua_tointeger(state, -1);
    lua_pop(state, 1);

    UnloadTexture((Texture2D) {
        (unsigned int) id,
        width, height,
        mipmaps, format
    });

    return 0;
}

int ohILoveGimp(lua_State *state) {
    if (!lua_istable(state, 1) || !lua_isnumber(state, 2) || !lua_isnumber(state, 3) || !lua_isnumber(state, 4) || !lua_isnumber(state, 5)) {
        return 0;
    }

    lua_Number x = lua_tonumber(state, -4);
    lua_Number y = lua_tonumber(state, -3);
    lua_Number s = lua_tonumber(state, -2);
    lua_Number r = lua_tonumber(state, -1);

    lua_settop(state, 1);

    lua_getfield(state, -1, "id");
    lua_Integer id = lua_tointeger(state, -1);
    lua_pop(state, 1);
    
    lua_getfield(state, -1, "width");
    lua_Integer width = lua_tointeger(state, -1);
    lua_pop(state, 1);

    lua_getfield(state, -1, "height");
    lua_Integer height = lua_tointeger(state, -1);
    lua_pop(state, 1);

    lua_getfield(state, -1, "mipmaps");
    lua_Integer mipmaps = lua_tointeger(state, -1);
    lua_pop(state, 1);

    lua_getfield(state, -1, "format");
    lua_Integer format = lua_tointeger(state, -1);
    lua_pop(state, 1);

    DrawTexturePro((Texture2D) {id, width, height, mipmaps, format}, (Rectangle) {0, 0, width, height},
            (Rectangle) {x, y, width * s, height * s}, (Vector2) {width / 2.0, height / 2.0}, r, WHITE);

    return 0;
}

int main(int argc, char **argv) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1280, 720, "Friday Night Funkin'");

    SCRIPT_STATE *silly = script_new();

    script_bind_func(silly, "loadTexture", donaldJTrump, 1);
    script_bind_func(silly, "unloadTexture", owoUwU, 1);
    script_bind_func(silly, "clearScreen", ohEmGeeGodotIsThatYou, 3);
    script_bind_func(silly, "drawTexture", ohILoveGimp, 5);
    script_bind_func(silly, "drawText", heheILikeCheese, 4);
    script_bind_func(silly, "drawFPS", iLoveEatingFlixel, 2);

    script_run_file(silly, "assets/scene.lua");

    while (!WindowShouldClose()) {
        BeginDrawing();

        lua_Number delta = GetFrameTime();
        script_init_args(silly, "update");
        script_push_arg(silly, (script_arg) {NUMBER, &delta});
        script_call_args_void(silly, 1);

        script_call_empty_void(silly, "draw");

        EndDrawing();
    }

    script_call_empty_void(silly, "madre");
    script_dispose(silly);
    CloseWindow();

    return 0;
}
