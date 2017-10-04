# Examples

Each `c` file within this directory contains the code to execute on the Microchip XC16
platform.  Modifications may be required for different chip variants.  The `main.c`
code is the primary example code.

# Project Structure

## Files

For the example, the expected MPLAB X project should look like:

```
header files
 -> cbuffer.h - circular buffer header (driver) - located in /src/drivers/pic24dspic33
 -> uart.h - uart driver header- located in /src/drivers/pic24dspic33
 -> frame.h - framing library header - located in /src
 -> dispatch.h - dispatch library header - located in /src
 -> dispatch_config.h - user-specific configuration for dispatch - located in /examples/xc16
 -> config.h - microcontroller configuration - located in /examples/xc16

source files
 -> cbuffer.c - circular buffer source (driver) - located in /src/drivers/pic24dspic33
 -> uart.c - uart driver source - located in /src/drivers/pic24dspic33
 -> frame.c - framing library source - located in /src
 -> dispatch.c - dispatch library source - located in /src
 -> main.c - user code - located in /examples/xc16
 
```

The `uart.c` and `uart.h` files comprise the software/hardware interface for the UART.  This is device-specific
and will likely need to be re-written for your platform.  In this iteration, it is written with a circular buffer
interface, requiring `cbuffer.h` and `cbuffer.c` as dependencies.

The `cbuffer.h` and `cbuffer.c` files comprise a software-only buffer for the UART.  They were written as part
of the PIC24 UART driver and are dependencies for that driver alone.  If the user writes their own UART interface
that has an integrated buffer, then these files will not be necessary.

The `frame.h` and `frame.c` is the glue between the `dispatch` layer and the `uart` layer.  It applies proper frame
delimiters along with escaping special characters appropriately.  The `frame` layer should be stable and require
no further work from the user.

The `dispatch.h` and `dispatch.c` files implement all of the logic required to operate the `dispatch` library.  All
subscribing and callbacks occur at this layer.  This file should be stable and require no intervention from the user.

The `main.c` library represents the user's portion of the code.  In this case, it simply provides an example of
several possible publish and subscribe methods.  This particular file is structured to listen to several different topics
types and then to respond to each topic with the same topic, but with slightly modified data.

The `config.h` is simply a microcontroller-specific configuration file.  This may or may not be required in your platform
depending on your platform and project configuration.

## Dependencies

The dependency graph for this file is as follows

```
main.c
  -> config.h
  -> dispatch
    -> frame
      -> uart
        -> cbuffer
```

# Functionality

This example project subscribes to the following topics

 * `received`
 * `string`
 * `i`
 * `array`
 * `arrays8`
 * `arrays16`
 * `arrays32`

## Topic: `received`

When the device receives a value on the `received` topic, it responds on the same topic with the number of messages that have been
received on all of the other topics.  This number should continually increment until it rolls over.

## Topic: `string`

When the device receives a value on the `string` topic, it responds on the same topic with the string `uC msg`.

## Topic: `i`

When the device receives a value on the `i` topic, it reads the value as a `uint16_t`, increments it, then responds
on the same topic with the incremented value.

## Topic `array`

When the device receives a value on the `array` topic, it reads the values as 4 `int16_t` values, increments each one, then responds
on the same topic with the incremented values.  For instance, if `{-2, -1, 0, 1}` were received, then the microcontroller
would return `{-1, 0, 1, 2}`.

## Topic `arrays8`

When the device receives a value on the `array` topic, it reads the values as 4 `int8_t` values followed by
4 `uint8_t` values.  The device increments each value, then responds on the same topic with the incremented values.
For instance, if `{{-2, -1, 0, 1}, {4, 5, 6, 7}}` were received, then the microcontroller would return 
`{{-1, 0, 1, 2}, {5, 6, 7, 8}}`.

## Topic `arraysX`

The `arrays16` and `arrays32` subscribers do the same thing as the `arrays8` subscriber, they simply operate on
16 and 32 bit values, respectively.
