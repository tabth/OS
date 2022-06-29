#include <stdint.h>
#include <stddef.h>

#include "include/limine.h"

static volatile struct limine_terminal_request terminal_request = {
    .id = LIMINE_TERMINAL_REQUEST,
    .revision = 0
};

static void done(void) {
    for (;;) {
        __asm__("hlt");
    }
}

// kernel entry
void _start(void) {
    if (terminal_request.response == NULL || terminal_request.response->terminal_count < 1) {
        done();
    }

    struct limine_terminal *terminal = terminal_request.response->terminals[0];
    terminal_request.response->write(terminal, "Hello World", 11);

    done();
}