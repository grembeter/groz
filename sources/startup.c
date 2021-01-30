/**
 * @file startup.c
 */

#include <lib/cmd.h>


void __oz_low_init(void);
void __oz_entry(void);

void __oz_low_init()
{
}

void __oz_entry()
{
    cmd_init();
    cmd_loop();
}
