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
