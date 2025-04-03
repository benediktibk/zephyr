/*
 * Copyright (c) 2025 SILA Embedded Solutions GmbH
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef _DUMMY_DEVICE_H_
#define _DUMMY_DEVICE_H_

#include <stddef.h>
#include <stdint.h>
#include <zephyr/device.h>
#include <zephyr/rtio/rtio.h>

/*
 * These defines would for normal devices reside in include/zephyr/rtio/rtio.h,
 * but for the purpose of this sample I do not want to pollute this header.
 */
#define RTIO_IODEV_DUMMY_DEVICE_START BIT(1)
#define RTIO_IODEV_DUMMY_DEVICE_STOP BIT(2)

typedef void (*dummy_device_api_iodev_submit)(const struct device *dev,
				     struct rtio_iodev_sqe *iodev_sqe);

__subsystem struct dummy_device_driver_api {
        dummy_device_api_iodev_submit iodev_submit;
};

static inline void dummy_device_iodev_submit(struct rtio_iodev_sqe *iodev_sqe)
{
	const struct device *dev = (const struct device *)iodev_sqe->sqe.iodev->data;
	const struct dummy_device_driver_api *api = (const struct dummy_device_driver_api *)dev->api;

        if (api->iodev_submit == NULL) {
		rtio_iodev_sqe_err(iodev_sqe, -ENOSYS);
		return;
	}
	api->iodev_submit(dev, iodev_sqe);
}

extern const struct rtio_iodev_api dummy_device_iodev_api;

#define DUMMY_DEVICE_IODEV_DEFINE(name, dev)                                     \
	RTIO_IODEV_DEFINE(name, &dummy_device_iodev_api, (void *)DEVICE_DT_GET(dev))

#endif /* _DUMMY_DEVICE_H_ */