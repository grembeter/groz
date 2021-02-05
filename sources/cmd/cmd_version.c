/**
 * @file cmd_version.c
 */

#include <groz.h>
#include <version.h>
#include <lib/cmd.h>
#include <lib/stream.h>
#include "cmd.h"

int cmd_version(struct cmd_table *cmd, int argc, char **argv);

#define CMD_USAGE  \
    "version\n" \
    " print firmware version"

int cmd_version(struct cmd_table *cmd, int argc, char **argv)
{
    dbg("%s\n", VERSION);

    return 0;
}

OZ_CMDT(version, CMD_USAGE);
