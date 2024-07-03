#ifndef LUA_WRAPPER_H
#define LUA_WRAPPER_H

#include "lua.h"
#include "list.h"

typedef struct {
    lua_State *raw_state;
} script_state;

typedef enum {
    NIL,
    BOOL,
    INT,
    NUMBER,
    STRING
} SCRIPT_ARG_TYPE;

typedef struct {
    SCRIPT_ARG_TYPE type;
    void *value;
} script_arg;

typedef int SCRIPT_ERROR;
typedef list_node* SCRIPT_ARGS;

script_state *script_new(void);
void script_dispose(script_state *state);

SCRIPT_ERROR script_run_string(script_state *state, const char *source);
SCRIPT_ERROR script_run_file(script_state *state, const char *path);
SCRIPT_ERROR script_call_empty_void(script_state *state, const char *func);
SCRIPT_ERROR script_call_args_void(script_state *state, const char *func, SCRIPT_ARGS args);
void _script_push_arg(script_state *state, script_arg *arg);

script_arg *script_arg_new(SCRIPT_ARG_TYPE type, void *value);
void script_arg_dispose(script_arg *arg);

SCRIPT_ARGS script_args_new(void);
SCRIPT_ARGS script_args_init(script_arg *pushed);
void script_args_dispose(SCRIPT_ARGS node);
void script_args_push(SCRIPT_ARGS args, script_arg *pushed);

#endif // !LUA_WRAPPER_H