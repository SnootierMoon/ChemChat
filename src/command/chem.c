#include <include/command/struct.h>
#include <include/csstream.h>
#include <include/socket.h>
#include <include/systems/chem.h>
#include <include/util.h>
#include <stdio.h>
#include <stdlib.h>

command_status print_boiling_point(client_index client, element_id element) {
    double boiling_point;
    chemdb_id chemdb = socket_get_chemdb(client);
    if (chemdb_good(client, chemdb) == -1) {
        return COMMAND_STATUS_FAILURE;
    }
    element_boiling_point(chemdb, element, &boiling_point);
    socket_println(client, "Boiling point of %s: %f K.", element_name(element), boiling_point);
    return COMMAND_STATUS_SUCCESS;
}

command_status print_melting_point(client_index client, element_id element) {
    double melting_point;
    chemdb_id chemdb = socket_get_chemdb(client);
    if (chemdb_good(client, chemdb) == -1) {
        return COMMAND_STATUS_FAILURE;
    }
    element_melting_point(chemdb, element, &melting_point);
    socket_println(client, "Melting point of %s: %f K.", element_name(element), melting_point);
    return COMMAND_STATUS_SUCCESS;
}

command_status print_electron_affinity(client_index client, element_id element) {
    double electron_affinity;
    chemdb_id chemdb = socket_get_chemdb(client);
    if (chemdb_good(client, chemdb) == -1) {
        return COMMAND_STATUS_FAILURE;
    }
    element_electron_affinity(chemdb, element, &electron_affinity);
    socket_println(client, "Electron affinity of %s: %f kJ/mol.", element_name(element), electron_affinity);
    return COMMAND_STATUS_SUCCESS;
}

command_status print_ionization_energy(client_index client, element_id element) {
    double ionization_energy;
    chemdb_id chemdb = socket_get_chemdb(client);
    if (chemdb_good(client, chemdb) == -1) {
        return COMMAND_STATUS_FAILURE;
    }
    element_ionization_energy(chemdb, element, &ionization_energy);
    socket_println(client, "Ionization energy of %s: %f kJ/mol.", element_name(element), ionization_energy);
    return COMMAND_STATUS_SUCCESS;
}

command_status print_electronegativity(client_index client, element_id element) {
    double electronegativity;
    chemdb_id chemdb = socket_get_chemdb(client);
    if (chemdb_good(client, chemdb) == -1) {
        return COMMAND_STATUS_FAILURE;
    }
    element_electronegativity(chemdb, element, &electronegativity);
    socket_println(client, "Electronegativity of %s: %f.", element_name(element), electronegativity);
    return COMMAND_STATUS_SUCCESS;
}

command_status print_molar_mass(client_index client, element_id element) {
    double molar_mass;
    chemdb_id chemdb = socket_get_chemdb(client);
    if (chemdb_good(client, chemdb) == -1) {
        return COMMAND_STATUS_FAILURE;
    }
    element_molar_mass(chemdb, element, &molar_mass);
    socket_println(client, "Molar mass of %s: %f g/mol.", element_name(element), molar_mass);
    return COMMAND_STATUS_SUCCESS;
}

command_status print_statistics(client_index client, element_id element) {
    double val;
    chemdb_id chemdb = socket_get_chemdb(client);
    if (chemdb_good(client, chemdb) == -1) {
        return COMMAND_STATUS_FAILURE;
    }
    element_molar_mass(chemdb, element, &val);
    socket_println(client, "Statistics of %s:", element_name(element));
    socket_println(client, "  Molar mass %f g/mol.", val);
    element_boiling_point(chemdb, element, &val);
    socket_println(client, "  Boiling point: %f K.", val);
    element_melting_point(chemdb, element, &val);
    socket_println(client, "  Melting point: %f K.", val);
    element_electron_affinity(chemdb, element, &val);
    socket_println(client, "  Electron affinity: %f kJ/mol.", val);
    element_ionization_energy(chemdb, element, &val);
    socket_println(client, "  Ionization energy: %f kJ/mol.", val);
    element_electronegativity(chemdb, element, &val);
    socket_println(client, "  Electronegativity: %f.", val);
    return COMMAND_STATUS_SUCCESS;

}


command_status fn_chem_econfig_of(client_index client, string_stream * ss) {
    element_id element;
    switch (sstream_readelement(ss, &element)) {
        case STREAM_STATUS_PARSE_ERROR:
            socket_println(client, "Invalid element.");
            return COMMAND_STATUS_FAILURE;
        case STREAM_STATUS_EOF:
            return COMMAND_STATUS_INVALID_USAGE;
        case STREAM_STATUS_SUCCESS:
            if (element_econfig(client, element) == -1) {
                return COMMAND_STATUS_FAILURE;
            }
            return COMMAND_STATUS_SUCCESS;
    }
    WHACK();
}

