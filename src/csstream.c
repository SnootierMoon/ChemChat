#include <ctype.h>
#include <stdlib.h>
#include <include/csstream.h>
#include <include/systems/chem.h>
#include <string.h>

int parse_unsigned(char * word, unsigned * ret) {
    unsigned i;
    char * endptr;
    i = strtoul(word, &endptr, 10);
    if (*endptr) {
        return -1;
    }
    *ret = i;
    return 0;
}

int parse_float(char * word, float * ret) {
    float i;
    char * endptr;
    i = strtof(word, &endptr);
    if (*endptr) {
        return -1;
    }
    *ret = i;
    return 0;
}


int parse_element(char * word, element_id * element) {
    if (parse_unsigned(word, element) != -1) {
        return 0;
    } else {
        for (element_id i = 0; i < element_count(); i++) {
            if ((!strcasecmp(word, element_name(i))) || (!strcasecmp(word, element_symbol(i)))) {
                *element = i;
                return 0;
            }
        }
    }
    return -1;
}

int parse_chemdb(char * word, chemdb_id * chemdb) {
    for (chemdb_id i = 0; i < chemdb_count(); i++) {
        if (!strcasecmp(word, chemdb_name(i))) {
            *chemdb = i;
            return 0;
        }
    }
    return -1;
}

int sstream_readword(string_stream * ss, char ** ret) {
    if (!sstream_hasdata(ss)) {
        return STREAM_STATUS_EOF;
    }
    while (!isgraph(*(*ss)) && *(*ss)) {
        (*ss)++;
    }
    if (!sstream_hasdata(ss)) {
        return STREAM_STATUS_EOF;
    }
    (*ret) = (*ss);
    while (isgraph(*(*ss))) {
        (*ss)++;
    }
    if (*(*ss)) {
        *(*ss) = 0;
        (*ss)++;
    }
    while (!isgraph(*(*ss)) && *(*ss)) {
        (*ss)++;
    }
    return STREAM_STATUS_SUCCESS;
}

int sstream_readunsigned(string_stream * ss, unsigned * ret) {
    char * word;
    if (sstream_readword(ss, &word) == STREAM_STATUS_EOF) {
        return STREAM_STATUS_EOF;
    }
    if (parse_unsigned(word, ret) == -1) {
        return STREAM_STATUS_PARSE_ERROR;
    }
    return STREAM_STATUS_SUCCESS;
}

int sstream_readfloat(string_stream * ss, float * ret) {
    char * word;
    if (sstream_readword(ss, &word) == STREAM_STATUS_EOF) {
        return STREAM_STATUS_EOF;
    }
    if (parse_float(word, ret) == -1) {
        return STREAM_STATUS_PARSE_ERROR;
    }
    return STREAM_STATUS_SUCCESS;
}

int sstream_readelement(string_stream * ss, element_id * ret) {
    char * word;
    if (sstream_readword(ss, &word) == STREAM_STATUS_EOF) {
        return STREAM_STATUS_EOF;
    }
    if (parse_element(word, ret) == -1) {
        return STREAM_STATUS_PARSE_ERROR;
    }
    return STREAM_STATUS_SUCCESS;
}

stream_status sstream_readchemdb(string_stream * ss, chemdb_id * ret) {
    char * word;
    if (sstream_readword(ss, &word) == STREAM_STATUS_EOF) {
        return STREAM_STATUS_EOF;
    }
    if (parse_chemdb(word, ret) == -1) {
        return STREAM_STATUS_PARSE_ERROR;
    }
    return STREAM_STATUS_SUCCESS;
}

int sstream_readeof(string_stream * ss, char ** ret) {
    if (!sstream_hasdata(ss)) {
        return STREAM_STATUS_EOF;
    }
    (*ret) = (*ss);
    (*ss) += strlen(*ss);
    return STREAM_STATUS_SUCCESS;
}

int sstream_hasdata(string_stream * ss) {
    return (ss && (*ss) && *(*ss));
}
