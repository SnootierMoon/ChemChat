#pragma once

#include <include/typedefs.h>

#define CLIENT_COUNT (32)

void socket_init();
char * socket_ip(client_index);
void socket_clear(client_index);
void socket_delete(client_index);
void socket_print(client_index, const char *, ...);
void socket_println(client_index, const char *, ...);
void socket_loop();

chemdb_id socket_get_chemdb(client_index);
void socket_set_chemdb(client_index, chemdb_id);

