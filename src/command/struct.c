#include <include/command/struct.h>
#include <include/socket.h>
#include <include/csstream.h>
#include <string.h>

char nullchar = 0;

int command_start(client_index client, string_stream * ss) {
    return command_eval(client, &command_root, ss);
}

int command_eval(client_index client, const command * cmd, string_stream * ss) {
    if (cmd->next_count) {
        char * word;
        if (sstream_readword(ss, &word) != STREAM_STATUS_EOF) {
            for (int i = 0; i < cmd->next_count; i++) {
                if (!strcasecmp(word, cmd->nexts[i]->trigger) || (*cmd->nexts[i]->trig_abbrev && !strcasecmp(word, cmd->nexts[i]->trig_abbrev))) {
                    return command_eval(client, cmd->nexts[i], ss);
                }
            }
        } else if (!cmd->trigger) {
            return COMMAND_STATUS_NONE;
        }
    } else {
        int ret = cmd->fn(client, ss);
        if (ret == COMMAND_STATUS_INVALID_USAGE) {
            socket_println(client, "Usage: %s%s%s", cmd->usage, (cmd->params == &nullchar) ? &nullchar: " ", cmd->params);
            return COMMAND_STATUS_FAILURE;
        }
        return ret;
    }
    return command_invalid(client);
}

int command_invalid(client_index client) {
    socket_println(client, "Invalid command.");
    socket_println(client, "Type 'help' for a list of valid commands.");
    return COMMAND_STATUS_FAILURE;
}

