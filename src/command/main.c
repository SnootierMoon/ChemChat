#include <include/command/struct.h>
#include <include/socket.h>
#include <include/csstream.h>
#include <string.h>

command_status help_eval(client_index client, const command * cmd, string_stream * ss, int indent) {
    char * word;
    if (sstream_readword(ss, &word) != STREAM_STATUS_EOF) {
        if (cmd->next_count) {
            for (int i = 0; i < cmd->next_count; i++) {
                if (!strcasecmp(word, cmd->nexts[i]->trigger) || (*cmd->nexts[i]->trig_abbrev && !strcasecmp(word, cmd->nexts[i]->trig_abbrev))) {
                    return help_eval(client, cmd->nexts[i], ss, indent);
                }
            }
        }
    } else {
        if (cmd->next_count) {
            if (cmd->help_title) {
                socket_println(client, "%*c%s", 2 * indent, ' ', cmd->help_title);
            }
            for (int i = 0; i < cmd->next_count; i++) {
                help_eval(client, cmd->nexts[i], ss, indent + 2);
            }
        } else {
            if (cmd->help_brief) {
                socket_println(client, "%*c- %s%s%s - %s", 2 * indent, ' ', cmd->usage, (cmd->params == &nullchar) ? &nullchar : " ", cmd->params, cmd->help_brief);
            }
        }
        return COMMAND_STATUS_SUCCESS;
    }
    return command_invalid();
}

command_status fn_help(client_index client, string_stream * ss) {
    socket_println(client, "");
    return help_eval(client, &command_root, ss, 0);
}

const command command_help = {
    .trigger = "help",
    .trig_abbrev = &nullchar,
    .next_count = 0,
    .usage = "help",
    .params = "[command]",
    .help_brief = "explains [command]'s usage, or, if no command is provided, briefly explains every command's usage",
    .fn = fn_help
};

const command command_root = {
    .trigger = &nullchar,
    .trig_abbrev = &nullchar,
    .next_count = 3,
    .nexts = (const command * []) { &command_help, &command_calc, &command_chem },
    .help_title = "Commands:"
};

