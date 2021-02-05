/**
 * @file cmd_version.c
 */

#include <groz.h>
#include <lib/cmd.h>
#include <lib/stream.h>
#include "cmd.h"

int cmd_version(struct cmd_table *cmd, int argc, char **argv)
{
    dbg("usage: %s\n", cmd->usage);
    return 0;
}

OZ_CMDT(version, "version", cmd_version);
