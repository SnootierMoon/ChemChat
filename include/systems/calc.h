#pragma once

#include <include/typedefs.h>

typedef float calc_value;

enum calc_status_enum {
    CALC_STATUS_FAILURE,
    CALC_STATUS_SUCCESS
};

unsigned execute(client_index, string_stream *, calc_value *);
