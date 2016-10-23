LED Firefly with Raspberry Pi
========

## Description
LED brightness control using PWM control on Raspberry Pi.

## Demo
* [YouTube](https://www.youtube.com/watch?v=u058fWJ1VMg)

## Requirement
### Hardware
* [Raspberry Pi](https://www.raspberrypi.org/products/raspberry-pi-3-model-b/)

### Software
* [Raspbian](https://www.raspberrypi.org/downloads/raspbian/)
* [WiringPi](http://wiringpi.com/)

## Circuit
Connect the LED between GPIO 18 and GND via the 330 ohm resister.

* [Bread Board View](https://goo.gl/photos/eBjseDQ8Qtk6opKb6)

## Usage
* Must be root to run `RasPi_LED_Firefly`.
    ```console
        $ sudo ./bin/RasPi_LED_Firefly
    ```

* See the help list to get optional usage.
    ```console
        $ ./bin/RasPi_LED_Firefly --help
    ```

## Installation
1. Download and Install WiringPi
    ```console
        $ git clone git://git.drogon.net/wiringPi
        $ cd wiringPi
        $ ./build
        $ gpio -v
    ```

2. Download and Compile RasPi_LED_Firefly
    ```console
        $ git clone https://github.com/KeitetsuWorks/RasPi_LED_Firefly.git
        $ cd RasPi_LED_Firefly
        $ make
        $ ./bin/RasPi_LED_Firefly --version
    ```

After that you can find `RasPi_LED_Firefly` under the `./bin/` directory.

## License
* MIT

