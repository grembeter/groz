/**
 * @file cmd_help.c
 */

#include <groz.h>
#include <lib/cmd.h>
#include <lib/stream.h>
#include "cmd.h"

#define CMD_USAGE  \
    "help [cmd]\n" \
    " give a short usage message"

int cmd_help(struct cmd_table *cmd, int argc, char **argv);

int cmd_help(struct cmd_table *cmd, int argc, char **argv)
{
    struct cmd_table *cmd_tab = &__cmd_tab_start;
    int ret = 0;

    if (argc == 1) {
        while (cmd_tab < &__cmd_tab_end) {
            dbg("%s\n", cmd_tab->name);
            ++cmd_tab;
        }

        ret = 0;
    } else {
        ret = 1;

        while (cmd_tab < &__cmd_tab_end) {
            if (0 == std_strcmp(argv[1], cmd_tab->name, sizeof(cmd_tab->name))) {
                dbg("usage: %s\n", cmd_tab->usage);
                ret = 0;
                break;
            }

            ++cmd_tab;
            ret = 1;
        }
    }

    return ret;
}

OZ_CMDT(help, CMD_USAGE);
