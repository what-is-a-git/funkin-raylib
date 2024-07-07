#ifndef LUA_FRONTEND_H
#define LUA_FRONTEND_H

#include "lua_wrapper.h"

int lua_DrawFPS(lua_State *state);
int lua_ClearBackground(lua_State *state);
int lua_DrawText(lua_State *state);
int lua_LoadTexture(lua_State *state);
int lua_UnloadTexture(lua_State *state);
int lua_DrawTexture(lua_State *state);

void frontend_bind(SCRIPT_STATE *state);

#endif // !LUA_FRONTEND_H