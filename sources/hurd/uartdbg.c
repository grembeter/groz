/**
 * @file uartdbg.c
 */

#include <groz.h>
#include <lib/uartdbg.h>
#include <mmr/uartdbg.h>

struct uartdbg_ctx {
    enum MODULE_INIT_STATE initialized;
    volatile struct uartdbg_mmr *mmr;
};

static struct uartdbg_ctx uartdbg_ctx;

/* ********** ********** **********
 * local functions
 */

static inline int is_initialized(struct uartdbg_ctx *ctx)
{
    return ctx->initialized == INITIALIZED;
}

/* ********** ********** **********
 * global functions, see <lib/uartdbg.h>
 */

void uartdbg_tx(void *handle, uint32_t data)
{
    struct uartdbg_ctx *ctx = (struct uartdbg_ctx *)handle;
    volatile struct uartdbg_mmr *mmr = ctx->mmr;

    while (mmr->fr & (0x1 << 5)) {
        /* TX FIFO is full */
    }

    mmr->dr = data & 0xff;
}

uint32_t uartdbg_rx(void *handle)
{
    struct uartdbg_ctx *ctx = (struct uartdbg_ctx *)handle;
    volatile struct uartdbg_mmr *mmr = ctx->mmr;

    while (mmr->fr & (0x1 << 4)) {
        /* RX FIFO is empty */
    }

    return mmr->dr & 0xff;
}

/* ********** ********** **********
 * init function
 */
void *uartdbg_init(struct hurd_uartdbg *init)
{
    struct uartdbg_ctx *ctx = &uartdbg_ctx;

    if (is_initialized(ctx)) {
        return ctx;
    }

    volatile struct uartdbg_mmr *mmr = (volatile struct uartdbg_mmr *)MMR_UARTDBG_BASE;

    mmr->cr |= (0x1 << 9) | (0x1 << 8);
    mmr->cr |= 0x1;

    /* save context */
    ctx->mmr = mmr;
    ctx->initialized = INITIALIZED;

    return ctx;
}
