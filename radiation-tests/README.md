# Radiation Tests
## Connecting to the Arietta G25
Currently using the [Arch Arm](https://archlinuxarm.org/platforms/armv5/arietta-g25) distribution for the Arietta.
The SD card has been setup following the guide, and in addition gcc has been installed to be able to compile.
To SSH into the Arietta and allow your computer to work as a gateway, follow the instructions at the bottom of the the installation page on the previous link, or use `setupNetworkConnection.sh` included in this folder.

The script `setupNetworkConnection.sh` must be run as root. Depending on your specific permissions, you may have to `su` to run as opposed to using `sudo`. This is for editing `/proc/sys/net/ipv4/ip_forward`. Supply the network name of the arietta as the first argument, and the name of your connection to the outside as your second argument.

For example, `./setupNetworkConnection.sh enp0s29u1u2 wlp4s0`. These values can be found by running `ifconfig` and checking the device names listed. You can also determine the name for a recently inserted usb device by watching `dmesg`.

## Setting up for run on startup

1. Mount the SD card on your machine.
2. On the card, go to `usr/lib/systemd/system`.
3. Copy in `radsrunner.service` included here.
4. On the card, go to `etc/systemd/system/multi-user.target.wants`.
5. Create a symbolic link to the radsrunner service, `ln -s ../../../../usr/lib/systemd/system/radsrunner.service`.
6. On the card, go to `home/alarm`, and create a folder named `RadiationTestsRunner`.
7. Copy in the contents of the `ARMBinary` included here.
8. Start server on host machine.
9. Connect arietta and verify packets received on server.

## SSH config
You can also try copying in the contents of the `ssh` folder included here to `etc/ssh/` on the card. Overwrite `sshd_config` and`ssh_config`, and add in the extra files included here. Don't overwrite `moduli`.
