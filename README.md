# Digital protractor

Device made to calculate angle between it's bcb board and an obstacle (e.g. wall). The device was made using arduino nano

## PCB design

![PCB design](/Schemat.png)

Note: in schema it was used display with common anode, and code is written for common cathode displays. If you have common anode display, change all HIGH values to LOW and LOW to HIGH in functions designed for showing digits (from zero() to nine() and from digit1() to digit4())

## How to use it

1. Turn arduino on by connecting it to the USB port.
2. Display shows current angle.
3. By pressing the button change from showing angle to distance between first sensor and an obstacle. Press again to see distance between second sensor and an obstacle. Press the botton once again to return to the angle.
