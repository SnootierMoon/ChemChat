#include <arpa/inet.h>
#include <include/typedefs.h>
#include <ctype.h>
#include <include/command/struct.h>
#include <include/socket.h>
#include <poll.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define POLL_COUNT ((CLIENT_COUNT) + 1)
#define ADDRESS_FORMAT(address) inet_ntoa(address.sin_addr), ntohs(address.sin_port)
#define STORAGE_BUFFER_LENGTH (200)
#define USERNAME_LENGTH (20)
#define LISTENER_PORT (42069)
#define LISTEN_QUEUE (5)

struct storage_buffer {
    char data[STORAGE_BUFFER_LENGTH];
    int offset;
};

struct pollfd poll_fds[POLL_COUNT + 1];
struct sockaddr_in poll_addrs[POLL_COUNT + 1];
struct pollfd * const listener_fd = poll_fds;
struct sockaddr_in * const listener_addr = poll_addrs;
struct pollfd * const client_fds = poll_fds + 1;
struct sockaddr_in * const client_addrs = poll_addrs + 1;
struct storage_buffer client_buffers[CLIENT_COUNT];
client_index client_ids[CLIENT_COUNT];
chemdb_id client_chemdbs[CLIENT_COUNT];

socklen_t address_length = sizeof(struct sockaddr_in);

void socket_init() {
    printf("Initializing socket listener...\n");
    listener_fd->events = POLLIN;
    listener_fd->revents = 0;
    listener_addr->sin_addr.s_addr = INADDR_ANY;
    listener_addr->sin_family = AF_INET;
    listener_addr->sin_port = htons(LISTENER_PORT);
    memset(listener_addr->sin_zero, 0, sizeof(listener_addr->sin_zero));
    for (client_index client = 0; client < CLIENT_COUNT; client++) {
        socket_clear(client);
    }
    if ((listener_fd->fd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket()");
        exit(EXIT_FAILURE);
    } else if (setsockopt(listener_fd->fd, SOL_SOCKET, SO_REUSEADDR, &(int){ 1 }, sizeof(int)) < 0) {
        perror("setsockopt(SOL_SOCKET, SO_REUSEADDR)");
        exit(EXIT_FAILURE);
    } else if (bind(listener_fd->fd, (struct sockaddr *)listener_addr, address_length) < 0) {
        perror("bind()");
        exit(EXIT_FAILURE);
    } else if (listen(listener_fd->fd, LISTEN_QUEUE) < 0) {
        perror("listen()");
        exit(EXIT_FAILURE);
    }
}

char * socket_ip(client_index client) {
    return inet_ntoa(client_addrs[client].sin_addr);
}

void socket_clear(client_index client) {
    client_fds[client].fd = -1;
    client_fds[client].events = 0;
    client_fds[client].revents = 0;
    client_ids[client] = -1;
    memset(client_addrs + client, 0, address_length);
    memset(client_buffers + client, 0, sizeof(struct storage_buffer));
    client_chemdbs[client] = 0;
}

void socket_delete(client_index client) {
    close(client_fds[client].fd);
    socket_clear(client);
}

void socket_print(client_index client, const char * format, ...) {
    va_list args;
    va_start(args, format);
    vdprintf(client_fds[client].fd, format, args);
    va_end(args);
}

void socket_println(client_index client, const char * format, ...) {
    va_list args;
    va_start(args, format);
    vdprintf(client_fds[client].fd, format, args);
    dprintf(client_fds[client].fd, "\r\n");
    va_end(args);
}

void socket_loop() {
    if (poll(poll_fds, POLL_COUNT, -1) < 0) {
        perror("poll()");
        exit(EXIT_FAILURE);
    }
    if (listener_fd->revents & POLLIN) {
        client_index client;
        for (client = 0; client < CLIENT_COUNT; client++) {
            if (client_fds[client].fd < 0) {
                break;
            }
        }
        if ((client_fds[client].fd = accept(listener_fd->fd, (struct sockaddr *)(client_addrs + client), &address_length)) < 0) {
            perror("accept()");
            exit(EXIT_FAILURE);
        } else if (client == CLIENT_COUNT) {
            printf("%s:%i- Attempted to join, but couldn't due to room overflow.\n", ADDRESS_FORMAT(client_addrs[client]));
            socket_println(client, "You cannot join due to room overflow.");
            socket_delete(client);
        } else {
            printf("%s:%i- Connected as %i\n", ADDRESS_FORMAT(client_addrs[client]), client);
            socket_println(client, "Welcome to the ChemDeal Server (preAlpha v0.0).");
            client_fds[client].events = POLLIN | POLLHUP;
        }
    }
    for (client_index client = 0; client < CLIENT_COUNT; client++) {
        if (client_fds[client].revents & POLLHUP) {
            printf("%s:%i- Disconnected (POLLHUP).\n", ADDRESS_FORMAT(client_addrs[client]));
            socket_delete(client);
        } else if (client_fds[client].revents & POLLIN) {
            static char recv_buffer[STORAGE_BUFFER_LENGTH];
            ssize_t bytes_read = 0;
            ssize_t recv_length = read(client_fds[client].fd, recv_buffer, STORAGE_BUFFER_LENGTH - 1);
            bytes_read += recv_length;
            if (bytes_read <= 0) {
                printf("%s:%i- Disconnected.\n", ADDRESS_FORMAT(client_addrs[client]));
                socket_delete(client);
            } else if (recv_length <= 0) {
            } else {
                for (int recv_client = 0; recv_client < recv_length; recv_client++) {
                    if (client_buffers[client].offset == -1) {
                        if (!isprint(recv_buffer[recv_client])) {
                            client_buffers[client].offset = 0;
                        }
                    } else {
                        if (client_buffers[client].offset > (STORAGE_BUFFER_LENGTH - 2)) {
                            client_buffers[client].offset = -1;
                            socket_println(client, "Input is too long, ignoring last command...");
                        } else if (isprint(recv_buffer[recv_client])) {
                            client_buffers[client].data[client_buffers[client].offset] = recv_buffer[recv_client];
                            client_buffers[client].offset++;
                        } else if ((recv_buffer[recv_client] == 127) || (recv_buffer[recv_client] == 8)) {
                            if (client_buffers[client].offset > 0) client_buffers[client].offset--;
                        } else if (client_buffers[client].offset != 0) {
                            client_buffers[client].data[client_buffers[client].offset] = 0;
                            printf("%s:%i- got data - %s.\n", ADDRESS_FORMAT(client_addrs[client]), client_buffers[client].data);
                            string_stream input = client_buffers[client].data;
                            command_start(client, &input);
                            client_buffers[client].offset = 0;
                        }
                    }
                }
            }
        }
    }
}

chemdb_id socket_get_chemdb(client_index client) {
    return client_chemdbs[client];
}

void socket_set_chemdb(client_index client, chemdb_id chemdb) {
    client_chemdbs[client] = chemdb;
}

