// SPDX-License-Identifier: BSD-2-Clause
/*
 * Qualcomm GENI serial engine UART driver
 *
 * Copyright (c) 2025, Linaro Limited
 *
 * Register values taken from TF-A UART driver written in assembly.
 */

#include <console.h>
#include <drivers/geni_uart.h>
#include <io.h>
#include <keep.h>

#define GENI_CMD_REG                0x0
#define GENI_STATUS_REG             0x40
#define GENI_STATUS_REG_CMD_ACTIVE  BIT(1)
#define GENI_TX_FIFO_REG            0x100
#define GENI_TX_TRANS_LEN_REG       0x170

#define GENI_M_CMD_TX               (0x08000000)

static vaddr_t chip_to_base(struct serial_chip *chip)
{
	struct geni_uart_data *pd =
		container_of(chip, struct geni_uart_data, chip);

	return io_pa_or_va(&pd->base, GENI_UART_REG_SIZE);
}

static void wait_tx_done(vaddr_t base) {
    while(io_read32(base + GENI_STATUS_REG) & GENI_STATUS_REG_CMD_ACTIVE)
		;
}

static void geni_uart_putc(struct serial_chip *chip, int ch) {
	vaddr_t base = chip_to_base(chip);

    wait_tx_done(base);
    io_write32(base + GENI_TX_FIFO_REG, ch);
}

static const struct serial_ops geni_uart_ops = {
	.putc = geni_uart_putc,
};
DECLARE_KEEP_PAGER(geni_uart_ops);

void geni_uart_init(struct geni_uart_data *pd, vaddr_t base)
{
	pd->base.pa = base;
	pd->chip.ops = &geni_uart_ops;
}
