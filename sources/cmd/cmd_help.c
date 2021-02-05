/**
 * @file cmd.c
 */

#include <groz.h>
#include <lib/cmd.h>
#include <lib/stream.h>
#include "cmd.h"

int cmd_help(struct cmd_table *cmd, int argc, char **argv);

#define CMD_USAGE  \
    "help [cmd]\n" \
    " give a short usage message"

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
            int i = 0;
            ret = 0;
            do {
                if (argv[1][i] != cmd_tab->name[i]) {
                    ret = 1;
                    break;
                }
            } while (argv[1][i++] != '\0');

            if (ret == 0) {
                dbg("usage: %s\n", cmd_tab->usage);
                break;
            }

            ++cmd_tab;
            ret = 1;
        }
    }

    return ret;
}

OZ_CMDT(help, CMD_USAGE);
