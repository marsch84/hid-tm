# hid-tm
Linux HID driver for Thrustmaster T150 racing wheel

This driver maps the brake and accelerator pedals of the racing wheel to the
section of the HID descriptor that is actually updated by the device. It looks
like the Y, Z and RZ axes that are defined in the descriptor are not used by
the device. Instead the driver maps the Y and Z axis to a vendor specific field
that reflects the actual status of the pedals.

Installation:

    make
    insmod hid-tm.ko
