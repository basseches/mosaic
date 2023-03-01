# *mosaic*, generative art for ESP32

<img src="installation.jpg" width=200 alt="Our installation">

<img src="example.gif" width=200>

A program that displays sentences generated from fragments of text on an ESP32.

## Getting started with the Arduino IDE

This program is written in Arduino so we'll work with the
[Arduino](https://www.arduino.cc) IDE. Download the Arduino IDE
[here](https://www.arduino.cc/en/software), then follow these steps to run code
on an ESP32:

1. In `Preferences`, paste the following link into `Additional boards manager
URLs`:

```
https://dl.espressif.com/dl/package_esp32_index.json
```

2. In `Tools > Boards > Boards Manager`, search for "esp32". There should be
one result, "esp32 by Espressif Systems"—install it.

3. Select the ESP32 board by clicking `Tools > Boards > esp32 > TTGO T1`.

4. In `Tools > Manage Libraries`, search for "TFT_eSPI Bodmer". Install the one
with the title "TFT_eSPI".

5. In `Preferences`, copy the filepath specified under "Sketchbook location".
`cd` into that directory in your terminal/terminal emulator. There should be a
`libraries` directory in there. `cd libraries/TFT_eSPI`, then open
`User_Setup_Select.h` with a text editor. In this file, there should be lines
like this:

```c
#include <User_Setup.h>           // Default setup is root library folder

...

//#include <User_Setups/Setup25_TTGO_T_Display.h>    // Setup file for ESP32 and TTGO T-Display ST7789V SPI bus TFT
```

Uncomment the second line, and comment the first:

```c
//#include <User_Setup.h>           // Default setup is root library folder

...

#include <User_Setups/Setup25_TTGO_T_Display.h>    // Setup file for ESP32 and TTGO T-Display ST7789V SPI bus TFT
```

Now, you should be ready to run code on your ESP32!


## Running the code

Connect your ESP32 via a USB-C cable to one of the ports on your computer. Open
`mosaic.ino` (inside `mosaic/`) with the Arduino IDE, and click the arrow
button in the top left corner of the IDE to upload the code to the ESP32.

> **Note**
> I had some difficulty getting code to export from my Mac. If your compilation is
> failing with an error message that ends with `A fatal error occurred: Failed
> to write to target RAM`, try following the steps in
> [this issue comment.](https://github.com/Xinyuan-LilyGO/LilyGo-T-Call-SIM800/issues/139#issuecomment-904390716)
