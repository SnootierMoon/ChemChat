#include <include/command/struct.h>
#include <include/socket.h>
#include <include/systems/calc.h>

command_status fn_calc_help(client_index client, string_stream * ss) {
    return COMMAND_STATUS_FAILURE;
}

command_status fn_calc_exec(client_index client, string_stream * ss) {
    float f;
    if (execute(client, ss, &f) == CALC_STATUS_FAILURE) {
        return COMMAND_STATUS_FAILURE;
    }
    socket_println(client, " = %f\n", f);
    return COMMAND_STATUS_SUCCESS;
}

const command command_calc_help = {
    .trigger = "help",
    .trig_abbrev = &nullchar,
    .next_count = 0,
    .usage = "calc help",
    .params = &nullchar,
    .help_brief = "learn calc script",
    .fn = fn_calc_help
};

const command command_calc_exec = {
    .trigger = "exec",
    .trig_abbrev = &nullchar,
    .next_count = 0,
    .usage = "calc exec [calculator script]",
    .params = &nullchar,
    .help_brief = "executes [calculator script]",
    .fn = fn_calc_exec
};

const command command_calc = {
    .trigger = "calc",
    .trig_abbrev = &nullchar,
    .next_count = 2,
    .nexts = (const command * []) { &command_calc_help, &command_calc_exec },
    .help_title = "Calculator Commands:"
};

