/**
 * @file cmd.c
 */

#include <groz.h>
#include <lib/cmd.h>
#include <lib/std.h>
#include <lib/stream.h>
#include <cmd.h>

static char cmdline[256];

/* ********** ********** **********
 * local functions
 */

static unsigned read_input(char *input, unsigned input_size)
{
    unsigned pos;

    if ((input == NULL) || (input_size < 2)) {
        return 0;
    }

    input[0] = '\0';
    pos = 1;

    while (1) {
        char c = (char)dbg_getchar();

        if ((c == 0x04) || (c == '\n')) {
            input[pos] = '\0';
            break;
        } else if ((c >= 0x20) && (c < 0x7f)) {
            dbg_putchar(c);

            if (c == ' ') {
                c = '\0';
            }

            if ((pos + 1) < input_size) {
                input[pos++] = c;
            }
        }
    }

    dbg_putchar('\n');

    return pos;
}

static int parse_input(char *input, unsigned len, char *argv[],
                       unsigned argv_size)
{
    int argc;

    if ((len < 2) || (input == NULL) || (*input++ != '\0')) {
        return 0;
    }

    argc = 0;

    while (--len > 0) {
        if ((*(input - 1) == '\0') && (*input != '\0')) {
            argv[argc++] = input;

            if (argc >= argv_size) {
                break;
            }
        }

        ++input;
    }

    return argc;
}

static int exec_input(int argc, char *argv[])
{
    struct cmd_table *cmd;
    int ret = 1;

    if (argc == 0) {
        return 0;
    }

    cmd = &__cmd_tab_start;

    while (cmd < &__cmd_tab_end) {
        if (0 == std_strcmp(argv[0], cmd->name, sizeof(cmd->name))) {
            ret = cmd->exec(cmd, argc, argv);
            break;
        }

        ++cmd;
    }

    return ret;
}

/* ********** ********** **********
 * global functions, see <lib/cmd.h>
 */

void cmd_loop()
{
    const char prompt[] = " oz :: ";
    unsigned cmdlen;
    char *argv[16];
    int argc;
    int ret;

    dbg("\n"
        "   __ _ _ __ ___ ____\n"
        "  / _` | '__/ _ \\_  /\n"
        " | (_| | | | (_) / / \n"
        "  \\__, |_|  \\___/___|\n"
        "   __/ |             \n"
        "  |___/      v0.1    \n"
        "\n:%s", prompt);

    while (1) {
        cmdlen = read_input(cmdline, sizeof(cmdline));
        argc = parse_input(cmdline, cmdlen, argv, sizeof(argv));
        ret = exec_input(argc, argv);
        if (ret != 0) {
            dbg("%d", ret);
        } else {
            dbg(":");
        }
        dbg(prompt);
    }
}

/* ********** ********** **********
 * init function
 */
int cmd_init()
{
    return stream_init();
}
