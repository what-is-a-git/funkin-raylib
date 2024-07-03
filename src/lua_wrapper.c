#include "lua_wrapper.h"

#include <stdlib.h>
#include "lauxlib.h"

script_state *script_new(void) {
    script_state *state = (script_state*) malloc(sizeof(script_state));
    state->raw_state = luaL_newstate();
    luaL_openlibs(state->raw_state);
    return state;
}

void script_dispose(script_state *state) {
    lua_close(state->raw_state);
    free(state); 
}

SCRIPT_ERROR script_run_string(script_state *state, const char *source) {
    return luaL_dostring(state->raw_state, source);
}

SCRIPT_ERROR script_run_file(script_state *state, const char *path) {
    return luaL_dofile(state->raw_state, path);
}

SCRIPT_ERROR script_call_empty_void(script_state *state, const char *func) {
    lua_getglobal(state->raw_state, func);
    return lua_pcall(state->raw_state, 0, 0, 0);
}

SCRIPT_ERROR script_init_args(script_state *state, const char *func) {
    lua_getglobal(state->raw_state, func);
}

void script_push_arg(script_state *state, script_arg arg) {
    switch (arg.type) {
        case NIL:
            lua_pushnil(state->raw_state);
            break;
        case BOOL:
            lua_pushboolean(state->raw_state, *(int*)arg.value);
            break;
        case INT:
            lua_pushinteger(state->raw_state, *(lua_Integer*)arg.value);
            break;
        case NUMBER:
            lua_pushnumber(state->raw_state, *(lua_Number*)arg.value);
            break;
        case STRING:
            lua_pushstring(state->raw_state, (const char*)arg.value);
            break;
    }
}

SCRIPT_ERROR script_call_args_void(script_state *state, int arg_count) {
    return lua_pcall(state->raw_state, arg_count, 0, 0);
}

void script_bind_func(script_state *state, const char *name, lua_CFunction func, int arg_count) {
    for (int i = 0; i < arg_count; i++) {
        lua_pushstring(state->raw_state, name);
    }
    
    lua_pushcclosure(state->raw_state, func, arg_count);
    lua_setglobal(state->raw_state, name);
}