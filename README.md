# Lightshow
WiFi Lightshow service implemented on Arduino Nano 33 IoT

## Hardware
It's all sitting on a breadboard and powering it from my laptop's USB for development purposes. I don't anticipate getting any fancier than transferring this to a [perfboard](https://www.amazon.com/gp/product/B07FFDFLZ3/ref=ppx_yo_dt_b_asin_title_o05_s00) for the finished product.

### [Arduino Nano 33 IoT](https://store.arduino.cc/usa/nano-33-iot).
- 32-bit SAMD21 Cortex
- 3.3V
- 256K Flash
- 32K RAM
- 18x45mm

![Pinouts](https://content.arduino.cc/assets/Pinout-NANO33IoT_latest.png)

### [Adafruit NeoPixel Ring](https://www.adafruit.com/product/1463)
- 16 individually addressable RGB LED's
- 5V
- 16mm outer diameter

### [3.3V-5V level converter](https://www.amazon.com/gp/product/B07H2C6SJJ)
- 4 channels (but I'm only using one)
- bi-directional
- I couldn't find any throughput specs for this little board, but I took a chance and it works fine for this project.
- Note that is is for signal leveling only. I'm not _driving_ anything with this.

![Board Layout and Pinouts](https://m.media-amazon.com/images/S/aplus-seller-content-images-us-east-1/ATVPDKIKX0DER/A278BT9THV444Y/e02429fa-77c9-4ff6-b6fa-d3096f763803._CR0,0,300,300_PT0_SX300__.jpg)

## REST Interface
I've found a decent article that's about my speed: [Understanding and Using REST APIs](https://www.smashingmagazine.com/2018/01/understanding-using-rest-api/)

That's about as far as I've gotten so far, but stay tuned.
