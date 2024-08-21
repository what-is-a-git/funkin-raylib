#include "lua_wrapper.h"

#include <stdlib.h>
#include "log.h"

SCRIPT_STATE *script_new(void) {
    SCRIPT_STATE *state = luaL_newstate();
    luaL_openlibs(state);
    return state;
}

void script_dispose(SCRIPT_STATE *state) {
    lua_close(state);
}

SCRIPT_ERROR script_run_string(SCRIPT_STATE *state, const char *source) {
    return luaL_dostring(state, source);
}

SCRIPT_ERROR script_run_file(SCRIPT_STATE *state, const char *path) {
    return luaL_dofile(state, path);
}

void script_call_empty_void(SCRIPT_STATE *state, const char *func) {
    lua_getglobal(state, func);
    script_call_args_void(state, 0);
}

SCRIPT_ERROR script_init_args(SCRIPT_STATE *state, const char *func) {
    return lua_getglobal(state, func);
}

void script_push_arg(SCRIPT_STATE *state, script_arg arg) {
    switch (arg.type) {
        case NIL:
            lua_pushnil(state);
            break;
        case BOOL:
            lua_pushboolean(state, *(int*)arg.value);
            break;
        case INT:
            lua_pushinteger(state, *(lua_Integer*)arg.value);
            break;
        case NUMBER:
            lua_pushnumber(state, *(lua_Number*)arg.value);
            break;
        case STRING:
            lua_pushstring(state, (const char*)arg.value);
            break;
    }
}

void script_call_args_void(SCRIPT_STATE *state, int arg_count) {
    // function does not exist (probably)
    if (!lua_isfunction(state, -1 - arg_count)) {
        // set back stuff lol
        lua_settop(state, 0);
        return;
    }

    script_handle_errors(state, lua_pcall(state, arg_count, 0, 0));
}

void script_handle_errors(SCRIPT_STATE *state, SCRIPT_ERROR error) {
    if (error == LUA_OK) {
        return;
    }

    error_fmt("%s", lua_tostring(state, -1));
}

void script_bind_func(SCRIPT_STATE *state, const char *name, lua_CFunction func, int arg_count) {
    // don't ask me why we need this for loop
    // i don't fully understand it lmao
    // upvalues maybe?
    for (int i = 0; i < arg_count; i++) {
        lua_pushnil(state);
    }
    
    lua_pushcclosure(state, func, arg_count);
    lua_setglobal(state, name);
}

void script_table_new(SCRIPT_STATE *state, int size) {
    if (size > 0) {
        lua_createtable(state, 0, size);
    } else {
        lua_newtable(state);
    }
}

void script_table_set_field_int(SCRIPT_STATE *state, const char *field, lua_Integer value, int index) {
    lua_pushinteger(state, value);
    lua_setfield(state, index, field);
}

lua_Integer script_table_get_field_int(SCRIPT_STATE *state, int table_index, const char *field) {
    lua_getfield(state, table_index, field);
    lua_Integer x = lua_tointeger(state, -1);
    lua_pop(state, 1);
    return x;
}

lua_Integer script_table_get_int(SCRIPT_STATE *state, int table_index, int item_index) {
    lua_rawgeti(state, table_index, item_index);
    lua_Integer x = lua_tointeger(state, -1);
    lua_pop(state, 1);
    return x;
}

void script_table_set_field_number(SCRIPT_STATE *state, const char *field, lua_Number value, int index) {
    lua_pushnumber(state, value);
    lua_setfield(state, index, field);
}

lua_Number script_table_get_field_number(SCRIPT_STATE *state, int table_index, const char *field) {
    lua_getfield(state, table_index, field);
    lua_Number x = lua_tonumber(state, -1);
    lua_pop(state, 1);
    return x;
}

lua_Number script_table_get_number(SCRIPT_STATE *state, int table_index, int item_index) {
    lua_rawgeti(state, table_index, item_index);
    lua_Number x = lua_tonumber(state, -1);
    lua_pop(state, 1);
    return x;
}

void script_table_set_field_bool(SCRIPT_STATE *state, const char *field, int value, int index) {
    lua_pushboolean(state, value);
    lua_setfield(state, index, field);
}

int script_table_get_field_bool(SCRIPT_STATE *state, int table_index, const char *field) {
    lua_getfield(state, table_index, field);
    int x = lua_toboolean(state, -1);
    lua_pop(state, 1);
    return x;
}