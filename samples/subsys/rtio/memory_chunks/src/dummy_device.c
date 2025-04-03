/*
 * Copyright (c) 2025 SILA Embedded Solutions GmbH
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/rtio/rtio.h>
#include "dummy_device.h"

const struct rtio_iodev_api dummy_device_iodev_api = {
        .submit = dummy_device_iodev_submit,
};