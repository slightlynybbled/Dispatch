# Examples #

Each `c` file within this directory contains the code to execute on the Microchip XC16
platform.  Modifications may be required for different chip variants.  The `main.c`
code is the primary example code.

## main.c ##

This is an example c file that works in conjunction with [SerialDispatch](https://github.com/slightlynybbled/SerialDispatch).
This file will publish one time at initialization to the topic `bar`.  It will also
subscribe to the topic `foo`.  Every time that the topic `foo` is received, the code
will also publish a count to topic `i`.

This sounds complicated, but the primary application is that the `main.c` will simply
keep count of the number of `foo` received messages and publishes that count on each
receipt.

## test_uart.c ##

Used to hardware test the UART driver code.

## test_frame.c ##

Used to test the framing library code.

## test_dispatch.c ##

Used to test the dispatch library code.