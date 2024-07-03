#include "lua_wrapper.h"

#include <stdlib.h>
#include "lauxlib.h"

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

SCRIPT_ERROR script_call_empty_void(SCRIPT_STATE *state, const char *func) {
    lua_getglobal(state, func);
    return lua_pcall(state, 0, 0, 0);
}

SCRIPT_ERROR script_init_args(SCRIPT_STATE *state, const char *func) {
    lua_getglobal(state, func);
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

SCRIPT_ERROR script_call_args_void(SCRIPT_STATE *state, int arg_count) {
    return lua_pcall(state, arg_count, 0, 0);
}

void script_bind_func(SCRIPT_STATE *state, const char *name, lua_CFunction func, int arg_count) {
    for (int i = 0; i < arg_count; i++) {
        lua_pushstring(state, name);
    }
    
    lua_pushcclosure(state, func, arg_count);
    lua_setglobal(state, name);
}