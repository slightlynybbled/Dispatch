# Purpose #

Dispatch is intended as an easy-to-use serial library that allows a simple exchange
of multi-dimensional, multi-value data.  Dispatch uses the concept of endpoints in
order to get data from the sender to the receiver.

The form of Dispatch was largely inspired by [Telemetry](https://github.com/Overdrivr/Telemetry),
which is described by the author as a publish-subscribe model.

More details may be found at [for(embed)](http://www.forembed.com).

# Project Maturity #

The project now has 80% unit test coverage and solid integration testing.  In some cases,
unit testing was skipped for a function that integrated the function, such as with the
fletcher16 checksum.

![travisci](https://travis-ci.org/slightlynybbled/Dispatch.svg?branch=master)

# Example Usage #

## Setting Up ##

In order to set up the variables and functions internal to Dispatch, the following four
functions MUST be called one time:

    DIS_init();
    
    DIS_assignChannelReadable(&readable);
    DIS_assignChannelWriteable(&writeable);
    DIS_assignChannelRead(&read8);
    DIS_assignChannelWrite(&write8);
    
## Running ##

In order to properly execute received message, the `DIS_process()` must be called continually.
`DIS_process()` may be called at reduced intervals, but the frequency of calling this function
will correspondingly reduce response times to subscribing functions.  In most microcontroller
platforms, `DIS_process()` will be placed inside the infinite `while(1)` loop.  If an RTOS is
involved, it should be assigned as a task.

If the platform is only sending Dispatch messages and not receiving them, then `DIS_process()`
may be omitted.

## Publishing to an Endpoint ##

    uint8_t myData0[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    uint16_t myData1[] = {10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
    DIS_publish("foo:10,u8,u16", myData);
    
All subscribers to the endpoint "foo" will be called when the above statement is executed.
    
## Subscribing to an Endpoint ##

    DIS_subscribe("foo", &mySubscriberFunction);
    
When an item is published to the endpoint "foo", then `mySubscriberFunction` is executed.

## Getting the Data within the Subscriber ##

    uint8_t myData0Received[10];
    uint16_t myData1Received[10];
    
    /* retrieve element 0, or the first element, into 'myData0Received'
        and save the array length into 'length' */
    uint8_t length = DIS_getElements(0, myDataReceived);
    
    /* retrieve element 1 into 'myData1Received' */
    DIS_getElements(1, myData1Received);
    
A more complete example may be found within the 'examples' directory.

# Contributions #

To make a contribution, simply fork the repository.  Create a branch that is appropriately
descriptive of your change and perform your development.  When complete, create a pull
request using that branch - DO NOT merge into master!  Once the proper test coverage is added
and passing on TravisCI, then we can merge into the master branch.

In some cases in which the documentation or examples are contributed, this process will be
fast-tracked.
