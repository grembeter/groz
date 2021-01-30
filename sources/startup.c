/**
 * @file startup.c
 */

#include <groz.h>
#include <lib/stream.h>


void __oz_low_init(void);
void __oz_entry(void);

void __oz_low_init()
{
}

static void io_readline(char *buf, size_t buf_size)
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

            if (pos < buf_size) {
                buf[pos++] = c;
            }
        }
    }

    dbg_putchar('\n');
}

size_t len(char *s);

size_t len(char *s)
{
    size_t l = 0;

    if (s == NULL) {
        return 0;
    }

    while (*s++ != '\0') {
        ++l;
    }

    return l;
}

void __oz_entry()
{
    const char prompt[] = " oz :: ";
    char cmdline[256];

    stream_init();

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
        io_readline(cmdline, sizeof(cmdline));

        dbg("you entered %d chars: %s\n", (int)len(cmdline), cmdline);

        dbg(prompt);
    }
}
