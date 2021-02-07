/**
 * @file stream.h
 */

#pragma once

/**
 * @brief Initialize default stream.
 */
int stream_init(void);

/**
 * @brief Output message to the debug stream.
 */
void dbg(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));

/**
 * @brief Put one char to the debug stream.
 */
void dbg_putchar(char ch);

/**
 * @brief Get char from the debug stream.
 */
uint32_t dbg_getchar(void);
