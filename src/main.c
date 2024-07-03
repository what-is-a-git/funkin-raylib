#include "raylib.h"
#include "lua_wrapper.h"

#include <stdio.h>

int fart = 0;
int tart = 0;
lua_Number poopy = 0.0;
lua_Number myBalls = 1.0;
const char *pleaseStopSRC = "Congrats! OwO!";

int helloMario(lua_State *state) {
    if (!lua_isnumber(state, 1)) {
        return 0;
    }

    myBalls = lua_tonumber(state, 1);
    return 0;
}

int yoMamaSoUgly(lua_State *state) {
    if (!lua_isnumber(state, 1)) {
        return 0;
    }

    poopy = lua_tonumber(state, 1);
    return 0;
}

int yoMamaSoHair(lua_State *state) {
    if (!lua_isnumber(state, 1)) {
        return 0;
    }

    fart = lua_tonumber(state, 1);
    return 0;
}

int yoMamaSoHairZ(lua_State *state) {
    if (!lua_isnumber(state, 1)) {
        return 0;
    }

    tart = lua_tonumber(state, 1);
    return 0;
}

int yoMamaSoHairy(lua_State *state) {
    if (!lua_isnumber(state, 1) || !lua_isnumber(state, 2)) {
        return 0;
    }

    fart = lua_tonumber(state, 1);
    tart = lua_tonumber(state, 2);
    return 0;
}

int srtYouHaveRagingAutism(lua_State *state) {
    if (!lua_isstring(state, 1)) {
        return 0;
    }

    pleaseStopSRC = lua_tostring(state, 1);
    return 0;
}

int iLoveEatingFlixel(lua_State *state) {
    if (!lua_isinteger(state, 1) || !lua_isinteger(state, 2)) {
        return 0;
    }

    DrawFPS(lua_tointeger(state, 1), lua_tointeger(state, 2));
    return 0;
}

Texture2D phighting;

int drawMyMyKrita(lua_State *state) {
    if (!lua_isnumber(state, 1) || !lua_isinteger(state, 2)) {
        DrawTexturePro(phighting, (Rectangle) {0, 0, phighting.width, phighting.height},
            (Rectangle) {fart, tart, phighting.width * myBalls, phighting.height * myBalls},
            (Vector2) {phighting.width * myBalls / 2.0, phighting.height * myBalls / 2.0}, poopy, WHITE);
        return 0;
    }

    int offX = lua_tonumber(state, 1);
    int offY = lua_tonumber(state, 2);

    DrawTexturePro(phighting, (Rectangle) {0, 0, phighting.width, phighting.height},
            (Rectangle) {fart + offX, tart + offY, phighting.width * myBalls, phighting.height * myBalls},
            (Vector2) {phighting.width * myBalls / 2.0, phighting.height * myBalls / 2.0}, poopy, WHITE);
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
    DrawText(text, x, y, s, LIGHTGRAY);
    return 0;
}

int pleaseBro(lua_State *state) {
    lua_pushstring(state, pleaseStopSRC);
    return 1;
}

int main(int argc, char **argv) {
    // SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1280, 720, "Friday Night Funkin'");

    script_state *silly = script_new();
    script_bind_func(silly, "setX", yoMamaSoHair, 1);
    script_bind_func(silly, "setY", yoMamaSoHairZ, 1);
    script_bind_func(silly, "setScale", helloMario, 1);
    script_bind_func(silly, "setAngle", yoMamaSoUgly, 1);
    script_bind_func(silly, "setPosition", yoMamaSoHairy, 1);
    script_bind_func(silly, "getText", pleaseBro, 0);
    script_bind_func(silly, "setText", srtYouHaveRagingAutism, 2);
    script_bind_func(silly, "drawFPS", iLoveEatingFlixel, 2);
    script_bind_func(silly, "drawPhighterBabyUwU", drawMyMyKrita, 2);
    script_bind_func(silly, "clearTheScreenOfFlies", ohEmGeeGodotIsThatYou, 3);
    script_bind_func(silly, "drawMyBeautifulText", heheILikeCheese, 4);

    

    script_run_file(silly, "assets/test.lua");

    phighting = LoadTexture("assets/peak.png");

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
    UnloadTexture(phighting);
    CloseWindow();

    return 0;
}