command_status fn_chem_econfig_order(client_index client, string_stream * ss) {
    socket_println(client, "Orbital order (least to greatest energy): %s", element_econfig_order());
    return COMMAND_STATUS_SUCCESS;
}

command_status fn_chem_element_list(client_index client, string_stream * ss) {
    for (element_id element = 1; element < element_count(); element++) {
        socket_println(client, "%s (%s), atomic number: %i.", element_name(element), element_symbol(element), element_number(element));
    }
    return COMMAND_STATUS_SUCCESS;
}

command_status fn_chem_element_name(client_index client, string_stream * ss) {
    element_id element;
    switch (sstream_readelement(ss, &element)) {
        case STREAM_STATUS_PARSE_ERROR:
            socket_println(client, "Invalid element.");
            return COMMAND_STATUS_FAILURE;
        case STREAM_STATUS_EOF:
            return COMMAND_STATUS_INVALID_USAGE;
        case STREAM_STATUS_SUCCESS:
            socket_println(client, "Name of %s: %s.", element_name(element), element_name(element));
            return COMMAND_STATUS_SUCCESS;
    }
    WHACK();
}

command_status fn_chem_element_number(client_index client, string_stream * ss) {
    element_id element;
    switch (sstream_readelement(ss, &element)) {
        case STREAM_STATUS_PARSE_ERROR:
            socket_println(client, "Invalid element.");
            return COMMAND_STATUS_FAILURE;
        case STREAM_STATUS_EOF:
            return COMMAND_STATUS_INVALID_USAGE;
        case STREAM_STATUS_SUCCESS:
            socket_println(client, "Atomic number of %s: %i.", element_name(element), element_number(element));
            return COMMAND_STATUS_SUCCESS;
    }
    WHACK();
}

command_status fn_chem_element_symbol(client_index client, string_stream * ss) {
    element_id element;
    switch (sstream_readelement(ss, &element)) {
        case STREAM_STATUS_PARSE_ERROR:
            socket_println(client, "Invalid element.");
            return COMMAND_STATUS_FAILURE;
        case STREAM_STATUS_EOF:
            return COMMAND_STATUS_INVALID_USAGE;
        case STREAM_STATUS_SUCCESS:
            socket_println(client, "Symbol of %s: %s.", element_name(element), element_symbol(element));
            return COMMAND_STATUS_SUCCESS;
    }
    WHACK();
}

command_status fn_chem_element_boilingpoint(client_index client, string_stream * ss) {
    element_id element;
    switch (sstream_readelement(ss, &element)) {
        case STREAM_STATUS_PARSE_ERROR:
            socket_println(client, "Invalid element.");
            return COMMAND_STATUS_FAILURE;
        case STREAM_STATUS_EOF:
            return COMMAND_STATUS_INVALID_USAGE;
        case STREAM_STATUS_SUCCESS:
            return print_boiling_point(client, element);
    }
    WHACK();
}

command_status fn_chem_element_meltingpoint(client_index client, string_stream * ss) {
    element_id element;
    switch (sstream_readelement(ss, &element)) {
        case STREAM_STATUS_PARSE_ERROR:
            socket_println(client, "Invalid element.");
            return COMMAND_STATUS_FAILURE;
        case STREAM_STATUS_EOF:
            return COMMAND_STATUS_INVALID_USAGE;
        case STREAM_STATUS_SUCCESS:
            return print_melting_point(client, element);
    }
    WHACK();
}

command_status fn_chem_element_electronaffinity(client_index client, string_stream * ss) {
    element_id element;
    switch (sstream_readelement(ss, &element)) {
        case STREAM_STATUS_PARSE_ERROR:
            socket_println(client, "Invalid element.");
            return COMMAND_STATUS_FAILURE;
        case STREAM_STATUS_EOF:
            return COMMAND_STATUS_INVALID_USAGE;
        case STREAM_STATUS_SUCCESS:
            return print_electron_affinity(client, element);
    }
    WHACK();
}

command_status fn_chem_element_ionizationenergy(client_index client, string_stream * ss) {
    element_id element;
    switch (sstream_readelement(ss, &element)) {
        case STREAM_STATUS_PARSE_ERROR:
            socket_println(client, "Invalid element.");
            return COMMAND_STATUS_FAILURE;
        case STREAM_STATUS_EOF:
            return COMMAND_STATUS_INVALID_USAGE;
        case STREAM_STATUS_SUCCESS:
            return print_ionization_energy(client, element);
    }
    WHACK();
}

