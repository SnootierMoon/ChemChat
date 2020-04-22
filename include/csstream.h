#pragma once

#include <include/typedefs.h>

enum stream_status_enum {
    STREAM_STATUS_PARSE_ERROR = -2,
    STREAM_STATUS_EOF = -1,
    STREAM_STATUS_SUCCESS = 1,
};

int parse_unsigned(char *, unsigned *);
int parse_float(char * word, float * ret);
int parse_element(char *, element_id *);
int parse_chemdb(char *, chemdb_id *);

stream_status sstream_readword(string_stream *, char **);
stream_status sstream_readunsigned(string_stream *, unsigned *);
stream_status sstream_readfloat(string_stream *, float *);
stream_status sstream_readelement(string_stream *, element_id *);
stream_status sstream_readchemdb(string_stream *, chemdb_id *);
stream_status sstream_readeof(string_stream *, char **);

stream_status sstream_hasdata(string_stream *);

