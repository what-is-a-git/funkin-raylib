#include "lua_frontend.h"

#include <string.h>
#include "raylib.h"

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

int lua_Sprite_free(lua_State *state) {
    if (!lua_istable(state, 1)) {
        return 0;
    }

    lua_getfield(state, 1, "texture");
    UnloadTexture((Texture2D) {
        script_table_get_field_int(state, 2, "id"),
        script_table_get_field_int(state, 2, "width"), script_table_get_field_int(state, 2, "height"),
        script_table_get_field_int(state, 2, "mipmaps"), script_table_get_field_int(state, 2, "format")
    });
    lua_pop(state, 1);
    return 0;
}

int lua_Sprite_draw(lua_State *state) {
    if (!lua_istable(state, 1)) {
        return 0;
    }

    lua_getfield(state, 1, "texture");

    // texture info //
    Texture2D texture = {
        script_table_get_field_int(state, 2, "id"),
        script_table_get_field_int(state, 2, "width"), script_table_get_field_int(state, 2, "height"),
        script_table_get_field_int(state, 2, "mipmaps"), script_table_get_field_int(state, 2, "format")
    };

    lua_pop(state, 1);

    lua_Number x = script_table_get_field_number(state, 1, "x");
    lua_Number y = script_table_get_field_number(state, 1, "y");

    lua_getfield(state, 1, "scale");
    lua_Number scale_x = script_table_get_field_number(state, 2, "x");
    lua_Number scale_y = script_table_get_field_number(state, 2, "y");
    lua_pop(state, 1);

    lua_getfield(state, 1, "origin");
    lua_Number origin_x = script_table_get_field_number(state, 2, "x");
    lua_Number origin_y = script_table_get_field_number(state, 2, "y");
    lua_pop(state, 1);

    lua_Number angle = script_table_get_field_number(state, 1, "angle");

    int flip_x = script_table_get_field_bool(state, 1, "flipX");
    int flip_y = script_table_get_field_bool(state, 1, "flipY");
    float width_multi = 1.0 - flip_x * 2.0;
    float height_multi = 1.0 - flip_y * 2.0;

    if (script_table_get_field_bool(state, 1, "antialiased")) {
        SetTextureFilter(texture, TEXTURE_FILTER_BILINEAR);
    } else {
        SetTextureFilter(texture, TEXTURE_FILTER_POINT);
    }

    DrawTexturePro(texture, (Rectangle) {0, 0, texture.width * width_multi, texture.height * height_multi},
            (Rectangle) {x, y, texture.width * scale_x, texture.height * scale_y},
            (Vector2) {origin_x * texture.width, origin_y * texture.height}, angle, WHITE);
    return 0;
}

int lua_Sprite_new(lua_State *state) {
    lua_newtable(state);

    lua_pushnumber(state, 0.0);
    lua_setfield(state, 2, "x");

    lua_pushnumber(state, 0.0);
    lua_setfield(state, 2, "y");

    lua_pushnumber(state, 0.0);
    lua_setfield(state, 2, "angle");

    lua_pushboolean(state, false);
    lua_setfield(state, 2, "flipX");

    lua_pushboolean(state, false);
    lua_setfield(state, 2, "flipY");

    lua_pushboolean(state, true);
    lua_setfield(state, 2, "antialiased");

    script_table_new(state, 2);
    script_table_set_field_number(state, "x", 0.5, 3);
    script_table_set_field_number(state, "y", 0.5, 3);
    lua_setfield(state, 2, "origin");

    script_table_new(state, 2);
    script_table_set_field_number(state, "x", 1.0, 3);
    script_table_set_field_number(state, "y", 1.0, 3);
    lua_setfield(state, 2, "scale");

    script_table_new(state, 5);
    script_table_set_field_int(state, "id", 0, 3);
    script_table_set_field_int(state, "width", 0, 3);
    script_table_set_field_int(state, "height", 0, 3);
    script_table_set_field_int(state, "mipmaps", 0, 3);
    script_table_set_field_int(state, "format", 0, 3);
    lua_setfield(state, 2, "texture");

    lua_pushnil(state);
    lua_pushcclosure(state, lua_Sprite_draw, 1);
    lua_setfield(state, 2, "draw");

    lua_pushnil(state);
    lua_pushcclosure(state, lua_Sprite_free, 1);
    lua_setfield(state, 2, "free");

    return 1;
}

int frontend_assets_load_texture(lua_State *state) {
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

int frontend_assets_path(lua_State *state) {
    if (!lua_isstring(state, 1)) {
        lua_pushnil(state);
        return 1;
    }

    const char *input = lua_tostring(state, 1);
    if (!str_starts_with(input, "assets/")) {
        lua_pushfstring(state, "assets/%s", input);
        return 1;
    }

    lua_pushstring(state, lua_tostring(state, 1));
    return 1;
}

void frontend_bind(SCRIPT_STATE *state) {
    script_bind_func(state, "clear", lua_ClearBackground, 3);
    script_bind_func(state, "drawText", lua_DrawText, 4);
    script_bind_func(state, "drawFPS", lua_DrawFPS, 2);

    lua_newtable(state);

    lua_pushcclosure(state, lua_Sprite_new, 0);
    lua_setfield(state, -2, "new");

    lua_setglobal(state, "Sprite");

    lua_newtable(state);

    lua_pushnil(state);
    lua_pushcclosure(state, frontend_assets_load_texture, 1);
    lua_setfield(state, -2, "loadTexture");

    lua_pushnil(state);
    lua_pushcclosure(state, frontend_assets_path, 1);
    lua_setfield(state, -2, "path");

    lua_setglobal(state, "Assets");
}