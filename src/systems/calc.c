#include <include/csstream.h>
#include <include/systems/chem.h>
#include <include/socket.h>
#include <include/systems/calc.h>
#include <string.h>
#include <stdio.h>

typedef float calc_value; // can be a struct later

calc_status execute(client_index client, string_stream * ss, calc_value * v) {
    char * word;
    if (sstream_readword(ss, &word) == STREAM_STATUS_EOF) {
        return CALC_STATUS_FAILURE;
    } if (parse_float(word, v) != -1) {
        socket_print(client, "%f", *v);
        return CALC_STATUS_SUCCESS;
    } else if (!strcasecmp(word, "add")) {
        calc_value v1, v2;
        socket_print(client, "(");
        if (execute(client, ss, &v1) == CALC_STATUS_FAILURE) {
            return CALC_STATUS_FAILURE;
        }
        socket_print(client, " + ");
        if (execute(client, ss, &v2) == CALC_STATUS_FAILURE) {
            return CALC_STATUS_FAILURE;
        }
        socket_print(client, ")");
        *v = v1 + v2;
        return CALC_STATUS_SUCCESS;
    } else if (!strcasecmp(word, "sub")) {
        calc_value v1, v2;
        socket_print(client, "(");
        if (execute(client, ss, &v1) == CALC_STATUS_FAILURE) {
            return CALC_STATUS_FAILURE;
        }
        socket_print(client, " - ");
        if (execute(client, ss, &v2) == CALC_STATUS_FAILURE) {
            return CALC_STATUS_FAILURE;
        }
        socket_print(client, ")");
        *v = v1 - v2;
        return CALC_STATUS_SUCCESS;
    } else if (!strcasecmp(word, "mult")) {
        calc_value v1, v2;
        socket_print(client, "(");
        if (execute(client, ss, &v1) == CALC_STATUS_FAILURE) {
            return CALC_STATUS_FAILURE;
        }
        socket_print(client, " * ");
        if (execute(client, ss, &v2) == CALC_STATUS_FAILURE) {
            return CALC_STATUS_FAILURE;
        }
        socket_print(client, ")");
        *v = v1 * v2;
        return CALC_STATUS_SUCCESS;
    } else if (!strcasecmp(word, "div")) {
        calc_value v1, v2;
        socket_print(client, "(");
        if (execute(client, ss, &v1) == CALC_STATUS_FAILURE) {
            return CALC_STATUS_FAILURE;
        }
        socket_print(client, " / ");
        if (execute(client, ss, &v2) == CALC_STATUS_FAILURE) {
            return CALC_STATUS_FAILURE;
        }
        socket_print(client, ")");
        *v = v1 / v2;
        return CALC_STATUS_SUCCESS;
    } else if (!strcasecmp(word, "mm")) {
        element_id element;
        socket_print(client, "(molar mass of ");
        if (sstream_readelement(ss, &element) != STREAM_STATUS_SUCCESS) {
            return CALC_STATUS_FAILURE;
        }
        socket_print(client, "%s)", element_name(element));
        double molar_mass;
        chemdb_id chemdb = socket_get_chemdb(client);
        if (chemdb_good(client, chemdb) == -1) {
            return CALC_STATUS_FAILURE;
        }

        element_molar_mass(chemdb, element, &molar_mass);
        *v = molar_mass;
        return CALC_STATUS_SUCCESS;
    }

    return CALC_STATUS_FAILURE;
}


