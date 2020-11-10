# Notes

This is a collection of notes and overall changelog.

---
## **v1.1.0**:
### **status**: proof of concept
* Managed to move the OLED management to a separate file. The Pro Mini doesn't have enough memory for the Adafruit_SSD1306 library. It needs a bare bones version.
* Currently trying to pass any 2d array to a function to draw on the screen on the fly.

## **v1.0.0**:
### **status**: compilation errors
* Put the *TinyTetris.ino* file in an appropriately named folder.
* Replaced the dpad support with buttons. I didn't have an analog stick at hand :( .
* Put the logos, title screen, etc. in a separe file.
* Noticed that when the Pro mini starts doing memory intensive stuff the buttons start bugging out. I hope that optimising the code will fix the issue.
