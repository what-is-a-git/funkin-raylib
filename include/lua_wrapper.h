#ifndef LUA_WRAPPER_H
#define LUA_WRAPPER_H

#include "lua.h"
#include "list.h"

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

typedef lua_State SCRIPT_STATE;
typedef int SCRIPT_ERROR;

SCRIPT_STATE *script_new(void);
void script_dispose(SCRIPT_STATE *state);

SCRIPT_ERROR script_run_string(SCRIPT_STATE *state, const char *source);
SCRIPT_ERROR script_run_file(SCRIPT_STATE *state, const char *path);

SCRIPT_ERROR script_call_empty_void(SCRIPT_STATE *state, const char *func);

SCRIPT_ERROR script_init_args(SCRIPT_STATE *state, const char *func);
SCRIPT_ERROR script_call_args_void(SCRIPT_STATE *state, int arg_count);

void script_push_arg(SCRIPT_STATE *state, script_arg arg);

void script_bind_func(SCRIPT_STATE *state, const char *name, lua_CFunction func, int arg_count);

#endif // !LUA_WRAPPER_H