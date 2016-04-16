

# Purpose #

Dispatch is intended as an easy-to-use serial library that allows a simple exchange
of multi-dimensional, multi-value data.  Dispatch uses the concept of endpoints in
order to get data from the sender to the receiver.

The form of Dispatch was largely inspired by [Telemetry](https://github.com/Overdrivr/Telemetry),
which is described by the author as a publish-subscribe model.

More details may be found at [for(embed)](http://www.forembed.com).

# Project Maturity #

The project is new and has not been fully tested nor optimized.  I have integrated TravisCI into
the workflow so that any commits contributed already has the test environment set up.  Currently,
testing exists for about 10% of the functionality of the project.  I will continue to add test
cases in the coming weeks.

![travisci](https://travis-ci.org/slightlynybbled/Dispatch.svg?branch=master)

# Example Usage #

## Publishing to an Endpoint ##

    uint8_t myData[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    DIS_publish("foo:10,u8", myData);
    
All subscribers to the endpoint "foo" will be called when the above statement is executed.
    
## Subscribing to an Endpoint ##

    DIS_subscribe("foo", &mySubscriberFunction);
    
When an item is published to the endpoint "foo", then `mySubscriberFunction` is executed.
    
A more complete example may be found within the 'examples' directory.
