#include <include/socket.h>

int main() {
    socket_init();
    while (1) {
        socket_loop();
    }
}

