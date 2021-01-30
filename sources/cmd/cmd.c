/**
 * @file cmd.c
 */

#include <groz.h>
#include <lib/cmd.h>
#include <lib/stream.h>

static char cmdline[256];

static void read_input(char *buf, size_t buf_size)
{
    size_t pos;

    if ((buf == NULL) || (buf_size == 0)) {
        return;
    }

    pos = 0;

    while (1) {
        char c = (char)dbg_getchar();

        if ((c == 0x04) || (c == '\n')) {
            buf[pos] = '\0';
            break;
        } else if ((c >= 0x20) && (c < 0x7f)) {
            dbg_putchar(c);

            if (c == ' ') {
                c = '\0';
            }

            if ((pos + 1) < buf_size) {
                buf[pos++] = c;
            }
        }
    }

    dbg_putchar('\n');
}

void cmd_init(void)
{
    stream_init();
}

void cmd_loop(void)
{
    const char prompt[] = " oz :: ";

    dbg("\n"
        "   __ _ _ __ ___ ____\n"
        "  / _` | '__/ _ \\_  /\n"
        " | (_| | | | (_) / / \n"
        "  \\__, |_|  \\___/___|\n"
        "   __/ |             \n"
        "  |___/      v0.1    \n"
        "\n");

    dbg(prompt);

    while (1) {
        read_input(cmdline, sizeof(cmdline));
        dbg("run %s\n", cmdline);
        dbg(prompt);
    }
}
