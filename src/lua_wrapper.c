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

SCRIPT_ERROR script_call_args_void(script_state *state, const char *func, SCRIPT_ARGS args) {
    lua_getglobal(state->raw_state, func);

    int arg_count = 0;
    if (args != NULL) {
        SCRIPT_ARGS last = args;
        arg_count++;
        _script_push_arg(state, (script_arg*) last->value);

        while (last->next != NULL) {
            last = last->next;
            arg_count++;
            _script_push_arg(state, (script_arg*) last->value);
        }
    }
    
    return lua_pcall(state->raw_state, arg_count, 0, 0);
}

void _script_push_arg(script_state *state, script_arg *arg) {
    switch (arg->type) {
        case NIL:
            lua_pushnil(state->raw_state);
            break;
        case BOOL:
            lua_pushboolean(state->raw_state, *(int*)arg->value);
            break;
        case INT:
            lua_pushinteger(state->raw_state, *(lua_Integer*)arg->value);
            break;
        case NUMBER:
            lua_pushnumber(state->raw_state, *(lua_Number*)arg->value);
            break;
        case STRING:
            lua_pushstring(state->raw_state, (const char*)arg->value);
            break;
    }
}

script_arg *script_arg_new(SCRIPT_ARG_TYPE type, void *value) {
    script_arg *arg = (script_arg*) malloc(sizeof(script_arg));
    arg->type = type;
    arg->value = value;
    return arg;
}

void script_arg_dispose(script_arg *arg) {
    free(arg);
}

SCRIPT_ARGS script_args_new(void) {
    return list_new();
}

SCRIPT_ARGS script_args_init(script_arg *pushed) {
    SCRIPT_ARGS args = script_args_new();
    args->value = (void*) pushed;
    return args;
}

void script_args_dispose(SCRIPT_ARGS args) {
    list_dispose_full(args);
}

void script_args_push(SCRIPT_ARGS args, script_arg *pushed) {
    list_push(args, (void*) pushed);
}