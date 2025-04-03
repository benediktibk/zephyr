/*
 * Copyright (c) 2025 SILA Embedded Solutions GmbH
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT vnd_dummy_driver

#include <zephyr/kernel.h>
#include <zephyr/rtio/rtio.h>
#include <zephyr/logging/log.h>
#include <zephyr/sys/util.h>
#include "dummy_device.h"

LOG_MODULE_REGISTER(dummy_driver, LOG_LEVEL_DBG);

struct dummy_driver_config {};

struct dummy_driver_data {};

static int dummy_driver_init(const struct device *dev)
{
        LOG_DBG("initializing dummy driver");
	return 0;
}

static void dummy_driver_iodev_submit(const struct device *dev, struct rtio_iodev_sqe *iodev_sqe)
{
	if (iodev_sqe->sqe.iodev_flags & RTIO_IODEV_DUMMY_DEVICE_START) {
		LOG_DBG("executing start procedure");
	}

	LOG_HEXDUMP_DBG(iodev_sqe->sqe.tx.buf, iodev_sqe->sqe.tx.buf_len, "writing data");

	if (iodev_sqe->sqe.iodev_flags & RTIO_IODEV_DUMMY_DEVICE_STOP) {
		LOG_DBG("executing stop procedure");
	}
}

static DEVICE_API(dummy_device, dummy_driver_api) = {
	.iodev_submit = dummy_driver_iodev_submit,
};

#define DUMMY_DRIVER_INIT(n)                                                                       \
                                                                                                   \
	static const struct dummy_driver_config dummy_driver_config_##n = { };                     \
                                                                                                   \
	static struct dummy_driver_data dummy_driver_data_##n = { };                               \
                                                                                                   \
	DEVICE_DT_INST_DEFINE(n, dummy_driver_init, NULL, &dummy_driver_data_##n,                  \
			      &dummy_driver_config_##n, POST_KERNEL,                               \
			      CONFIG_KERNEL_INIT_PRIORITY_DEVICE, NULL);

DT_INST_FOREACH_STATUS_OKAY(DUMMY_DRIVER_INIT)