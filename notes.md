# Notes

This is a collection of notes and overall changelog.

---
## **v1.2**:
### **status**: We are halfway there
* Graphics work. Downwards collision detection and movement works. Rotation works.
* Cloning objects works
* BEWARE when using the Printable class. It has caused multiple bugs. [Further reading on using Printable](https://arduino.stackexchange.com/questions/53732/is-it-possible-to-print-a-custom-object-by-passing-it-to-serial-print). [Further reading on Serial.print bugs](https://forum.arduino.cc/index.php?topic=48577.0)

## **v1.1.1**:
### **status**: Trying to easily show graphics
* There is no way to read the GDDRAM from the SSD1306. Only SH1106 supports returning the pixels on the screen. I have screens with only SSD1306. I have to use another way. [Further reading](http://www.technoblogy.com/show?2CFT).

## **v1.1.0**:
### **status**: first correctly shown graphics
* The way I handle graphics in title.cpp is not the best. The compiler does not like it when I try to pass a static array of a library to a function of another library. Good news is that this way uses the same amount of resources.
* I am so sorry to [tobozo](https://github.com/tobozo) for deleting the artwork! I hoped I could use it, but I have changed the code too much. I have to mirror each piece both horizontally and vertically. It is much easier to make it from scratch, unfortunatelly...


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
