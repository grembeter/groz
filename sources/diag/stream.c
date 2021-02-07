/**
 * @file stream.c
 */

#include <groz.h>
#include <lib/stream.h>
#include <lib/uartdbg.h>

struct stream_ctx {
    enum MODULE_INIT_STATE initialized;
    struct uartdbg_ctx *uartdbg;
};

static struct stream_ctx stream_ctx;

/* ********** ********** **********
 * local functions
 */

static inline int is_initialized(struct stream_ctx *ctx)
{
    return ctx->initialized == INITIALIZED;
}

static inline void _put_string(const char *str)
{
    if (str == NULL) {
        str = "(null)";
    }

    while (*str != '\0') {
        dbg_putchar(*str++);
    }
}

static inline void _put_integer(int integer)
{
    int input;
    char out[32];
    int i = 32;

    out[--i] = '\0';

    if (integer < 0) {
        input = -integer;
    } else {
        input = integer;
    }

    do {
        out[--i] = (char)('0' + input % 10);
        input /= 10;
    } while (input > 0);

    if (integer < 0) {
        out[--i] = '-';
    }

    _put_string(&out[i]);
}

static inline char _hexchar(unsigned char halfbyte)
{
    char off = '0';

    if (halfbyte > 9) {
        off = 'a' - 10;
    }

    return (char)(halfbyte + off);
}

static inline void _put_hexadecimal(unsigned int hex)
{
    char out[32];
    int i = 32;

    out[--i] = '\0';

    do {
        out[--i] = _hexchar(hex & 0x0f);
        hex >>= 4;
    } while (hex > 0);

    _put_string(&out[i]);
}

/* ********** ********** **********
 * global functions, see <lib/stream.h>
 */

void dbg_putchar(char ch)
{
    uartdbg_tx(stream_ctx.uartdbg, (ch));
}

uint32_t dbg_getchar()
{
    return uartdbg_rx(stream_ctx.uartdbg);
}

void dbg(const char *fmt, ...)
{
    if (fmt == NULL) {
        return;
    }

    const uint32_t *varg = (uint32_t *)&fmt + 1;

    while (*fmt != '\0') {
        if (*fmt == '%') {
            char spec = *(fmt + 1);

            if (spec == '\0') {
                dbg_putchar(*fmt);
                break;
            }

            if (spec == '%') {
                dbg_putchar('%');
            } else if (spec == 'c') {
                dbg_putchar((unsigned char)(*varg++));
            } else if (spec == 's') {
                _put_string((const char *)(*varg++));
            } else if (spec == 'd') {
                _put_integer((int)(*varg++));
            } else if (spec == 'x') {
                _put_hexadecimal((unsigned int)(*varg++));
            } else {
                dbg_putchar(*fmt);
                dbg_putchar(spec);
            }

            ++fmt;
        } else {
            dbg_putchar(*fmt);
        }

        ++fmt;
    }
}

/* ********** ********** **********
 * init function
 */
int stream_init()
{
    if (is_initialized(&stream_ctx)) {
        return 0;
    }

    stream_ctx.uartdbg = uartdbg_init(NULL);

    if (stream_ctx.uartdbg != NULL) {
        stream_ctx.initialized = INITIALIZED;
    }

    return is_initialized(&stream_ctx);
}
