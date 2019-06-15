/*
 *  HID driver for Thrustmaster T150 racing wheel
 *
 *  Copyright (c) 2019 Martin Scherer
 */

/*
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 */

#include <linux/hid.h>
#include <linux/module.h>

static int tm_input_mapping(struct hid_device *hdev, struct hid_input *hi,
		struct hid_field *field, struct hid_usage *usage,
		unsigned long **bit, int *max)
{
	/* Axis Y, Z and RZ from the descriptor are not updated by the device.
	   Mapping vendor specific fields instead. */
	if (usage->hid == HID_GD_Y || usage->hid == HID_GD_Z ||
			usage->hid == HID_GD_RZ) {
		return -1;
	}
	if (usage->hid == 0xff00002a) {
		hid_map_usage_clear(hi, usage, bit, max, EV_ABS, ABS_Y);
		return 1;
	}
	if (usage->hid == 0xff00002b) {
		hid_map_usage_clear(hi, usage, bit, max, EV_ABS, ABS_Z);
		return 1;
	}

	return 0;
}

static const struct hid_device_id tm_devices[] = {
	{ HID_USB_DEVICE(0x044f, 0xb65d),
		.driver_data = 0 },
	{ }
};

MODULE_DEVICE_TABLE(hid, tm_devices);

static struct hid_driver tm_driver = {
	.name = "thrustmaster_t150",
	.id_table = tm_devices,
	.input_mapping = tm_input_mapping,
};
module_hid_driver(tm_driver);

MODULE_LICENSE("GPL");