command_status fn_chem_element_electronegativity(client_index client, string_stream * ss) {
    element_id element;
    switch (sstream_readelement(ss, &element)) {
        case STREAM_STATUS_PARSE_ERROR:
            socket_println(client, "Invalid element.");
            return COMMAND_STATUS_FAILURE;
        case STREAM_STATUS_EOF:
            return COMMAND_STATUS_INVALID_USAGE;
        case STREAM_STATUS_SUCCESS:
            return print_electronegativity(client, element);
    }
    return
    WHACK();
}

command_status fn_chem_element_molarmass(client_index client, string_stream * ss) {
    element_id element;
    switch (sstream_readelement(ss, &element)) {
        case STREAM_STATUS_PARSE_ERROR:
            socket_println(client, "Invalid element.");
            return COMMAND_STATUS_FAILURE;
        case STREAM_STATUS_EOF:
            return COMMAND_STATUS_INVALID_USAGE;
        case STREAM_STATUS_SUCCESS:
            return print_molar_mass(client, element);
    }
    WHACK();
}

command_status fn_chem_element_statistics(client_index client, string_stream * ss) {
    element_id element;
    switch (sstream_readelement(ss, &element)) {
        case STREAM_STATUS_PARSE_ERROR:
            socket_println(client, "Invalid element.");
            return COMMAND_STATUS_FAILURE;
        case STREAM_STATUS_EOF:
            return COMMAND_STATUS_INVALID_USAGE;
        case STREAM_STATUS_SUCCESS:
            return print_statistics(client, element);
    }
    return COMMAND_STATUS_FAILURE;
}

command_status fn_chem_element_database_list(client_index client, string_stream * ss) {
    for (chemdb_id chemdb = 1; chemdb < chemdb_count(); chemdb++) {
        socket_println(client, "- %s (%s)", chemdb_name(chemdb), chemdb_description(chemdb));
    }
    return COMMAND_STATUS_SUCCESS;
}

command_status fn_chem_element_database_select(client_index client, string_stream * ss) {
    chemdb_id chemdb;
    switch (sstream_readchemdb(ss, &chemdb)) {
        case STREAM_STATUS_PARSE_ERROR:
            socket_println(client, "Invalid database.");
            return COMMAND_STATUS_FAILURE;
        case STREAM_STATUS_EOF:
            return COMMAND_STATUS_INVALID_USAGE;
        case STREAM_STATUS_SUCCESS:
            socket_set_chemdb(client, chemdb);
            socket_println(client, "Selected database \"%s\".", chemdb_name(chemdb));
            return COMMAND_STATUS_SUCCESS;
    }
    WHACK();
    return COMMAND_STATUS_SUCCESS;
}

command_status fn_chem_element_database_selected(client_index client, string_stream * ss) {
    socket_println(client, "Selected database: \"%s\".", chemdb_name(socket_get_chemdb(client)));
    return COMMAND_STATUS_SUCCESS;
}

const command command_chem_econfig_of = {
    .trigger = "of",
    .trig_abbrev = &nullchar,
    .next_count  = 0,
    .usage = "chem econfig of",
    .params = "[element]",
    .help_brief = "gets electron config of [element]",
    .fn = fn_chem_econfig_of
};

const command command_chem_econfig_order = {
    .trigger = "order",
    .trig_abbrev = &nullchar,
    .next_count  = 0,
    .usage = "chem econfig order",
    .params = &nullchar,
    .help_brief = "gets electron config orbital order (least to greatest energy)",
    .fn = fn_chem_econfig_order
};

const command command_chem_econfig = {
    .trigger = "econfig",
    .trig_abbrev = &nullchar,
    .next_count = 2,
    .nexts = (const command * []) { &command_chem_econfig_of, &command_chem_econfig_order },
    .help_title = "Electron Configuration Commands:"
};

const command command_chem_element_list = {
    .trigger = "list",
    .trig_abbrev = &nullchar,
    .next_count  = 0,
    .usage = "chem element list",
    .params = &nullchar,
    .help_brief = "gets list of elements",
    .fn = fn_chem_element_list
};


const command command_chem_element_name = {
    .trigger = "name",
    .trig_abbrev = &nullchar,
    .next_count  = 0,
    .usage = "chem element name",
    .params = "[element]",
    .help_brief = "gets name of [element]",
    .fn = fn_chem_element_name
};

const command command_chem_element_number = {
    .trigger = "number",
    .trig_abbrev = &nullchar,
    .next_count  = 0,
    .usage = "chem element number",
    .params = "[element]",
    .help_brief = "gets atomic number of [element]",
    .fn = fn_chem_element_number
};

