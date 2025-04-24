# Contributing

## Adding a new controller

### Collect info about your controller

#### Finding vendor and product ID

> [!NOTE]
> This guide assumes you are running Linux.

First, find out the vendor and product IDs for your controller: connect it to your Linux machine, switch it on (if there's a button for that) and run the following command:

    $ lsusb
    Bus 001 Device 001: ID 1d6b:0002 Linux Foundation 2.0 root hub
    Bus 001 Device 005: ID 26ce:01a2 ASRock LED Controller
    ...
    Bus 001 Device 015: ID 2dc8:3106 8BitDo 8BitDo Ultimate Controller
    Bus 002 Device 001: ID 1d6b:0003 Linux Foundation 3.0 root hub

The two hexadecimal numbers after the "ID" are the vendor and product IDs, respectively.

You can see more detailed information on your device with the command
(substitute xxxx:yyyy with the vendor:product IDs you got from the previous
command):

    $ lsusb -vd xxxx:yyyy

If the `bInterfaceClass` field says "3 Human Interface Device", then your
controller implements the HID specification, and you can get more information
out of it.


#### Checking the HID data

If your controller implements the USB HID protocol, you'll find a file named
`report_descriptor` deep under `/sys/devices`; actually, there'll be probably
several of these files, if you have HID-compatible mouse and keyboard, so to
find out which one it is, you could run the command:

    # as usual, xxxx:yyyy is vendor:product ID
    find /sys/ -name report_descriptor 2> /dev/null | grep xxxx:yyyy

With a program like `hid-decode` from
[hid-tools](https://gitlab.freedesktop.org/bentiss/hid-tools) you'll then be
able to see the HID data in plain text. However, this step is not really
necessary, because the stream data should be relatively easy to understand even
without this.

What is more interesting is seeing the data which the device reports when it's
being used. To do so, run the command

    # Remember to change xxxx:yyyy into the actual values
    sudo usbhid-dump -d xxxx:yyyy -e stream

This will output an infinite stream of text of this form:

    001:016:000:STREAM             1745521125.595673
     80 80 84 80 80 0F 00 40

    001:016:000:STREAM             1745521125.603672
     80 80 84 80 80 0F 00 40

You can ignore the first line, what you care about is the second line showing a
packet of bytes in hexadecimal format. Pressing the buttons on the gamepad and
moving the joysticks will cause the byte values to change, and soon you'll
figure which action is described by the various bits/bytes.



#### Checking the raw USB data

**TODO**
