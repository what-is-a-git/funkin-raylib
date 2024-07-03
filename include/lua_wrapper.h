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

script_state *script_new(void);
void script_dispose(script_state *state);

SCRIPT_ERROR script_run_string(script_state *state, const char *source);
SCRIPT_ERROR script_run_file(script_state *state, const char *path);

SCRIPT_ERROR script_call_empty_void(script_state *state, const char *func);
SCRIPT_ERROR script_call_args_void(script_state *state, const char *func, int arg_count);

void script_push_arg(script_state *state, script_arg *arg);

#endif // !LUA_WRAPPER_H