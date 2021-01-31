/**
 * @file cmd.c
 */

#include <groz.h>
#include <lib/cmd.h>
#include <lib/stream.h>

static char cmdline[256];

struct cmd_table {
    const char name[16];
    const char usage[256];
    int (*exe)(struct cmd_table *, int, char **);
};

int cmd_help(struct cmd_table *cmd, int argc, char **argv);

int cmd_help(struct cmd_table *cmd, int argc, char **argv)
{
    dbg("usage: %s\n", cmd->usage);
    return 0;
}

struct cmd_table cmdt_help = {
    "help",
    "help [cmd]\n"
    " show 'cmd' usage message",
    cmd_help
};

static size_t read_input(char *input, size_t input_size)
{
    size_t pos = 0;

    if ((input == NULL) || (input_size < 2)) {
        return 0;
    }

    input[pos++] = '\0';

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

int parse_input(char *input, size_t len, char *argv[], size_t argv_size);
int exec_input(int argc, char *argv[]);

int parse_input(char *input, size_t len, char *argv[], size_t argv_size)
{
    int argc = 0;

    if ((len < 2) || (input == NULL) || (*input++ != '\0')) {
        return 0;
    }

    while (--len > 0) {
        if ((*(input - 1) == '\0') && (*input != '\0')) {
            argv[argc++] = input;
        }

        ++input;
    }

    return argc;
}

int exec_input(int argc, char *argv[])
{
    int ret = 0;
    struct cmd_table *cmd = &cmdt_help;
    int i;

    for (i = 0; i < argc; ++i) {
        dbg("%d: %s\n", i, argv[i]);
    }

    if (argc == 0) {
        return ret;
    }

    i = 0;
    do {
        if (argv[0][i] != cmd->name[i]) {
            ret = 1;
            break;
        }
    } while (argv[0][i++] != '\0');

    if (ret == 0) {
        ret = cmd->exe(cmd, argc, argv);
    }

    return ret;
}

void cmd_init(void)
{
    stream_init();
}

void cmd_loop(void)
{
    const char prompt[] = " oz :: ";
    size_t cmdlen;
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
        "\n");

    dbg(prompt);

    while (1) {
        cmdlen = read_input(cmdline, sizeof(cmdline));
        argc = parse_input(cmdline, cmdlen, argv, sizeof(argv));
        ret = exec_input(argc, argv);
        if (ret != 0) {
            dbg("%d ", ret);
        }
        dbg(prompt);
    }
}
