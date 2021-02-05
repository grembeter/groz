/**
 * @file cmd.h
 */

#pragma once

extern struct cmd_table __cmd_tab_start;
extern struct cmd_table __cmd_tab_end;

struct cmd_table {
    const char name[16];
    const char usage[256];
    int (*exec)(struct cmd_table *, int, char **);
};

#define OZ_CMDT_SECTION ".cmd_tab_"
#define OZ_CMDT(_name,_usage)                                                                   \
    extern struct cmd_table cmdt_##_name __attribute__ ((section (OZ_CMDT_SECTION#_name)));     \
    struct cmd_table cmdt_##_name = {                                                           \
        .name = #_name,                                                                         \
        .usage = _usage,                                                                        \
        .exec = cmd_##_name                                                                     \
    }


