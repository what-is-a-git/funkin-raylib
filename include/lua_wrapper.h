#ifndef LUA_WRAPPER_H
#define LUA_WRAPPER_H

#include "lua.h"
#include "lauxlib.h"

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

void script_call_empty_void(SCRIPT_STATE *state, const char *func);

SCRIPT_ERROR script_init_args(SCRIPT_STATE *state, const char *func);
void script_call_args_void(SCRIPT_STATE *state, int arg_count);

void script_handle_errors(SCRIPT_STATE *state, SCRIPT_ERROR error);

// IDEA: replace this with null terminated array of script_arg ?
void script_push_arg(SCRIPT_STATE *state, script_arg arg);

void script_bind_func(SCRIPT_STATE *state, const char *name, lua_CFunction func, int arg_count);

void script_table_new(SCRIPT_STATE *state, int size);

void script_table_set_field_int(SCRIPT_STATE *state, const char *field, lua_Integer value, int index);
lua_Integer script_table_get_field_int(SCRIPT_STATE *state, int table_index, const char *field);
lua_Integer script_table_get_int(SCRIPT_STATE *state, int table_index, int item_index);

void script_table_set_field_number(SCRIPT_STATE *state, const char *field, lua_Number value, int index);
lua_Number script_table_get_field_number(SCRIPT_STATE *state, int table_index, const char *field);
lua_Number script_table_get_number(SCRIPT_STATE *state, int table_index, int item_index);

void script_table_set_field_bool(SCRIPT_STATE *state, const char *field, int value, int index);
int script_table_get_field_bool(SCRIPT_STATE *state, int table_index, const char *field);

#endif // !LUA_WRAPPER_H