const command command_chem_element_symbol = {
    .trigger = "symbol",
    .trig_abbrev = &nullchar,
    .next_count  = 0,
    .usage = "chem element symbol",
    .params = "[element]",
    .help_brief = "gets symbol of [element]",
    .fn = fn_chem_element_symbol
};

const command command_chem_element_boilingpoint = {
    .trigger = "boiling_point",
    .trig_abbrev = &nullchar,
    .next_count  = 0,
    .usage = "chem element boiling_point",
    .params = &nullchar,
    .help_brief = "gets boiling point of [element]",
    .fn = fn_chem_element_boilingpoint
};

const command command_chem_element_meltingpoint = {
    .trigger = "melting_point",
    .trig_abbrev = &nullchar,
    .next_count  = 0,
    .usage = "chem element melting_point",
    .params = &nullchar,
    .help_brief = "gets melting point of [element]",
    .fn = fn_chem_element_meltingpoint
};

const command command_chem_element_electronaffinity = {
    .trigger = "electron_affinity",
    .trig_abbrev = &nullchar,
    .next_count  = 0,
    .usage = "chem element electron_affinity",
    .params = &nullchar,
    .help_brief = "gets electron affinity of [element]",
    .fn = fn_chem_element_electronaffinity
};

const command command_chem_element_ionizationenergy = {
    .trigger = "ionization_energy",
    .trig_abbrev = &nullchar,
    .next_count  = 0,
    .usage = "chem element ionization_energy",
    .params = &nullchar,
    .help_brief = "gets ionization energy of [element]",
    .fn = fn_chem_element_ionizationenergy
};

const command command_chem_element_electronegativity = {
    .trigger = "electronegativity",
    .trig_abbrev = &nullchar,
    .next_count  = 0,
    .usage = "chem element electronegativity",
    .params = &nullchar,
    .help_brief = "gets electronegativity of [element]",
    .fn = fn_chem_element_electronegativity
};

const command command_chem_element_molarmass = {
    .trigger = "molar_mass",
    .trig_abbrev = &nullchar,
    .next_count  = 0,
    .usage = "chem element molar_mass",
    .params = "[element]",
    .help_brief = "gets molar mass of [element]",
    .fn = fn_chem_element_molarmass
};

const command command_chem_element_statistics = {
    .trigger = "statistics",
    .trig_abbrev = &nullchar,
    .next_count = 0,
    .usage = "chem element statistics",
    .params = "[element]",
    .help_brief = "gets full statistics of [element]",
    .fn = fn_chem_element_statistics
};

const command command_chem_element_database_list = {
    .trigger = "list",
    .trig_abbrev = &nullchar,
    .next_count = 0,
    .usage = "chem element database list",
    .params = &nullchar,
    .help_brief = "lists all databases",
    .fn = fn_chem_element_database_list
};

const command command_chem_element_database_select = {
    .trigger = "select",
    .trig_abbrev = &nullchar,
    .next_count = 0,
    .usage = "chem element database select",
    .params = "[database]",
    .help_brief = "selects [database] for element data commands, deselects databases if [database] is \"none\"",
    .fn = fn_chem_element_database_select
};

const command command_chem_element_database_selected = {
    .trigger = "selected",
    .trig_abbrev = &nullchar,
    .next_count = 0,
    .usage = "chem element database selected",
    .params = "",
    .help_brief = "gets selected chemdb",
    .fn = fn_chem_element_database_selected
};

const command command_chem_element_database = {
    .trigger = "database",
    .trig_abbrev = &nullchar,
    .next_count = 3,
    .nexts = (const command * []) { &command_chem_element_database_list, &command_chem_element_database_select, &command_chem_element_database_selected },
    .help_title = "Element Database Commands:"
};

const command command_chem_element = {
    .trigger = "element",
    .trig_abbrev = &nullchar,
    .next_count = 12,
    .nexts = (const command * []) {
        &command_chem_element_list,
        &command_chem_element_name,
        &command_chem_element_number,
        &command_chem_element_symbol,
        &command_chem_element_boilingpoint,
        &command_chem_element_meltingpoint,
        &command_chem_element_electronaffinity,
        &command_chem_element_ionizationenergy,
        &command_chem_element_electronegativity,
        &command_chem_element_molarmass,
        &command_chem_element_statistics,
        &command_chem_element_database
    },
    .help_title = "Element Commands:"
};

const command command_chem = {
    .trigger = "chem",
    .trig_abbrev = &nullchar,
    .next_count = 2,
    .nexts = (const command * []) { &command_chem_econfig, &command_chem_element },
    .help_title = "Chemistry Commands:",
};

