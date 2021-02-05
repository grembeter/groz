/**
 * @file cmd_mem.c
 */

#include <groz.h>
#include <lib/cmd.h>
#include <lib/stream.h>
#include "cmd.h"

int cmd_mem(struct cmd_table *cmd, int argc, char **argv);

#define CMD_USAGE  \
    "mem action [args]\n" \
    " show [-1|-2|-4] addr [nmemb]"

int cmd_mem(struct cmd_table *cmd, int argc, char **argv)
{
    if (argc < 2) {
        dbg("usage: %s\n", cmd->usage);
    }

    return 0;
}

OZ_CMDT(mem, CMD_USAGE);
