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

void __oz_entry()
{
    stream_init();

    dbg("\n"
        "   __ _ _ __ ___ ____\n"
        "  / _` | '__/ _ \\_  /\n"
        " | (_| | | | (_) / / \n"
        "  \\__, |_|  \\___/___|\n"
        "   __/ |             \n"
        "  |___/      v0.1    \n"
        "\n");

    const char prompt[] = " oz :: ";

    dbg(prompt);
}
