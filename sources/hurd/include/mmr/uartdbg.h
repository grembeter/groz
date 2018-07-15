/**
 * @file uartdbg.h
 */

#pragma once

#include <groz.h>

#define MMR_UARTDBG_BASE (0x80074000)

struct uartdbg_mmr {
    uint32_t dr;
    uint32_t ecr;
    uint32_t reserved1[4];
    uint32_t fr;
    uint32_t reserved2[1];
    uint32_t ilpr;
    uint32_t ibrd;
    uint32_t fbrd;
    uint32_t h;
    uint32_t cr;
    uint32_t iflc;
    uint32_t imsc;
    uint32_t ris;
    uint32_t mis;
    uint32_t icr;
    uint32_t dmacr;
};
