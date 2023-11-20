# bindkeys
example : ./bindkeys64 /dev/hidraw8 test.conf

how it works under FreeBSD:
you need to load the hidraw module
## kldload hidraw

spot the right hidraw:
## dmesg|grep hidraw
hidraw0: <AsusTek Computer Inc. AURA LED Controller Raw HID Device> on hidbus0
hidraw1: <Logitech USB Receiver Raw HID Device> on hidbus1
hidraw2: <Logitech USB Receiver Raw HID Device> on hidbus2
hidraw3: <Logitech USB Receiver Raw HID Device> on hidbus3
hidraw4: <Logitech USB Receiver Raw HID Device> on hidbus4
hidraw5: <Logitech USB Receiver Raw HID Device> on hidbus5
hidraw6: <Logitech USB Receiver Raw HID Device> on hidbus6
hidraw7: <Logitech Logitech USB Keyboard Raw HID Device> on hidbus7
hidraw8: <Logitech Logitech USB Keyboard Raw HID Device> on hidbus8
hidraw9: <SWITCH CO.,LTD. Pro Controller Raw HID Device> on hidbus9

Change rights to hidraw:
## chown myuser:mysuser /dev/hidraw?

install xdotool for key simulation
## pkg install xdotool

Prepare a bin directory for the user:
$ mkdir ~/bin
$ export PATH=$PATH:~/bin
$ cp bindkeys64 ~/bin

Locate the button codes:
$ touch test.conf
$ bindkeys64 /dev/hidraw? test.conf
bindkeys v0.1
Key : 01 05 00 00 
Key : 01 00 00 00 

For example on this keyboard the code key XF86AudioPlay is 01 05 00 00

Example files for the XF86AudioPlay button recognized under xev:
$ cat test.conf
01 05 00 00 XF86AudioPlay.sh

Create a script to simulate the touch:
$ cat XF86AudioPlay.sh
##!/bin/sh
xdotool key XF86AudioPlay

$ mv XF86AudioPlay.sh ~/bin
$ chmod u+x ~/bin/XF86AudioPlay.sh

Now restart bindkeys64:
$ bindkeys64 /dev/hidraw? test.conf
bindkeys v0.1
Key : 01 05 00 00 Command -> XF86AudioPlay.sh
Key : 01 00 00 00 

ok the script is launched for the XF86AudioPlay button
Now test under xev or gimp or audacious...
