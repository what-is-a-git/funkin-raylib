#ifndef LUA_FRONTEND_H
#define LUA_FRONTEND_H

#include "lua_wrapper.h"

int lua_DrawFPS(lua_State *state);
int lua_ClearBackground(lua_State *state);
int lua_DrawText(lua_State *state);
int lua_UnloadTexture(lua_State *state);
int lua_Sprite_loadTexture(lua_State *state);
int lua_Sprite_draw(lua_State *state);
int lua_Sprite_new(lua_State *state);
int frontend_assets_load_texture(lua_State *state);
int frontend_assets_path(lua_State *state);

void frontend_bind(SCRIPT_STATE *state);

#endif // !LUA_FRONTEND_H