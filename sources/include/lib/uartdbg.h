/**
 * @file uartdbg.h
 * @brief Function API for the Debug UART driver.
 */

#pragma once

struct hurd_uartdbg {
    int baud_rate;
    int fifo_enable;
};

/**
 * @brief Initialize UARTDBG module.
 */
void *uartdbg_init(struct hurd_uartdbg *init);

/**
 * @brief Send data.
 */
void uartdbg_tx(void *h, uint32_t data);

/**
 * @brief Receive data.
 */
uint32_t uartdbg_rx(void *h);
