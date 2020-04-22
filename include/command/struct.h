#pragma once

#include <include/typedefs.h>

enum command_status_enum {
    COMMAND_STATUS_INVALID_USAGE = -2,
    COMMAND_STATUS_FAILURE = -1,
    COMMAND_STATUS_NONE = 0,
    COMMAND_STATUS_SUCCESS = 1
};

struct command_struct {
    const char * trigger;
    const char * trig_abbrev;
    int next_count;
    union {
        struct {
            const command ** nexts;
            const char * help_title;
        };
        struct {
            const char * usage;
            const char * params;
            const char * help_brief;
            command_status (*fn)(client_index, string_stream *);
        };
    };
    const char * help_detailed;
};

int command_start(client_index, string_stream *);
int command_eval(client_index, const command *, string_stream *);
int command_invalid();

extern char nullchar;

const command command_root;
const command command_calc;
const command command_chem;

